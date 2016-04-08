#pragma once
#include "Core/Log/ILogger.h"
#include "Core/IO/Stream/FileStream.h"

MEDUSA_BEGIN;

class FileLogger :public ILogger
{
public:
	FileLogger(StringRef filePath,bool isLogHeader=true);
	virtual ~FileLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);

private:
	
	FileStream mWriter;
};

MEDUSA_END;
