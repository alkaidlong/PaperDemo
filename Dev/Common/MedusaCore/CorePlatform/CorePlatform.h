#pragma once
#include "CorePlatform/CorePlatformDefines.h"
#include "CoreLib/CoreLib.h"

#include "CorePlatform/Common/CommonMarcos.h"
#include "CorePlatform/Common/MacroUtility.h"
#include "CorePlatform/Threading/ThreadingDefines.h"

#if __cplusplus <= 199711L
#ifndef override
#define override
#endif
#endif


#ifdef _MSC_VER

#else

#endif



#ifdef MEDUSA_WINDOWS
typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef unsigned int		uint;
typedef wchar_t wchar;
typedef unsigned char byte;

typedef HWND MedusaWindowHandle;
typedef intptr_t intptr;
typedef uintptr_t uintptr;

#ifdef MEDUSA_X64
typedef int64 intp;
typedef uint64 uintp;
#else
typedef int32 intp;
typedef uint32 uintp;
#endif

typedef uint64 ProfileTimeType;

#ifndef strtoll
#define strtoll  _strtoi64
#endif // !strtoll


#ifndef strtoull
#define strtoull  _strtoui64
#endif // !strtoull

#endif


#if defined (MEDUSA_IOS) || defined( MEDUSA_ANDROID )|| defined( MEDUSA_LINUX)
typedef unsigned short		ushort;
typedef unsigned long		ulong;
typedef unsigned int		uint;

//typedef unsigned int		size_t;
typedef unsigned char byte;
typedef wchar_t wchar;

typedef intptr_t intptr;
typedef uintptr_t uintptr;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#ifdef MEDUSA_X64
typedef int64 intp;
typedef uint64 uintp;
#else
typedef int32 intp;
typedef uint32 uintp;

#endif

typedef uint64 ProfileTimeType;

typedef intp MedusaWindowHandle;

typedef int SOCKET;
#endif


//Functions
#ifdef MEDUSA_WINDOWS

#define MEDUSA_TRACEA(s) OutputDebugStringA(s)
#define MEDUSA_TRACEW(s) OutputDebugStringW(s)
#define MEDUSA_TRACE(s) MEDUSA_TRACEA(s)

MEDUSA_BEGIN;
namespace Platform
{
	inline ProfileTimeType GetTimeFreq()
	{
		LARGE_INTEGER prev;
		QueryPerformanceFrequency(&prev);
		return prev.QuadPart;
	}

	inline ProfileTimeType GetTicks()
	{
		LARGE_INTEGER prev;
		QueryPerformanceCounter(&prev);
		return prev.QuadPart;
	}

}
MEDUSA_END;
#endif



#if defined(MEDUSA_IOS) || defined(MEDUSA_ANDROID)||defined(MEDUSA_LINUX)

MEDUSA_BEGIN;
#define MEDUSA_TRACE(s) 
#define MEDUSA_TRACEA(s) 
#define MEDUSA_TRACEW(s) 

namespace Platform
{

	inline ProfileTimeType GetTimeFreq()
	{
		return 1000;
	}

	inline ProfileTimeType GetTicks()
	{
		struct timeval t;

		gettimeofday ( &t, NULL );
		t.tv_sec %= 86400; // one day ticks 24*60*60

		return ( t.tv_sec*1000 + t.tv_usec );
	}
}

MEDUSA_END;
#endif
