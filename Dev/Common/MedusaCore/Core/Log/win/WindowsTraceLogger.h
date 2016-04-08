#pragma once
#include "Core/Log/ILogger.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

class WindowsTraceLogger :public ILogger
{
public:
	WindowsTraceLogger(bool isLogHeader=true);
	virtual ~WindowsTraceLogger(void);

protected:
	virtual void OutputLogString(StringRef inString);
	virtual void OutputLogString(WStringRef inString);


};

#endif
MEDUSA_END;
