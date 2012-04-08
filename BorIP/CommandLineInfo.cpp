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
