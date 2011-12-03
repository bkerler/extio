// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"
/*
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>            // MFC socket extensions
//#include <afxdhtml.h>
*/
#define TEH_BASE_LINK_STATIC
#include <TehBase\TehLinkBaseLib.h>

#define TEH_INCLUDE_MANIFEST
#include <TehBase\TehManifest.h>

#include <TehBase\TehAfx.h>

#include <psapi.h>

#include <TehBase\TehMemoryContainer.h>
#include <TehBase\TehUtils.h>
#include <TehBase\TehRefCounter.h>

#include <iostream>
#include <XmlRpc.h>

#include <setupapi.h>
#include <devguid.h>

#include <mmsystem.h>
#include <dsound.h>

#include <complex>
#include <afxwin.h>

#include <atlbase.h>

//#include <uhd/usrp/single_usrp.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <usrp/libusrp.h>

#ifndef _DEBUG
inline void AFX_CDECL _AfxTrace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vstprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args); 

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	//afxDump << szBuffer;
	OutputDebugString(szBuffer);

	va_end(args);
}

#define AfxTrace	_AfxTrace
#endif // !_DEBUG
