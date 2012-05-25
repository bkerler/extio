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
