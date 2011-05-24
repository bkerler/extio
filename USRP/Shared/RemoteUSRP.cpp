#include "StdAfx.h"
#include "USRP.h"

#include "BorIP.h"

RemoteUSRP::RemoteUSRP(CRuntimeClass* pSocket /*= NULL*/)
	: m_pClient(NULL)
	, m_bPendingResponse(false)
	, m_bConnected(false)
	, m_hThread(NULL)
	, m_dwThreadID(0)
	, m_hDataEvent(NULL)
	, m_hQuitEvent(NULL)
	, m_hPacketEvent(NULL)
	, m_hStopEvent(NULL)
	, m_hDataSocket(INVALID_SOCKET)
	, m_pNetworkBuffer(NULL)
	, m_nNetworkBufferSize(256)
	, m_nNetworkBufferStart(0)
	, m_nNetworkBufferItems(0)
	, m_nItemSize(0)
	, m_nSocketBufferSize(1024 * 1024/* * 16*/)
	, m_nPacketSize(0)
	, m_usCounter(0)
	, m_nNetworkOverrun(0)
	, m_nBufferOverrun(0)
	, m_nLastSkip(0)
	, m_pSocketClass(pSocket)
{
	ZERO_MEMORY(m_wsaOverlapped);
}

RemoteUSRP::~RemoteUSRP()
{
	Destroy();

	if (m_hDataEvent)
		CloseHandle(m_hDataEvent);

	if (m_hQuitEvent)
		CloseHandle(m_hQuitEvent);

	if (m_hPacketEvent)
		CloseHandle(m_hPacketEvent);

	if (m_hStopEvent)
		CloseHandle(m_hStopEvent);

	SAFE_DELETE_ARRAY(m_pNetworkBuffer);
}

void RemoteUSRP::ResetStats()
{
	__super::ResetStats();
}

void RemoteUSRP::Reset()
{
	ResetEvent(m_hPacketEvent);
	ResetEvent(m_hStopEvent);

	{
		CSingleLock lock(&m_cs, TRUE);

		m_nNetworkBufferStart = m_nNetworkBufferItems = 0;
		m_usCounter = 0;
		m_nNetworkOverrun = m_nBufferOverrun = m_nLastSkip = 0;
	}
}

void RemoteUSRP::Destroy()
{
	Close();

	SAFE_DELETE(m_pClient);
}

void RemoteUSRP::Close()
{
	Stop();

	if (m_pClient)
		m_pClient->Close();

	m_bConnected = false;

	m_strExpectedResponse.Empty();

	if (m_bPendingResponse)
	{
		m_bPendingResponse = false;
		PostMessage(NULL, WM_USER, 0, 0);
	}

	if (m_hThread)
	{
		SetEvent(m_hQuitEvent);
		WaitForSingleObject(m_hThread, INFINITE);

		m_hThread = NULL;
		m_dwThreadID = 0;
	}

	if (m_hDataSocket != INVALID_SOCKET)
	{
		closesocket(m_hDataSocket);
		m_hDataSocket = INVALID_SOCKET;
	}
}

bool RemoteUSRP::PumpMessageLoop(DWORD dwTimeout /*= 0*/, UINT nReturnMsg /*= WM_QUIT*/, HWND hWnd /*= NULL*/, UINT nMsgFilterMin /*= 0*/, UINT nMsgFilterMax /*= 0*/)
{
	CWinApp* pApp = AfxGetApp();

	MSG msg;
	DWORD dwStart = GetTickCount();
teh_pump_message_loop:
	while (PeekMessage(&msg, hWnd, nMsgFilterMin, nMsgFilterMax, PM_REMOVE))
	{
		if (msg.message == nReturnMsg)
			return false;

		if (pApp->PreTranslateMessage(&msg))
			continue;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if ((dwTimeout != 0) &&
			((dwTimeout == INFINITE) ||
			((GetTickCount() - dwStart) < dwTimeout)))
	{
		WaitMessage();

		if (m_bPendingResponse == false)
			return true;

		goto teh_pump_message_loop;
	}

	return true;
}

bool RemoteUSRP::SendAndWaitForResponse(const CString& str, LPCTSTR strData /*= NULL*/)
{
	if (m_pClient == NULL)
		return false;

	CString strBuf(str);
	if (IS_EMPTY(strData) == false)
		strBuf += CString(_T(" ")) + strData;

	if (m_pClient->_Send(strBuf) == false)
		return false;

	return WaitForResponse(str);
}

bool RemoteUSRP::SendAndWaitForOK(const CString& strCommand, LPCTSTR strData /*= NULL*/)
{
	if (SendAndWaitForResponse(strCommand, strData) == false)
		return false;

	CString str(m_strResponseData);
	int iIndex = str.Find(_T(' '));
	if (iIndex > -1)
		str = str.Left(iIndex);

	str = str.MakeUpper();

	return (str == _T("OK"));
}

bool RemoteUSRP::WaitForResponse(LPCTSTR strCommand /*= NULL*/, bool bMustBeSame /*= true*/, bool bAbortIfWaiting /*= true*/)
{
	if ((bAbortIfWaiting) && (m_bPendingResponse))
	{
		AfxTrace(_T("Aborting wait for command \"%s\" as already waiting on \"%s\""), strCommand, m_strExpectedResponse);
		return false;
	}
retry_response_wait:
	m_bPendingResponse = true;
	m_strExpectedResponse = strCommand;
	m_strResponse.Empty();
	m_strResponseData.Empty();

	if (PumpMessageLoop(INFINITE, WM_QUIT, NULL, WM_SOCKET_NOTIFY, WM_SOCKET_DEAD) == false)	// GUI will remain un-responsive while waiting
		return false;

	if (m_strExpectedResponse.IsEmpty())	// Happens when connection is closed
		return false;

	bool bSame = (m_strResponse == m_strExpectedResponse);

	if ((bMustBeSame) && (bSame == false))
		goto retry_response_wait;

	return bSame;
}

static DWORD WINAPI _ReceiveThread(LPVOID lpThreadParameter)
{
	return ((RemoteUSRP*)lpThreadParameter)->ReceiveThread();
}

bool RemoteUSRP::Connect(LPCTSTR strAddress, LPCTSTR strHint /*= NULL*/)
{
	if (IS_EMPTY(strAddress))
		return false;

	if (m_hDataEvent == NULL)
	{
		if ((m_hDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hDataEvent);

	if (m_hQuitEvent == NULL)
	{
		if ((m_hQuitEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hQuitEvent);

	if (m_hPacketEvent == NULL)
	{
		if ((m_hPacketEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hPacketEvent);

	if (m_hStopEvent == NULL)
	{
		if ((m_hStopEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hStopEvent);

	Destroy();

	if (m_pSocketClass)
	{
		m_pClient = (CsocketClient*)m_pSocketClass->CreateObject();
		m_pClient->_SetCallback(this);
	}
	else
		m_pClient = new CsocketClient(this);

	if (m_pClient->Create() == FALSE)
	{
		goto connect_failure;
	}

	m_hDataSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_hDataSocket == INVALID_SOCKET)
	{
		goto connect_failure;
	}

	SOCKADDR_IN addr;
	ZERO_MEMORY(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(BOR_PORT);
	int iResult = bind(m_hDataSocket, (sockaddr*)&addr, sizeof(addr));
	if (iResult == SOCKET_ERROR)
	{
		goto connect_failure;
	}

	const int iReceiveBufferSize = m_nSocketBufferSize;
	int iOptLen = sizeof(int);
	if (setsockopt(m_hDataSocket, SOL_SOCKET, SO_RCVBUF, (const char*)&iReceiveBufferSize, iOptLen) != 0)
	{
		AfxTrace(_T("Failed to set socket receive buffer size\n"));
	}

	if (getsockopt(m_hDataSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iReceiveBufferSize, &iOptLen) == 0)
	{
		AfxTrace(_T("Socket receive buffer size: %i\n"), iReceiveBufferSize);
	}
	else
	{
		AfxTrace(_T("Failed to get socket receive buffer size\n"));
	}

	ZERO_MEMORY(m_wsaOverlapped);
	m_wsaOverlapped.hEvent = m_hDataEvent;

	m_hThread = CreateThread(NULL, 0, _ReceiveThread, this, 0, &m_dwThreadID);	// FIXME: Create before Start if Read won't break when not-yet-started
	if (m_hThread == NULL)
	{
		goto connect_failure;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	/*u_long ulIO = TRUE;	// Non-blocking
	if (ioctlsocket(m_pClient->m_hSocket, FIONBIO, &ulIO) != 0)
	{
		AfxTrace(_T("Failed to set non-blocking mode\n"));
	}*/

	/*if (m_pClient->AsyncSelect() == FALSE)
	{
		AfxTrace(_T("Failed to set non-blocking mode\n"));
	}*/

	/////////////
/*
	USES_CONVERSION_EX;

	ASSERT(lpszHostAddress != NULL);

	if (lpszHostAddress == NULL)
	{
		WSASetLastError (WSAEINVAL);
		return FALSE;
	}

	SOCKADDR_IN sockAddr;
	memset(&sockAddr,0,sizeof(sockAddr));

	LPSTR lpszAscii = T2A_EX((LPTSTR)lpszHostAddress, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
	if (lpszAscii == NULL)
	{
		WSASetLastError(ERROR_NOT_ENOUGH_MEMORY);
		return FALSE;
	}

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}
	}

	sockAddr.sin_port = htons((u_short)nHostPort);

	/////////////

	if (connect(m_hSocket, lpSockAddr, nSockAddrLen == SOCKET_ERROR))
	{
		if (GetLastError() == WSAEWOULDBLOCK)
		{
			while (PumpMessages(FD_CONNECT))
			{
				if (m_nConnectError != -1)
				{
					WSASetLastError(m_nConnectError);
					return (m_nConnectError == 0);
				}
			}
		}
		return FALSE;
	}
	return TRUE;
*/
	if (m_pClient->Connect(strAddress, BOR_PORT) == FALSE)
	{
		goto connect_failure;
	}

	/*ulIO = FALSE;	// Blocking
	if (ioctlsocket(m_pClient->m_hSocket, FIONBIO, &ulIO) != 0)
	{
		//
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////

	m_bConnected = true;

	if (WaitForResponse(_T("DEVICE")) == false)
	{
		goto connect_failure;
	}

	if ((m_strName.IsEmpty()) || (IS_EMPTY(strHint) == false))
	{
		if (IS_EMPTY(strHint))
			strHint = _T("-");

		if (SendAndWaitForResponse(_T("DEVICE"), strHint) == false)
			goto connect_failure;
	}

	if (m_strName.IsEmpty())
	{
		goto connect_failure;
	}

	if (m_nItemSize <= 0)
	{
		ASSERT(FALSE);
		goto connect_failure;
	}

	if (SendAndWaitForResponse(_T("RATE")) == false)
		goto connect_failure;

	if (SendAndWaitForResponse(_T("FREQ")) == false)
		goto connect_failure;

	if (SendAndWaitForResponse(_T("GAIN")) == false)
		goto connect_failure;

	if (SendAndWaitForResponse(_T("ANTENNA")) == false)
		goto connect_failure;

	SAFE_DELETE_ARRAY(m_pBuffer);

	m_pBuffer = new short[m_recv_samples_per_packet * 2];

	SAFE_DELETE_ARRAY(m_pNetworkBuffer);

	m_nPacketSize = offsetof(BOR_PACKET, data) + m_nItemSize;

	AfxTrace(_T("Item size = %lu, packet size = %lu\n"), m_nItemSize, m_nPacketSize);

	m_pNetworkBuffer = new BYTE[m_nNetworkBufferSize * m_nPacketSize];

	m_nNetworkBufferStart = m_nNetworkBufferItems = 0;

	return true;
connect_failure:
	Destroy();
	return false;
}

bool RemoteUSRP::Create(LPCTSTR strHint /*= NULL*/)
{
	return Connect(m_strAddress, strHint);
}

double RemoteUSRP::SetSampleRate(double dSampleRate)
{
	if (dSampleRate <= 0)
		return -1.0;

	m_dDesiredSampleRate = dSampleRate;

	if (!m_bConnected)
		return 0.0;

	if (SendAndWaitForOK(_T("RATE"), Teh::Utils::ToString(dSampleRate)) == false)
	{
		return -1.0;
	}

	// FIXME: Flush

	return m_dSampleRate;
}

bool RemoteUSRP::SetGain(double dGain)
{
	//if ((dGain < 0.0) || (1.0 < dGain))	// FIXME: Is <0 a valid value?
	//	return false;

	m_dGain = dGain;

	if (!m_bConnected)
		return true;

	if (SendAndWaitForOK(_T("GAIN"), Teh::Utils::ToString(dGain)) == false)
	{
		return false;
	}

	return true;
}

std::vector<std::string> RemoteUSRP::GetAntennas() const
{
	return m_arrayAntennas;
}

bool RemoteUSRP::SetAntenna(int iIndex)
{
	if ((!m_bConnected) || (iIndex < 0))
		return false;

	if (iIndex >= (int)m_arrayAntennas.size())
		return false;

	m_strAntenna = CStringA(m_arrayAntennas[iIndex].c_str());

	if (SendAndWaitForOK(_T("ANTENNA"), CString(m_strAntenna)) == false)
	{
		return false;
	}

	return true;
}

bool RemoteUSRP::SetAntenna(LPCTSTR strAntenna)
{
	if (IS_EMPTY(strAntenna))
		return false;

	m_strAntenna = strAntenna;

	if (!m_bConnected)
		return true;

	if (SendAndWaitForOK(_T("ANTENNA"), CString(m_strAntenna)) == false)
	{
		return false;
	}

	return true;
}

double RemoteUSRP::SetFreq(double dFreq)
{
	if (dFreq < 0)
		return -1;

	m_dFreq = dFreq;

	if (!m_bConnected)
		return 0;

	if (SendAndWaitForOK(_T("FREQ"), Teh::Utils::ToString(dFreq)) == false)
	{
		return -1;
	}

	return m_tuneResult.actual_inter_freq + m_tuneResult.actual_dsp_freq;
}

bool RemoteUSRP::CopyState(IUSRP* pOther)	// FIXME: Remote address
{
	if (pOther == NULL)
		return false;

	if (DYNAMIC_CAST(RemoteUSRP, pOther, pRemote))
		m_strAddress = pRemote->GetRemoteAddress();

	if (SetSampleRate(pOther->GetSampleRate()) <= 0)
		return false;

	if (SetGain(pOther->GetGain()) == false)
		return false;

	if (SetAntenna(pOther->GetAntenna()) == false)
		return false;

	if (SetFreq(pOther->GetFreq()) < 0)
		return false;
	
	return true;
}

bool RemoteUSRP::Start()
{
	if (!m_bConnected)
		return false;

	if (m_bRunning)
		return true;

	Reset();

	if (SendAndWaitForOK(_T("GO")) == false)
	{
		return false;
	}

	ResetStats();

	m_bRunning = true;

	return true;
}

void RemoteUSRP::Stop()
{
	if (!m_bConnected)
		return;

	if (m_bRunning == false)
		return;

	if (SendAndWaitForOK(_T("STOP")) == false)
	{
		return;
	}

	SetEvent(m_hStopEvent);

	m_bRunning = false;
}

int RemoteUSRP::ReadPacket()
{
	if (m_bRunning == false)
		return 0;

	CSingleLock lock(&m_cs, TRUE);

	if (m_nNetworkBufferItems == 0)
	{
		lock.Unlock();

		HANDLE hHandles[] = { m_hStopEvent, m_hPacketEvent };
	
		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
		if (dw == (WAIT_OBJECT_0 + 0))
		{
			return 0;
		}
		else if (dw == (WAIT_OBJECT_0 + 1))
		{
			lock.Lock();
		}
		else
		{
			ASSERT(FALSE);

			return 0;
		}
	}

	//ASSERT(m_nNetworkBufferItems > 0);

	if (m_nNetworkBufferItems == 0)
	{
		//AfxTrace(_T("Reading packet after signal, but no items in buffer (start now %lu)\n"), m_nNetworkBufferStart);	// FIXME: Why does this happen?

		return 0;
	}

	if (m_nNetworkBufferItems > 1)
	{
		//AfxTrace(_T("Reading packet from index %lu (%lu remain)\n"), m_nNetworkBufferStart, (m_nNetworkBufferItems - 1));
	}

	PBOR_PACKET pPacket = (PBOR_PACKET)(m_pNetworkBuffer + (m_nPacketSize * m_nNetworkBufferStart));

	memcpy(m_pBuffer, pPacket->data, m_nItemSize);

	++m_nSamplesReceived;

	if (pPacket->flags & BF_HARDWARE_OVERRUN)
	{
		++m_nOverflows;

		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_OVERFLOW;
	}
	else
		m_metadata.error_code = uhd::rx_metadata_t::ERROR_CODE_NONE;

	--m_nNetworkBufferItems;

	ASSERT(m_nNetworkBufferItems != -1);

	if (m_nNetworkBufferItems > 0)
		m_nNetworkBufferStart = (m_nNetworkBufferStart + 1) % m_nNetworkBufferSize;

	return m_recv_samples_per_packet;
}

CString RemoteUSRP::GetExtraInfo() const
{
	CString str;

	str.Format(_T("Overruns: buffer %lu, network %lu (skipped %lu)"), m_nBufferOverrun, m_nNetworkOverrun, m_nLastSkip);

	return str;
}

void RemoteUSRP::OnCommand(CsocketClient* pSocket, const CString& str)
{
	if (pSocket != m_pClient)
	{
		ASSERT(FALSE);
		return;
	}

	CString strCommand(str), strData;
	int iIndex = str.Find(_T(' '));
	if (iIndex > -1)
	{
		strCommand = str.Left(iIndex);
		strData = str.Mid(iIndex + 1).Trim();
	}

	strCommand = strCommand.MakeUpper();

	if (strCommand == _T("DEVICE"))
	{
		if (strData == _T("-"))
		{
			m_strName.Empty();
		}
		else
		{
			CStringArray array;
			if (Teh::Utils::Tokenise(strData, array, _T('|')) != 7)
			{
				m_strName.Empty();
			}
			else	//usrp1 mboard - 4c69abc2|0.000000|51.500000|0.500000|64000000.000000|4096|TX/RX,RX2
			{
				m_strName = array[0];

				m_gainRange = uhd::gain_range_t(_tstof(array[1]), _tstof(array[2]), _tstof(array[3]));

				m_fpga_master_clock_freq = _tstof(array[4]);

				m_recv_samples_per_packet = _tstoi(array[5]);
				m_nItemSize = m_recv_samples_per_packet * 2 * sizeof(short);

				CStringArray arrayAnt;
				Teh::Utils::Tokenise(array[6], arrayAnt, _T(','));
				m_arrayAntennas.clear();
				for (INT_PTR i = 0; i < arrayAnt.GetCount(); ++i)
					m_arrayAntennas.push_back((LPCSTR)CStringA(arrayAnt[i]));
			}
		}
	}
	else if (strCommand == _T("RATE"))
	{
		CStringArray array;
		if (Teh::Utils::Tokenise(strData, array, _T(' ')))
		{
			if (array[0] != _T("OK"))
				m_dSampleRate = _tstof(array[0]);
			else if (array.GetCount() == 2)
				m_dSampleRate = _tstof(array[1]);
		}
	}
	else if (strCommand == _T("FREQ"))
	{
		CStringArray array;
		if (Teh::Utils::Tokenise(strData, array, _T(' ')))
		{
			if (array[0] != _T("OK"))
			{
				m_dFreq = _tstof(array[0]);
			}
			else if (array.GetCount() == 5)
			{
				m_tuneResult.target_inter_freq = _tstof(array[1]);
				m_tuneResult.actual_inter_freq = _tstof(array[2]);
				m_tuneResult.target_dsp_freq = _tstof(array[3]);
				m_tuneResult.actual_dsp_freq = _tstof(array[4]);
			}
		}
	}
	else if (strCommand == _T("GAIN"))
	{
		if (strData != _T("OK"))
			m_dGain = _tstof(strData);
	}
	else if (strCommand == _T("ANTENNA"))
	{
		if (strData != _T("OK"))
		{
			if (strData != _T("UNKNOWN"))
				m_strAntenna = strData;
		}
	}

	if (m_bPendingResponse)
	{
		m_strResponse = strCommand;
		m_strResponseData = strData;

		//PostQuitMessage(0);

		m_bPendingResponse = false;
		PostMessage(NULL, WM_USER, 0, 0);	// Anything to kick the message pump
	}
}

void RemoteUSRP::OnClose(CsocketClient* pSocket)
{
	if (pSocket != m_pClient)
	{
		ASSERT(FALSE);
		return;
	}

	Close();
}

DWORD RemoteUSRP::ReceiveThread()
{
	SetThreadPriority(GetCurrentThread(), /*THREAD_PRIORITY_HIGHEST*/THREAD_PRIORITY_TIME_CRITICAL);

	HANDLE hHandles[] = { m_hQuitEvent, m_hDataEvent };
	const int iBufferSize = /*m_nSocketBufferSize*/65536;
	PCHAR pBuffer = new CHAR[iBufferSize];

	while (true)
	{
		WSABUF buf;
		buf.buf = pBuffer;
		buf.len = iBufferSize;

		DWORD dwReceived = 0;
		DWORD dwFlags = 0;

		int iResult = WSARecv(m_hDataSocket, &buf, 1, &dwReceived, &dwFlags, &m_wsaOverlapped, NULL);

		ASSERT(dwFlags == 0);

		if (iResult == SOCKET_ERROR)
		{
			DWORD dwError = WSAGetLastError();

			if (dwError != WSA_IO_PENDING)
			{
				ASSERT(FALSE);

				break;
			}

			DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
			if (dw == (WAIT_OBJECT_0 + 0))
			{
				break;
			}
			else if (dw == (WAIT_OBJECT_0 + 1))
			{
				dwReceived = 0;
				dwFlags = 0;
				BOOL bResult = WSAGetOverlappedResult(m_hDataSocket, &m_wsaOverlapped, &dwReceived, FALSE, &dwFlags);

				ASSERT(dwFlags == 0);

				if (bResult == FALSE)
				{
					DWORD dwError = WSAGetLastError();

					if (dwError == 10040)
					{
						++m_nNetworkOverrun;
					}
					else
					{
						ASSERT(FALSE);
					}

					continue;
				}

				iResult = 0;
			}
			else
			{
				ASSERT(FALSE);

				break;
			}
		}

		ASSERT(iResult == 0);

		if (dwReceived == 0)
		{
			ASSERT(FALSE);
			
			continue;
		}
		else if (dwReceived != m_nPacketSize)
		{
			continue;
		}

		{
			CSingleLock lock(&m_cs, TRUE);

			UINT nIndex = ((m_nNetworkBufferStart + m_nNetworkBufferItems) % m_nNetworkBufferSize);

			PBOR_PACKET pPacket = (PBOR_PACKET)pBuffer;

			if (pPacket->idx != m_usCounter)
			{
				//AfxTrace(_T("Ignoring out-of-sequence packet of %lu bytes (expecting %hu, got %hu, start: %lu, %lu items)\n"), dwReceived, m_usCounter, pPacket->idx, nIndex, m_nNetworkBufferItems);

				//continue;

				pPacket->flags |= BF_NETWORK_OVERRUN;

				++m_nNetworkOverrun;

				m_nLastSkip = pPacket->idx - m_usCounter;

				m_usCounter = pPacket->idx;
			}

			//AfxTrace(_T("Writing %lu bytes into packet index %lu (%lu items)\n"), dwReceived, nIndex, m_nNetworkBufferItems);

			LPBYTE pDest = m_pNetworkBuffer + (m_nPacketSize * nIndex);

			memcpy(pDest, pBuffer, dwReceived);

			if (m_nNetworkBufferItems < m_nNetworkBufferSize)
			{
				++m_nNetworkBufferItems;
			}
			else
			{
				m_nNetworkBufferStart = (m_nNetworkBufferStart + 1) % m_nNetworkBufferSize;

				pPacket->flags |= BF_BUFFER_OVERRUN;

				++m_nBufferOverrun;
			}

			++m_usCounter;

			SetEvent(m_hPacketEvent);
		}

		// FIXME: Might have to check event if it never gets a chance to start overlapped I/O
	}

	delete [] pBuffer;

	AfxTrace(_T("Receiver thread 0x%x exiting...\n"), m_dwThreadID);

	return 0;
}
