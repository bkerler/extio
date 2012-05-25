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

// BorIP.h : main header file for the server application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "Server.h"
#include "CommandLineInfo.h"

// CappMain:
// See BorIP.cpp for the implementation of this class
//

class CappMain : public CWinAppEx
{
public:
	CappMain();
// Overrides
public:
	virtual BOOL InitInstance();
// Implementation
	DECLARE_MESSAGE_MAP()
public:
	Server m_server;
	CommandLineInfo m_cli;
};

extern CappMain theApp;
