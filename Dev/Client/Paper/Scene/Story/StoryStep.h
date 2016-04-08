#pragma once
#include "Core/Pattern/Singleton.h"
USING_MEDUSA;

#include "Core/Script/ScriptObject.h"


class StoryStep 
{
public:
	StoryStep(StringRef fun);
	~StoryStep();

	bool Initialize();
	bool UnInitialize();

	StringRef GetFunName() const { return mFunName; }
	void SetFunName(StringRef val) { mFunName = val; }
private:
	HeapString mFunName;
};