#include "MedusaCorePreCompiled.h"
#include "AndroidTraceLogger.h"

MEDUSA_BEGIN;


#ifdef MEDUSA_ANDROID

AndroidTraceLogger::AndroidTraceLogger(bool isLogHeader/*=true*/):ILogger(isLogHeader)
{
}


AndroidTraceLogger::~AndroidTraceLogger(void)
{
}

void AndroidTraceLogger::OutputLogString( StringRef inString )
{

	__android_log_print(ANDROID_LOG_DEBUG,"Medusa",inString.c_str());
	//assert(false);

}

void AndroidTraceLogger::OutputLogString( WStringRef inString )
{
	//__android_log_print(ANDROID_LOG_DEBUG,"Medusa",inString.c_str());
	//CCLog( "OutputLog" );

	//assert(false);
	//__android_log_print(ANDROID_LOG_DEBUG,"Medusa",inString.c_str());
}

#endif

MEDUSA_END;
