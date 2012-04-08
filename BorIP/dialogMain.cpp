/* (C) 2011-2012 by Balint Seeber <balint256@gmail.com>
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*&*/

// dialogMain.cpp : implementation file
//

#include "stdafx.h"
#include "BorIPApp.h"
#include "dialogMain.h"

#include "USRP.h"

#define AUTORUN_REGISTRY_KEY	_T("BorIP")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslinkWww(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_WWW, &CAboutDlg::OnNMClickSyslinkWww)
END_MESSAGE_MAP()

// FIXME: Get version info from current file and append to About version text

///////////////////////////////////////////////////////////////////////////////
// CdialogMain dialog

CdialogMain::CdialogMain(Server* pServer, CWnd* pParent /*=NULL*/)
	: CDialog(CdialogMain::IDD, pParent)
	, m_pServer(pServer)
	, m_nClientPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_cntrlList_Log);
}

BEGIN_MESSAGE_MAP(CdialogMain, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RELEASE_DEVICE, &CdialogMain::OnBnClickedButtonReleaseDevice)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CdialogMain::OnBnClickedButtonAbout)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipNotify)
	ON_BN_CLICKED(IDC_CHECK_AUTORUN, &CdialogMain::OnBnClickedCheckAutorun)
END_MESSAGE_MAP()

// CdialogMain message handlers

BOOL CdialogMain::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableToolTips();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->InsertMenu(0, MF_BYPOSITION | MF_SEPARATOR);
			pSysMenu->InsertMenu(0, MF_BYPOSITION | MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	_UpdateUI();

	CRegKey keyAutoRun;
	if (keyAutoRun.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), KEY_QUERY_VALUE) == ERROR_SUCCESS)
	{
		CString str;
		ULONG ul = 1024;
		LONG l = keyAutoRun.QueryStringValue(AUTORUN_REGISTRY_KEY, str.GetBuffer(ul), &ul);
		str.ReleaseBuffer();
		if ((l == ERROR_SUCCESS) && (str.IsEmpty() == false))
			CheckDlgButton(IDC_CHECK_AUTORUN, BST_CHECKED);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CdialogMain::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CdialogMain::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CdialogMain::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CdialogMain::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXT);

	TOOLTIPTEXT* pTTT = (TOOLTIPTEXT*)pNMHDR;
	UINT_PTR nID = pNMHDR->idFrom;

	if (pTTT->uFlags & TTF_IDISHWND)
		nID = ::GetDlgCtrlID((HWND)nID);	// idFrom is actually the HWND of the tool

	CString strTipText;

	if (nID != 0) // will be zero on a separator
	{
		if (strTipText.LoadString(nID) == FALSE)
			return FALSE;
		if (strTipText.GetLength() > _countof(pTTT->szText))
			strTipText = strTipText.Left(_countof(pTTT->szText) - 1);
		//strTipText.Format(_T("Control ID = %d"), nID);
	}

	_tcscpy_s(pTTT->szText, _countof(pTTT->szText), strTipText);

//	pTTT->uFlags &= ~TTF_CENTERTIP;

	*pResult = 0;

	return TRUE;
}

void CdialogMain::OnDestroy()
{
	m_pServer->SetCallback(NULL);

	CDialog::OnDestroy();
}

void CdialogMain::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		_UpdateUI();
	}
	else if (nIDEvent == 1)
	{
		m_pServer->RunPeriodicTasks();
	}

	CDialog::OnTimer(nIDEvent);
}

void CdialogMain::_UpdateUI()
{
	GetDlgItem(IDC_BUTTON_RELEASE_DEVICE)->EnableWindow(I2B(m_pServer->m_pUSRP));

	CString str;

	{
		CString strBuf((m_pServer->m_pUSRP ? m_pServer->m_pUSRP->GetName() : _T("(none)")));

		CSingleLock lock(&m_pServer->m_cs, TRUE);

		str.Format(
			_T("Device:\t\t%s\n")

			_T("Client:\t\t%s:%lu\n")
			_T("Command:\t%s\n")

			_T("Read failures:\t%lu\n")
			_T("Short reads:\t%lu\n")
			_T("Overrun:\t\t%lu\n")
			_T("Blocking errors:\t%lu\n")
			_T("Blocking waits:\t%lu\n")
			_T("Socket errors:\t%lu\n")
			_T("Short sends:\t%lu\n")
			_T("Packets received:\t%lu\n")
			_T("Packets sent:\t%lu\n")
			_T("Blocking sends:\t%lu\n")
			,

			strBuf,

			m_strClientAddress, m_nClientPort,
			m_strLastCommand,

			m_pServer->m_nReadFailures,
			m_pServer->m_nShortReads,
			m_pServer->m_nOverruns,
			m_pServer->m_nBlockingErrors,
			m_pServer->m_nBlockingWaits,
			m_pServer->m_nSocketErrors,
			m_pServer->m_nShortSends,
			m_pServer->m_nPacketsReceived,
			m_pServer->m_nPacketsSent,
			m_pServer->m_nBlockingSends
		);
	}

	str.Replace(_T("\n"), _T("\r\n"));
	SetDlgItemText(IDC_EDIT_INFO, str);

	UpdateWindow();
}

int CdialogMain::OnServerEvent(const EVENT& event)
{
	switch (event.code)
	{
		case ServerCallback::EC_LOG:
			_Log(event.message);
			break;
		case ServerCallback::EC_CREATED:
			_UpdateUI();
			SetTimer(1, 1000, NULL);
			break;
		case ServerCallback::EC_CLOSED:
			_UpdateUI();
			KillTimer(1);
			break;
		case ServerCallback::EC_CONNECTED:
			m_pServer->m_pClient->GetPeerName(m_strClientAddress, m_nClientPort);
			_UpdateUI();
			break;
		case ServerCallback::EC_DISCONNECTED:
			m_strClientAddress.Empty();
			m_nClientPort = 0;
			m_strLastCommand.Empty();
			_UpdateUI();
			break;
		case ServerCallback::EC_START:
			_UpdateUI();
			SetTimer(0, 500, NULL);
			break;
		case ServerCallback::EC_STOP:
			KillTimer(0);
			_UpdateUI();
			break;
		case ServerCallback::EC_COMMAND:
			m_strLastCommand = event.message;
			_UpdateUI();
			break;
	}

	return 0;
}

void CdialogMain::_Log(const CString& str)
{
	int iIndex = m_cntrlList_Log.AddString(str);
	m_cntrlList_Log.SetCurSel(iIndex);
}

void CdialogMain::OnBnClickedButtonReleaseDevice()
{
	m_pServer->CloseDevice();
}

void CAboutDlg::OnNMClickSyslinkWww(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(NULL, _T("open"), _T("http://spench.net/r/BorIP"), NULL, NULL, SW_SHOW);

	*pResult = 0;
}

void CdialogMain::OnBnClickedButtonAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CdialogMain::OnBnClickedCheckAutorun()
{
	CRegKey keyAutoRun;
	if (keyAutoRun.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), STANDARD_RIGHTS_WRITE | KEY_SET_VALUE) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("Could not open AutoRun registry key"), MB_ICONERROR);
		return;
	}

	if (IsDlgButtonChecked(IDC_CHECK_AUTORUN))
	{
		CString str;

		DWORD dw = GetModuleFileName(NULL, str.GetBuffer(MAX_PATH), MAX_PATH);
		str.ReleaseBuffer();
		if (dw == 0)
		{
			AfxMessageBox(_T("Failed to get process path"), MB_ICONERROR);
			return;
		}

		str = _T("\"") + str + _T("\" /autorun");

		if (keyAutoRun.SetStringValue(AUTORUN_REGISTRY_KEY, str) != ERROR_SUCCESS)
			AfxMessageBox(_T("Could not open AutoRun registry key"), MB_ICONERROR);
	}
	else
	{
		LONG l = keyAutoRun.DeleteValue(AUTORUN_REGISTRY_KEY);
		if ((l != ERROR_SUCCESS) && (l != ERROR_FILE_NOT_FOUND))
			AfxMessageBox(_T("Failed to delete AutoRun key"), MB_ICONERROR);
	}
}
