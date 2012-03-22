#pragma once
#include "afxwin.h"

class CommandLineInfo : public CCommandLineInfo
{
public:
	CommandLineInfo();
	~CommandLineInfo();
public:
	void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
public:	// Options
	CString m_strDeviceHint;
	bool m_bDeviceSet;
	int m_iListenerPort;
	CTime m_timeDeviceReset;
private:
	enum NextExpectedParam
	{
		NEP_NONE,
		NEP_DEVICE_HINT,
		NEP_LISTENER_PORT,
		NEP_DEVICE_RESET_TIME
	};
	NextExpectedParam m_nextexpectedparam;
};
