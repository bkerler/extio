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
#include "Utils.h"

int GetMapIndex(int iValue, const int* map, int iCount)
{
	int i = 0;
	for (; i < iCount; i++)
	{
		if (map[i*2 + 0] >= iValue)
		{
			if (map[i*2 + 0] > iValue)
				--i;

			break;
		}
	}

	if ((i == -1) || (i == iCount))
		return i;

	return (i*2/* + 1*/);
}
