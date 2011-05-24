#pragma once

#include "USRP.h"

//class USRP;
class CdialogExtIO;

class ExtIO_USRP : public USRPConfiguration
{
public:
	ExtIO_USRP();
	~ExtIO_USRP();
public:
	typedef void (*FnCallback)(int, int, float, short *);	// __stdcall isn't necessary!
public:
	enum IFLimits
	{
		LOW,
		HIGH,
		IF_LIMIT_COUNT
	};
	enum CallbackStatus
	{
		CS_HWSRChange	= 100,
		CS_LOChange		= 101,
		CS_LOBlocked	= 102,
		CS_LOUnblocked	= 103,
		CS_LOChangeEx	= 104,
		CS_TuneChange	= 105,
		CS_DeModChange	= 106,
		CS_Start		= 107,
		CS_Stop			= 108,
		CS_FilterChange	= 109
	};
private:
	IUSRP* m_pUSRP;
	CString m_strDevice;
	CString m_strAddress;
	//long m_lLO;
	HANDLE m_hEvent;
	CString m_strSerial;
	DWORD m_dwWorkerID;
	FnCallback m_pfnCallback;
	CdialogExtIO* m_pDialog;
	CCriticalSection m_cs;
	HANDLE m_hWorker;
	//CString m_strAntenna;
	//double m_dGain;
	long m_lIFLimits[IF_LIMIT_COUNT];
	long m_lTunedFreq;
	//long m_lSampleRate;
	bool m_bError;
	bool m_bForceSampleRateUpdate;
public:
	bool Init();
	void Destroy();
	bool TryOpen();
	bool Open(LPCTSTR strHint = NULL, LPCTSTR strAddress = NULL);
	void Close();
	void SetCallback(FnCallback pfnCallback);
	DWORD Worker();
	void SetIFLimits(long lLow, long lHigh);
	void SetTunedFrequency(long lFreq);
	int SetLO(ULONG lFreq);
	long GetLO();
	int Start();
	void Stop();
	void Abort();
	void Signal(CallbackStatus status);
	bool SetSampleRate(double dSampleRate);
public:
	inline CdialogExtIO* GetDialog()
	{ return m_pDialog; }
	inline IUSRP* GetUSRP()
	{ return m_pUSRP; }
	//inline long GetLO()
	//{ return m_lLO; }
	//inline LPCTSTR GetSerial() const
	//{ return m_strSerial; }
	inline bool GetError() const
	{ return m_bError; }
	//inline double GetGain() const
	//{ return m_dGain; }
	inline CString GetDevice() const
	{ return m_strDevice; }
	//inline CString GetAntenna() const
	//{ return m_strAntenna; }
	inline CString GetRemoteAddress() const
	{ return m_strAddress; }
public:
	inline void SetDeviceHint(LPCTSTR str)
	{ m_strDevice = str; }
	inline void SetRemoteAddress(LPCTSTR str)
	{ m_strAddress = str; }
public:
	inline double GetSampleRate() const
	{
		if (!m_pUSRP) return __super::GetSampleRate();
		return m_pUSRP->GetSampleRate();
	}
	inline double GetFreq() const
	{
		if (!m_pUSRP) return __super::GetFreq();
		return m_pUSRP->GetFreq();
	}
	inline CString GetAntenna() const
	{
		if (!m_pUSRP) return __super::GetAntenna();
		return m_pUSRP->GetAntenna();
	}
	inline double GetGain() const
	{
		if (!m_pUSRP) return __super::GetGain();
		return m_pUSRP->GetGain();
	}
};
