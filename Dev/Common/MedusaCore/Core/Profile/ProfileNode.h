#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Collection/List.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class ProfileNode
{
	static void InitFreq();
public:
	ProfileNode(const StringRef& name,ProfileNode* parent,size_t count=1,size_t logCount=0);
	~ProfileNode();
public:
	void Begin();
	bool End();
	void Reset();

	void Stop();
	ProfileNode* FindOrCreateChildNode(const StringRef& name,size_t count=1,size_t logCount=0);
	void PrintResult(const StringRef& totalPrefix,const StringRef& perPrefix)const;


public:
	const StringRef& GetName() const { return mName; }
	ProfileNode* GetParent() const { return mParent; }

private:
	StringRef mName;
	ProfileNode* mParent;
	List<ProfileNode*> mChildren;
	size_t mTestCount;

	size_t mTotalCount;
	ProfileTimeType mTotalTime;
	ProfileTimeType mStartTime;
	int mRecursionCounter;

	List<int64> mTimeLogs;
	size_t mMinLogIndex;
	size_t mMaxLogIndex;

	ProfileTimeType mMinTime;
	ProfileTimeType mMaxTime;

	static ProfileTimeType mSelfCost; 
	static ProfileTimeType mTimeFreq;
	MEDUSA_DECLARE_STATIC_CONSTRUCTOR();
};


MEDUSA_END;