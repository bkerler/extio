#include "StdAfx.h"
#include "CommandLineInfo.h"

CommandLineInfo::CommandLineInfo()
	: m_nextexpectedparam(NEP_NONE)
	, m_bDeviceSet(false)
	, m_iListenerPort(0)
{
}

CommandLineInfo::~CommandLineInfo()
{
}

void CommandLineInfo::ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
	CString strParam(pszParam);

	if (bFlag)
	{
		if (strParam == _T("device"))
		{
			m_bDeviceSet = true;
			m_nextexpectedparam = NEP_DEVICE_HINT;
		}
		else if (strParam == _T("port"))
			m_nextexpectedparam = NEP_LISTENER_PORT;
		else
		{
			m_nextexpectedparam = NEP_NONE;

			CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
		}
	}
	else
	{
		switch (m_nextexpectedparam)
		{
			case NEP_DEVICE_HINT:
				m_strDeviceHint = strParam;

				m_nextexpectedparam = NEP_NONE;
				break;
			case NEP_LISTENER_PORT:
				m_iListenerPort = _tstoi(strParam);

				m_nextexpectedparam = NEP_NONE;
				break;
			default:
				CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
		}
	}
}
