// dialogExtIO.cpp : implementation file
//

#include "stdafx.h"
#include "WinradUSRP.h"
#include "dialogExtIO.h"

#include "ExtIO_USRP.h"
#include "MemoryUSRP.h"

#define REGISTRY_PROFILE_SECTION	_T("Settings")
#include <TehBase\TehAfxRegistryProfile.h>

#define IDM_ABOUTBOX                    0x0010

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
	afx_msg void OnBnClickedButtonWww();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_WWW, &CAboutDlg::OnBnClickedButtonWww)
END_MESSAGE_MAP()

// FIXME: Get version info from current file and append to About version text

///////////////////////////////////////////////////////////////////////////////
// CdialogExtIO dialog

IMPLEMENT_DYNAMIC(CdialogExtIO, CDialog)

CdialogExtIO::CdialogExtIO(ExtIO_USRP* pUSRP, CWnd* pParent /*=NULL*/)
	: CDialog(CdialogExtIO::IDD, pParent)
	, m_pUSRP(pUSRP)
{
	ASSERT(pUSRP);
}

CdialogExtIO::~CdialogExtIO()
{
}

void CdialogExtIO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_cntrlSlider_Gain);
	DDX_Control(pDX, IDC_COMBO_SAMPLE_RATE, m_cntrlCombo_SampleRate);
	DDX_Control(pDX, IDC_COMBO_ANTENNA, m_cntrlCombo_Antenna);
	DDX_Control(pDX, IDC_LIST_LOG, m_cntrlList_Log);
}

BEGIN_MESSAGE_MAP(CdialogExtIO, CDialog)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MIN_GAIN, &CdialogExtIO::OnBnClickedButtonMinGain)
	ON_BN_CLICKED(IDC_BUTTON_MAX_GAIN, &CdialogExtIO::OnBnClickedButtonMaxGain)
	ON_BN_CLICKED(IDC_BUTTON_MID_GAIN, &CdialogExtIO::OnBnClickedButtonMidGain)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_DEVICE, &CdialogExtIO::OnBnClickedButtonCreateDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_ANTENNA, &CdialogExtIO::OnCbnSelchangeComboAntenna)
	ON_CBN_SELCHANGE(IDC_COMBO_SAMPLE_RATE, &CdialogExtIO::OnCbnSelchangeComboSampleRate)
	ON_BN_CLICKED(IDC_BUTTON_SET_SAMPLE_RATE, &CdialogExtIO::OnBnClickedButtonSetSampleRate)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFF, OnToolTipNotify)
	ON_CBN_EDITCHANGE(IDC_COMBO_SAMPLE_RATE, &CdialogExtIO::OnCbnEditchangeComboSampleRate)
	ON_BN_CLICKED(IDC_CHECK_REMOTE, &CdialogExtIO::OnBnClickedCheckRemote)
	ON_BN_CLICKED(IDC_CHECK_OFFSET, &CdialogExtIO::OnBnClickedCheckOffset)
	ON_EN_CHANGE(IDC_EDIT_REMOTE_ADDRESS, &CdialogExtIO::OnEnChangeEditRemoteAddress)
	ON_BN_CLICKED(IDC_CHECK_RELAY_TO_UDP_SOURCE, &CdialogExtIO::OnBnClickedCheckRelayToUdpSource)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_RELAY_XMLRPC, &CdialogExtIO::OnBnClickedCheckEnableRelayXmlrpc)
	ON_EN_CHANGE(IDC_EDIT_OFFSET, &CdialogExtIO::OnEnChangeEditOffset)
	ON_BN_CLICKED(IDC_BUTTON_SET_UDP_SOURCE_DESTINATION, &CdialogExtIO::OnBnClickedButtonSetUdpSourceDestination)
	ON_BN_CLICKED(IDC_BUTTON_SET_XMLRPC_IF_PORT, &CdialogExtIO::OnBnClickedButtonSetXmlrpcIfPort)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CdialogExtIO::OnBnClickedButtonAbout)
END_MESSAGE_MAP()

// CdialogExtIO message handlers
/*
void PASCAL _myFilterToolTipMessage(MSG* pMsg, CWnd* pWnd)
{
	((CdialogExtIO*)pWnd)->myFilterToolTipMessage(pMsg);
}
*//*
typedef struct tagAFX_OLDTOOLINFO {
	UINT cbSize;
	UINT uFlags;
	HWND hwnd;
	UINT uId;
	RECT rect;
	HINSTANCE hinst;
	LPTSTR lpszText;
	LPARAM lParam;
} AFX_OLDTOOLINFO;
*//*
static WNDPROC _myOldEditProc;

static LRESULT CALLBACK _myEditProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
//	AfxTrace(_T("Remote address: %08x %04x %08x %08x [%i 0x%08x]\n"), hWnd, nMsg, wParam, lParam, _bInside.GetData()->i, AfxGetThread());

	MSG msg;
	msg.hwnd = hWnd;
	msg.message = nMsg;
	msg.wParam = wParam;
	msg.lParam = lParam;

//if (nMsg == 0x0200)
//	nMsg = 0x0200;
//else if (nMsg == 0x20)
//	nMsg = 0x20;
//if (AfxGetThread())
//	nMsg = nMsg;

	PTMRC* pPTMRC = _ptmrc.GetData();

	if (pPTMRC->RefIncCount() == 1)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		msg.pt = CPoint(::GetMessagePos());
		msg.time = ::GetMessageTime();

		if (AfxInternalPreTranslateMessage(&msg))
		{
			pPTMRC->RefDecCount();
			return 0;
		}

		//HWND hParent = GetParent(hWnd);
		//CdialogExtIO* p = (CdialogExtIO*)CWnd::FromHandlePermanent(hParent);
		//p->myFilterToolTipMessage(&msg);
	}

	pPTMRC->RefDecCount();	// Must be done before so _AfxWndProcDllStatic manages static module state once more

	return CallWindowProc(_myOldEditProc, hWnd, nMsg, wParam, lParam);
}
*/
static WNDPROC _GetOldProc(HWND hWnd)
{
	HWND hParent = GetParent(hWnd);
	CdialogExtIO* p = (CdialogExtIO*)CWnd::FromHandlePermanent(hParent);
	CdialogExtIO::SUBCLASSINFO& info = p->m_mapSubclasses[hWnd];
	return info.pfnWndProc;
}

static LRESULT CALLBACK _PTMProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	MSG msg;
	msg.hwnd = hWnd;
	msg.message = nMsg;
	msg.wParam = wParam;
	msg.lParam = lParam;

	PTMRC* pPTMRC = _ptmrc.GetData();

	WNDPROC pOld = NULL;

	if (pPTMRC->RefIncCount() == 1)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		msg.pt = CPoint(::GetMessagePos());
		msg.time = ::GetMessageTime();

		/*if (AfxInternalPreTranslateMessage(&msg))	// Can't do full PTM because key strokes become doubled-up in text boxes
		{
			pPTMRC->RefDecCount();
			return 0;
		}*/

		HWND hParent = GetParent(hWnd);
		CdialogExtIO* p = (CdialogExtIO*)CWnd::FromHandlePermanent(hParent);
		p->FilterToolTipMessage(&msg);

		pOld = _GetOldProc(hWnd);
	}
	else
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		pOld = _GetOldProc(hWnd);
	}

	pPTMRC->RefDecCount();	// Must be done before so _AfxWndProcDllStatic manages static module state once more

	ASSERT(pOld);
	return CallWindowProc(pOld, hWnd, nMsg, wParam, lParam);
}

BOOL CdialogExtIO::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	//////////////////////////////////

	//m_cntrlSlider_Gain.SetRange(0, 100);

	SetDlgItemText(IDC_EDIT_DEVICE_HINT, m_pUSRP->GetDevice());

	SetDlgItemText(IDC_EDIT_REMOTE_ADDRESS, m_pUSRP->GetRemoteAddress());
	//if (m_pUSRP->GetRemoteAddress().IsEmpty() == false)
	if (m_pUSRP->IsUsingRemoteDevice())
		CheckDlgButton(IDC_CHECK_REMOTE, BST_CHECKED);

	_CreateUI();

	//////////////////////////////////

	static UINT nIDs[] = {
		//IDC_COMBO_ANTENNA,
		//IDC_COMBO_SAMPLE_RATE,
		IDC_EDIT_REMOTE_ADDRESS,
		IDC_EDIT_DEVICE_HINT,
		IDC_EDIT_OFFSET,
		IDC_CHECK_REMOTE,
		IDC_CHECK_OFFSET,
		IDC_BUTTON_CREATE_DEVICE,
		IDC_BUTTON_SET_SAMPLE_RATE,
		// These only started working after group box was deleted, then restored (change in Z-order affects parent relationship?)
		IDC_CHECK_RELAY_TO_UDP_SOURCE,
		IDC_CHECK_ENABLE_RELAY_XMLRPC,
		IDC_BUTTON_SET_UDP_SOURCE_DESTINATION,
		IDC_BUTTON_SET_XMLRPC_IF_PORT,
		IDC_EDIT_UDP_SOURCE_DESTINATION,
		IDC_EDIT_XMLRPC_IF_PORT
	};

	for (int i = 0; i < (sizeof(nIDs) / sizeof(nIDs[0])); ++i)
	{
		HWND hWnd = GetDlgItem(nIDs[i])->GetSafeHwnd();
		ASSERT(hWnd);
		WNDPROC pOld = (WNDPROC)::GetWindowLongPtr(hWnd, GWLP_WNDPROC);
		ASSERT(pOld);
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)_PTMProc);
		SUBCLASSINFO info = { hWnd, pOld };
		m_mapSubclasses[hWnd] = info;
	}

	//_myOldEditProc = (WNDPROC)::GetWindowLongPtr(GetDlgItem(IDC_EDIT_REMOTE_ADDRESS)->GetSafeHwnd(), GWLP_WNDPROC);
	//::SetWindowLongPtr(GetDlgItem(IDC_EDIT_REMOTE_ADDRESS)->GetSafeHwnd(), GWLP_WNDPROC, (LONG_PTR)_myEditProc);

	EnableToolTips();

/*	{
		BOOL bEnable = TRUE; UINT nFlag = WF_TOOLTIPS;

		ASSERT(nFlag == WF_TOOLTIPS || nFlag == WF_TRACKINGTOOLTIPS);

		AFX_MODULE_THREAD_STATE* pModuleThreadState = AfxGetModuleThreadState();
		CToolTipCtrl* pToolTip = pModuleThreadState->m_pToolTip;

		if (!bEnable)
		{
			// nothing to do if tooltips not enabled
			if (!(m_nFlags & nFlag))
				return TRUE;

			// cancel tooltip if this window is active
			if (pModuleThreadState->m_pLastHit == this)
				CancelToolTips(TRUE);

			// remove "dead-area" toolbar
			if (pToolTip->GetSafeHwnd() != NULL)
			{
				TOOLINFO ti; memset(&ti, 0, sizeof(TOOLINFO));
				ti.cbSize = sizeof(AFX_OLDTOOLINFO);
				ti.uFlags = TTF_IDISHWND;
				ti.hwnd = m_hWnd;
				ti.uId = (UINT_PTR)m_hWnd;
				pToolTip->SendMessage(TTM_DELTOOL, 0, (LPARAM)&ti);
			}

			// success
			m_nFlags &= ~nFlag;
			return TRUE;
		}

		// if already enabled for tooltips, nothing to do
		if (!(m_nFlags & nFlag))
		{
			// success
			AFX_MODULE_STATE* pModuleState = _AFX_CMDTARGET_GETSTATE();
			pModuleState->m_pfnFilterToolTipMessage = _myFilterToolTipMessage;
			m_nFlags |= nFlag;
		}
	}
*/
	CRect rectWindow;
	ZERO_MEMORY(rectWindow);
	LOAD_BINARY(rectWindow);
	if (rectWindow.IsRectNull() == FALSE)
		SetWindowPos(NULL, rectWindow.left, rectWindow.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CdialogExtIO::_CreateUI()
{
	IUSRP* pUSRP = m_pUSRP->GetUSRP();
	if (pUSRP == NULL)
	{
		_UpdateUI(UF_RELAY);
		return;
	}

	m_cntrlCombo_Antenna.ResetContent();

	std::vector<std::string> array = pUSRP->GetAntennas();
	if (array.empty())
	{
		_Log(_T("Antenna list is empty - is your daughterboard loose?"));
	}
	else
	{
		int iSelected = -1;
		for (std::vector<std::string>::iterator it = array.begin(); it != array.end(); ++it)
		{
			CStringA strA((*it).c_str());
			CString str(strA);

			int iIndex = m_cntrlCombo_Antenna.AddString(str);

			if (pUSRP->GetAntenna().CompareNoCase(str) == 0)
			{
				ASSERT(iSelected == -1);

				iSelected = iIndex;
			}
		}

		if (iSelected == -1)
		{
			_Log(_T("Selected antenna not found in antenna list: \"") + pUSRP->GetAntenna() + "\"");

			iSelected = 0;
		}

		m_cntrlCombo_Antenna.SetCurSel(iSelected);
	}

	////////////////////////////////////////

	m_cntrlCombo_SampleRate.ResetContent();

	int iSelected = -1;
	for (int i = 4, j = 0; i <= 256; i *= 2, ++j)
	{
		double d = (pUSRP->GetMasterClock() / (double)i);

		if (pUSRP->GetSampleRate() == d)
			iSelected = j;

		double dMSPS = d / 1000000.0;
		CString str;
		str.Format(_T("%.3f"), dMSPS, i);	// (d%i)

		int iIndex = m_cntrlCombo_SampleRate.AddString(str);
		m_cntrlCombo_SampleRate.SetItemData(iIndex, (DWORD_PTR)i);
	}

	if (iSelected == -1)
	{
		double d = pUSRP->GetSampleRate() / 1000000.0;
		CString str;
		str.Format(_T("%f"), d);
		m_cntrlCombo_SampleRate.SetWindowText(str);
	}
	else
	{
		m_cntrlCombo_SampleRate.SetCurSel(iSelected);
	}

	////////////////////////////////////////

	double dSteps = (pUSRP->GetGainRange().stop() - pUSRP->GetGainRange().start()) / pUSRP->GetGainRange().step();
	int iSteps = ((int)dSteps);
	AfxTrace(_T("Gain steps: %i\n"), iSteps);

	m_cntrlSlider_Gain.SetRange(0, iSteps);

	////////////////////////////////////////

	_UpdateUI();
}

static CString FormatFrequency(double dFreq)
{
	LPCTSTR strUnits = _T("Hz");
	double dMul = 1.0;

	double dF = fabs(dFreq);

	if (dF >= 1e9)
	{
		strUnits = _T("GHz");
		dMul = 1e9;
	}
	else if (dF >= 1e6)
	{
		strUnits = _T("MHz");
		dMul = 1e6;
	}
	else if (dF >= 1e3)
	{
		strUnits = _T("kHz");
		dMul = 1e3;
	}

	double d = dFreq / dMul;

	CString str;
	str.Format(_T("%f %s"), d, strUnits);
	return str;
}

void CdialogExtIO::_UpdateUI(DWORD dwFlags /*= UF_ALL*/)
{
	IUSRP* pUSRP = m_pUSRP->GetUSRP();

	if (dwFlags & UF_WINDOW_TITLE)
	{
		if (pUSRP)
		{
			if (CAN_CAST(pUSRP, MemoryUSRP))
				SetWindowText(_T("Playback"));
			else
			{
				CString strName(pUSRP->GetName());
				if (strName.IsEmpty())
					strName = _T("(no name)");
				SetWindowText(CString(_T("USRP: ")) + strName);
			}
		}
		else
			SetWindowText(_T("USRP"));
	}

	////////////////////////////////////////

	CString str, strBuf;

	if ((pUSRP) && (dwFlags & UF_GAIN_RANGE))
	{
		str.Format(_T("%.1f - %.1f"), pUSRP->GetGainRange().start(), pUSRP->GetGainRange().stop());
		SetDlgItemText(IDC_EDIT_GAIN_RANGE, str);
	}

	if ((pUSRP) && (dwFlags & UF_GAIN_VALUE))
		SetDlgItemText(IDC_EDIT_GAIN_VALUE, Teh::Utils::ToString(m_pUSRP->GetGain()));

	if ((pUSRP) && (dwFlags & UF_GAIN_SLIDER))
	{
		//double dGain = (100.0 * (m_pUSRP->GetGain() - pUSRP->GetGainRange().start())) / (pUSRP->GetGainRange().stop() - pUSRP->GetGainRange().start());
		double dGain = (m_pUSRP->GetGain() - pUSRP->GetGainRange().start()) / (pUSRP->GetGainRange().step());

		m_cntrlSlider_Gain.SetPos(CLAMP(m_cntrlSlider_Gain.GetRangeMin(), (int)dGain, m_cntrlSlider_Gain.GetRangeMax()));
	}

	if ((pUSRP) && (dwFlags & UF_TUNE_INFO))
	{
		strBuf.Empty();

		int iResult = pUSRP->WasTuneSuccessful();
		str.Format(_T("Req:\t\t%s"), FormatFrequency(pUSRP->GetDesiredFreq()));
		strBuf += str;

		if (iResult != 0)
		{
			strBuf += CString(_T(" (too ")) + ((iResult < 0) ? _T("low") : _T("high")) + _T(")");
		}

		str.Format(_T("\nH/W:\t\t%s\nTarget LO:\t%s\nActual LO:\t%s\nTarget DDC:\t%s\nActual DDC:\t%s"),
			FormatFrequency(pUSRP->GetFreq()),
			FormatFrequency(pUSRP->GetTuneResult().target_inter_freq),
			FormatFrequency(pUSRP->GetTuneResult().actual_inter_freq),
			FormatFrequency(pUSRP->GetTuneResult().target_dsp_freq),
			FormatFrequency(pUSRP->GetTuneResult().actual_dsp_freq));
		strBuf += str;

		strBuf.Replace(_T("\n"), _T("\r\n"));
		SetDlgItemText(IDC_EDIT_TUNE_INFO, strBuf);
	}

	if ((pUSRP) && (dwFlags & UF_STATISTICS))
	{
		str.Format(_T("Master:\t\t%s\nSamples/packet:\t%lu\nSamples:\t\t%I64i (%lu overflows)"),
			FormatFrequency(pUSRP->GetMasterClock()),
			pUSRP->GetSamplesPerPacket(),
			pUSRP->GetSamplesReceived(),
			pUSRP->GetOverflows());

		strBuf = pUSRP->GetExtraInfo();
		if (strBuf.IsEmpty() == false)
			str += _T("\n") + strBuf;

		str.Replace(_T("\n"), _T("\r\n"));
		SetDlgItemText(IDC_EDIT_STATISTICS, str);
	}

	if (dwFlags & UF_RELAY)
	{
		CheckDlgButton(IDC_CHECK_RELAY_TO_UDP_SOURCE, (m_pUSRP->IsUDPRelayEnabled() ? BST_CHECKED : BST_UNCHECKED));
		CheckDlgButton(IDC_CHECK_ENABLE_RELAY_XMLRPC, (m_pUSRP->IsXMLRPCIFEnabled() ? BST_CHECKED : BST_UNCHECKED));

		SetDlgItemText(IDC_EDIT_UDP_SOURCE_DESTINATION, m_pUSRP->GetUDPRelayAddress());
		SetDlgItemInt(IDC_EDIT_XMLRPC_IF_PORT, m_pUSRP->GetXMLRPCIFPort());
	}

	if ((pUSRP) && (dwFlags & UF_OFFSET))
	{
		CheckDlgButton(IDC_CHECK_OFFSET, (m_pUSRP->IsOffset() ? BST_CHECKED : BST_UNCHECKED));

		SetDlgItemInt(IDC_EDIT_OFFSET, m_pUSRP->GetOffset());
	}
}

BOOL CdialogExtIO::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
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

void CdialogExtIO::OnDestroy()
{
	CRect rectWindow;
	GetWindowRect(&rectWindow);
	SAVE_BINARY(rectWindow);

	CDialog::OnDestroy();
}

void CdialogExtIO::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == (CScrollBar*)&m_cntrlSlider_Gain)
	{
		int iPos = m_cntrlSlider_Gain.GetPos();

		_SetGain((double)iPos/* / 100.0*/, true);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CdialogExtIO::_ToggleRunning(bool bRunning)
{
	if (bRunning)
	{
		_UpdateUI(UF_STATISTICS);

		SetTimer(0, 500, NULL);
	}
	else
	{
		KillTimer(0);
	}
}

void CdialogExtIO::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
		_UpdateUI(UF_STATISTICS);

	CDialog::OnTimer(nIDEvent);
}

void CdialogExtIO::OnBnClickedButtonMinGain()
{
	_SetGain(0.0);
}

void CdialogExtIO::OnBnClickedButtonMaxGain()
{
	_SetGain(1.0);
}

void CdialogExtIO::OnBnClickedButtonMidGain()
{
	_SetGain(0.5);
}

void CdialogExtIO::_SetGain(double dGain, bool bFromSlider /*= false*/)
{
	IUSRP* pUSRP = m_pUSRP->GetUSRP();

	if (pUSRP == NULL)
		return;

	if (bFromSlider)
		dGain = pUSRP->GetGainRange().start() + (dGain * pUSRP->GetGainRange().step());
	else
		dGain = pUSRP->GetGainRange().start() + (dGain * (pUSRP->GetGainRange().stop() - pUSRP->GetGainRange().start()));

	pUSRP->SetGain(dGain);

	_UpdateUI((UF_ALL & ~(bFromSlider ? UF_GAIN_SLIDER : 0)));
}

void CdialogExtIO::OnBnClickedButtonCreateDevice()
{
	GetDlgItem(IDC_BUTTON_CREATE_DEVICE)->EnableWindow(FALSE);

	m_pUSRP->Close();

	CString str;
	GetDlgItemText(IDC_EDIT_DEVICE_HINT, str);

	m_pUSRP->Open(str);

	GetDlgItem(IDC_BUTTON_CREATE_DEVICE)->EnableWindow();
}

void CdialogExtIO::OnCbnSelchangeComboAntenna()
{
	IUSRP* pUSRP = m_pUSRP->GetUSRP();

	if (pUSRP == NULL)
		return;

	//m_cntrlCombo_Antenna.GetCurSel();

	CString str;
	m_cntrlCombo_Antenna.GetWindowText(str);

	pUSRP->SetAntenna(str);
}

void CdialogExtIO::OnCbnSelchangeComboSampleRate()
{
	GetDlgItem(IDC_BUTTON_SET_SAMPLE_RATE)->EnableWindow(FALSE);

	IUSRP* pUSRP = m_pUSRP->GetUSRP();

	if (pUSRP == NULL)
		return;

	int iIndex = m_cntrlCombo_SampleRate.GetCurSel();
	if (iIndex == -1)
		return;

	int i = (int)m_cntrlCombo_SampleRate.GetItemData(iIndex);
	if (i < 0)
		return;

	double d = (pUSRP->GetMasterClock() / (double)i);

	if (m_pUSRP->SetSampleRate(d) == false)
	{
		AfxMessageBox(_T("Failed to set sample rate"));
	}
}

void CdialogExtIO::OnBnClickedButtonSetSampleRate()
{
	CString str;
	m_cntrlCombo_SampleRate.GetWindowText(str);
	
	double d =_tstof(str);
	if (d == 0.0)
	{
		GetDlgItem(IDC_BUTTON_SET_SAMPLE_RATE)->EnableWindow(FALSE);
		AfxMessageBox(_T("Invalid sample rate"));
		return;
	}

	d *= 1000000.0;

	if (m_pUSRP->SetSampleRate(d) == false)
	{
		AfxMessageBox(_T("Failed to set sample rate"));
	}
}

void CdialogExtIO::OnCbnEditchangeComboSampleRate()
{
	GetDlgItem(IDC_BUTTON_SET_SAMPLE_RATE)->EnableWindow();
}

void CdialogExtIO::_Log(const CString& str)
{
	int iIndex = m_cntrlList_Log.AddString(str);	// FIXME: Time stamp
	m_cntrlList_Log.SetCurSel(iIndex);
}

void CdialogExtIO::OnBnClickedCheckRemote()
{
	CString str;
	GetDlgItemText(IDC_EDIT_REMOTE_ADDRESS, str);

	if (IsDlgButtonChecked(IDC_CHECK_REMOTE))
	{
		if (str.IsEmpty())
		{
			//CheckDlgButton(IDC_CHECK_REMOTE, BST_UNCHECKED);
		}
		else
		{
			m_pUSRP->SetRemoteAddress(str);
		}
	}
	else
	{
		//m_pUSRP->SetRemoteAddress(NULL);
		m_pUSRP->UseRemoveDevice(false);
	}
}

void CdialogExtIO::OnBnClickedCheckOffset()
{
	if (IsDlgButtonChecked(IDC_CHECK_OFFSET))
	{
		BOOL bTrans;
		int iOffset = (int)GetDlgItemInt(IDC_EDIT_OFFSET, &bTrans);
		/*if (bTrans == FALSE)
		{
			CheckDlgButton(IDC_CHECK_OFFSET, BST_UNCHECKED);
			AfxMessageBox(_T("Enter a valid offset"));
			return;
		}*/

		m_pUSRP->SetOffset(iOffset);
		m_pUSRP->UseOffset(true);
	}
	else
	{
		m_pUSRP->UseOffset(false);
	}
}

void CdialogExtIO::OnEnChangeEditOffset()
{
	if (IsDlgButtonChecked(IDC_CHECK_OFFSET))
	{
		BOOL bTrans;
		int iOffset = (int)GetDlgItemInt(IDC_EDIT_OFFSET, &bTrans);
		/*if (bTrans == FALSE)
		{
			CheckDlgButton(IDC_CHECK_OFFSET, BST_UNCHECKED);
			AfxMessageBox(_T("Enter a valid offset"));
			return;
		}*/

		m_pUSRP->SetOffset(iOffset);
		m_pUSRP->UseOffset(true);
	}
}

void CdialogExtIO::OnEnChangeEditRemoteAddress()
{
	if (IsDlgButtonChecked(IDC_CHECK_REMOTE))
	{
		CString str;
		GetDlgItemText(IDC_EDIT_REMOTE_ADDRESS, str);
		m_pUSRP->SetRemoteAddress(str);
	}
}

void CdialogExtIO::OnBnClickedCheckRelayToUdpSource()
{
	if (IsDlgButtonChecked(IDC_CHECK_RELAY_TO_UDP_SOURCE))
	{
		CString strDestination;
		GetDlgItemText(IDC_EDIT_UDP_SOURCE_DESTINATION, strDestination);
		if (strDestination.IsEmpty() == false)
		{
			if (m_pUSRP->EnableUDPRelay(strDestination))
				_Log(_T("Enabled relay"));
			else
				AfxMessageBox(_T("Failed to enable relay"));
		}
		else
		{
			CheckDlgButton(IDC_CHECK_RELAY_TO_UDP_SOURCE, BST_UNCHECKED);
			AfxMessageBox(_T("Cannot enable relay without destination"));
		}
	}
	else
	{
		m_pUSRP->DisableUDPRelay();
		_Log(_T("Disabled relay"));
	}
}

void CdialogExtIO::OnBnClickedCheckEnableRelayXmlrpc()
{
	if (IsDlgButtonChecked(IDC_CHECK_ENABLE_RELAY_XMLRPC))
	{
		if (m_pUSRP->IsUDPRelayEnabled() == false)
		{
			CheckDlgButton(IDC_CHECK_ENABLE_RELAY_XMLRPC, BST_UNCHECKED);
			AfxMessageBox(_T("Enable UDP relay first"));
			return;
		}

		BOOL bTrans;
		int iPort = (int)GetDlgItemInt(IDC_EDIT_XMLRPC_IF_PORT, &bTrans, FALSE);
		if (iPort <= 0)
		{
			CheckDlgButton(IDC_CHECK_ENABLE_RELAY_XMLRPC, BST_UNCHECKED);
			AfxMessageBox(_T("Invalid port"));
			return;
		}

		if (m_pUSRP->EnableXMLRPCIF(iPort))
			_Log(_T("Enabled XMLRPC IF"));
		else
			AfxMessageBox(_T("Failed to enable XML-RPC IF"));
	}
	else
	{
		m_pUSRP->DisableXMLRPCIF();
		_Log(_T("Disabled XML-RPC IF"));
	}
}

void CdialogExtIO::OnBnClickedButtonSetUdpSourceDestination()
{
	CString str;
	GetDlgItemText(IDC_EDIT_UDP_SOURCE_DESTINATION, str);
	if (m_pUSRP->SetUDPRelayDestination(str) == false)
	{
		AfxMessageBox(_T("Failed to set UDP Source destination"));
		_UpdateUI(UF_RELAY);
	}
}

void CdialogExtIO::OnBnClickedButtonSetXmlrpcIfPort()
{
	BOOL bTrans;
	int iPort = (int)GetDlgItemInt(IDC_EDIT_XMLRPC_IF_PORT, &bTrans, FALSE);
	if (iPort <= 0)
	{
		AfxMessageBox(_T("Invalid port"));
		_UpdateUI(UF_RELAY);
		return;
	}

	if (m_pUSRP->SetXMLRPCIFPort(iPort) == false)
	{
		AfxMessageBox(_T("Failed to set XML-RPC IF port"));
		_UpdateUI(UF_RELAY);
	}
}
/*
BOOL CdialogExtIO::PreTranslateMessage(MSG* pMsg)
{
	//FilterToolTipMessage(pMsg);

//	AfxTrace(_T("CdialogExtIO::PreTranslateMessage hWnd=%08x nMsg=%04x\n"), pMsg->hwnd, pMsg->message);
//#define WM_MOUSEMOVE                    0x0200
//#define WM_SETCURSOR                    0x0020
	return CDialog::PreTranslateMessage(pMsg);
}
*//*
LRESULT CdialogExtIO::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
//	MSG msg;

//	msg.message = message;
//	msg.lParam = lParam;
//	msg.wParam = wParam;

//	msg.hwnd = GetSafeHwnd();
//	msg.time = GetTickCount();
//	GetCursorPos(&msg.pt);
//AfxTrace(_T("MSG: %lu\n"), message);
//	FilterToolTipMessage(&msg);
//	//if (PreTranslateMessage(&msg));
	//	return 0;

	return CDialog::WindowProc(message, wParam, lParam);
}
*//*
static HWND AFXAPI _myAfxChildWindowFromPoint(HWND hWnd, POINT pt)
{
	ASSERT(hWnd != NULL);

	// check child windows
	::ClientToScreen(hWnd, &pt);
	HWND hWndChild = ::GetWindow(hWnd, GW_CHILD);

	static int i = 0;
	AfxTrace(_T("[%08i] Checking "), i++);

	for (; hWndChild != NULL; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
	{
		int i = ::GetDlgCtrlID(hWndChild);
		//if (i == 3016)
		//{
		//	LONG l = ::GetWindowLong(hWndChild, GWL_STYLE);
		//	l = 0;
		//}

		if (::GetDlgCtrlID(hWndChild) != (WORD)-1 &&
			(::GetWindowLong(hWndChild, GWL_STYLE) & WS_VISIBLE))
		{
			if (i == 3016)
			{
				i=i;
			}
			// see if point hits the child window
			CRect rect;
			::GetWindowRect(hWndChild, rect);
			if (rect.PtInRect(pt))
			{
				TCHAR str[1024];
				GetWindowText(hWndChild, str, 1024);
				AfxTrace(_T("Hit: %s\n"), str);
				return hWndChild;
			}
		}
	}

	AfxTrace(_T("\n"));

	return NULL;    // not found
}
*//*
INT_PTR CdialogExtIO::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// find child window which hits the point
	// (don't use WindowFromPoint, because it ignores disabled windows)
	HWND hWndChild = _myAfxChildWindowFromPoint(m_hWnd, point);
	if (hWndChild != NULL)
	{
		// return positive hit if control ID isn't -1
		INT_PTR nHit = ::GetDlgCtrlID(hWndChild);

		// hits against child windows always center the tip
		if (pTI != NULL && pTI->cbSize >= sizeof(AFX_OLDTOOLINFO))
		{
			// setup the TOOLINFO structure
			pTI->hwnd = m_hWnd;
			pTI->uId = (UINT_PTR)hWndChild;
			pTI->uFlags |= TTF_IDISHWND;
			pTI->lpszText = LPSTR_TEXTCALLBACK;

			// set TTF_NOTBUTTON and TTF_CENTERTIP if it isn't a button
			if (!(::SendMessage(hWndChild, WM_GETDLGCODE, 0, 0) & DLGC_BUTTON))
				pTI->uFlags |= TTF_NOTBUTTON|TTF_CENTERTIP;
		}
		return nHit;
	}
	return -1;  // not found
}
*//*
AFX_STATIC void AFXAPI _AfxRelayToolTipMessage(CToolTipCtrl* pToolTip, MSG* pMsg)
{
	// transate the message based on TTM_WINDOWFROMPOINT
	MSG msg = *pMsg;
	msg.hwnd = (HWND)pToolTip->SendMessage(TTM_WINDOWFROMPOINT, 0, (LPARAM)&msg.pt);
	CPoint pt = pMsg->pt;
	if (msg.message >= WM_MOUSEFIRST && msg.message <= AFX_WM_MOUSELAST)
		::ScreenToClient(msg.hwnd, &pt);
	msg.lParam = MAKELONG(pt.x, pt.y);

	// relay mouse event before deleting old tool
	pToolTip->SendMessage(TTM_RELAYEVENT, 0, (LPARAM)&msg);
}

#define WM_SYSKEYFIRST  WM_SYSKEYDOWN
#define WM_SYSKEYLAST   WM_SYSDEADCHAR

void CdialogExtIO::myFilterToolTipMessage(MSG* pMsg)
{
	// this CWnd has tooltips enabled
	UINT message = pMsg->message;
	if ((message == WM_MOUSEMOVE || message == WM_NCMOUSEMOVE ||
		 message == WM_LBUTTONUP || message == WM_RBUTTONUP ||
		 message == WM_MBUTTONUP) &&
		(GetKeyState(VK_LBUTTON) >= 0 && GetKeyState(VK_RBUTTON) >= 0 &&
		 GetKeyState(VK_MBUTTON) >= 0))
	{
		AFX_MODULE_THREAD_STATE* pModuleThreadState = AfxGetModuleThreadState();
AfxTrace(_T("[%08i] Filtering hWnd=%08x msg=%04x\n"), pMsg->time, pMsg->hwnd, pMsg->message);
		// make sure that tooltips are not already being handled
		CWnd* pWnd = CWnd::FromHandle(pMsg->hwnd);
		while (pWnd != NULL && !(pWnd->m_nFlags & (WF_TOOLTIPS|WF_TRACKINGTOOLTIPS)))
		{
			pWnd = pWnd->GetParent();
		}
		if (pWnd != this)
		{
			CString strThis, strWnd;
			this->GetWindowText(strThis);
			if (pWnd)
				pWnd->GetWindowText(strWnd);
			AfxTrace(_T("Windows un-equal: this = %08x (%s), pWnd = %08x (%s)\n"), this->GetSafeHwnd(), strThis, pWnd->GetSafeHwnd(), strWnd);
			if (pWnd == NULL)
			{
				// tooltips not enabled on this CWnd, clear last state data
				pModuleThreadState->m_pLastHit = NULL;
				pModuleThreadState->m_nLastHit = static_cast<INT_PTR>(-1);
			}
			return;
		}

		CToolTipCtrl* pToolTip = pModuleThreadState->m_pToolTip;
		CWnd* pOwner = GetParentOwner();
		if (pToolTip != NULL && pToolTip->GetOwner() != pOwner)
		{
			pToolTip->DestroyWindow();
			delete pToolTip;
			pModuleThreadState->m_pToolTip = NULL;
			pToolTip = NULL;
		}
		if (pToolTip == NULL)
		{
			pToolTip = new CToolTipCtrl;
			if (!pToolTip->Create(pOwner, TTS_ALWAYSTIP))
			{
				delete pToolTip;
				return;
			}
			pToolTip->SendMessage(TTM_ACTIVATE, FALSE);
			pModuleThreadState->m_pToolTip = pToolTip;
		}

		ASSERT_VALID(pToolTip);
		ASSERT(::IsWindow(pToolTip->m_hWnd));

		TOOLINFO ti; memset(&ti, 0, sizeof(TOOLINFO));

		// determine which tool was hit
		CPoint point = pMsg->pt;
		::ScreenToClient(m_hWnd, &point);
		TOOLINFO tiHit; memset(&tiHit, 0, sizeof(TOOLINFO));
		tiHit.cbSize = sizeof(AFX_OLDTOOLINFO);
		INT_PTR nHit = OnToolHitTest(point, &tiHit);

		// build new toolinfo and if different than current, register it
		CWnd* pHitWnd = nHit == -1 ? NULL : this;
		if (pModuleThreadState->m_nLastHit != nHit || pModuleThreadState->m_pLastHit != pHitWnd)
		{
			if (nHit != -1)
			{
				// add new tool and activate the tip
				ti = tiHit;
				ti.uFlags &= ~(TTF_NOTBUTTON|TTF_ALWAYSTIP);
				if (m_nFlags & WF_TRACKINGTOOLTIPS)
					ti.uFlags |= TTF_TRACK;
				VERIFY(pToolTip->SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti));
				if ((tiHit.uFlags & TTF_ALWAYSTIP) || IsTopParentActive())
				{
					// allow the tooltip to popup when it should
					pToolTip->SendMessage(TTM_ACTIVATE, TRUE);
					if (m_nFlags & WF_TRACKINGTOOLTIPS)
						pToolTip->SendMessage(TTM_TRACKACTIVATE, TRUE, (LPARAM)&ti);

					// bring the tooltip window above other popup windows
					::SetWindowPos(pToolTip->m_hWnd, HWND_TOP, 0, 0, 0, 0,
						SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);
				}
			}
			else
			{
				pToolTip->SendMessage(TTM_ACTIVATE, FALSE);
			}

			// relay mouse event before deleting old tool
			_AfxRelayToolTipMessage(pToolTip, pMsg);

			// now safe to delete the old tool
			if (pModuleThreadState->m_pLastInfo != NULL &&
					pModuleThreadState->m_pLastInfo->cbSize >= sizeof(AFX_OLDTOOLINFO))
				pToolTip->SendMessage(TTM_DELTOOL, 0, (LPARAM)pModuleThreadState->m_pLastInfo);

			pModuleThreadState->m_pLastHit = pHitWnd;
			pModuleThreadState->m_nLastHit = nHit;
			if (pModuleThreadState->m_pLastInfo == NULL)
			{
				pModuleThreadState->m_pLastInfo = new TOOLINFO;
				memset(pModuleThreadState->m_pLastInfo, 0, sizeof(TOOLINFO));
			}
			*pModuleThreadState->m_pLastInfo = tiHit;
		}
		else
		{
			if (m_nFlags & WF_TRACKINGTOOLTIPS)
			{
				POINT pt;

				::GetCursorPos( &pt );
				pToolTip->SendMessage(TTM_TRACKPOSITION, 0, MAKELPARAM(pt.x, pt.y));
			}
			else
			{
				// relay mouse events through the tooltip
				if (nHit != -1)
					_AfxRelayToolTipMessage(pToolTip, pMsg);
			}
		}

		if ((tiHit.lpszText != LPSTR_TEXTCALLBACK) && (tiHit.hinst == 0))
			free(tiHit.lpszText);
	}
	else if (m_nFlags & (WF_TOOLTIPS|WF_TRACKINGTOOLTIPS))
	{
		// make sure that tooltips are not already being handled
		CWnd* pWnd = CWnd::FromHandle(pMsg->hwnd);
		while (pWnd != NULL && pWnd != this && !(pWnd->m_nFlags & (WF_TOOLTIPS|WF_TRACKINGTOOLTIPS)))
			pWnd = pWnd->GetParent();
		if (pWnd != this)
			return;

		BOOL bKeys = (message >= WM_KEYFIRST && message <= WM_KEYLAST) ||
			(message >= WM_SYSKEYFIRST && message <= WM_SYSKEYLAST);
		if ((m_nFlags & WF_TRACKINGTOOLTIPS) == 0 &&
			(bKeys ||
			 (message == WM_LBUTTONDOWN || message == WM_LBUTTONDBLCLK) ||
			 (message == WM_RBUTTONDOWN || message == WM_RBUTTONDBLCLK) ||
			 (message == WM_MBUTTONDOWN || message == WM_MBUTTONDBLCLK) ||
			 (message == WM_NCLBUTTONDOWN || message == WM_NCLBUTTONDBLCLK) ||
			 (message == WM_NCRBUTTONDOWN || message == WM_NCRBUTTONDBLCLK) ||
			 (message == WM_NCMBUTTONDOWN || message == WM_NCMBUTTONDBLCLK)))
		{
			CWnd::CancelToolTips(bKeys);
		}
	}
}
*/
void CdialogExtIO::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAboutDlg::OnBnClickedButtonWww()
{
	ShellExecute(NULL, _T("open"), _T("http://spench.net/r/ExtIO_USRP"), NULL, NULL, SW_SHOW);
}

void CdialogExtIO::OnBnClickedButtonAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
