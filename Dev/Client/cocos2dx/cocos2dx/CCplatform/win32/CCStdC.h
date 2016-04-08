/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_STD_C_H__
#define __CC_STD_C_H__

#include "CCplatform/CCPlatformMacros.h"
#include <float.h>

// for math.h on win32 CCplatform
#ifndef __MINGW32__

#if !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES       // make M_PI can be use
#endif

#if !defined(isnan)
    #define isnan   _isnan
#endif

#ifndef snprintf
#define snprintf _snprintf
#endif

#endif // __MINGW32__

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// for CC_MIN CC_MAX and sys/time.h on win32 CCplatform
#ifndef __MINGW32__


#ifndef CC_MIN
#define CC_MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // CC_MIN

#ifndef CC_MAX
#define CC_MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // CC_MAX

#else // __MINGW32__

#include <sys/time.h>

#ifndef CC_MIN
#define CC_MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // CC_MIN

#ifndef CC_MAX
#define CC_MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // CC_MAX

#endif // __MINGW32__


#if _MSC_VER >= 1600 || defined(__MINGW32__)
    #include <stdint.h>
#else
    #include "./compat/stdint.h"
#endif

#define _WINSOCKAPI_
// Structure timeval has define in winsock.h, include windows.h for it.
#include <Windows.h>

#ifndef __MINGW32__

#include <WinSock2.h>

NS_CC_BEGIN

struct timezone
{
    int tz_minuteswest;
    int tz_dsttime;
};

int CC_DLL gettimeofday(struct timeval *, struct timezone *);

NS_CC_END

#else

#include <winsock.h>

#endif // __MINGW32__

#endif  // __CC_STD_C_H__
