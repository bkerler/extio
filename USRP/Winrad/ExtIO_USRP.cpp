#include "StdAfx.h"
#include "ExtIO_USRP.h"

#include "dialogExtIO.h"
#include "socketClientWaitable.h"
#include "BorIP.h"
#include "MemoryUSRP.h"

#define REGISTRY_PROFILE_SECTION	m_strSerial // _T("USRP ExtIO")
#include <TehBase\TehAfxRegistryProfile.h>
#define SETTINGS_SECTION	_T("Settings")

ExtIO_USRP::ExtIO_USRP()
	: m_pUSRP(NULL)
	//, m_lLO(0)
	, m_hEvent(NULL)
	, m_dwWorkerID(0)
	, m_pfnCallback(NULL)
	, m_pDialog(NULL)
	, m_hWorker(NULL)
	//, m_dGain(0.45)
	, m_lTunedFreq(0)
	//, m_lSampleRate(250000)
	, m_bError(false)
	, m_strSerial(SETTINGS_SECTION)
	, m_bForceSampleRateUpdate(false)
	, m_hDataSocket(INVALID_SOCKET)
	, m_nMaxPacketSize(0)
	, m_pXMLRPCClient(NULL)
	, m_iXMLRPCPort(0)
	, m_bEnableUDPRelay(FALSE)
	, m_bEnableXMLRPCIF(FALSE)
	, m_bRemoteDevice(FALSE)
	, m_lOffset(0)
	, m_bUseOffset(FALSE)
	, m_bSkipFailedXMLRPC(false)
{
	ZERO_MEMORY(m_lIFLimits);

	m_dSampleRate = 250000.0;
	m_dGain = 0.45;
	m_dFreq = 50000000.0;

	ZERO_MEMORY(m_addrDest);
	m_addrDest.sin_family = AF_INET;
	m_addrDest.sin_port = htons(BOR_PORT);
}

ExtIO_USRP::~ExtIO_USRP()
{
	Destroy();
}

bool ExtIO_USRP::Init()
{
	LOAD_STRING(m_strDevice);
	LOAD_STRING(m_strAddress);
	LOAD_INT(m_bRemoteDevice);
	LOAD_INT(m_bEnableUDPRelay);
	LOAD_INT(m_bEnableXMLRPCIF);
	LOAD_INT(m_iXMLRPCPort);
	LOAD_STRING(m_strUDPRelayAddress);

	if (m_hEvent == NULL)
	{
		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_hEvent == NULL)
			return false;
	}

	if (m_bEnableUDPRelay)
	{
		if (m_strUDPRelayAddress.IsEmpty())
			m_bEnableUDPRelay = FALSE;
		else
		{
			if (EnableUDPRelay(m_strUDPRelayAddress) == false)
			{
				//m_bEnableUDPRelay = FALSE;
			}
		}
	}

	if (m_bEnableXMLRPCIF)
	{
		if (m_iXMLRPCPort <= 0)
			m_bEnableXMLRPCIF = FALSE;
		else
		{
			if (EnableXMLRPCIF(m_iXMLRPCPort) == false)
			{
				//
			}
		}
	}

	if (m_pDialog == NULL)
	{
		m_pDialog = new CdialogExtIO(this, NULL);

		if (m_pDialog->Create(IDD_DIALOG_EXTIO) == FALSE)
		{
			AfxTrace(_T("Failed to create dialog\n"));
			return false;
		}
	}

	return true;
}

void ExtIO_USRP::Destroy()
{
	Close();

	/////////////////////////////////////

	m_strSerial = SETTINGS_SECTION;

	SAVE_STRING(m_strDevice);
	SAVE_STRING(m_strAddress);
	SAVE_INT(m_bRemoteDevice);
	SAVE_INT(m_bEnableUDPRelay);
	SAVE_INT(m_bEnableXMLRPCIF);
	SAVE_INT(m_iXMLRPCPort);
	SAVE_STRING(m_strUDPRelayAddress);

	/////////////////////////////////////

	DisableUDPRelay(true);
	DisableXMLRPCIF(true);

	if (m_pDialog)
	{
		m_pDialog->DestroyWindow();
		SAFE_DELETE(m_pDialog);
	}

	if (m_hEvent != NULL)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
}

bool ExtIO_USRP::TryOpen()
{
	if (Open() == false)
	{
		m_pDialog->_Log("Failed to open device, will force sample rate update check next time");
		m_bForceSampleRateUpdate = true;
		return false;
	}

	return true;
}

void ExtIO_USRP::Playback()
{
	if (m_pUSRP)
	{
		ASSERT(FALSE);
		return;
	}

	m_pDialog->_Log(_T("Entering playback mode..."));

	m_pUSRP = new MemoryUSRP;

	m_strSerial.Empty();

	VERIFY(Start());
}

bool ExtIO_USRP::Open(LPCTSTR strHint /*= NULL*/, LPCTSTR strAddress /*= NULL*/)
{
	if (m_hEvent == NULL)
		return false;

	if (m_pUSRP)
	{
		m_pDialog->_Log(_T("Cannot create new device while existing device open"));
		return true;
	}

	if (GetAsyncKeyState(VK_SHIFT) & (1 << 15))
	{
		m_pDialog->_Log(_T("Skipping creation because SHIFT is being held"));
		return true;
	}

	double dPrevSampleRate = GetSampleRate();

	if (strHint != NULL)
		m_strDevice = strHint;
	if (IS_EMPTY(strAddress) == false)
		m_strAddress = strAddress;

	///////////////////////////////////////////////////////////////////////////

	if (m_bRemoteDevice == FALSE)
	{
		int iIndex = -1;
		CStringArray array;
		if (Teh::Utils::Tokenise(m_strDevice, array, _T(' ')))
		{
			iIndex = _tstoi(array[0]);
			if ((iIndex == 0) && (array[0] != _T("0")))
				iIndex = -1;
		}

		if (iIndex > -1)
		{
			m_pDialog->_Log(_T("Creating legacy device..."));

			m_pUSRP = new LegacyUSRP();
		}
		else
		{
			m_pDialog->_Log(_T("Creating UHD device..."));

			m_pUSRP = new USRP();
		}
	}
	else
	{
		if (m_strAddress.IsEmpty())
		{
			AfxMessageBox(_T("Cannot connect to remote device without specifying address"));
			return false;
		}

		m_pDialog->_Log(_T("Creating remote device..."));

		RemoteUSRP* pUSRP = new RemoteUSRP(RUNTIME_CLASS(CsocketClientWaitable));
		pUSRP->SetRemoteAddress(m_strAddress);
		m_pUSRP = pUSRP;
	}

	///////////////////////////////////////////////////////////////////////////

	CString strFilteredDevice(m_strDevice);
	if ((m_bRemoteDevice == FALSE) && (m_strDevice == _T("-")))
		strFilteredDevice.Empty();

	if (m_pUSRP->Create(m_strDevice) == false)
	{
		m_pDialog->_Log(_T("Failed to create device: ") + m_pUSRP->GetLastError());

		if (m_strDevice.IsEmpty() == false)
		{
			if (AfxMessageBox(_T("Failed to create USRP: ") + m_strDevice + _T("\n\n(") + m_pUSRP->GetLastError() + _T(")\n\nTry without device hint?"), MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				if (m_pUSRP->Create() == false)
				{
					m_pDialog->_Log(_T("Failed to create default device: ") + m_pUSRP->GetLastError());
					AfxMessageBox(_T("Failed to create default USRP even without device hint:\n\n") + m_pUSRP->GetLastError());

					SAFE_DELETE(m_pUSRP);
					return false;
				}
			}
			else
			{
				SAFE_DELETE(m_pUSRP);
				return false;
			}
		}
		else
		{
			AfxMessageBox(_T("Failed to create USRP without device hint:\n\n") + m_pUSRP->GetLastError());

			SAFE_DELETE(m_pUSRP);
			return false;
		}
	}

	/////////////////////////////////////

	m_strSerial = m_pUSRP->GetName();
	if (m_strSerial.IsEmpty())
		m_strSerial = _T("(no name)");

	m_pDialog->_Log(_T("Loading settings for: ") + m_strSerial);

	LOAD_INT(m_dFreq);
	LOAD_FLOAT(m_dGain);
	LOAD_STRING(m_strAntenna);
	LOAD_INT(m_dSampleRate);

	LOAD_INT(m_bUseOffset);
	LOAD_INT(m_lOffset);

	if ((m_dGain < m_pUSRP->GetGainRange().start()) || (m_dGain > m_pUSRP->GetGainRange().stop()))
		m_dGain = m_pUSRP->GetGainRange().start();
	if (m_strAntenna.IsEmpty() && (m_pUSRP->GetAntennas().empty() == false))
		m_strAntenna = CString(m_pUSRP->GetAntennas()[0].c_str());

	/////////////////////////////////////

	//if (m_pUSRP->SetSampleRate(m_dSampleRate) <= 0)	// Must be called as GetHWSR will be called next
	if (SetSampleRate(m_dSampleRate) == false)
	{
		CString str(_T("Failed to set initial sampling rate: ") + Teh::Utils::ToString(m_dSampleRate));
		m_pDialog->_Log(str + _T(" (") + m_pUSRP->GetLastError() + _T(")"));
		AfxMessageBox(str + _T("\n\n") + m_pUSRP->GetLastError());

		return false;
	}

	// So UI gets correct value
	m_pUSRP->SetDesiredGain(m_dGain);
	m_pUSRP->SetDesiredAntenna(m_strAntenna);
	m_pUSRP->SetDesiredFrequency(m_dFreq);

	m_pDialog->_CreateUI();

	if (m_bForceSampleRateUpdate)
	{
		if (dPrevSampleRate != GetSampleRate())
		{
			AfxTrace(_T("Sample rate has changed since last reported - notifying...\n"));

			Signal(CS_HWSRChange);
		}
	}

	m_bForceSampleRateUpdate = false;

	return true;
}

void ExtIO_USRP::Close()
{
	if (m_pUSRP == NULL)
		return;

	if (m_pUSRP->IsRunning())
		Abort();

	/////////////////////////////////////
	// Only save it if a device exists, because then it'll be saved to the correct location

	//ASSERT((m_strSerial.IsEmpty() == false) && (m_strSerial != SETTINGS_SECTION));

	CopyFrom(m_pUSRP);

	if ((m_strSerial.IsEmpty() == false) && (m_strSerial != SETTINGS_SECTION))
	{
		m_pDialog->_Log(_T("Saving settings for: ") + m_strSerial);

		SAVE_INT(m_dFreq);
		SAVE_FLOAT(m_dGain);
		SAVE_STRING(m_strAntenna);
		SAVE_INT(m_dSampleRate);

		SAVE_INT(m_bUseOffset);
		SAVE_INT(m_lOffset);
	}

	/////////////////////////////////////

	if ((m_pUSRP) && (m_bError) && (CAN_CAST(m_pUSRP, RemoteUSRP) == false))
	{
		if (AfxMessageBox(_T("An error occurred at some point.\n\nThere is a chance that the program will hang when cleaning up\nif your USRP has been disconnected while it was running.\n\nDo you want to skip the clean-up just in case?"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON1) == IDYES)
		{
			m_pUSRP = NULL;

			return;
		}
	}

	m_pDialog->_Log(_T("Deleting device..."));

	SAFE_DELETE(m_pUSRP);

	m_pDialog->_Log(_T("Deleted"));
}

bool ExtIO_USRP::SetSampleRate(double dSampleRate)
{
	m_dSampleRate = dSampleRate;

	if (m_pUSRP == NULL)
		return true;

	if (m_pUSRP->SetSampleRate(dSampleRate) <= 0)
	{
		m_pDialog->_Log(_T("While setting sample rate: ") + m_pUSRP->GetLastError());
		return false;
	}

	Signal(CS_HWSRChange);

	return true;
}

int ExtIO_USRP::SetLO(ULONG lFreq)
{
	if (m_bUseOffset)
		lFreq += m_lOffset;

	m_dFreq = lFreq;

	if (m_pUSRP == NULL)
		return 1;	// Higher than possible

	double d = m_pUSRP->SetFreq(lFreq);

	m_pDialog->_UpdateUI(CdialogExtIO::UF_TUNE_INFO);	// Update regardless of error

	if (d < 0)
	{
		m_pDialog->_Log(_T("While setting frequency: ") + m_pUSRP->GetLastError());
		return 1;
	}

	return m_pUSRP->WasTuneSuccessful(/*m_pUSRP->GetTuneResult()*/);	// Return 0 if the frequency is within the limits the HW can generate
}

void ExtIO_USRP::SetTunedFrequency(long lFreq)
{
	if (m_bUseOffset)
		lFreq += m_lOffset;

	m_lTunedFreq = lFreq;

	if (m_pUSRP)
	{
		double dOffset = m_pUSRP->GetFreq() - (double)lFreq;

		AfxTrace(_T("Tuning offset = %f\n"), dOffset);

		if (m_pXMLRPCClient)
		{
			XmlRpc::XmlRpcValue args, result;
			args[0] = dOffset;

			if (m_pXMLRPCClient->execute("set_xlate_offset", args, result) == false)
			{
				m_pDialog->_Log(_T("Failed to execute XML-RPC command - is the server running?"));

				if (m_bSkipFailedXMLRPC == false)
				{
					int iResult = AfxMessageBox(_T("Failed to sending tuning offset via XML-RPC. The server might not be running.\n\nWould you like to switch this feature off until you re-enable the server later?\n\n('Cancel' will leave it enabled and prevent this from being shown again this session.)"), MB_YESNOCANCEL);
					if (iResult == IDCANCEL)
					{
						m_bSkipFailedXMLRPC = true;
					}
					else if (iResult == IDYES)
					{
						DisableXMLRPCIF();
						m_pDialog->_UpdateUI(CdialogExtIO::UF_RELAY);
					}
				}
			}
		}
	}

	//PostMessage
}

void ExtIO_USRP::SetIFLimits(long lLow, long lHigh)
{
	if (m_bUseOffset)
	{
		lLow += m_lOffset;
		lHigh += m_lOffset;
	}

	m_lIFLimits[LOW] = lLow;
	m_lIFLimits[HIGH] = lHigh;

	//long lCentre = lLow + ((lHigh - lLow) / 2);
	double dWidth = lHigh - lLow;

	AfxTrace(_T("IF width = %f\n"), dWidth);

	//PostMessage
}

void ExtIO_USRP::SetCallback(FnCallback pfnCallback)
{
	CSingleLock lock(&m_cs, TRUE);

	m_pfnCallback = pfnCallback;
}

void ExtIO_USRP::Signal(CallbackStatus status)
{
	CSingleLock lock(&m_cs, TRUE);	// FIXME: Deadlock?

	if (m_pfnCallback == NULL)
		return;

	(m_pfnCallback)(-1, (int)status, 0, NULL);
}

static DWORD WINAPI _Worker(LPVOID lpThreadParameter)
{
	return ((ExtIO_USRP*)lpThreadParameter)->Worker();
}

int ExtIO_USRP::Start()
{
	if ((m_pUSRP == NULL) || (m_pUSRP->IsRunning()) || (m_hWorker != NULL))
	{
		m_pDialog->_Log(_T("Cannot start"));
		Signal(CS_Stop);
		return 0;
	}

	bool bResult = true;
retry_start:
	if (m_pUSRP->SetSampleRate(m_dSampleRate) <= 0)
	{
		m_pDialog->_Log(_T("While setting sample rate: ") + m_pUSRP->GetLastError());
		bResult = false;
	}
	if (m_pUSRP->SetGain(m_dGain) == false)
	{
		m_pDialog->_Log(_T("While setting gain: ") + m_pUSRP->GetLastError());
		bResult = false;
	}
	if (m_pUSRP->SetAntenna(m_strAntenna) == false)
	{
		m_pDialog->_Log(_T("While setting antenna: ") + m_pUSRP->GetLastError());
		bResult = false;
	}
	if (m_pUSRP->SetFreq(m_dFreq) < 0)	// Set here the frequency of the controlled hardware to LOfreq
	{
		m_pDialog->_Log(_T("While setting frequency: ") + m_pUSRP->GetLastError());
		bResult = false;
	}

	bool bError = false;
	if ((bResult == false) && (m_bError))
	{
		int iResult = IDRETRY;

		//if (CAN_CAST(m_pUSRP, RemoteUSRP) == false)
			iResult = AfxMessageBox(_T("Failed to set some USRP parameters.\nThis is probably due to your device being disconnected.\nMake sure it is connected before continuing!\n\nAbort:\tStop\nRetry:\tAttempt to re-create device (probably will not work if device link was broken)\nIgnore:\tContinue (expect things to break/hang)"), MB_ABORTRETRYIGNORE | MB_ICONWARNING | MB_DEFBUTTON2);

		if (iResult == IDABORT)
		{
			Signal(CS_Stop);
			return 0;
		}
		else if (iResult == IDRETRY)
		{
 			m_pUSRP->Stop();

			if (CAN_CAST(m_pUSRP, RemoteUSRP))
				iResult = IDYES;
			else
				iResult = AfxMessageBox(_T("Would you like to clean-up the device?\n\nThis may cause the program to freeze if the device link was previously broken."), MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON2);

			if (iResult == IDYES)
			{
				SAFE_DELETE(m_pUSRP);
			}
			else if (iResult == IDNO)
			{
				m_pUSRP = NULL;
			}
			else
			{
				Signal(CS_Stop);
				return 0;
			}

			if (Open() == false)
			{
				AfxMessageBox(_T("Failed to re-create device.\n\nPlease check your USRP and re-start the program."));
				Signal(CS_Stop);
				return 0;
			}

			bResult = true;
			goto retry_start;
		}
		else
		{
			bError = true;
		}
	}

	m_pDialog->_UpdateUI();

	if (m_pUSRP->Start() == false)
	{
		m_pDialog->_Log(_T("While starting streaming: ") + m_pUSRP->GetLastError());
		Signal(CS_Stop);
		AfxMessageBox(_T("Failed to start USRP:\n\n") + m_pUSRP->GetLastError());
		return 0;
	}

	m_hWorker = CreateThread(NULL, 0, _Worker, this, 0, &m_dwWorkerID);	// FIXME: Create before Start if Read won't break when not-yet-started
	if (m_hWorker == NULL)
	{
		AfxTrace(_T("Failed to create worker thread"));
		return 0;
	}

	m_pDialog->_Log(_T("Started"));

	m_bError = bError;

	m_pDialog->_ToggleRunning(true);

	//AfxTrace(_T("Priority class before rise: 0x%04x\n"), GetPriorityClass(GetCurrentProcess()));
	//SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	return m_pUSRP->GetSamplesPerPacket(); // Number of complex elements returned each invocation of the callback routine, multiple of 512
}

void ExtIO_USRP::Abort()
{
	//m_pDialog->_Log(_T("Aborting..."));

	Stop();

	Signal(CS_Stop);
}

void ExtIO_USRP::Stop()
{
	if ((m_pUSRP == NULL) || (m_hEvent == NULL))	// Not checking whether running, only existence of thread
		return;

	//AfxTrace(_T("Priority class before fall: 0x%04x\n"), GetPriorityClass(GetCurrentProcess()));
	//SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	m_pDialog->_Log(_T("Stopping..."));

	SetEvent(m_hEvent);

	m_pUSRP->Stop();	// Wait for this to complete?
	//Sleep(500);

	if (m_hWorker)
	{
		//SetEvent(m_hEvent);

		AfxTrace(_T("Waiting for termination of thread 0x%x...\n"), m_dwWorkerID);

		if (CAN_CAST(m_pUSRP, MemoryUSRP) == false)	// TODO: Figure out why this deadlocks on shutdown (does it anymore?)
			WaitForSingleObject(m_hWorker, INFINITE);

		CloseHandle(m_hWorker);
		m_hWorker = NULL;
	}

	ResetEvent(m_hEvent);

	m_dwWorkerID = 0;

	m_pDialog->_Log(_T("Stopped"));

	m_pDialog->_ToggleRunning(false);

	CopyFrom(m_pUSRP);
}

bool ExtIO_USRP::EnableXMLRPCIF(int iPort /*= 0*/)
{
	if (m_pXMLRPCClient == NULL)
	{
		if (m_addrDest.sin_addr.S_un.S_addr == 0)
			return false;

		CStringA strA(inet_ntoa(m_addrDest.sin_addr));

		if (iPort > 0)
			m_iXMLRPCPort = iPort;

		m_pXMLRPCClient = new XmlRpc::XmlRpcClient(strA, m_iXMLRPCPort);
	}
	else
		return SetXMLRPCIFPort(iPort);

	m_bEnableXMLRPCIF = TRUE;

	return true;
}

void ExtIO_USRP::DisableXMLRPCIF(bool bKeepSetting /*= false*/)
{
	SAFE_DELETE(m_pXMLRPCClient);

	if (bKeepSetting == false)
		m_bEnableXMLRPCIF = FALSE;
}

bool ExtIO_USRP::SetXMLRPCIFPort(int iPort)
{
	if (iPort <= 0)
		return false;
	else if (m_iXMLRPCPort == iPort)
		return true;

	if (m_pXMLRPCClient)
	{
		DisableXMLRPCIF(true);
		EnableXMLRPCIF(iPort);	// Ignore errors
	}
	else
		m_iXMLRPCPort = iPort;

	return true;
}

bool ExtIO_USRP::EnableUDPRelay(LPCTSTR strDestination /*= NULL*/)
{
	{
		CSingleLock lock(&m_csRelay, TRUE);

		if (m_hDataSocket == INVALID_SOCKET)
		{
			if ((m_hDataSocket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)	// FIXME: Use local var and do while unlocked
				return false;

			int iLength = sizeof(m_nMaxPacketSize);
			//if (m_pDataStream->GetSockOpt(SO_MAX_MSG_SIZE, &m_nMaxPacketSize, &iLength) == 0)
			if (getsockopt(m_hDataSocket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char*)&m_nMaxPacketSize, &iLength) != 0)
			{
				AfxTrace(_T("Failed to get maximum packet size\n"));
				return false;
			}
			else
			{
				//CString str;
				//str.Format(_T("Maximum packet size: %lu"), m_nMaxPacketSize);
				//Log(str);
			}

			int iBufferSize = 1024 * 1024;
			if (setsockopt(m_hDataSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufferSize, sizeof(iBufferSize)) == 0)
			{
				int iOptLen = sizeof(iBufferSize);

				if (getsockopt(m_hDataSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufferSize, &iOptLen) == 0)
				{
					//CString str;
					//str.Format(_T("Send socket buffer size: %i"), iBufferSize);
					//Log(str);
				}
				else
					AfxTrace(_T("Failed to get send socket buffer size\n"));
			}
			else
				AfxTrace(_T("Failed to set send socket buffer size\n"));
		}
	}

	if (IS_EMPTY(strDestination) == false)
	{
		if (SetUDPRelayDestination(strDestination) == false)
			return false;
	}

	m_bEnableUDPRelay = TRUE;

	return true;
}

bool ExtIO_USRP::SetUDPRelayDestination(const CString& strDestination)
{
	if (strDestination.IsEmpty())
		return false;

	CString strData(strDestination);
	int iIndex = strData.Find(_T(':'));
	UINT nPort = BOR_PORT;
	if (iIndex > -1)
	{
		nPort = _tstoi(strData.Mid(iIndex + 1));
		strData = strData.Left(iIndex);
	}

	ULONG ulAddress = inet_addr(CStringA(strData));
	if (ulAddress == -1)
	{
		if (m_addrDest.sin_addr.S_un.S_addr == 0)
			DisableUDPRelay();

		return false;
	}
	else
	{
		CSingleLock lock(&m_csRelay, TRUE);

		m_addrDest.sin_addr.S_un.S_addr = ulAddress;
		m_addrDest.sin_port = htons(nPort);
	}

	m_strUDPRelayAddress = strDestination;

	return true;
}

void ExtIO_USRP::DisableUDPRelay(bool bKeepSetting /*= false*/)
{
	CSingleLock lock(&m_csRelay, TRUE);

	if (m_hDataSocket != INVALID_SOCKET)
	{
		closesocket(m_hDataSocket);	// FIXME: Use local var and do while unlocked
		m_hDataSocket = INVALID_SOCKET;
	}

	if (bKeepSetting == false)
		m_bEnableUDPRelay = FALSE;
}

DWORD ExtIO_USRP::Worker()
{
	WSABUF wsabuf;
	WSAOVERLAPPED wsaoverlapped;
	HANDLE hDataSent = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(hDataSent);
	if (hDataSent == NULL)
	{
		AfxTrace(_T("Failed to create data sent wait handle\n"));
		return -1;
	}

	////////////////////////////

	SetThreadPriority(GetCurrentThread(), /*THREAD_PRIORITY_HIGHEST*/THREAD_PRIORITY_TIME_CRITICAL);

	while (true)
	{
		DWORD dw = WaitForSingleObject(m_hEvent, 0);

		if (dw == WAIT_OBJECT_0)
		{
			AfxTrace(_T("Worker thread 0x%x received stop event\n"), GetCurrentThreadId());

			break;
		}

		int iSamplesRead = m_pUSRP->ReadPacket();

		if (iSamplesRead == -1)
		{
			{
				CSingleLock lock(&m_cs, TRUE);
				m_bError = true;
			}

			AfxTrace(_T("Failed to read packet\n"));

			Signal(CS_Stop);
			WaitForSingleObject(m_hEvent, INFINITE);	// 'Stop' callback will be called, so wait for it before exiting
			break;
		}
		else if (iSamplesRead != m_pUSRP->GetSamplesPerPacket())
		{
			if (iSamplesRead > 0)
			{
				AfxTrace(_T("Only read %lu samples of %lu (missing %lu)\n"), iSamplesRead, m_pUSRP->GetSamplesPerPacket(), (m_pUSRP->GetSamplesPerPacket() - iSamplesRead));
			}

			continue;
		}

		////////////////////////////

		CSingleLock lock(&m_cs, TRUE);

		if (m_pfnCallback)
			(m_pfnCallback)(m_pUSRP->GetSamplesPerPacket(), 0, 0, const_cast<short*>(m_pUSRP->GetBuffer()));

		lock.Unlock();

		////////////////////////////

		CSingleLock lockRelay(&m_csRelay, TRUE);

		if ((m_hDataSocket != INVALID_SOCKET) && (m_addrDest.sin_addr.S_un.S_addr != 0))
		{
			wsabuf.buf = (char*)m_pUSRP->GetBuffer();
			wsabuf.len = iSamplesRead * 2 * sizeof(short);

			ZERO_MEMORY(wsaoverlapped);
			wsaoverlapped.hEvent = hDataSent;

			DWORD dwSocketBytesSent = 0;
			int iResult = WSASendTo(m_hDataSocket, &wsabuf, 1, &dwSocketBytesSent, 0, (sockaddr*)&m_addrDest, sizeof(m_addrDest), &wsaoverlapped, NULL);	// FIXME: Unlock & use local var
			if (iResult == SOCKET_ERROR)
			{
				DWORD dw = WSAGetLastError();

				if (dw != WSA_IO_PENDING/*WSAEWOULDBLOCK*/)
				{
					{
						//CSingleLock lock(&m_cs, TRUE);
						//++m_nSocketErrors;
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
						//CSingleLock lock(&m_cs, TRUE);
						//++m_nBlockingErrors;
					}

					continue;
				}

				ASSERT(dwSocketFlags == 0);

				{
					//CSingleLock lock(&m_cs, TRUE);
					//++m_nPacketsSent;
					//++m_nBlockingSends;
				}
			}
			else if (iResult != 0)
			{
				{
					//CSingleLock lock(&m_cs, TRUE);
					//++m_nShortSends;
				}
			}
			else
			{
				{
					//CSingleLock lock(&m_cs, TRUE);
					//++m_nPacketsSent;
				}
			}
		}
		
		lockRelay.Unlock();
	}

	AfxTrace(_T("Worker thread 0x%x exiting\n"), GetCurrentThreadId());

	if (hDataSent)
		CloseHandle(hDataSent);

	return 0;
}
