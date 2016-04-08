#pragma once

#undef MEDUSA_OS
#undef MEDUSA_DEBUG
#undef MEDUSA_LOG
#undef MEDUSA_IS_SIMULATOR

#undef MEDUSA_WINDOWS
#undef MEDUSA_IOS
#undef MEDUSA_MAC
#undef MEDUSA_ANDROID
#undef MEDUSA_LINUX


//Features

//#define MEDUSA_MATH_CPP11

//#define MEDUSA_ZLIB
//#define MEDUSA_VFP
//#define MEDUSA_NEON
//#define MEDUSA_SOCKET
#define MEDUSA_ZIP
#define MEDUSA_7Z
#define MEDUSA_SCRIPT
#define MEDUSA_PROTOBUF
#define MEDUSA_XML


//#define MEDUSA_PROFILE_FEATURE
//#define MEDUSA_VIRTUAL_ENABLED
//#define MEDUSA_MEMORY_LEAK_DETECTED_ENABLED


#define MEDUSA_BIT_X86 1
#define MEDUSA_BIT_X64 2

#define MEDUSA_OS_WINDOWS 100
#define MEDUSA_OS_IOS 200
#define MEDUSA_OS_MAC 300
#define MEDUSA_OS_ANDROID 400
#define MEDUSA_OS_LINUX 500

#define WEAK_MULTIPLE_DEFINE
#define FORCE_INLINE


#if defined(DEBUG) || defined(_DEBUG)
#define MEDUSA_DEBUG
#endif

#ifdef MEDUSA_VIRTUAL_ENABLED
#define MEDUSA_VIRTUAL virtual
#else
#define MEDUSA_VIRTUAL
#endif

////////////////////////////////////////////////////////////////////////// Win
#if defined(_WIN64)||defined(_WIN32)||defined(WIN32)||defined(WIN64)
#define MEDUSA_OS MEDUSA_OS_WINDOWS
#define MEDUSA_WINDOWS MEDUSA_OS
#define  MEDUSA_LOG(...)  

#undef WEAK_MULTIPLE_DEFINE
#define WEAK_MULTIPLE_DEFINE __declspec(selectany)

#undef FORCE_INLINE
#define FORCE_INLINE __forceinline

#if defined(MEDUSA_DEBUG) && defined(MEDUSA_MEMORY_LEAK_DETECTED_ENABLED)
#define MEDUSA_ENABLE_VLD
#endif

#ifdef _WIN64
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86

//A value of predefined macro __cplusplus is still 199711L in VS2012
#define MEDUSA_CPP11  201103L

#endif

////////////////////////////////////////////////////////////////////////// Apple
#elif __APPLE__

#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
#define MEDUSA_OS MEDUSA_OS_IOS
#define MEDUSA_IOS	MEDUSA_OS
#ifdef TARGET_IPHONE_SIMULATOR
#define MEDUSA_IS_SIMULATOR
#else
//#define MEDUSA_MATH_VFP_ENABLED
#endif 

#elif TARGET_OS_MAC
#define MEDUSA_OS MEDUSA_OS_MAC
#define MEDUSA_MAC	MEDUSA_OS
#else
#endif

#ifdef _ARM_ARCH_7
//#define MEDUSA_MATH_NEON_ENABLED
#endif

#define  MEDUSA_LOG(...)  

#undef WEAK_MULTIPLE_DEFINE
#define WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef FORCE_INLINE
#define FORCE_INLINE __attribute__((always_inline)) inline

#if __x86_64__ || __ppc64__ ||__LP64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86
#endif

#if __cplusplus <= 199711L
//#error "C++11 not supported!"
#else
#ifndef MEDUSA_CPP11 
//#define MEDUSA_CPP11 __cplusplus
#endif
#endif

//A value of predefined macro __cplusplus is still 199711L in VS2012
#define MEDUSA_CPP11  201103L

#elif __ANDROID__
////////////////////////////////////////////////////////////////////////// Android
#define MEDUSA_OS MEDUSA_OS_ANDROID
#define MEDUSA_ANDROID	MEDUSA_OS
#define  MEDUSA_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG,"Medusa",__VA_ARGS__)

#undef WEAK_MULTIPLE_DEFINE
#define WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef FORCE_INLINE
#define FORCE_INLINE inline __attribute__((always_inline))

#if __x86_64__ || __ppc64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86
#endif

#if __cplusplus <= 199711L
#error "C++11 not supported!"
#else
#ifndef MEDUSA_CPP11 
#define MEDUSA_CPP11 __cplusplus
#endif
#endif

#elif defined(linux)||defined(__linux)||defined(__linux__)
////////////////////////////////////////////////////////////////////////// Linux
#define MEDUSA_OS MEDUSA_OS_LINUX
#define MEDUSA_LINUX	MEDUSA_OS
#define  MEDUSA_LOG(...) 

#undef WEAK_MULTIPLE_DEFINE
#define WEAK_MULTIPLE_DEFINE __attribute__((weak))

#undef FORCE_INLINE
#define FORCE_INLINE __attribute__((always_inline))

#if __x86_64__ || __ppc64__
#define MEDUSA_X64 MEDUSA_BIT_X64
#define MEDUSA_BIT MEDUSA_X64
#else
#define MEDUSA_X86 MEDUSA_BIT_X86
#define MEDUSA_BIT MEDUSA_X86
#endif

#if __cplusplus <= 199711L
#error "C++11 not supported!"
#else
#ifndef MEDUSA_CPP11 
#define MEDUSA_CPP11 __cplusplus
#endif
#endif

#else
#error "No platform"
#endif

#ifndef MEDUSA_OS
#error  "Can not recognize the target platform(MEDUSA_WINDOWS,MEDUSA_IOS,MEDUSA_ANDROID), compling under a unsupported platform?"
#endif 

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#elif defined(__has_attribute)
#if __has_attribute(format)
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos) __attribute__((__format__(printf, formatPos, argPos)))
#endif 
#else
#define MEDUSA_CHECK_AS_PRINTF_FORMAT(formatPos, argPos)
#endif


#if defined(__GNUC__) && (__GNUC__ >= 4)
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos)
#elif defined(__has_attribute)
#if __has_attribute(format)
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos) 
#endif 
#else
#define MEDUSA_CHECK_AS_WPRINTF_FORMAT(formatPos, argPos)
#endif

#if !defined(MEDUSA_REQUIRES_NULL_TERMINATION)
#if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
#define MEDUSA_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
#elif defined(__GNUC__)
#define MEDUSA_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
#else
#define MEDUSA_REQUIRES_NULL_TERMINATION
#endif
#endif

//////////////////////////////////////////////////////////////////////////


//used to debug free,delete
//#define MEDUSA_MEMORY_DEBUG
