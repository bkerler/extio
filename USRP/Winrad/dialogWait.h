#pragma once

class CthreadWait;

// CdialogWait dialog

class CdialogWait : public CDialog
{
DECLARE_DYNAMIC(CdialogWait)
public:
	CdialogWait(CthreadWait* pThread, CWnd* pParent = NULL);   // standard constructor
	virtual ~CdialogWait();
// Dialog Data
	enum { IDD = IDD_DIALOG_WAIT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
private:
	CthreadWait* m_pThread;
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
