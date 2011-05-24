#include <windows.h>

#include "config.h"

#include <math.h>

double rint(double x)
{
	if (ceil(x+0.5) == floor(x+0.5))	//middle value point test
	{
		int a = (int)ceil(x);
		if (a%2 == 0)
			return ceil(x);
		else
			return floor(x);
	}
	else
		return floor(x+0.5);
}

//static LARGE_INTEGER liFreq;

int nanosleep (const struct timespec *delay, struct timespec *rem)
{
	//if (liFreq.QuadPart == 0)
	//	QueryPerformanceFrequency(&liFreq);

	//LARGE_INTEGER li;

	Sleep((1000 * delay->tv_sec) + (delay->tv_nsec / 1000000));

	if (rem)
	{
		rem->tv_nsec = 0;
		rem->tv_sec = 0;
	}

	return 0;
}
