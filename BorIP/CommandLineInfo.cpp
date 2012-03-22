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
		else if (strParam == _T("resettime"))
			m_nextexpectedparam = NEP_DEVICE_RESET_TIME;
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
			case NEP_DEVICE_RESET_TIME:
			{
				int iTime = _tstoi(strParam);
				int iHour = iTime / 100;
				int iMin = iTime % 100;
				if ((iHour >= 0) && (iHour <= 23) && (iMin >= 00) && (iMin <= 59))
				{
					CTime timeNow = CTime::GetCurrentTime();
					m_timeDeviceReset = CTime(timeNow.GetYear(), timeNow.GetMonth(), timeNow.GetDay(), iHour, iMin, 0);
				}
				break;
			}
			default:
				CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
		}
	}
}
