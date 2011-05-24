#pragma once

#ifdef LIBUSRP_EXPORTS
#define LIBUSRP_SPEC	__declspec(dllexport)
#else
#define LIBUSRP_SPEC	__declspec(dllimport)
#endif // LIBUSRP_EXPORTS

#ifndef LIBUSRP_EXPORTS
#include <usrp/usrp_standard.h>
#include <usrp/usrp_subdev_spec.h>
#include <usrp/usrp_dbid.h>
#endif // LIBUSRP_EXPORTS
