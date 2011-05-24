#pragma once

#define BOR_PORT	28888

#pragma pack(push)
#pragma pack(1)

typedef struct BorPacket {
	BYTE flags;
	BYTE notification;
	USHORT idx;
	BYTE data[1];
} BOR_PACKET, *PBOR_PACKET;

#pragma pack(pop)

enum BorFlags
{
	BF_NONE				= 0x00,
	BF_HARDWARE_OVERRUN	= 0x01,
	BF_NETWORK_OVERRUN	= 0x02,
	BF_BUFFER_OVERRUN	= 0x04,
	BF_EMPTY_PAYLOAD	= 0x08,
	BF_STREAM_START		= 0x10,
	BF_STREAM_END		= 0x20
};
