
// BorIP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BorIPApp.h"
#include "dialogMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CappMain

BEGIN_MESSAGE_MAP(CappMain, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CappMain construction

CappMain::CappMain()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CappMain object

CappMain theApp;

// CappMain initialization

BOOL CappMain::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Baz's Appz"));

	ParseCommandLine(m_cli);

	CdialogMain dlg(&m_server);

	INT_PTR nResponse = IDCANCEL;

	if (dlg.Create(CdialogMain::IDD) == FALSE)
		return FALSE;

	m_pMainWnd = &dlg;

	if (m_server.Initialise(&dlg, m_cli.m_iListenerPort) == false)
	{
		AfxMessageBox(_T("Failed to initialise server"));
	}
	else
	{
		if (m_cli.m_timeDeviceReset.GetTime() != 0)
			m_server.SetResetTime(&m_cli.m_timeDeviceReset);

		if (m_cli.m_bDeviceSet)
			m_server.CreateDevice(m_cli.m_strDeviceHint);

		nResponse = dlg./*DoModal*/RunModalLoop();
	}

	dlg.DestroyWindow();
	
	/*if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}*/

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
