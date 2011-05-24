#pragma once

class CdialogWait;

// CthreadWait

class CthreadWait : public CWinThread
{
friend class CdialogWait;
DECLARE_DYNCREATE(CthreadWait)
protected:
	CthreadWait();           // protected constructor used by dynamic creation
	virtual ~CthreadWait();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	static CthreadWait* _Create(HANDLE hEvent, HWND hWnd = NULL, LPCTSTR strMessage = NULL);
private:
	HANDLE m_hEvent;
	HWND m_hWnd;
	CString m_strMessage;
	CdialogWait* m_pDialog;
public:
	void _Close();
	//inline HANDLE _GetEvent() const
	//{ return m_hEvent; }
protected:
	DECLARE_MESSAGE_MAP()
};
