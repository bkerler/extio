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
	HANDLE m_hCreatedEvent;
public:
	void _Close(bool bResetEvent = true);
	//inline HANDLE _GetEvent() const
	//{ return m_hEvent; }
protected:
	DECLARE_MESSAGE_MAP()
};
