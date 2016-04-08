#pragma once
#ifdef MEDUSA_PROTOBUF
#define NOMINMAX
#endif


#ifdef MEDUSA_WINDOWS
////////////////////////////////////////////////////////////////////////// Windows
#ifdef MEDUSA_SOCKET
#include <Windows.h>
#else
#define _WINSOCKAPI_
#include <Windows.h>
#include <WinSock2.h>
#endif

//add socket lib
#pragma comment(lib,"wsock32.lib")		//必须包含，否则编译出错
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <direct.h>
typedef int socklen_t;

 #ifdef MEDUSA_ENABLE_VLD
 #pragma comment(lib,"vld.lib")		//必须包含，否则编译出错
 #include "CoreLib/win/vld/vld.h"
 #endif

#include "CoreLib/win/pthread/pthread.h"
#include "CoreLib/win/pthread/sched.h"
#include "CoreLib/win/pthread/semaphore.h"

#include "CoreLib/win/curl/curl.h"

#include "CoreLib/win/iconv/iconv.h" 

#endif
