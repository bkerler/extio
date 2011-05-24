#pragma once

#include <usrp/libusrp.h>

#include <io.h>

#ifdef __cplusplus
#include <boost\math\special_functions\round.hpp>
#define round boost::math::round
#endif // __cplusplus
/*
#include <algorithm>

#undef min
#undef max
*/
extern double rint(double x);

struct timespec
{
	time_t tv_sec;	/* Seconds. */
	long   tv_nsec;	/* Nanoseconds. */
};

#define snprintf _snprintf
#define access _access

// access mode constants
#define R_OK   4  // read only
#define W_OK   2  // write only
#define X_OK   1  // execute only
#define F_OK   0  // existence

#define nanosleep our_nanosleep

extern int nanosleep (const struct timespec *delay, struct timespec *rem);
