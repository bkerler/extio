// dialogExtIO.cpp : implementation file
//

#include "stdafx.h"
#include "WinradUSRP.h"
#include "dialogExtIO.h"

#include "ExtIO_USRP.h"

#define REGISTRY_PROFILE_SECTION	_T("Settings")
#include <TehBase\TehAfxRegistryProfile.h>

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
END_MESSAGE_MAP()

// CdialogExtIO message handlers

BOOL CdialogExtIO::OnInitDialog()
{
	CDialog::OnInitDialog();

	//////////////////////////////////

	//m_cntrlSlider_Gain.SetRange(0, 100);

	SetDlgItemText(IDC_EDIT_DEVICE_HINT, m_pUSRP->GetDevice());

	SetDlgItemText(IDC_EDIT_REMOTE_ADDRESS, m_pUSRP->GetRemoteAddress());
	if (m_pUSRP->GetRemoteAddress().IsEmpty() == false)
		CheckDlgButton(IDC_CHECK_REMOTE, BST_CHECKED);

	_CreateUI();

	//////////////////////////////////

	EnableToolTips();

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
		return;

	m_cntrlCombo_Antenna.ResetContent();

	std::vector<std::string> array = pUSRP->GetAntennas();
	int iSelected = -1;
	for (std::vector<std::string>::iterator it = array.begin(); it != array.end(); ++it)
	{
		CStringA strA((*it).c_str());
		CString str(strA);

		int iIndex = m_cntrlCombo_Antenna.AddString(str);

		if (CString(pUSRP->GetAntenna()).CompareNoCase(str) == 0)
		{
			ASSERT(iSelected == -1);

			iSelected = iIndex;
		}
	}

	if (iSelected == -1)
		iSelected = 0;

	m_cntrlCombo_Antenna.SetCurSel(iSelected);

	////////////////////////////////////////

	m_cntrlCombo_SampleRate.ResetContent();

	iSelected = -1;
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

	if (pUSRP == NULL)
	{
		if (dwFlags & UF_WINDOW_TITLE)
			SetWindowText(_T("USRP"));

		return;
	}

	if (dwFlags & UF_WINDOW_TITLE)
		SetWindowText(CString(_T("USRP: ")) + pUSRP->GetName());

	////////////////////////////////////////

	CString str, strBuf;

	if (dwFlags & UF_GAIN_RANGE)
	{
		str.Format(_T("%.1f - %.1f"), pUSRP->GetGainRange().start(), pUSRP->GetGainRange().stop());
		SetDlgItemText(IDC_EDIT_GAIN_RANGE, str);
	}

	if (dwFlags & UF_GAIN_VALUE)
		SetDlgItemText(IDC_EDIT_GAIN_VALUE, Teh::Utils::ToString(m_pUSRP->GetGain()));

	if (dwFlags & UF_GAIN_SLIDER)
	{
		//double dGain = (100.0 * (m_pUSRP->GetGain() - pUSRP->GetGainRange().start())) / (pUSRP->GetGainRange().stop() - pUSRP->GetGainRange().start());
		double dGain = (m_pUSRP->GetGain() - pUSRP->GetGainRange().start()) / (pUSRP->GetGainRange().step());

		m_cntrlSlider_Gain.SetPos(CLAMP(m_cntrlSlider_Gain.GetRangeMin(), (int)dGain, m_cntrlSlider_Gain.GetRangeMax()));
	}

	if (dwFlags & UF_TUNE_INFO)
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

	if (dwFlags & UF_STATISTICS)
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
		m_pUSRP->SetRemoteAddress(NULL);
}

void CdialogExtIO::OnBnClickedCheckOffset()
{
	//IsDlgButtonChecked(IDC_CHECK_OFFSET)
}

void CdialogExtIO::OnEnChangeEditRemoteAddress()
{
	CString str;
	GetDlgItemText(IDC_EDIT_REMOTE_ADDRESS, str);
	m_pUSRP->SetRemoteAddress(str);
}
