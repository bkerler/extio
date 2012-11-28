#pragma once

#define LOAD_STRING(str)			str = AfxGetApp()->GetProfileString(REGISTRY_PROFILE_SECTION, _T(#str), str)
#define SAVE_STRING(str)			AfxGetApp()->WriteProfileString(REGISTRY_PROFILE_SECTION, _T(#str), str)

#define LOAD_INT(i)					i = AfxGetApp()->GetProfileInt(REGISTRY_PROFILE_SECTION, _T(#i), i)
#define SAVE_INT(i)					AfxGetApp()->WriteProfileInt(REGISTRY_PROFILE_SECTION, _T(#i), i)

#define LOAD_FLOAT(flt)				flt = (float)AfxGetApp()->GetProfileInt(REGISTRY_PROFILE_SECTION, _T(#flt), (int)(flt * 1000.0f)) / 1000.0f;
#define SAVE_FLOAT(flt)				AfxGetApp()->WriteProfileInt(REGISTRY_PROFILE_SECTION, _T(#flt), (int)(flt * 1000.0f))

// Must be reference (not pointer), no error checking
#define SECT_LOAD_BINARY_LEN(sect,ref,len) { LPBYTE pData; UINT nSize; \
	if (AfxGetApp()->GetProfileBinary(sect, _T(#ref), &pData, &nSize)) \
	{ memcpy(&ref, pData, min(nSize,len)); delete [] pData; } }
#define SECT_SAVE_BINARY_LEN(sect,ref,len) \
	AfxGetApp()->WriteProfileBinary(sect, _T(#ref), (LPBYTE)&ref, len);

#define LOAD_BINARY(ref)			SECT_LOAD_BINARY_LEN(REGISTRY_PROFILE_SECTION,ref,sizeof(ref))
#define SAVE_BINARY(ref)			SECT_SAVE_BINARY_LEN(REGISTRY_PROFILE_SECTION,ref,sizeof(ref))
