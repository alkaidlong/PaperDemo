#pragma once

#ifdef MEDUSA_ANDROID
//add socket lib
#include <android/log.h>
#include <jni.h>

#include <sys/types.h>   
#include <sys/socket.h>   //Linux only
#include <sys/time.h>   //Linux only
#include <sys/stat.h>
#include <sys/uio.h>   //Linux only
#include <sys/wait.h>   //Linux only
#include <sys/un.h>   //Linux only
#include <sys/select.h>   //Linux only
#include <netinet/in.h>   //Linux only
#include <arpa/inet.h>   //Linux only
#include <time.h>   
#include <errno.h>   
#include <fcntl.h>
#include <netdb.h>   //Linux only
#include <signal.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include <unistd.h>  //Linux only
#include <stdarg.h>	//Linux only
#include <ctype.h>	//Linux only
#include <dirent.h>


#include "pthread.h"
#include "sched.h"
#include "semaphore.h"

#include "CoreLib/android/uuid/uuid.h"
#include "CoreLib/android/libcurl/include/curl/curl.h"
#include "CoreLib/android/iconv/include/iconv.h"


#endif
