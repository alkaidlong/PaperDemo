#pragma once
#include "Core/Log/ILogger.h"
#include "Core/Pattern/Delegate.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS
#define MEDUSA_STD_CALL _stdcall
#else
#define MEDUSA_STD_CALL 
#endif
typedef void (MEDUSA_STD_CALL *LogCallback)(char*);


class CallbackLogger :public ILogger
{
public:
	CallbackLogger(LogCallback callback=NULL,bool isLogHeader=true);
	virtual ~CallbackLogger(void);

	Medusa::LogCallback GetCallback() const { return mCallback; }
	void SetCallback(Medusa::LogCallback val) { mCallback = val; }
protected:
	virtual void OutputLogString(StringRef inString);
	LogCallback mCallback;
	

};

MEDUSA_END;
