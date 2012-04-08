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

#pragma once

#include "AfxWin.h"

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
