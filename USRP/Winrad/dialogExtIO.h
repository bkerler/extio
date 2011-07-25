#pragma once

#include "afxcmn.h"
#include "Resource.h"
#include "afxwin.h"

class ExtIO_USRP;

// CdialogExtIO dialog

class CdialogExtIO : public CDialog
{
DECLARE_DYNAMIC(CdialogExtIO)
public:
	CdialogExtIO(ExtIO_USRP* pUSRP, CWnd* pParent = NULL);   // standard constructor
	virtual ~CdialogExtIO();
// Dialog Data
	enum { IDD = IDD_DIALOG_EXTIO };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	ExtIO_USRP* m_pUSRP;
private:
	CComboBox m_cntrlCombo_SampleRate;
	CComboBox m_cntrlCombo_Antenna;
	CListBox m_cntrlList_Log;
private:
	typedef struct SubclassInfo
	{
		HWND hWnd;
		WNDPROC pfnWndProc;
	} SUBCLASSINFO;
	std::map<HWND,SUBCLASSINFO> m_mapSubclasses;
	friend WNDPROC _GetOldProc(HWND hWnd);
public:
	enum UpdateFlags
	{
		UF_ALL = -1,
		UF_GAIN_SLIDER	= 0x0001,
		UF_WINDOW_TITLE	= 0x0002,
		UF_GAIN_RANGE	= 0x0004,
		UF_GAIN_VALUE	= 0x0008,
		UF_TUNE_INFO	= 0x0010,
		UF_STATISTICS	= 0x0020,
		UF_RELAY		= 0x0040,
		UF_OFFSET		= 0x0080,
	};
public:
	void _CreateUI();
	void _UpdateUI(DWORD dwFlags = UF_ALL);
	void _SetGain(double dGain, bool bFromSlider = false);
	void _ToggleRunning(bool bRunning);
	void _Log(const CString& str);
//public:
	//void myFilterToolTipMessage(MSG* pMsg);
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
//protected:
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
public:
	virtual BOOL OnInitDialog();
public:
	CSliderCtrl m_cntrlSlider_Gain;
public:
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonMinGain();
	afx_msg void OnBnClickedButtonMaxGain();
	afx_msg void OnBnClickedButtonMidGain();
	afx_msg void OnBnClickedButtonCreateDevice();
	afx_msg void OnCbnSelchangeComboAntenna();
	afx_msg void OnCbnSelchangeComboSampleRate();
	afx_msg void OnBnClickedButtonSetSampleRate();
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnEditchangeComboSampleRate();
	afx_msg void OnBnClickedCheckRemote();
	afx_msg void OnBnClickedCheckOffset();
	afx_msg void OnEnChangeEditRemoteAddress();
	afx_msg void OnBnClickedCheckRelayToUdpSource();
	afx_msg void OnBnClickedCheckEnableRelayXmlrpc();
	afx_msg void OnEnChangeEditOffset();	
	afx_msg void OnBnClickedButtonSetUdpSourceDestination();
	afx_msg void OnBnClickedButtonSetXmlrpcIfPort();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBnClickedButtonAbout();
};
