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
#include "MemoryUSRP.h"

MemoryUSRP::MemoryUSRP(size_t nSamplesPerPacket /*= 0*/)
	: m_hThread(NULL)
	, m_dwThreadID(0)
	, m_hDataEvent(NULL)
	, m_hQuitEvent(NULL)
	//, m_pData(NULL)
	//, m_nLength(0)
	, m_nBufferStart(0)
	, m_nBufferLength(0)
{
	SetSamplesPerPacket((nSamplesPerPacket ? nSamplesPerPacket : 4096));

	m_gainRange = uhd::gain_range_t(0, 1, 1);
}

MemoryUSRP::~MemoryUSRP()
{
	Stop();
}

void MemoryUSRP::SetSamplesPerPacket(size_t nSamplesPerPacket)
{
	m_recv_samples_per_packet = nSamplesPerPacket;
	m_mem.AllocateMemory(m_recv_samples_per_packet * 2 * sizeof(short));

	m_memBuffer.AllocateMemory(m_mem.GetMemoryLength() * 16);
}

bool MemoryUSRP::Create(LPCTSTR strHint /*= NULL*/)
{
	ASSERT(FALSE);

	return true;
}

double MemoryUSRP::SetSampleRate(double dSampleRate)
{
	return dSampleRate;
}

bool MemoryUSRP::SetGain(double dGain)
{
	return true;
}

std::vector<std::string> MemoryUSRP::GetAntennas() const
{
	return std::vector<std::string>();
}

bool MemoryUSRP::SetAntenna(int iIndex)
{
	return true;
}

bool MemoryUSRP::SetAntenna(LPCTSTR strAntenna)
{
	return true;
}

double MemoryUSRP::SetFreq(double dFreq)
{
	return dFreq;
}
/*
static DWORD WINAPI _ReceiveThread(LPVOID lpThreadParameter)
{
	return ((MemoryUSRP*)lpThreadParameter)->ReceiveThread();
}
*/
bool MemoryUSRP::Start()
{
	if (m_hDataEvent == NULL)
	{
		if ((m_hDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hDataEvent);

	if (m_hQuitEvent == NULL)
	{
		if ((m_hQuitEvent = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
			return false;
	}
	else
		ResetEvent(m_hQuitEvent);

	//m_hThread = CreateThread(NULL, 0, _ReceiveThread, this, 0, &m_dwThreadID);

	//m_pData = NULL;
	//m_nLength = 0;

	m_bRunning = true;

	return true;
}

void MemoryUSRP::Stop()
{
	{
		CSingleLock lock(&m_cs, TRUE);

		m_bRunning = false;
	}

	SetEvent(m_hQuitEvent);

	if (m_hThread)
	{
		//SetEvent(m_hQuitEvent);
		WaitForSingleObject(m_hThread, INFINITE);

		m_hThread = NULL;
		m_dwThreadID = 0;
	}

	if (m_hDataEvent)
	{
		CloseHandle(m_hDataEvent);
		m_hDataEvent = NULL;
	}

	if (m_hQuitEvent)
	{
		CloseHandle(m_hQuitEvent);
		m_hQuitEvent = NULL;
	}
}

bool MemoryUSRP::SubmitSamples(LPBYTE pData, UINT nLength)
{
	if ((pData == NULL) || (nLength == 0))
		return false;

	CSingleLock lock(&m_cs, TRUE);

	if ((m_memBuffer.GetMemoryLength() - m_nBufferLength) < nLength)
	{
		AfxTrace(_T("Dropping samples\n"));
		return true;
	}

	UINT nStart = (m_nBufferStart + m_nBufferLength) % m_memBuffer.GetMemoryLength();
	UINT n1 = min(nStart + nLength, m_memBuffer.GetMemoryLength()) - nStart;

	memcpy(m_memBuffer.GetMemoryPointer() + nStart, pData, n1);

	if (n1 != nLength)
	{
		memcpy((m_memBuffer.GetMemoryPointer() + 0), (pData + n1), (nLength - n1));
	}

	m_nBufferLength += nLength;

	ASSERT(m_nBufferLength <= m_memBuffer.GetMemoryLength());

	if (m_nBufferLength >= (GetSamplesPerPacket() * 2 * sizeof(short)))
		SetEvent(m_hDataEvent);

	return true;
}

int MemoryUSRP::ReadPacket()
{
	UINT nSize = GetSamplesPerPacket() * 2 * sizeof(short);

	CSingleLock lock(&m_cs, TRUE);
retry_read:
	if (m_bRunning == false)
		return 0;

	if (m_nBufferLength < nSize)
	{
		lock.Unlock();

		HANDLE hHandles[] = { m_hQuitEvent, m_hDataEvent };

		DWORD dw = WaitForMultipleObjects(sizeof(hHandles)/sizeof(hHandles[0]), hHandles, FALSE, INFINITE);
		if (dw == (WAIT_OBJECT_0 + 0))
		{
			return 0;
		}
		else if (dw == (WAIT_OBJECT_0 + 1))
		{
			lock.Lock();

			if (m_nBufferLength < nSize)
			{
				AfxTrace(_T("MemoryUSRP::ReadPacket received un-block event, but not yet enough data in buffer\n"));
				goto retry_read;
			}
		}
		else
		{
			ASSERT(FALSE);

			return 0;
		}
	}

	UINT n1 = min(m_nBufferStart + nSize, m_memBuffer.GetMemoryLength()) - m_nBufferStart;

	memcpy(m_mem.GetMemoryPointer(), (m_memBuffer.GetMemoryPointer() + m_nBufferStart), n1);

	if (n1 != nSize)
	{
		memcpy((m_mem.GetMemoryPointer() + n1), (m_memBuffer.GetMemoryPointer() + 0), (nSize - n1));
	}

	ASSERT(m_nBufferLength >= nSize);
	m_nBufferLength -= nSize;
	m_nBufferStart = (m_nBufferStart + nSize) % m_memBuffer.GetMemoryLength();

	return GetSamplesPerPacket();
}
