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
	HANDLE m_hWorkedFinished;
	bool m_bWorkerActive;
	UINT m_nAlignedSamplesPerPacket;
	//CString m_strAntenna;
	//double m_dGain;
	long m_lIFLimits[IF_LIMIT_COUNT];
	long m_lTunedFreq;
	//long m_lSampleRate;
	bool m_bError;
	bool m_bForceSampleRateUpdate;
	BOOL m_bRemoteDevice;
	bool m_bSkipFailedXMLRPC;
private:
	SOCKET m_hDataSocket;
	UINT m_nMaxPacketSize;
	SOCKADDR_IN m_addrDest;
	CCriticalSection m_csRelay;
	CCriticalSection m_csXMLRPCClient;
	XmlRpc::XmlRpcClient* m_pXMLRPCClient;
	int m_iXMLRPCPort;
	BOOL m_bEnableUDPRelay;
	BOOL m_bEnableXMLRPCIF;
	CString m_strUDPRelayAddress;
	long m_lOffset;
	BOOL m_bUseOffset;
	BOOL m_bRelayAsBorIP;
	int m_nMemoryUSRPSamplesPerPacket;
	BOOL m_bTestMode;
public:
	bool Init();
	void Destroy();
	bool TryOpen();
	bool Open(LPCTSTR strHint = NULL, LPCTSTR strAddress = NULL);
	void Playback();
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
	bool EnableUDPRelay(LPCTSTR strDestination = NULL);
	void DisableUDPRelay(bool bKeepSetting = false);
	bool SetUDPRelayDestination(const CString& strDestination);
	bool EnableXMLRPCIF(int iPort = 0);
	void DisableXMLRPCIF(bool bKeepSetting = false);
	bool SetXMLRPCIFPort(int iPort);
	void RelayAsBorIP(bool bEnable = true);
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
	inline bool IsUDPRelayEnabled() const
	{ return (m_bEnableUDPRelay && (m_addrDest.sin_addr.S_un.S_addr != 0)); }
	inline bool IsXMLRPCIFEnabled() const
	{ return (m_bEnableXMLRPCIF && (m_addrDest.sin_addr.S_un.S_addr != 0) && (m_iXMLRPCPort > 0)); }
	inline const CString& GetUDPRelayAddress() const
	{ return m_strUDPRelayAddress; }
	inline int GetXMLRPCIFPort() const
	{ return m_iXMLRPCPort; }
	inline bool IsRelayingAsBorIP() const
	{ return I2B(m_bRelayAsBorIP); }
	inline bool IsOffset() const
	{ return I2B(m_bUseOffset); }
	inline void UseOffset(bool bUse = true)
	{ m_bUseOffset = B2I(bUse); }
	inline long GetOffset() const
	{ return m_lOffset; }
	inline void SetOffset(long lOffset)
	{ m_lOffset = lOffset; }
public:
	inline void SetDeviceHint(LPCTSTR str)
	{ m_strDevice = str; }
	inline void SetRemoteAddress(LPCTSTR str)
	{ m_strAddress = str; UseRemoveDevice(!IS_EMPTY(str)); }
	inline void UseRemoveDevice(bool bUse = true)
	{ m_bRemoteDevice = B2I(bUse); }
	inline bool IsUsingRemoteDevice() const
	{ return (m_bRemoteDevice && (!m_strAddress.IsEmpty())); }
public:
	inline double _GetSampleRate() const
	{
		if (!m_pUSRP) return __super::GetSampleRate();
		return m_pUSRP->GetSampleRate();
	}
	inline double GetSampleRate() const
	{
		double d = _GetSampleRate();
		if (d <= 0)
			d = (m_pUSRP ? m_pUSRP->GetDesiredSampleRate() : 1);
		return d;
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
