#include "IOSConsoleLogger.h"

#ifdef MEDUSA_IOS
MEDUSA_BEGIN;
IOSConsoleLogger::IOSConsoleLogger(bool isLogHeader/*=true*/):ILogger(isLogHeader)
{
}


IOSConsoleLogger::~IOSConsoleLogger(void)
{
}

void IOSConsoleLogger::OutputLogString( StringRef inString )
{
    printf("%s",inString.c_str());
   // NSString *pStr = [[NSString alloc] initWithCString:inString  encoding:NSASCIIStringEncoding];
   
   // NSLog(@"%@",pStr);
}

void IOSConsoleLogger::OutputLogString( WStringRef inString )
{
    wprintf(L"%ls",inString.c_str());
   // NSString *pStr = [[NSString alloc] initWithCString:inString  encoding:NSASCIIStringEncoding];
   
   // NSLog(@"%@",pStr);
}

MEDUSA_END;
#endif