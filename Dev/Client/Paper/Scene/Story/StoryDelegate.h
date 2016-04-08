#pragma once
#include "Core/Pattern/Singleton.h"
USING_MEDUSA;

#include "Scene/Story/StoryGroup.h"


class StoryDelegate 
{
public:
	StoryDelegate();
	~StoryDelegate();

	virtual bool NextStepBefore(const StoryGroup& group) = 0;
	virtual bool NextStepAfter(const StoryGroup& group) = 0;
	virtual bool StoryGroupEnd(const StoryGroup& group) = 0;
	virtual bool MessageBack(StringRef messageName) = 0;
};