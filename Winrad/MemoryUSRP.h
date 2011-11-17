#pragma once

#include "USRP.h"

class MemoryUSRP : public USRPSkeleton
{
public:
	MemoryUSRP(size_t nSamplesPerPacket = 0);
	virtual ~MemoryUSRP();
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
	Teh::MemoryContainer m_mem;
	Teh::MemoryContainer m_memBuffer;
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
	bool SubmitSamples(LPBYTE pData, UINT nLength);
public:
	inline const short* GetBuffer() const
	{ return (short*)m_mem.GetMemoryPointer(); }
	//inline size_t GetSamplesPerPacket() const
	//{ return (m_mem.GetMemoryLength() / (2 * sizeof(short))); }
};
