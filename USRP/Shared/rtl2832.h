#pragma once

#include "IUSRP.h"
#include <libusb-1.0/libusb.h>

class rtl2832 : public USRPSkeleton
{
public:
	rtl2832();
	~rtl2832();
public:
	enum TUNER_TYPE {
		TUNER_UNKNOWN,
		TUNER_E4000,
		TUNER_FC0013
	} tuner_type;
public:
	typedef unsigned int uint32_t;
public:
	struct libusb_device_handle *devh;
	int find_device();
	bool tuner_init();
	void rtl_init();
	void set_i2c_repeater(int on);
	bool set_samp_rate(uint32_t samp_rate);
	void demod_write_reg(uint8_t page, uint16_t addr, uint16_t val, uint8_t len);
	uint16_t demod_read_reg(uint8_t page, uint8_t addr, uint8_t len);
	void rtl_write_reg(uint8_t block, uint16_t addr, uint16_t val, uint8_t len);
	uint16_t rtl_read_reg(uint8_t block, uint16_t addr, uint8_t len);
	int rtl_i2c_read(uint8_t i2c_addr, uint8_t *buffer, int len);
	int rtl_i2c_write(uint8_t i2c_addr, uint8_t *buffer, int len);
	int rtl_write_array(uint8_t block, uint16_t addr, uint8_t *array, uint8_t len);
	int rtl_read_array(uint8_t block, uint16_t addr, uint8_t *array, uint8_t len);
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
	int m_iTunerGainMode;
	bool m_bUSBInitDone;
	UINT m_nReadLength;
	UINT m_nBufferMultiplier;
	bool m_bUseBuffer;
	float m_fBufferLevel;
	UINT m_nReadPacketCount;
	LARGE_INTEGER m_liFreq;
	UINT m_nBufferOverflowCount;
	UINT m_nBufferUnderrunCount;
public:
	void Destroy();
	void Reset();
	UINT CaptureThreadProc();
	int SetTunerMode();
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
