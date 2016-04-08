#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Log/ILogger.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/Event.h"


MEDUSA_BEGIN;

class Log
{
public:
	typedef Pattern::Delegate<void (StringRef text,Pattern::Action0 callback)> AlertViewDelegate;
	typedef Pattern::Delegate<void (WStringRef text,Pattern::Action0 callback)> WAlertViewDelegate;


	static Pattern::Event<void (StringRef text,Pattern::Action0 callback)> AlertViewEvent;
	static Pattern::Event<void (WStringRef text,Pattern::Action0 callback)> WAlertViewEvent;

	static bool Initialize();
	static bool Uninitialize();

	static bool IsEnabled() { return mEnabled; }
	static void Enable(bool val) { mEnabled = val; }

	static void AddLogger(ILogger* logger);
	static void AddFileLogger(StringRef filePath);

	//////////////////////////////////////////////////////////////////////////
	static void LogInfoFormat(const char* inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(1,2);
	static void LogInfo(const char* inString);
	static void LogErrorFormat(const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(1,2);
	static void LogError(const char* inString);

	static void LogInfo(StringRef inString){return LogInfo(inString.Buffer());}
	static void LogError(StringRef inString){return LogError(inString.Buffer());}

	static void AssertFormat(bool condition,const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(2,3);
	static void Assert(bool condition,StringRef inString);

	static void AssertFailedFormat(const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(1,2);
	static void AssertFailed(StringRef inString);
	static void AssertNotNull(const void* item,StringRef paramName);

	static void AssertNotNullFormat(const void* item,const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(2,3);

	//////////////////////////////////////////////////////////////////////////
	static void LogInfoFormat(const wchar_t* inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(1,2);
	static void LogInfo(const wchar_t* inString);
	static void LogErrorFormat(const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(1,2);
	static void LogError(const wchar_t* inString);

	static void LogInfo(WStringRef inString){return LogInfo(inString.Buffer());}
	static void LogError(WStringRef inString){return LogError(inString.Buffer());}

	static void AssertFormat(bool condition,const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(2,3);
	static void Assert(bool condition,WStringRef inString);

	static void AssertFailedFormat(const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(1,2);
	static void AssertFailed(WStringRef inString);
	static void AssertNotNull(const void* item,WStringRef paramName);
	static void AssertNotNullFormat(const void* item,const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(2,3);

private:
	static void AssertCallback();

	static List<ILogger*> mLoggers;
	static bool mEnabled;
};


#define MEDUSA_NOT_IMPLEMENT(func) Log::AssertFailed(false,#func" not implementd!");

#define LOG_ASSERT_NOT_NULL(p) Log::AssertNotNull(p,#p)
#define LOG_ASSERT_STRING_MAX_LENGTH(str,length) Log::AssertFormat(str.Length()<=length,#str" :%s length > "#length,str.c_str());
#define LOG_ASSERT_COLLECTION_MAX_COUNT(val,count) Log::AssertFormat(val.GetCount()<=count,#val" count:%d  > "#count,val.GetCount());

#define LOG_ASSERT_INT_RANGE(val,min,max) Log::AssertFormat(min<=max&&val>=min&&val<=max,#min"<= %s:%d <="#max,#val,val);



MEDUSA_END;
