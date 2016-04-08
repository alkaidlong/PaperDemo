#include "MedusaCorePreCompiled.h"
#include "ILogger.h"
#include "Core/String/StdString.h"


MEDUSA_BEGIN;

ILogger::ILogger(bool isLogHeader/*=true*/):mBufferW(Math::ByteMaxValue)
{
	mCurrentLevel=LogLevel::All;	//open all logs
	mIsLogHeadder=isLogHeader;

	mBufferA.ReserveSize(512);
	mBufferW.ReserveSize(512);

}

ILogger::~ILogger(void)
{
}

//////////////////////////////////////////////////////////////////////////

void ILogger::LogHeaderInBufferA()
{
	time_t tNowTime;
	time(&tNowTime);

	tm localTime;
#ifdef WIN32
	int errorId= localtime_s(&localTime,&tNowTime);
#else
	localtime_r(&tNowTime,&localTime);
#endif

	StdString::SPrintf(mBufferA.GetItems(),mBufferA.GetSize(),"%d-%d-%d %d:%d:%d => ",
		localTime.tm_year+1900,localTime.tm_mon+1,localTime.tm_mday,localTime.tm_hour,localTime.tm_min,localTime.tm_sec);

	OutputLogString(mBufferA.GetItems());
}


void ILogger::LogInfoFormat( const char* inFormat, ... )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	va_list ap;
	va_start(ap, inFormat);

	int size=StdString::GetFormatLength(inFormat,ap)+1;
	mBufferA.ReserveSize(size);
	StdString::VSNPrintf(mBufferA.GetItems(), mBufferA.GetSize(), size,inFormat, ap);

	va_end(ap);

	OutputLogString(mBufferA.GetItems());
	OutputLogString("\n");
}

void ILogger::LogInfoFormat( const char* inFormat, va_list args )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	int size=StdString::GetFormatLength(inFormat,args)+1;
	mBufferA.ReserveSize(size);
	StdString::VSNPrintf(mBufferA.GetItems(), mBufferA.GetSize(), size,inFormat, args);

	va_end(args);

	OutputLogString(mBufferA.GetItems());
	OutputLogString("\n");
}


void ILogger::LogInfo( StringRef inString )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	OutputLogString(inString);
	OutputLogString("\n");
}



void ILogger::LogErrorFormat( const char* inFormat, ... )
{
	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	OutputLogString("ERROR: ");

	va_list ap;
	va_start(ap, inFormat);

	int size=StdString::GetFormatLength(inFormat,ap)+1;
	mBufferA.ReserveSize(size);
	StdString::VSNPrintf(mBufferA.GetItems(), mBufferA.GetSize(), size,inFormat, ap);

	va_end(ap);

	OutputLogString(mBufferA.GetItems());
	OutputLogString("\n");
}

void ILogger::LogErrorFormat( const char* inFormat, va_list args )
{
	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	OutputLogString("ERROR: ");


	int size=StdString::GetFormatLength(inFormat,args)+1;
	mBufferA.ReserveSize(size);
	StdString::VSNPrintf(mBufferA.GetItems(), mBufferA.GetSize(), size,inFormat, args);

	va_end(args);

	OutputLogString(mBufferA.GetItems());
	OutputLogString("\n");
}

void ILogger::LogError( StringRef inString )
{

	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferA();
	}

	OutputLogString("ERROR: ");

	OutputLogString(inString);
	OutputLogString("\n");
}

void ILogger::AssertFormat( bool condition,const char* inFormat, ... )
{
	if (!condition)
	{
		if(IsLogError())
		{
			va_list ap;
			va_start(ap, inFormat);
			LogErrorFormat(inFormat,ap);
		}

		assert(false);
	}

}

void ILogger::AssertFormat( bool condition,const char* inFormat, va_list args )
{
	if (!condition)
	{
		LogErrorFormat(inFormat,args);
		assert(false);
	}
}

void ILogger::Assert( bool condition,StringRef inString )
{
	if (!condition)
	{
		LogError(inString);
		assert(false);
	}

}

void ILogger::AssertFailedFormat( const char* inFormat, ... )
{
	if(IsLogError())
	{
		va_list ap;
		va_start(ap, inFormat);
		LogErrorFormat(inFormat,ap);
	}

	assert(false);
}

void ILogger::AssertFailedFormat( const char* inFormat, va_list args )
{
	LogErrorFormat(inFormat,args);
	assert(false);
}

void ILogger::AssertFailed( StringRef inString )
{
	LogError(inString);
	assert(false);
}

//////////////////////////////////////////////////////////////////////////

void ILogger::LogHeaderInBufferW()
{
	time_t tNowTime;
	time(&tNowTime);

	tm localTime;
#ifdef WIN32
	int errorId= localtime_s(&localTime,&tNowTime);
#else
	localtime_r(&tNowTime,&localTime);
#endif

	StdString::SPrintf(mBufferW.GetItems(),mBufferW.GetSize(),L"%d-%d-%d %d:%d:%d => ",
		localTime.tm_year+1900,localTime.tm_mon+1,localTime.tm_mday,localTime.tm_hour,localTime.tm_min,localTime.tm_sec);

	OutputLogString(mBufferW.GetItems());
}


void ILogger::LogInfoFormat( const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	va_list ap;
	va_start(ap, inFormat);
	int size=StdString::GetFormatLength(inFormat,ap)+1;
	mBufferW.ReserveSize(size);
	StdString::VSNPrintf(mBufferW.GetItems(), mBufferW.GetSize(), size,inFormat, ap);

	va_end(ap);

	OutputLogString(mBufferW.GetItems());
	OutputLogString(L"\n");
}

void ILogger::LogInfoFormat( const wchar_t* inFormat, va_list args )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	int size=StdString::GetFormatLength(inFormat,args)+1;
	mBufferW.ReserveSize(size);
	StdString::VSNPrintf(mBufferW.GetItems(), mBufferW.GetSize(), size,inFormat, args);

	va_end(args);

	OutputLogString(mBufferW.GetItems());
	OutputLogString(L"\n");
}


void ILogger::LogInfo( WStringRef inString )
{
	RETURN_IF_FALSE(IsLogInfo());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	OutputLogString(inString);
	OutputLogString(L"\n");
}



void ILogger::LogErrorFormat( const wchar_t* inFormat, ... )
{
	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	OutputLogString(L"ERROR: ");

	va_list ap;
	va_start(ap, inFormat);

	int size=StdString::GetFormatLength(inFormat,ap)+1;
	mBufferW.ReserveSize(size);
	StdString::VSNPrintf(mBufferW.GetItems(), mBufferW.GetSize(), size,inFormat, ap);

	va_end(ap);

	OutputLogString(mBufferW.GetItems());
	OutputLogString(L"\n");
}

void ILogger::LogErrorFormat( const wchar_t* inFormat, va_list args )
{
	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	OutputLogString(L"ERROR: ");

	int size=StdString::GetFormatLength(inFormat,args)+1;
	mBufferW.ReserveSize(size);
	StdString::VSNPrintf(mBufferW.GetItems(), mBufferW.GetSize(), size,inFormat, args);

	va_end(args);

	OutputLogString(mBufferW.GetItems());
	OutputLogString(L"\n");
}

void ILogger::LogError( WStringRef inString )
{

	RETURN_IF_FALSE(IsLogError());

	if (mIsLogHeadder)
	{
		LogHeaderInBufferW();
	}

	OutputLogString(L"ERROR: ");

	OutputLogString(inString);
	OutputLogString(L"\n");
}

void ILogger::AssertFormat( bool condition,const wchar_t* inFormat, ... )
{
	if (!condition)
	{
		if(IsLogError())
		{
			va_list ap;
			va_start(ap, inFormat);
			LogErrorFormat(inFormat,ap);
		}

		assert(false);
	}

}

void ILogger::AssertFormat( bool condition,const wchar_t* inFormat, va_list args )
{
	if (!condition)
	{
		LogErrorFormat(inFormat,args);
		assert(false);
	}
}

void ILogger::Assert( bool condition,WStringRef inString )
{
	if (!condition)
	{
		LogError(inString);
		assert(false);
	}

}

void ILogger::AssertFailedFormat( const wchar_t* inFormat, ... )
{
	if(IsLogError())
	{
		va_list ap;
		va_start(ap, inFormat);
		LogErrorFormat(inFormat,ap);
	}

	assert(false);
}

void ILogger::AssertFailedFormat( const wchar_t* inFormat, va_list args )
{
	LogErrorFormat(inFormat,args);
	assert(false);
}

void ILogger::AssertFailed( WStringRef inString )
{
	LogError(inString);
	assert(false);
}
MEDUSA_END;
