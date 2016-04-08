#include "MedusaCorePreCompiled.h"
#include "WindowsTraceLogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

WindowsTraceLogger::WindowsTraceLogger(bool isLogHeader/*=true*/):ILogger(isLogHeader)
{
}


WindowsTraceLogger::~WindowsTraceLogger(void)
{
}

void WindowsTraceLogger::OutputLogString( StringRef inString )
{
	WHeapString text= StringParser::ToW(inString);
	OutputDebugStringW(text.c_str());
}

void WindowsTraceLogger::OutputLogString( WStringRef inString )
{
	OutputDebugStringW(inString.c_str());
}

#endif
MEDUSA_END;
