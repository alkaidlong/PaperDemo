#include "MedusaCorePreCompiled.h"
#include "Core/Log/Log.h"
#include "Core/Log/FileLogger.h"

#ifdef MEDUSA_WINDOWS
#ifdef _CONSOLE
#include "Core/Log/win/WindowsConsoleLogger.h"
#define DEFAULT_LOGGER WindowsConsoleLogger
#else
#include "Core/Log/win/WindowsTraceLogger.h"
#define DEFAULT_LOGGER WindowsTraceLogger
#endif

#elif defined(MEDUSA_IOS)
#include "Core/Log/ios/IOSConsoleLogger.h"
#define DEFAULT_LOGGER IOSConsoleLogger

#elif defined(MEDUSA_ANDROID)
#include "Core/Log/android/AndroidTraceLogger.h"
#define DEFAULT_LOGGER AndroidTraceLogger
#elif defined(MEDUSA_LINUX)
#include "Core/Log/linux/LinuxConsoleLogger.h"
#define DEFAULT_LOGGER LinuxConsoleLogger
#else
#error "No plaform for default logger";

#endif

MEDUSA_BEGIN;

bool Log::Initialize()
{
	mLoggers.Append(new DEFAULT_LOGGER());
	return true;
}

bool Log::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mLoggers);
	return true;
}


void Log::AddLogger( ILogger* logger )
{
	mLoggers.Append(logger);
}

void Log::AddFileLogger( StringRef filePath )
{
	FileLogger* logger=new FileLogger(filePath);
	AddLogger(logger);
}
//////////////////////////////////////////////////////////////////////////

void Log::LogInfoFormat( const char* inFormat, ... )
{
	RETURN_IF_NULL(inFormat);
	RETURN_IF_FALSE(mEnabled);

#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogInfoFormat(inFormat,ap);
	}
#endif
}

void Log::LogInfo( const char* inString )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inString);

#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogInfo(inString);
	}
#endif
}

void Log::LogErrorFormat( const char* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogErrorFormat(inFormat,ap);
	}
#endif
}

void Log::LogError( const char* inString )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inString);

#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogError(inString);
	}

#endif
}



void Log::AssertFormat( bool condition,const char* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

	if (!condition)
	{
#ifdef MEDUSA_DEBUG
		va_list ap;
		va_start(ap, inFormat);
		HeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat(inFormat,ap);
			text=logger->GetLogStringA();
		}
		AlertViewEvent(text,Log::AssertCallback);
#endif

	}

}

void Log::Assert( bool condition,StringRef inString )
{
	RETURN_IF_FALSE(mEnabled);

	if (!condition)
	{
#ifdef MEDUSA_DEBUG
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogError(inString);
		}
#endif
		AlertViewEvent(inString,Log::AssertCallback);
	}
}

void Log::AssertFailedFormat( const char* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	HeapString text;

	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogErrorFormat(inFormat,ap);
		text=logger->GetLogStringA();

	}
	AlertViewEvent(text,Log::AssertCallback);
#endif


}

void Log::AssertFailed( StringRef inString )
{
	RETURN_IF_FALSE(mEnabled);

#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogError(inString);
	}
#endif
	AlertViewEvent(inString,Log::AssertCallback);
}

void Log::AssertNotNull(const void* item,StringRef paramName )
{
	RETURN_IF_FALSE(mEnabled);

	if (item==NULL)
	{
#ifdef MEDUSA_DEBUG
		HeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat("%s should not be null!",paramName.c_str());
			text=logger->GetLogStringA();
		}
		AlertViewEvent(text,Log::AssertCallback);
#endif

	}
}


void Log::AssertNotNullFormat( const void* item,const char* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

	if (item==NULL)
	{
#ifdef MEDUSA_DEBUG
		va_list ap;
		va_start(ap, inFormat);
		HeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat(inFormat,ap);
			text=logger->GetLogStringA();
		}
		AlertViewEvent(text,Log::AssertCallback);
#endif

	}

}

//////////////////////////////////////////////////////////////////////////

void Log::LogInfoFormat( const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogInfoFormat(inFormat,ap);
	}
#endif
}

void Log::LogInfo( const wchar_t* inString )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inString);

#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogInfo(inString);
	}
#endif
}

void Log::LogErrorFormat( const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);


#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogErrorFormat(inFormat,ap);
	}
#endif
}

void Log::LogError( const wchar_t* inString )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inString);


#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogError(inString);
	}

#endif
}

void Log::AssertFormat( bool condition,const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

	if (!condition)
	{
#ifdef MEDUSA_DEBUG
		va_list ap;
		va_start(ap, inFormat);
		WHeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat(inFormat,ap);
			text=logger->GetLogStringW();
		}
		WAlertViewEvent(text,Log::AssertCallback);
#endif

	}

}

void Log::Assert( bool condition,WStringRef inString )
{
	RETURN_IF_FALSE(mEnabled);

	if (!condition)
	{
#ifdef MEDUSA_DEBUG
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogError(inString);
		}
#endif
		WAlertViewEvent(inString,Log::AssertCallback);
	}
}

void Log::AssertFailedFormat( const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

#ifdef MEDUSA_DEBUG
	va_list ap;
	va_start(ap, inFormat);
	WHeapString text;

	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogErrorFormat(inFormat,ap);
		text=logger->GetLogStringW();

	}
	WAlertViewEvent(text,Log::AssertCallback);
#endif


}

void Log::AssertFailed( WStringRef inString )
{
	RETURN_IF_FALSE(mEnabled);

#ifdef MEDUSA_DEBUG
	FOR_EACH_COLLECTION(i,mLoggers)
	{
		ILogger* logger=*i;
		logger->LogError(inString);
	}
#endif
	WAlertViewEvent(inString,Log::AssertCallback);
}

void Log::AssertNotNull(const void* item,WStringRef paramName )
{
	RETURN_IF_FALSE(mEnabled);

	if (item==NULL)
	{
#ifdef MEDUSA_DEBUG
		WHeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat("%lss should not be null!",paramName.c_str());
			text=logger->GetLogStringW();
		}
		WAlertViewEvent(text,Log::AssertCallback);
#endif

	}
}

void Log::AssertNotNullFormat( const void* item,const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(mEnabled);
	RETURN_IF_NULL(inFormat);

	if (item==NULL)
	{
#ifdef MEDUSA_DEBUG
		va_list ap;
		va_start(ap, inFormat);
		WHeapString text;
		FOR_EACH_COLLECTION(i,mLoggers)
		{
			ILogger* logger=*i;
			logger->LogErrorFormat(inFormat,ap);
			text=logger->GetLogStringW();
		}
		WAlertViewEvent(text,Log::AssertCallback);
#endif

	}
}

void Log::AssertCallback()
{
	 assert(false);
}

Pattern::Event<void (WStringRef text,Pattern::Action0 callback)> Log::WAlertViewEvent;
Pattern::Event<void (StringRef text,Pattern::Action0 callback)> Log::AlertViewEvent;

bool Log::mEnabled=true;

List<ILogger*> Log::mLoggers;

MEDUSA_END;
