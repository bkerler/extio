// dialogMain.h : header file
//

#pragma once

#include "Server.h"
#include "afxwin.h"

// CdialogMain dialog
class CdialogMain : public CDialog, public ServerCallback
{
// Construction
public:
	CdialogMain(Server* pServer, CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_BORIP_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Server* m_pServer;
	CString m_strLastCommand;
	CString m_strClientAddress;
	UINT m_nClientPort;
public:
	CListBox m_cntrlList_Log;
public:
	int OnServerEvent(const EVENT& event);
	void _Log(const CString& str);
	void _UpdateUI();
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonReleaseDevice();
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnBnClickedCheckAutorun();
	BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
};
