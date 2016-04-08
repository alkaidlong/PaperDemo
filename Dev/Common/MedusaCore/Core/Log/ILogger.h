#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

STRONG_FLAGS_CUSTOM_2(LogLevel,Info,0x1,Error,0x2);

class ILogger
{
public:
	ILogger(bool isLogHeader=true);
	virtual ~ILogger(void);
	StringRef GetLogStringA() const { return mBufferA.GetItems(); }
	WStringRef GetLogStringW() const { return mBufferW.GetItems(); }


	LogLevel GetCurrentLevel() const { return mCurrentLevel; }
	void SetCurrentLevel(LogLevel inCurrentLevel) { mCurrentLevel = inCurrentLevel; }
	bool IsLogInfo(){return mCurrentLevel.HasFlag(LogLevel::Info);}
	bool IsLogError(){return mCurrentLevel.HasFlag(LogLevel::Error);}
	bool IsLogAll(){return mCurrentLevel.HasFlag(LogLevel::All);}

	bool IsLogHeadder() const { return mIsLogHeadder; }
	void SetIsLogHeadder(bool inIsLogHeadder) { mIsLogHeadder = inIsLogHeadder; }
public:
	virtual void LogInfoFormat(const char* inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(2,3);
	virtual void LogInfoFormat(const char* inFormat, va_list args);
	virtual void LogInfo(StringRef inString);

	virtual void LogErrorFormat(const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(2,3);
	virtual void LogErrorFormat(const char* inFormat, va_list args);
	virtual void LogError(StringRef inString);

	virtual void AssertFormat(bool condition,const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(3,4);
	virtual void AssertFormat(bool condition,const char* inFormat, va_list args);
	virtual void Assert(bool condition,StringRef inString);

	virtual void AssertFailedFormat(const char*  inFormat, ... ) MEDUSA_CHECK_AS_PRINTF_FORMAT(2,3);
	virtual void AssertFailedFormat(const char* inFormat, va_list args);
	virtual void AssertFailed(StringRef inString);
public:
	virtual void LogInfoFormat(const wchar_t* inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(2,3);
	virtual void LogInfoFormat(const wchar_t* inFormat, va_list args);
	virtual void LogInfo(WStringRef inString);

	virtual void LogErrorFormat(const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(2,3);
	virtual void LogErrorFormat(const wchar_t* inFormat, va_list args);
	virtual void LogError(WStringRef inString);

	virtual void AssertFormat(bool condition,const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(3,4);
	virtual void AssertFormat(bool condition,const wchar_t* inFormat, va_list args);
	virtual void Assert(bool condition,WStringRef inString);

	virtual void AssertFailedFormat(const wchar_t*  inFormat, ... ) MEDUSA_CHECK_AS_WPRINTF_FORMAT(2,3);
	virtual void AssertFailedFormat(const wchar_t* inFormat, va_list args);
	virtual void AssertFailed(WStringRef inString);
protected:
	void LogHeaderInBufferA();
	void LogHeaderInBufferW();

	virtual void OutputLogString(StringRef inString)=0;
	virtual void OutputLogString(WStringRef inString)=0;

protected:
	LogLevel mCurrentLevel;
	
	bool mIsLogHeadder;
	List<char> mBufferA;
	List<wchar_t> mBufferW;
};

MEDUSA_END;
