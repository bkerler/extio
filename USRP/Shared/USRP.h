#pragma once

//#include <uhd/usrp/single_usrp.hpp>
#include <uhd/usrp/multi_usrp.hpp>

#include "IUSRP.h"

class USRP : public USRPSkeleton
{
public:
	USRP();
	~USRP();
/*protected:
	double	m_dDesiredSampleRate;
	//bool	m_external_ref;
	size_t	m_recv_samples_per_packet;
	double 	m_fpga_master_clock_freq;
	bool	m_bRunning;
	CString	m_strName;
	short*	m_pBuffer;
	UINT64	m_nSamplesReceived;
	UINT	m_nOverflows;
protected:
	uhd::gain_range_t m_gainRange;
	uhd::tune_result_t m_tuneResult;
	uhd::rx_metadata_t m_metadata;*/
protected:
	uhd::usrp::/*single*/multi_usrp::sptr m_dev;
	CCriticalSection m_cs;
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
/*public:
	virtual bool CopyState(IUSRPConfiguration* pOther);
	virtual void ResetStats();
	virtual int WasTuneSuccessful();
public:
	//inline double GetSampleRate() const
	//{ return m_sample_rate; }
	virtual inline double GetDesiredSampleRate() const
	{ return m_dDesiredSampleRate; }
	virtual inline size_t GetSamplesPerPacket() const
	{ return m_recv_samples_per_packet; }
	//inline double GetFreq() const
	//{ return m_dFreq; }
	//inline double GetGain() const
	//{ return m_dGain; }
	//inline LPCTSTR GetAntenna() const
	//{ return m_strAntenna.c_str(); }
	virtual inline bool IsRunning() const
	{ return m_bRunning; }
	virtual inline const uhd::tune_result_t& GetTuneResult() const
	{ return m_tuneResult; }
	virtual inline CString GetName() const
	{ return m_strName; }
	//inline const CCriticalSection* GetLock() const
	//{ return &m_cs; }
	virtual inline const uhd::rx_metadata_t& GetMetadata() const
	{ return m_metadata; }
	virtual inline const short* GetBuffer() const
	{ return m_pBuffer; }
	virtual inline const uhd::gain_range_t& GetGainRange() const
	{ return m_gainRange; }
	virtual inline double GetMasterClock() const
	{ return m_fpga_master_clock_freq; }
	virtual inline double GetDesiredFreq() const
	{ return __super::GetFreq(); }
	virtual inline UINT64 GetSamplesReceived() const
	{ return m_nSamplesReceived; }
	virtual inline UINT GetOverflows() const
	{ return m_nOverflows; }
	virtual inline CString GetExtraInfo() const
	{ return _T(""); }
public:
	virtual inline void SetDesiredGain(double dGain)
	{ m_dGain = dGain; }*/
public:
	virtual inline double GetSampleRate() const
	{
		if (!m_dev) return __super::GetSampleRate();
		CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);
		try { return m_dev->get_rx_rate(); } catch (...) { return m_dSampleRate; }
	}
	virtual inline double GetGain() const
	{
		if (!m_dev) return __super::GetGain();
		CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);
		//AfxTrace(_T("H/W Gain = %f,\tStored = %f\t(Running = %s)\n"), m_dev->get_rx_gain(), m_dGain, (m_bRunning ? _T("true") : _T("false")));
		if (!m_bRunning) return m_dGain;
		try { return m_dev->get_rx_gain(); } catch (...) { return m_dGain; }
	}
	virtual inline CString GetAntenna() const
	{
		if (!m_dev) return __super::GetAntenna();
		CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);
		try { return CString(CStringA(m_dev->get_rx_antenna().c_str())); } catch (...) { return m_strAntenna; }
	}
	virtual inline double GetFreq() const
	{
		if (!m_dev) return __super::GetFreq();
		CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);
		try { return m_dev->get_rx_freq(); } catch (...) { return m_dFreq; }
	}
};

#include "socketClient.h"

class RemoteUSRP : public USRPSkeleton, public ClientSocketCallback
{
public:
	RemoteUSRP(CRuntimeClass* pSocket = NULL);
	~RemoteUSRP();
public:
	inline void SetSocketRuntimeClass(CRuntimeClass* pSocket)
	{ m_pSocketClass = pSocket; }
public:
	CRuntimeClass* m_pSocketClass;
	CsocketClient* m_pClient;
	CString m_strAddress;
	bool m_bPendingResponse;
	CString m_strExpectedResponse;
	CString m_strResponse;
	CString m_strResponseData;
	bool m_bConnected;
	std::vector<std::string> m_arrayAntennas;
public:
	CCriticalSection m_cs;
	HANDLE m_hThread;
	DWORD m_dwThreadID;
	HANDLE m_hDataEvent;
	HANDLE m_hQuitEvent;
	HANDLE m_hPacketEvent;
	HANDLE m_hStopEvent, m_hAbortEvent;
	SOCKET m_hDataSocket;
	LPBYTE m_pNetworkBuffer;
	UINT m_nItemSize;	// Payload size
	UINT m_nPacketSize;
	UINT m_nSocketBufferSize;
	UINT m_nNetworkBufferSize;
	UINT m_nNetworkBufferStart;
	UINT m_nNetworkBufferItems;
	WSAOVERLAPPED m_wsaOverlapped;
	USHORT m_usCounter;
	UINT m_nNetworkOverrun;
	UINT m_nBufferOverrun;
	UINT m_nLastSkip;
	HANDLE m_hAbortPump;
	UINT64 m_nPacketsReceived;
	UINT64 m_nPreBufferCount;
public:
	DWORD ReceiveThread();
public:
	bool Connect(LPCTSTR strAddress, LPCTSTR strHint = NULL);
	void Close(bool bAbort = false);
	void Stop(bool bAbort);
	void Destroy();
	bool WaitForResponse(LPCTSTR strCommand = NULL, bool bMustBeSame = true, bool bAbortIfWaiting = true);
	bool SendAndWaitForResponse(const CString& strCommand, LPCTSTR strData = NULL);
	bool SendAndWaitForOK(const CString& strCommand, LPCTSTR strData = NULL);
	bool PumpMessageLoop(DWORD dwTimeout = 0, UINT nReturnMsg = WM_QUIT, HWND hWnd = NULL, UINT nMsgFilterMin = 0, UINT nMsgFilterMax = 0);
	void Reset();
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
	CString GetExtraInfo() const;
public:
	bool CopyState(IUSRPConfiguration* pOther);
	void ResetStats();
public:	// ClientSocketCallback
	void OnCommand(CsocketClient* pSocket, const CString& str);
	void OnClose(CsocketClient* pSocket);
public:
	inline void SetRemoteAddress(const CString& str)
	{ m_strAddress = str; }
	inline CString GetRemoteAddress() const
	{ return m_strAddress; }
public:	// USRP
	inline double GetSampleRate() const
	{ return USRPConfiguration::GetSampleRate(); }
	inline double GetGain() const
	{ return USRPConfiguration::GetGain(); }
	inline CString GetAntenna() const
	{ return USRPConfiguration::GetAntenna(); }
	inline double GetFreq() const
	{ return USRPConfiguration::GetFreq(); }
};

#include <usrp/libusrp.h>

class LegacyUSRP : public USRPSkeleton
{
public:
	LegacyUSRP();
	~LegacyUSRP();
protected:
	CCriticalSection m_cs;
	usrp_standard_rx_sptr m_u_rx;
	db_base_sptr m_db_rx;
	CString m_strImage, m_strFirmware;
	UINT m_nBlockCount;
	int m_iMux;
	UINT m_nChannel;
	UINT m_nDecimation;
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
	virtual inline double GetSampleRate() const
	{
		/*if (!m_dev) */return __super::GetSampleRate();
		//CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE); return m_dev->get_rx_rate();
	}
	virtual inline double GetGain() const
	{
		/*if (!m_dev) */return __super::GetGain();
		//CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE);
		//if (!m_bRunning) return m_dGain;
		//return m_dev->get_rx_gain();
	}
	virtual inline CString GetAntenna() const
	{
		/*if (!m_dev) */return __super::GetAntenna();
		//CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE); return CString(CStringA(m_dev->get_rx_antenna().c_str()));
	}
	virtual inline double GetFreq() const
	{
		/*if (!m_dev) */return __super::GetFreq();
		//CSingleLock lock(const_cast<CCriticalSection*>(&m_cs), TRUE); return m_dev->get_rx_freq();
	}
};
