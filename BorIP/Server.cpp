#include "StdAfx.h"
#include "Server.h"

#include "socketListener.h"
#include "socketClient.h"
#include "USRP.h"
#include "BorIP.h"

Server::Server()
	: m_pListener(NULL)
	, m_pClient(NULL)
	, m_pUSRP(NULL)
	//, m_pDataStream(NULL)
	, m_hDataSocket(INVALID_SOCKET)
	, m_hEvent(NULL)
	, m_dwWorkerID(0)
	, m_hWorker(0)
	, m_nMaxPacketSize(0)
	, m_pCallback(NULL)
{
	ZERO_MEMORY(m_addrDest);

	m_addrDest.sin_family = AF_INET;
}

Server::~Server()
{
	Destroy();
}

void Server::Reset()
{
	m_nReadFailures =
	m_nShortReads =
	m_nOverruns =
	m_nBlockingErrors =
	m_nBlockingWaits =
	m_nSocketErrors =
	m_nShortSends =
	m_nPacketsReceived =
	m_nPacketsSent =
	m_nBlockingSends =
	0;
}

bool Server::Initialise(ServerCallback* pCallback /*= NULL*/)
{
	m_pCallback = pCallback;

	if (m_hEvent == NULL)
	{
		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_hEvent == NULL)
		{
			Log(_T("Failed to create event"));
			return false;
		}
	}

	//m_pDataStream = new CAsyncSocket();

	//if (m_pDataStream->Create(0, SOCK_DGRAM) == FALSE)
	if ((m_hDataSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
		return false;

	int iLength = sizeof(m_nMaxPacketSize);
	//if (m_pDataStream->GetSockOpt(SO_MAX_MSG_SIZE, &m_nMaxPacketSize, &iLength) == 0)
	if (getsockopt(m_hDataSocket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)&m_nMaxPacketSize, &iLength) != 0)
	{
		Log(_T("Failed to get maximum packet size\n"));
	}
	else
	{
		CString str;
		str.Format(_T("Maximum packet size: %lu"), m_nMaxPacketSize);
		Log(str);
	}

	int iBufferSize = 1024 * 1024;
	if (setsockopt(m_hDataSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufferSize, sizeof(iBufferSize)) == 0)
	{
		int iOptLen = sizeof(iBufferSize);

		if (getsockopt(m_hDataSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufferSize, &iOptLen) == 0)
		{
			CString str;
			str.Format(_T("Send socket buffer size: %i"), iBufferSize);
			Log(str);
		}
		else
			Log(_T("Failed to get send socket buffer size"));
	}
	else
		Log(_T("Failed to set send socket buffer size"));

	m_pListener = new CsocketListener(this);

	if (m_pListener->Create(BOR_PORT) == FALSE)
	{
		CString str;
		str.Format(_T("Failed to create listener on port %i"), BOR_PORT);
		Log(str);
		return false;
	}

	if (m_pListener->Listen() == FALSE)
	{
		CString str;
		str.Format(_T("Failed to listen on port %i"), BOR_PORT);
		Log(str);
		return false;
	}

	return true;
}

void Server::Log(const CString& str)
{
	AfxTrace(str + _T("\n"));

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_LOG;
		event.message = str;

		m_pCallback->OnServerEvent(event);
	}
}

void Server::Destroy()
{
	CloseDevice();

	if (m_pListener)
	{
		m_pListener->Close();
		SAFE_DELETE(m_pListener);
	}

	/*if (m_pDataStream)
	{
		m_pDataStream->Close();
		SAFE_DELETE(m_pDataStream);
	}*/

	if (m_hDataSocket != INVALID_SOCKET)
	{
		closesocket(m_hDataSocket);
		m_hDataSocket = INVALID_SOCKET;
	}

	if (m_hEvent != NULL)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
}

void Server::OnAccept()
{
	if (m_pClient)
	{
		CsocketClient s;

		if (m_pListener->Accept(s))
		{
			CString strAddress;
			UINT nPort = 0;
			s.GetPeerName(strAddress, nPort);

			s._Send(_T("BUSY"));
			s.Close();

			CString str;
			str.Format(_T("Ignoring connection from %s:%lu"), strAddress, nPort);
			Log(str);
		}
		else
			Log(_T("Failed to accept connection"));

		return;
	}

	m_pClient = new CsocketClient(this);

	int iLength = sizeof(m_addrDest);
	if (m_pListener->Accept((*m_pClient), (SOCKADDR*)&m_addrDest, &iLength) == FALSE)
	{
		Log(_T("Failed to accept connection"));
		SAFE_DELETE(m_pClient);
		return;
	}

	CString strAddress;
	UINT nPort = 0;
	m_pClient->GetPeerName(strAddress, nPort);

	CString str;
	str.Format(_T("Accepted connection from %s:%lu"), strAddress, nPort);
	Log(str);

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_CONNECTED;
		m_pCallback->OnServerEvent(event);
	}

	m_addrDest.sin_port = htons(BOR_PORT);

	if (m_pClient->_Send(_T("DEVICE ") + FormatDevice()) == false)
	{
		m_pClient->Close();
		SAFE_DELETE(m_pClient);
		return;
	}
}

CString Server::FormatDevice()
{
	if (m_pUSRP == NULL)
		return _T("-");

	CString str(m_pUSRP->GetName());
	CString strBuf;

	strBuf.Format(_T("|%f|%f|%f|%f|%lu"),
		m_pUSRP->GetGainRange().start(),
		m_pUSRP->GetGainRange().stop(),
		m_pUSRP->GetGainRange().step(),
		m_pUSRP->GetMasterClock(),
		m_pUSRP->GetSamplesPerPacket());

	str += strBuf;

	std::vector<std::string> array = m_pUSRP->GetAntennas();
	if (array.empty() == false)
		str += _T("|");
	for (std::vector<std::string>::iterator it = array.begin(); it != array.end(); ++it)
	{
		if (it != array.begin())
			str += _T(",");

		str += CString((*it).c_str());
	}

	return str;
}

void Server::OnCommand(CsocketClient* pSocket, const CString& str)
{
	if ((m_pClient == NULL) || (pSocket != m_pClient))
	{
		ASSERT(FALSE);
		return;
	}

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_COMMAND;
		event.message = str;
		m_pCallback->OnServerEvent(event);
	}

	CString strCommand(str), strData;
	int iIndex = str.Find(_T(' '));
	if (iIndex > -1)
	{
		strCommand = str.Left(iIndex);
		strData = str.Mid(iIndex + 1).Trim();
	}

	strCommand = strCommand.MakeUpper();

	CString strResult(_T("OK"));

	if (strCommand == _T("GO"))
	{
		if (m_pUSRP)
		{
			if (m_pUSRP->IsRunning())
			{
				strResult = _T("RUNNING");
			}
			else
			{
				if (Start() == false)
					strResult = _T("FAIL");
			}
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("STOP"))
	{
		if (m_pUSRP)
		{
			if (m_pUSRP->IsRunning() == false)
				strResult = _T("STOPPED");

			Stop();
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("DEVICE"))
	{
		if (strData.IsEmpty() == false)
		{
			if (strData == _T("!"))
			{
				CloseDevice();
			}
			else
			{
				LPCTSTR strHint = NULL;
				if (strData != _T("-"))
					strHint = strData;

				CreateDevice(strHint);
			}
		}

		strResult = FormatDevice();
	}
	else if (strCommand == _T("FREQ"))
	{
		if (m_pUSRP)
		{
			if (strData.IsEmpty())
			{
				strResult = Teh::Utils::ToString(m_pUSRP->GetFreq());
			}
			else
			{
				double d = _tstof(strData);

				if (m_pUSRP->SetFreq(d) < 0)
				{
					CString str;
					str.Format(_T("Failed to set frequency: %f"), d);
					Log(str);

					strResult = _T("FAIL");
				}
				else
				{
					int iResult = m_pUSRP->WasTuneSuccessful();
					if (iResult < 0)
						strResult = _T("LOW");
					else if (iResult > 0)
						strResult = _T("HIGH");

					CString strBuf;
					strBuf.Format(_T(" %f %f %f %f"),
						m_pUSRP->GetTuneResult().target_inter_freq,
						m_pUSRP->GetTuneResult().actual_inter_freq,
						m_pUSRP->GetTuneResult().target_dsp_freq,
						m_pUSRP->GetTuneResult().actual_dsp_freq);

					strResult += strBuf;
				}
			}
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("ANTENNA"))
	{
		if (m_pUSRP)
		{
			if (strData.IsEmpty())
			{
				strResult = m_pUSRP->GetAntenna();

				if (strResult.IsEmpty())
					strResult = _T("UNKNOWN");
			}
			else
			{
				if (m_pUSRP->SetAntenna(strData) == false)
				{
					CString str;
					str.Format(_T("Failed to set antenna: %s"), strData);
					Log(str);

					strResult = _T("FAIL");
				}
			}
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("GAIN"))
	{
		if (m_pUSRP)
		{
			if (strData.IsEmpty())
			{
				strResult = Teh::Utils::ToString(m_pUSRP->GetGain());
			}
			else
			{
				double d = _tstof(strData);

				if (m_pUSRP->SetGain(d) == false)
				{
					CString str;
					str.Format(_T("Failed to set gain: %f"), d);
					Log(str);

					strResult = _T("FAIL");
				}
			}
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("RATE"))
	{
		if (m_pUSRP)
		{
			if (strData.IsEmpty())
			{
				strResult = Teh::Utils::ToString(m_pUSRP->GetSampleRate());
			}
			else
			{
				double d = _tstof(strData);

				if (m_pUSRP->SetSampleRate(d) <= 0)
				{
					CString str;
					str.Format(_T("Failed to set sample rate: %f"), d);
					Log(str);

					strResult = _T("FAIL");
				}
				else
				{
					strResult += _T(" ") + Teh::Utils::ToString(m_pUSRP->GetSampleRate());
				}
			}
		}
		else
			strResult = _T("DEVICE");
	}
	else if (strCommand == _T("DEST"))
	{
		if (strData.IsEmpty())
		{
			UINT nPort;
			if (m_pClient->GetPeerName(strData, nPort) == FALSE)
			{
				Log(_T("Failed to get peer name for current connection"));
			}
		}

		if (strData.IsEmpty())
		{
			strResult = _T("FAIL");
		}
		else
		{
			iIndex = strData.Find(_T(':'));
			UINT nPort = BOR_PORT;
			if (iIndex > -1)
			{
				nPort = _tstoi(strData.Mid(iIndex + 1));
				strData = strData.Left(iIndex);
			}

			ULONG ulAddress = inet_addr(CStringA(strData));
			if (ulAddress == -1)
			{
				strResult = _T("FAIL");
			}
			else
			{
				m_addrDest.sin_addr.S_un.S_addr = ulAddress;
				m_addrDest.sin_port = htons(nPort);
			}
		}
	}
	else
		strResult = _T("UNKNOWN");

	if (strResult.IsEmpty())
		return;

	strResult = strCommand + _T(" ") + strResult;

	m_pClient->_Send(strResult);
}

bool Server::CreateDevice(LPCTSTR strHint /*= NULL*/)
{
	CloseDevice();

	int iIndex = -1;
	CStringArray array;
	if (Teh::Utils::Tokenise(strHint, array, _T(' ')))
		iIndex = _tstoi(array[0]);

	if (iIndex > -1)
		m_pUSRP = new LegacyUSRP();
	else
		m_pUSRP = new USRP();

	if (m_pUSRP->Create(strHint) == false)
	{
		CString str;
		str.Format(_T("Failed to create device with hint: %s"), (strHint ? strHint : _T("(none)")));
		Log(str);

		SAFE_DELETE(m_pUSRP);

		return false;
	}

	Log(_T("Created device: ") + m_pUSRP->GetName());

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_CREATED;
		m_pCallback->OnServerEvent(event);
	}

	return true;
}

void Server::CloseDevice()
{
	if (m_pUSRP == NULL)
		return;

	if (m_pUSRP->IsRunning())
	{
		Log(_T("Stopping running device when closing..."));

		Stop();
	}

	Log(_T("Closing device..."));

	SAFE_DELETE(m_pUSRP);

	Log(_T("Closed"));

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_CLOSED;
		m_pCallback->OnServerEvent(event);
	}
}

static DWORD WINAPI _Worker(LPVOID lpThreadParameter)
{
	return ((Server*)lpThreadParameter)->Worker();
}

bool Server::Start()
{
	if (m_pUSRP == NULL)
	{
		Log(_T("Cannot start when no device created"));

		//if (CreateDevice() == false)	// Cannot do this before information should be sent back
			return false;
	}
	else if (m_pUSRP->IsRunning())
	{
		Log(_T("Already running"));

		return true;
	}

	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	if (m_pUSRP->Start() == false)
	{
		Log(_T("Failed to start device"));

		return false;
	}

	Reset();
	
	m_hWorker = CreateThread(NULL, 0, _Worker, this, 0, &m_dwWorkerID);	// FIXME: Create before Start if Read won't break when not-yet-started
	if (m_hWorker == NULL)
	{
		Log(_T("Failed to create worker thread"));
		return 0;
	}

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_START;
		m_pCallback->OnServerEvent(event);
	}

	return true;
}

void Server::Stop()
{
	if ((m_pUSRP == NULL) || (m_hEvent == NULL))	// Not checking whether running, only existence of thread
	{
		Log(_T("Cannot stop with no device"));

		return;
	}

	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	m_pUSRP->Stop();

	if (m_hWorker)
	{
		SetEvent(m_hEvent);

		AfxTrace(_T("Waiting for termination of thread 0x%x...\n"), m_dwWorkerID);

		WaitForSingleObject(m_hWorker, INFINITE);

		AfxTrace(_T("Thread 0x%x terminated.\n"), m_dwWorkerID);

		CloseHandle(m_hWorker);
		m_hWorker = NULL;
	}

	m_dwWorkerID = 0;

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_STOP;
		m_pCallback->OnServerEvent(event);
	}
}

void Server::OnClose(CsocketClient* pClient)
{
	if (pClient != m_pClient)
	{
		ASSERT(FALSE);
		return;
	}

	Log(_T("Connection closed"));

	if (m_pCallback)
	{
		ServerCallback::EVENT event;
		event.code = ServerCallback::EC_DISCONNECTED;
		m_pCallback->OnServerEvent(event);
	}

	if (m_pUSRP)
		Stop();

	m_pClient = NULL;
}

DWORD Server::Worker()
{
	SetThreadPriority(GetCurrentThread(), /*THREAD_PRIORITY_HIGHEST*/THREAD_PRIORITY_TIME_CRITICAL);

	LPBYTE p = new BYTE[m_nMaxPacketSize];
	PBOR_PACKET pPacket = (PBOR_PACKET)p;
	USHORT usIndex = 0;

	/*timeval timeout;
	timeout.tv_usec = 0;
	timeout.tv_sec = 0;*/
	/*fd_set tx;
	FD_ZERO(&tx);
	FD_SET(m_pDataStream->m_hSocket, &tx);*/

	WSABUF wsabuf;
	WSAOVERLAPPED wsaoverlapped;
	HANDLE hDataSent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(hDataSent);
	if (hDataSent == NULL)
	{
		AfxTrace(_T("Failed to create data sent wait handle\n"));
		return -1;
	}

	bool bFirstPacket = true;

	while (true)
	{
		DWORD dw = WaitForSingleObject(m_hEvent, 0);

		if (dw == WAIT_OBJECT_0)
			break;

		int iSamplesRead = m_pUSRP->ReadPacket();

		if (iSamplesRead == -1)
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nReadFailures;
				//m_bError = true;
			}

			AfxTrace(_T("Failed to read packet\n"));

			break;
		}
		else if (iSamplesRead != m_pUSRP->GetSamplesPerPacket())
		{
			if (iSamplesRead > 0)
			{
				{
					CSingleLock lock(&m_cs, TRUE);
					++m_nShortReads;
				}

				AfxTrace(_T("Only read %lu samples of %lu (missing %lu)\n"), iSamplesRead, m_pUSRP->GetSamplesPerPacket(), (m_pUSRP->GetSamplesPerPacket() - iSamplesRead));
			}

			continue;
		}

		{
			CSingleLock lock(&m_cs, TRUE);
			++m_nPacketsReceived;
		}

		pPacket->flags = 0;

		if (m_pUSRP->GetMetadata().error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW)
		{
			pPacket->flags |= BF_HARDWARE_OVERRUN;

			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nOverruns;
			}
		}
		else if (m_pUSRP->GetMetadata().error_code != 0)
		{
			AfxMessageBox(_T("Non-zero meta data: ") + Teh::Utils::ToString(m_pUSRP->GetMetadata().error_code));
		}
		
		pPacket->idx = usIndex++;
		//pPacket->sub_idx = 0;

		int iLength = /*sizeof(BOR_PACKET)*/offsetof(BOR_PACKET, data);
		int iPayloadLength = m_pUSRP->GetSamplesPerPacket() * 2 * sizeof(short);
		iLength += iPayloadLength;

		memcpy(pPacket->data, m_pUSRP->GetBuffer(), iPayloadLength);

		if (bFirstPacket)
		{
			pPacket->flags |= BF_STREAM_START;
			bFirstPacket = false;
		}

		//////////////////////////////////////////////

		wsabuf.buf = (char*)pPacket;
		wsabuf.len = iLength;

		ZERO_MEMORY(wsaoverlapped);
		wsaoverlapped.hEvent = hDataSent;

		DWORD dwSocketBytesSent = 0;
		int iResult = WSASendTo(m_hDataSocket, &wsabuf, 1, &dwSocketBytesSent, 0, (sockaddr*)&m_addrDest, sizeof(m_addrDest), &wsaoverlapped, NULL);
		if (iResult == SOCKET_ERROR)
		{
			DWORD dw = WSAGetLastError();

			if (dw != WSA_IO_PENDING/*WSAEWOULDBLOCK*/)
			{
				{
					CSingleLock lock(&m_cs, TRUE);
					++m_nSocketErrors;
				}

				continue;
			}

			dw = WaitForSingleObject(hDataSent, INFINITE);
			if (dw != WAIT_OBJECT_0)
			{
				AfxTrace(_T("Unexpected result while waiting for send: %lu\n"), dw);
			}

			DWORD dwSocketFlags = 0;
			dwSocketBytesSent = 0;
			if (WSAGetOverlappedResult(m_hDataSocket, &wsaoverlapped, &dwSocketBytesSent, TRUE, &dwSocketFlags) == FALSE)
			{
				{
					CSingleLock lock(&m_cs, TRUE);
					++m_nBlockingErrors;
				}

				continue;
			}

			ASSERT(dwSocketFlags == 0);

			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nPacketsSent;
				++m_nBlockingSends;
			}
		}
		else if (iResult != 0)
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nShortSends;
			}
		}
		else
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nPacketsSent;
			}
		}

		continue;

		//////////////////////////////////////////////

		/*int iSent = m_pDataStream->SendTo(pPacket, iLength, (SOCKADDR*)&m_addrDest, sizeof(m_addrDest));
		if (iSent == SOCKET_ERROR)
		{
			DWORD dwError = WSAGetLastError();

			if (dwError == WSAEWOULDBLOCK)
			{
				int iResult = select(((int)m_pDataStream->m_hSocket) + 1, NULL, &tx, NULL, NULL);	//&timeout
				if (iResult == SOCKET_ERROR)
				{
					{
						CSingleLock lock(&m_cs, TRUE);
						++m_nBlockingErrors;
					}

					dwError = WSAGetLastError();

					AfxTrace(_T("Socket error while blocking: %lu\n"), dwError);
				}
				else if (iResult != 1)
				{
					{
						CSingleLock lock(&m_cs, TRUE);
						++m_nBlockingWaits;
					}

					AfxTrace(_T("Blocking wait result: %i\n"), iResult);
				}
				else
				{
					{
						CSingleLock lock(&m_cs, TRUE);
						++m_nPacketsSent;
						++m_nBlockingSends;
					}
				}
			}
			else
			{
				{
					CSingleLock lock(&m_cs, TRUE);
					++m_nSocketErrors;
				}

				AfxTrace(_T("Socket error: %lu\n"), dwError);
			}
		}
		else if (iSent != iLength)
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nShortSends;
			}

			AfxTrace(_T("Short send: %i != %i\n"), iSent, iLength);
		}
		else
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				++m_nPacketsSent;
			}
		}*/
	}

	if (hDataSent)
		CloseHandle(hDataSent);

	SAFE_DELETE_ARRAY(p);

	ASSERT(m_dwWorkerID == GetCurrentThreadId());

	AfxTrace(_T("Worker thread 0x%x exiting...\n"), GetCurrentThreadId());

	return 0;
}
