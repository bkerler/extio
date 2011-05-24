// WinradUSRP.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinradUSRP.h"

#include "ExtIO_USRP.h"
#include "dialogExtIO.h"

typedef std::complex<float> complex;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CWinradUSRPApp

BEGIN_MESSAGE_MAP(CWinradUSRPApp, CWinApp)
END_MESSAGE_MAP()

// CWinradUSRPApp construction

CWinradUSRPApp::CWinradUSRPApp()
	: m_pUSRP(NULL)
	//, m_pDialog(NULL)
	//, m_iLO(50000000)
{
}

CWinradUSRPApp::~CWinradUSRPApp()
{
	ASSERT(m_pUSRP == NULL);

	_Close();
}

bool CWinradUSRPApp::_Open()
{
	_Close();

	m_pUSRP = new ExtIO_USRP();

	if (m_pUSRP->Init() == false)
		return false;

	return true;
}

void CWinradUSRPApp::_Close()
{
	if (m_pUSRP)
	{
		m_pUSRP->Destroy();
	}

	SAFE_DELETE(m_pUSRP);
}

// The one and only CWinradUSRPApp object

CWinradUSRPApp theApp;

// CWinradUSRPApp initialization

BOOL CWinradUSRPApp::InitInstance()
{
	/*INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES | ICC_LINK_CLASS;
	if (InitCommonControlsEx(&InitCtrls) == FALSE)
	{
		AfxTrace(_T("Failed to initialise common controls\n"));
	}*/

	CWinApp::InitInstance();

	//////////////////////////////////////////////////////////

	HANDLE hProcess = GetCurrentProcess();
	//TCHAR strModule[MAX_PATH]
	CString strModule;
	DWORD dwResult = GetModuleBaseName(hProcess, NULL, strModule.GetBuffer(MAX_PATH), MAX_PATH);
	strModule.ReleaseBuffer();

	LPCTSTR strKey = _T("Baz's Appz");
	if (dwResult)
	{
		strModule = strModule.MakeLower();

		if (strModule.Find(_T("winrad")) != -1)
			strKey = _T("Winrad15");
		else if (strModule.Find(_T("hdsdr")) != -1)
			strKey = _T("HDSDR");
		else if (strModule.Find(_T("wrplus")) != -1)
			strKey = _T("WRplus");
	}

	SetRegistryKey(strKey);

	//////////////////////////////////////////////////////////

	WSADATA wsa;
	ZERO_MEMORY(wsa);
	if (!AfxSocketInit(&wsa))
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxTrace(_T("Maximum UDP size: %hu\n"), wsa.iMaxUdpDg);

	return TRUE;
}

int CWinradUSRPApp::ExitInstance()
{
	ASSERT(m_pUSRP == NULL);

	_Close();

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////////

/*
	* Option to enable transverter frequency offset
*/

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) bool __stdcall InitHW(char *name, char *model, int& type)
{
	AfxTrace(_T("Initialising...\n"));

	type = 3;	// H/W type

	_tcscpy_s(name, 16, "USRP");

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if (theApp._GetUSRP() == NULL)
		{
			if (theApp._Open() == false)
				return false;

			ASSERT(theApp._GetUSRP());
		}

		CStringA strModel/*(theApp._GetUSRP()->GetSerial())*/;	// Cannot get serial/model as device isn't opened yet
		_tcscpy_s(model, 16, strModel);
	}

	AfxTrace(_T("Initialised.\n"));

	return true;
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) bool __stdcall OpenHW(void)
{
	AfxTrace(_T("Opening...\n"));

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		if (theApp._GetUSRP()->TryOpen() == false)
		{
			//return false;

			AfxTrace(_T("Failed to open - waiting for user involvement...\n"));

			return true;
		}
	}

	AfxTrace(_T("Opened.\n"));

	return true;
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) int __stdcall StartHW(long LOfreq)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return 1;	// Sensible value (avoid divide-by-zero)
	}

	AfxTrace(_T("Starting... (LO: %i)\n"), LOfreq);

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		int nSampleRate = theApp._GetUSRP()->Start();
		if (nSampleRate == 0)
			return 1;

		return nSampleRate;
	}
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) void __stdcall StopHW(void)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	AfxTrace(_T("Stopping...\n"));

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		theApp._GetUSRP()->Stop();
	}
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) void __stdcall CloseHW(void)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	AfxTrace(_T("Closing...\n"));

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		theApp._Close();
	}

	AfxTrace(_T("Closed.\n"));
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) int __stdcall GetStatus(void)
{
	ASSERT(FALSE);

	return 0;	// Not actually called
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) int __stdcall SetHWLO(long freq)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return 1;	// Higher than possible
	}

	ULONG ulFreq = (ULONG)freq;

	//AfxTrace(_T("Setting HW LO: %i\n"), freq);

	int iResult = 0;

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		iResult = theApp._GetUSRP()->SetLO(ulFreq);
	}

	return iResult;
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) long __stdcall GetHWLO(void)	// Called after Set
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return 0;
	}

	//AfxTrace(_T("Getting HW LO...\n"));

	//return theApp.m_iLO;

	long lResult = 0;

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		lResult = (long)theApp._GetUSRP()->GetFreq();
	}

	return lResult;
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) void __stdcall TuneChanged(long freq)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	//AfxTrace(_T("Tune changed: %i\n"), freq);	// Do whatever you want with the information about the new frequency tuned by the user

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		theApp._GetUSRP()->SetTunedFrequency(freq);
	}
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) long __stdcall GetHWSR(void)
{
	if ((theApp._GetUSRP() == NULL)/* || (theApp._GetUSRP()->GetUSRP() == NULL)*/)
	{
		ASSERT(FALSE);
		return 48000;	// Sensible default
	}

	//AfxTrace(_T("Getting HW sample rate...\n"));	// Only happens once automatically at beginning

	//return /*250000*/(long)m_pUSRP->m_desired_sample_rate;	// 64M / decim (min = 250k)

	return (long)theApp._GetUSRP()/*->GetUSRP()*/->GetSampleRate();
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) void __stdcall IFLimitsChanged(long low, long high)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	//AfxTrace(_T("IF limits changed: %i - %i\n"), low, high);	// Do whatever you want with the information about the new limits of the spectrum/waterfall window

	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		theApp._GetUSRP()->SetIFLimits(low, high);
	}
}

//---------------------------------------------------------------------------

extern "C"
__declspec(dllexport) void __stdcall SetCallback(ExtIO_USRP::FnCallback Callback)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	theApp._GetUSRP()->SetCallback(Callback);
}

extern "C"
__declspec(dllexport) void __stdcall ShowGUI(void)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	AfxTrace(_T("Showing GUI...\n"));
	
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CDialog* pDialog = theApp._GetUSRP()->GetDialog();

		if (pDialog)
		{
			pDialog->ShowWindow(SW_SHOW);
			pDialog->SetForegroundWindow();
		}
	}
}

extern "C"
__declspec(dllexport) void __stdcall HideGUI(void)
{
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return;
	}

	AfxTrace(_T("Hiding GUI...\n"));
	
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CDialog* pDialog = theApp._GetUSRP()->GetDialog();

		if (pDialog)
		{
			pDialog->ShowWindow(SW_HIDE);
		}
	}
}

extern "C"
__declspec(dllexport) void __stdcall RawDataReady(long samprate, int *Ldata, int *Rdata, int numsamples)
{
	// Pre-process raw data
}
