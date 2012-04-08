#pragma once

class IUSRPConfiguration
{
public:
	virtual void CopyFrom(const IUSRPConfiguration* pOther)=0;
public:
	virtual double GetSampleRate() const=0;
	virtual double GetFreq() const=0;
	virtual double GetGain() const=0;
	virtual CString GetAntenna() const=0;
};

class USRPConfiguration : virtual public IUSRPConfiguration
{
public:
	USRPConfiguration();
	USRPConfiguration(const USRPConfiguration& src);
	//virtual ~USRPConfiguration();
public:
	virtual void CopyFrom(const IUSRPConfiguration* pOther);
protected:
	double m_dSampleRate;
	double m_dFreq;
	double m_dGain;
	CString m_strAntenna;
public:
	inline virtual double GetSampleRate() const
	{ return m_dSampleRate; }
	inline virtual double GetFreq() const
	{ return m_dFreq; }
	inline virtual double GetGain() const
	{ return m_dGain; }
	inline virtual CString GetAntenna() const
	{ return m_strAntenna; }
};

class IUSRP : virtual public IUSRPConfiguration
{
public:
	virtual ~IUSRP()
	{ }
public:
	virtual bool Create(LPCTSTR strHint = NULL)=0;
	virtual bool Start()=0;
	virtual void Stop()=0;
	virtual bool SetGain(double dGain)=0;
	virtual bool SetAntenna(int iIndex)=0;
	virtual bool SetAntenna(LPCTSTR strAntenna)=0;
	virtual double SetFreq(double dFreq)=0;
	virtual double SetSampleRate(double dSampleRate)=0;
	virtual std::vector<std::string> GetAntennas() const=0;
	//virtual SetClock()=0;
	virtual int ReadPacket()=0;
public:
	virtual bool CopyState(IUSRPConfiguration* pOther)=0;
	virtual void ResetStats()=0;
	virtual int WasTuneSuccessful()=0;
public:
	//inline double GetSampleRate() const=0;
	virtual inline double GetDesiredSampleRate() const=0;
	virtual inline size_t GetSamplesPerPacket() const=0;
	//inline double GetFreq() const=0;
	//inline double GetGain() const=0;
	//inline LPCTSTR GetAntenna() const=0;
	virtual inline bool IsRunning() const=0;
	virtual inline const uhd::tune_result_t& GetTuneResult() const=0;
	virtual inline CString GetName() const=0;
	virtual inline CString GetSerial() const=0;
	//inline const CCriticalSection* GetLock() const=0;
	virtual inline const uhd::rx_metadata_t& GetMetadata() const=0;
	virtual inline const short* GetBuffer() const=0;
	virtual inline const uhd::gain_range_t& GetGainRange() const=0;
	virtual inline double GetMasterClock() const=0;
	virtual inline double GetDesiredFreq() const=0;
	virtual inline UINT64 GetSamplesReceived() const=0;
	virtual inline UINT GetOverflows() const=0;
	virtual inline CString GetExtraInfo() const=0;
	virtual inline CString GetLastError() const=0;
public:
	virtual inline void SetDesiredGain(double dGain)=0;
	virtual inline void SetDesiredAntenna(LPCTSTR strAntenna)=0;
	virtual inline void SetDesiredFrequency(double dFreq)=0;
};

class USRPSkeleton : public IUSRP, public USRPConfiguration
{
public:
	USRPSkeleton();
	virtual ~USRPSkeleton();
protected:
	double	m_dDesiredSampleRate;
	//bool	m_external_ref;
	size_t	m_recv_samples_per_packet;
	double 	m_fpga_master_clock_freq;
	bool	m_bRunning;
	CString	m_strName, m_strSerial;
	short*	m_pBuffer;
	UINT64	m_nSamplesReceived;
	UINT	m_nOverflows;
protected:
	uhd::gain_range_t m_gainRange;
	uhd::tune_result_t m_tuneResult;
	uhd::rx_metadata_t m_metadata;
	CString m_strLastError;
public:
/*	virtual bool Create(LPCTSTR strHint = NULL);
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
*/public:
	virtual bool CopyState(IUSRPConfiguration* pOther);
	virtual void ResetStats();
	virtual int WasTuneSuccessful()
	{ return 0; }
public:
	virtual void CopyFrom(const IUSRPConfiguration* pOther)
	{ return USRPConfiguration::CopyFrom(pOther); }
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
	virtual inline CString GetSerial() const
	{ return m_strSerial; }
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
	virtual inline CString GetLastError() const
	{ return m_strLastError; }
public:
	virtual inline void SetDesiredGain(double dGain)
	{ m_dGain = dGain; }
	virtual inline void SetDesiredAntenna(LPCTSTR strAntenna)
	{ m_strAntenna = strAntenna; }
	virtual inline void SetDesiredFrequency(double dFreq)
	{ m_dFreq = dFreq; }
public:
	inline double GetSampleRate() const
	{ return USRPConfiguration::GetSampleRate(); }
	inline double GetGain() const
	{ return USRPConfiguration::GetGain(); }
	inline CString GetAntenna() const
	{ return USRPConfiguration::GetAntenna(); }
	inline double GetFreq() const
	{ return USRPConfiguration::GetFreq(); }
};
