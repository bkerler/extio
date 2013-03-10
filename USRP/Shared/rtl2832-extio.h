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

#include "IUSRP.h"

#include <rtl2832.h>

class LogMonitor
{
private:
	bool* m_pMonitor;
public:
	LogMonitor(bool& bMonitor)
		: m_pMonitor(&bMonitor)
	{ bMonitor = true; }
	~LogMonitor()
	{ (*m_pMonitor) = false; }
};

#define SCOPED_LOG_MONITOR(b)		LogMonitor _log_monitor(b);

class RTL2832 : public USRPSkeleton, public rtl2832::log_sink
{
public:
	RTL2832();
	~RTL2832();
private:
	rtl2832::demod::PARAMS m_demod_params;
	rtl2832::demod m_demod;
public:
	CCriticalSection m_cs;
	CWinThread* m_pCaptureThread;
	UINT m_nItemSize;	// # samples output by ReadPacket
	UINT m_nBufferSize;
	UINT m_nBufferStart;
	UINT m_nBufferItems;
	HANDLE m_hStopEvent;
	HANDLE m_hPacketEvent;
	HANDLE m_hAbortEvent;
	LPBYTE m_pUSBBuffer;
	bool m_bBuffering;
	LPBYTE m_pConversionBuffer;
	UINT m_nReadPacketCount;
	LARGE_INTEGER m_liFreq;
	UINT m_nBufferOverflowCount;
	UINT m_nBufferUnderrunCount;
	UINT m_nReadLength;
	UINT m_nBufferMultiplier;
	bool m_bUseBuffer;
	float m_fBufferLevel;
	DWORD m_dwReadPacketWait;
	bool m_bExternalCall;
private:
	void on_log_message_va(int level, const char* msg, va_list args);
public:
	void Destroy();
	void Reset();
	UINT CaptureThreadProc();
public:
	virtual bool Create(LPCTSTR strHint = NULL);
	virtual bool Start();
	virtual void Stop();
	virtual bool SetGain(double dGain);
	virtual bool SetAntenna(int iIndex);
	virtual bool SetAntenna(LPCTSTR strAntenna);
	virtual double SetFreq(double dFreq);
	virtual double SetSampleRate(double dSampleRate);
	virtual std::vector<std::string> GetAntennas() const;
	//virtual SetClock();
	virtual int ReadPacket();
public:
	CString GetExtraInfo() const;
};
