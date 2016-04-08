#include "MedusaCorePreCompiled.h"
#include "FileLogger.h"

MEDUSA_BEGIN;

FileLogger::FileLogger(StringRef filePath,bool isLogHeader/*=true*/):ILogger(isLogHeader),mWriter(filePath)
{
	
}


FileLogger::~FileLogger(void)
{
	
}

void FileLogger::OutputLogString( StringRef inString )
{
	mWriter.WriteString(inString);
}

void FileLogger::OutputLogString( WStringRef inString )
{
	mWriter.WriteString(inString);
}

MEDUSA_END;
