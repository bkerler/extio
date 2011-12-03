// WinradUSRP.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinradUSRP.h"

#include "ExtIO_USRP.h"
#include "dialogExtIO.h"
#include "MemoryUSRP.h"

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

//static AFX_MODULE_STATE* _pStatic;
//static WNDPROC _pWndProc;
/*
LRESULT CALLBACK
myAfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	// special message which identifies the window as using AfxWndProc
	if (nMsg == WM_QUERYAFXWNDPROC)
		return 1;

	// all other messages route through message map
	CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
	ASSERT(pWnd != NULL);					
	ASSERT(pWnd==NULL || pWnd->m_hWnd == hWnd);
	if (pWnd == NULL || pWnd->m_hWnd != hWnd)
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
	return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}
*//*
bool operator < (const MSG& m1, const MSG& m2)
{
	if (m1.hwnd < m2.hwnd)
		return true;
	else if (m1.hwnd > m2.hwnd)
		return false;
	// Same hwnd
	if (m1.message < m2.message)
		return true;
	else if (m1.message > m2.message)
		return false;
	// Same message
	if (m1.wParam < m2.wParam)
		return true;
	else if (m1.wParam > m2.wParam)
		return false;
	// Same wParam
	if (m1.lParam < m2.lParam)
		return true;
	else if (m1.lParam > m2.lParam)
		return false;
	// Same lParam
	return false;
}
*/
LRESULT CALLBACK _AfxWndProcDllStatic(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	PTMRC* pRC = _ptmrc.GetData();

/*	if (pRC->RefGetCount() > 0)
	{
		AfxTrace(_T("Thread %04x already inside %i [hWnd=%08x, nMsg=%04x]\n"), GetCurrentThreadId(), _bInside.GetData()->i, hWnd, nMsg);
		return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
	}
*/
	Teh::ScopeRefDec<PTMRC> _rc(pRC);

	//AFX_MANAGE_STATE(&afxModuleState);
	//AFX_MANAGE_STATE(AfxGetStaticModuleState()/*_pStatic*/);
	AFX_MAINTAIN_STATE2* _ctlState = NULL;
	AFX_MODULE_STATE* pStaticState = AfxGetStaticModuleState();
	//ASSERT(pStaticState == _pStatic);
	if (pRC->RefGetCount() == 1)
	{
		//AfxTrace(_T("{MAINTAIN STATE}\n"));
//		ASSERT(_bInside.GetData()->pre.empty());
		_AfxInitManaged();
		_ctlState = new AFX_MAINTAIN_STATE2(pStaticState/*_pStatic*/);
	}

	AFX_MODULE_STATE* pState = AfxGetModuleState();
//	ASSERT(pState == pStaticState);	// Not true when getting here via Edit callback
//	pState->m_pfnAfxWndProc = _pWndProc;	// This approach doesn't appear to work (plus, for _AFXDLL it's a static global so not thread-safe)

	MSG msg;
	msg.hwnd = hWnd;
	msg.message = nMsg;
	msg.wParam = wParam;
	msg.lParam = lParam;

/*	if (_bInside.GetData()->pre.find(msg) != _bInside.GetData()->pre.end())
	{
		AfxTrace(_T("[%08lu] SKIP Pre-translate: thread %04x hWnd=%08x, nMsg=%04x\n"), _bInside.GetData()->n, GetCurrentThreadId(), hWnd, nMsg);
		goto skip_pre;
	}
*/
	if (pRC->RefGetCount() == 1)
	{
		//if (hWnd)	// Could be thread message
		{
//			_bInside.GetData()->n++;

//			_bInside.GetData()->pre.insert(msg);

			MSG msg2 = msg;
			msg2.pt = CPoint(::GetMessagePos());
			msg2.time = ::GetMessageTime();

			//AfxTrace(_T("<"));
//			AfxTrace(_T("[%08lu] Pre-translate: thread %04x hWnd=%08x, nMsg=%04x lParam=%08x wParam=%08x\n"), _bInside.GetData()->n, GetCurrentThreadId(), hWnd, nMsg, wParam, lParam);
			BOOL b = FALSE;
			b = AfxPreTranslateMessage(&msg2);
			//AfxTrace(_T(">\n"));

//			_bInside.GetData()->pre.erase(msg);

			if (b)
			{
//				pState->m_pfnAfxWndProc = _AfxWndProcDllStatic;
//				_bInside.GetData()->i--;
				//if (_ctlState)
				//	AfxTrace(_T("{MAINTAIN %05i}\n"), _bInside.GetData()->i);
				SAFE_DELETE(_ctlState);
				return 0;
			}
		}
	}
//skip_pre:
	//pState->m_pfnAfxWndProc = _pWndProc;
#undef AfxWndProc
	LRESULT l = AfxWndProc/*(_pWndProc)*//*myAfxWndProc*/(hWnd, nMsg, wParam, lParam);

//	pState->m_pfnAfxWndProc = _AfxWndProcDllStatic;

	//if (_ctlState)
	//	AfxTrace(_T("{MAINTAIN %05i}\n"), _bInside.GetData()->i);
	SAFE_DELETE(_ctlState);
//	pRC->RefDecCount();
	return l;
}

CWinradUSRPApp::CWinradUSRPApp()
	: m_pUSRP(NULL)
	//, m_pDialog(NULL)
	//, m_iLO(50000000)
	, m_bPlayback(false)
{
	//_pStatic = AfxGetStaticModuleState();

	AFX_MODULE_STATE* pState = AfxGetModuleState();
	//_pWndProc = pState->m_pfnAfxWndProc;
	pState->m_pfnAfxWndProc = _AfxWndProcDllStatic;
}

CWinradUSRPApp::~CWinradUSRPApp()
{
	//ASSERT(m_pUSRP == NULL);

	_Close(true);
}

bool CWinradUSRPApp::_Open()
{
	_Close(true);

	m_pUSRP = new ExtIO_USRP();

	if (m_pUSRP->Init() == false)
		return false;

	return true;
}

void CWinradUSRPApp::_Close(bool bAll /*= false*/)
{
	if (m_pUSRP)
	{
		m_pUSRP->Destroy();
	}

	SAFE_DELETE(m_pUSRP);

	m_bPlayback = false;

	if (bAll == false)
	{
		AfxTrace(_T("Creating playback interface...\n"));

		m_pUSRP = new ExtIO_USRP();

		if (m_pUSRP->Init() == false)
		{
			m_pUSRP->Destroy();
			SAFE_DELETE(m_pUSRP);
			return;
		}

		m_pUSRP->Playback();

		m_bPlayback = true;
	}
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

	m_memPlayback.AllocateMemory(512 * 2 * sizeof(short));	// RawDataReady processes in 512-sample chunks

	return TRUE;
}

int CWinradUSRPApp::ExitInstance()
{
	//ASSERT(m_pUSRP == NULL);

	_Close(true);

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

		if (theApp._IsPlayingBack())
			theApp._Close(true);

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
	if (theApp._GetUSRP() == NULL)
	{
		ASSERT(FALSE);
		return false;
	}

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
__declspec(dllexport) void __stdcall RawDataReady(long samprate, int *Ldata, int *Rdata, int numsamples)	// Pre-process raw data
{
	ExtIO_USRP* pUSRP = theApp._GetUSRP();

	if ((pUSRP == NULL) || (theApp._IsPlayingBack() == false) || (pUSRP->IsUDPRelayEnabled() == false))
	{
		return;
	}

	UINT nSize = 2 * sizeof(short) * numsamples;

	if ((int)nSize <= 0)
		return;

	MemoryUSRP* pMU = dynamic_cast<MemoryUSRP*>(pUSRP->GetUSRP());
	if (pMU == NULL)	// FIXME: Was playing back, then created remote connection, then Start
		return;

	Teh::MemoryContainer& mem = theApp._GetPlaybackMemory();

	if (mem.GetMemoryLength() != nSize)
	{
		if (mem.GetMemoryPointer() == NULL)
			mem.AllocateMemory(nSize);	// Shouldn't happen because it's pre-allocated on Init
		else
			mem.ReallocateMemory(nSize);
	}

	//LPBYTE pDest = mem.GetMemoryPointer();
	PSHORT pDest = (PSHORT)mem.GetMemoryPointer();
	ASSERT(pDest);

	//AfxTrace(_T("RawDataReady: %i samples\n"), numsamples);

	for (int i = 0; i < numsamples; ++i)	// Although int data is 24-bits (first 8 is 0), last 8 seems to be sign extension
	{
		//memcpy(pDest, ((LPBYTE)(Ldata + i)) + 1, sizeof(short));
		//pDest += sizeof(short);
		int L = (*(Ldata + i) >> 8);
		BYTE bL = (((BYTE)(L >> 12) & 0x0F) - 2) & 0x0F;
		pDest[2*i+0] = (USHORT)((L & 0x00000FFF) | (bL << 12));

		//memcpy(pDest, ((LPBYTE)(Rdata + i)) + 1, sizeof(short));
		//pDest += sizeof(short);
		int R = (*(Rdata + i) >> 8);
		BYTE bR = (((BYTE)(R >> 12) & 0x0F) - 2) & 0x0F;
		pDest[2*i+1] = (USHORT)((R & 0x00000FFF) | (bR << 12));
	}

	pMU->SubmitSamples(mem.GetMemoryPointer(), nSize);
}
