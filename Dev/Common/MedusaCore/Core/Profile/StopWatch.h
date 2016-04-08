#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;



class StopWatch
{
public:
	StopWatch(const StringRef& name=StringRef::Empty,size_t runTimes=1,bool enabled=true);
public:
	void Start();
	void Stop();
	void Reset();
	void PrintResult()const;
public:
	int64 GetElapsedTicks() const {return mEnabled?mElapsedTime:0; }
	float GetElapsedMilliseconds()const{return mEnabled?(float)mElapsedTime/mTimeFreq*1000.f:0.f;}

	StringRef GetName() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	size_t GetRunTimes() const { return mRunTimes; }
	void SetRunTimes(size_t val) { mRunTimes = val; }

	bool Enabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }
private:
	HeapString mName;

	size_t mRunTimes;
	
	ProfileTimeType mTimeFreq;
	ProfileTimeType mStartTime;
	ProfileTimeType mEndTime;

	ProfileTimeType mElapsedTime;
	bool mEnabled;
	
};


MEDUSA_END;