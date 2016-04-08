#include "MedusaCorePreCompiled.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Math/MathHeader.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;

StopWatch::StopWatch(const StringRef& name,size_t runTimes/*=1*/,bool enabled/*=true*/):mName(name),mRunTimes(runTimes),mStartTime(0),mEndTime(0),mElapsedTime(0),mEnabled(enabled)
{	
}


void StopWatch::Start()
{
	RETURN_IF_FALSE(mEnabled);
	mTimeFreq=Platform::GetTimeFreq();
	mStartTime=Platform::GetTicks();
	mEndTime=0;
	mElapsedTime=0;
}

void StopWatch::Stop()
{
	RETURN_IF_FALSE(mEnabled);
	mEndTime=Platform::GetTicks();
	mElapsedTime=mEndTime-mStartTime;
}

void StopWatch::Reset()
{
	mStartTime=0;
	mEndTime=0;
	mElapsedTime=0;

}
void StopWatch::PrintResult() const
{
	RETURN_IF_FALSE(mEnabled);
	float dt=GetElapsedMilliseconds();

	HeapString str("★★★");
	if (!mName.IsNullOrEmpty())
	{
		str.AppendFormat("%s\t",mName.Buffer());
	}

	if (mRunTimes>0&&dt!=0)
	{
		str.AppendFormat("%f / %d = %f",dt,mRunTimes,dt/mRunTimes);
	}

	str+='\n';
	MEDUSA_TRACE(str.Buffer());
}



MEDUSA_END;