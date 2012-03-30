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
