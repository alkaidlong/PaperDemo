#include "MedusaCorePreCompiled.h"
#include "AutoStopWatch.h"
#include "StopWatch.h"

MEDUSA_BEGIN;



AutoStopWatch::AutoStopWatch(StopWatch& watch):mStopWatch(watch)
{
	mStopWatch.Start();
}

AutoStopWatch::~AutoStopWatch()
{
	mStopWatch.Stop();
}

MEDUSA_END;