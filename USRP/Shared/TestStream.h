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

#include "USRP.h"

class TestStream : public USRPSkeleton
{
public:
	TestStream(size_t nSamplesPerPacket = 0);
	virtual ~TestStream();
public:
	public:
	CCriticalSection m_cs;
	HANDLE m_hThread;
	DWORD m_dwThreadID;
	HANDLE m_hDataEvent;
	HANDLE m_hQuitEvent;
public:
	//LPBYTE m_pData;
	//UINT m_nLength;
	//Teh::MemoryContainer m_mem;
	//Teh::MemoryContainer m_memBuffer;
	UINT m_nBufferStart, m_nBufferLength;
public:	// USRP
	bool Create(LPCTSTR strHint = NULL);
	bool Start();
	void Stop();
	bool SetGain(double dGain);
	bool SetAntenna(int iIndex);
	bool SetAntenna(LPCTSTR strAntenna);
	double SetFreq(double dFreq);
	double SetSampleRate(double dSampleRate);
	std::vector<std::string> GetAntennas() const;
	int ReadPacket();
public:
	void SetSamplesPerPacket(size_t nSamplesPerPacket);
public:
	//DWORD ReceiveThread();
public:
	//bool SubmitSamples(LPBYTE pData, UINT nLength);
public:
	//inline const short* GetBuffer() const
	//{ return (short*)m_mem.GetMemoryPointer(); }
	//inline size_t GetSamplesPerPacket() const
	//{ return (m_mem.GetMemoryLength() / (2 * sizeof(short))); }
};
