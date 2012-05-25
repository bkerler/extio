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

class FUNcubeDongle : public USRPSkeleton
{
public:
	FUNcubeDongle();
	~FUNcubeDongle();
public:
	CCriticalSection m_cs;
public:
	void Destroy();
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
	BOOL DSEnumCallback(LPGUID lpGuid, LPCTSTR lpcstrDescription, LPCTSTR lpcstrModule);
	UINT CaptureThreadProc();
public:
	BOOL HIDWriteCommand(unsigned __int8 u8Cmd, unsigned __int8 *pu8Data, unsigned __int8 u8Len);
private:
	int m_iDeviceIndex;
	GUID m_guidCaptureDevice;
	int m_iCaptureDeviceIndex;
private:
	LPDIRECTSOUNDCAPTURE8 m_pCaptureDevice;
	DSCBUFFERDESC m_descBuffer;
	LPDIRECTSOUNDCAPTUREBUFFER m_pCaptureBuffer;
	LPDIRECTSOUNDNOTIFY m_pNotifications;
	HANDLE m_hNotificationEvent;
	HANDLE m_hQuitEvent;
	CWinThread* m_pCaptureThread;
	int m_iCaptureNotificationCount;
	DWORD m_dwReadCursorPosition;
	UINT m_nItemSize;	// Bytes in packet
	HANDLE m_hStopEvent;
	HANDLE m_hPacketEvent;
	UINT m_nBufferItems;	// I/Q samples in buffer
	LPBYTE m_pAudioBuffer;
	UINT m_nBufferStart;// I/Q sample offset to start in audio buffer
	UINT m_nBufferSize;	// I/Q samples in audio buffer
	UINT m_nBufferLockCount;
	bool m_bSkipNextBlock;
	HANDLE m_hHIDRead, m_hHIDWrite;
	CFile m_fileDump;
public:
	virtual inline double GetSampleRate() const
	{
		return __super::GetSampleRate();
	}
	virtual inline double GetGain() const
	{
		return __super::GetGain();
	}
	virtual inline CString GetAntenna() const
	{
		return __super::GetAntenna();
	}
	virtual inline double GetFreq() const
	{
		return __super::GetFreq();
	}
};
