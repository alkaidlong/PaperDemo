#include "MedusaCorePreCompiled.h"
#include "WindowsConsoleLogger.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

WindowsConsoleLogger::WindowsConsoleLogger(bool isLogHeader/*=true*/):ILogger(isLogHeader)
{
}


WindowsConsoleLogger::~WindowsConsoleLogger(void)
{
}

void WindowsConsoleLogger::OutputLogString( StringRef inString )
{
	printf("%s",inString.c_str());
}

void WindowsConsoleLogger::OutputLogString( WStringRef inString )
{
	wprintf(L"%s",inString.c_str());
}
#endif

MEDUSA_END;
