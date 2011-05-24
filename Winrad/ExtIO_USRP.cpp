#include "StdAfx.h"
#include "ExtIO_USRP.h"

#include "dialogExtIO.h"
#include "socketClientWaitable.h"

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
{
	ZERO_MEMORY(m_lIFLimits);

	m_dSampleRate = 250000.0;
	m_dGain = 0.45;
	m_dFreq = 50000000.0;
}

ExtIO_USRP::~ExtIO_USRP()
{
	Destroy();
}

bool ExtIO_USRP::Init()
{
	LOAD_STRING(m_strDevice);
	LOAD_STRING(m_strAddress);

	if (m_hEvent == NULL)
	{
		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (m_hEvent == NULL)
			return false;
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

	/////////////////////////////////////

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

	if (m_strAddress.IsEmpty())
	{
		int iIndex = -1;
		CStringArray array;
		if (Teh::Utils::Tokenise(m_strDevice, array, _T(' ')))
			iIndex = _tstoi(array[0]);

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
		m_pDialog->_Log(_T("Creating remote device..."));

		RemoteUSRP* pUSRP = new RemoteUSRP(RUNTIME_CLASS(CsocketClientWaitable));
		pUSRP->SetRemoteAddress(m_strAddress);
		m_pUSRP = pUSRP;
	}

	///////////////////////////////////////////////////////////////////////////

	if (m_pUSRP->Create(m_strDevice) == false)
	{
		if (m_strDevice.IsEmpty() == false)
		{
			if (AfxMessageBox(_T("Failed to create USRP: ") + m_strDevice + _T("\n\nTry without device hint?"), MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				if (m_pUSRP->Create() == false)
				{
					AfxMessageBox(_T("Failed to create default USRP even without device hint"));

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
			AfxMessageBox(_T("Failed to create USRP without device hint"));

			SAFE_DELETE(m_pUSRP);
			return false;
		}
	}

	/////////////////////////////////////

	m_strSerial = m_pUSRP->GetName();

	m_pDialog->_Log(_T("Loading settings for: ") + m_strSerial);

	LOAD_INT(m_dFreq);
	LOAD_FLOAT(m_dGain);
	LOAD_STRING(m_strAntenna);
	LOAD_INT(m_dSampleRate);

	/////////////////////////////////////

	if (m_pUSRP->SetSampleRate(m_dSampleRate) <= 0)	// Must be called as GetHWSR will be called next
	{
		AfxMessageBox(_T("Failed to set initial sampling rate: ") + Teh::Utils::ToString(m_dSampleRate));

		return false;
	}

	m_pUSRP->SetDesiredGain(m_dGain);	// So UI gets correct value

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

	m_pDialog->_Log(_T("Saving settings for: ") + m_strSerial);

	ASSERT((m_strSerial.IsEmpty() == false) && (m_strSerial != SETTINGS_SECTION));

	CopyFrom(m_pUSRP);

	SAVE_INT(m_dFreq);
	SAVE_FLOAT(m_dGain);
	SAVE_STRING(m_strAntenna);
	SAVE_INT(m_dSampleRate);

	/////////////////////////////////////

	if (m_bError)
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
		return false;

	Signal(CS_HWSRChange);

	return true;
}

int ExtIO_USRP::SetLO(ULONG lFreq)
{
	m_dFreq = lFreq;

	if (m_pUSRP == NULL)
		return 1;	// Higher than possible

	if (m_pUSRP->SetFreq(lFreq) < 0)
		return 1;

	m_pDialog->_UpdateUI(CdialogExtIO::UF_TUNE_INFO);

	return m_pUSRP->WasTuneSuccessful(/*m_pUSRP->GetTuneResult()*/);	// Return 0 if the frequency is within the limits the HW can generate
}

void ExtIO_USRP::SetTunedFrequency(long lFreq)
{
	m_lTunedFreq = lFreq;

	//PostMessage
}

void ExtIO_USRP::SetIFLimits(long lLow, long lHigh)
{
	m_lIFLimits[LOW] = lLow;
	m_lIFLimits[HIGH] = lHigh;

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

	if (m_pUSRP->SetSampleRate(m_dSampleRate) <= 0)
		bResult = false;
	if (m_pUSRP->SetGain(m_dGain) == false)
		bResult = false;
	if (m_pUSRP->SetAntenna(m_strAntenna) == false)
		bResult = false;
	if (m_pUSRP->SetFreq(m_dFreq))	// Set here the frequency of the controlled hardware to LOfreq
		bResult = false;

	bool bError = false;
	if ((bResult == false) && (m_bError))
	{
		int iResult = AfxMessageBox(_T("Failed to set some USRP parameters.\nThis is probably due to your device being disconnected.\nMake sure it is connected before continuing!\n\nAbort:\tStop\nRetry:\tAttempt to re-create device (probably will not work if device link was broken)\nIgnore:\tContinue (expect things to break/hang)"), MB_ABORTRETRYIGNORE | MB_ICONWARNING | MB_DEFBUTTON2);
		if (iResult == IDABORT)
		{
			Signal(CS_Stop);
			return 0;
		}
		else if (iResult == IDRETRY)
		{
			m_pUSRP->Stop();

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
		}
		else
		{
			bError = true;
		}
	}

	m_pDialog->_UpdateUI();

	if (m_pUSRP->Start() == false)
	{
		Signal(CS_Stop);
		AfxMessageBox(_T("Failed to start USRP"));
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

	m_pUSRP->Stop();	// Wait for this to complete?
	//Sleep(500);

	if (m_hWorker)
	{
		SetEvent(m_hEvent);

		AfxTrace(_T("Waiting for termination of thread 0x%x...\n"), m_dwWorkerID);

		WaitForSingleObject(m_hWorker, INFINITE);

		CloseHandle(m_hWorker);
		m_hWorker = NULL;
	}

	m_dwWorkerID = 0;

	m_pDialog->_Log(_T("Stopped"));

	m_pDialog->_ToggleRunning(false);

	CopyFrom(m_pUSRP);
}

DWORD ExtIO_USRP::Worker()
{
	SetThreadPriority(GetCurrentThread(), /*THREAD_PRIORITY_HIGHEST*/THREAD_PRIORITY_TIME_CRITICAL);

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
				m_bError = true;
			}

			AfxTrace(_T("Failed to read packet\n"));

			Signal(CS_Stop);
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

		CSingleLock lock(&m_cs, TRUE);

		if (m_pfnCallback == NULL)
			continue;

		(m_pfnCallback)(m_pUSRP->GetSamplesPerPacket(), 0, 0, const_cast<short*>(m_pUSRP->GetBuffer()));
	}

	AfxTrace(_T("Worker thread exiting\n"));

	return 0;
}
