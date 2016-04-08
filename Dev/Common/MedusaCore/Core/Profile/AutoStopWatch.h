#pragma once
#include "MedusaCorePreCompiled.h"
MEDUSA_BEGIN;



class AutoStopWatch
{
public:
	AutoStopWatch(StopWatch& watch);
	~AutoStopWatch();
private:
	StopWatch& mStopWatch;
	
};


MEDUSA_END;