#pragma once


#include "Engine/Animation/AnimationBlock.h"
#include "Engine/Animation/IAnimation.h"
#include "Core/Collection/Queue.h"
USING_MEDUSA;


class AnimationPool
{
	friend class AnimationManager;
private:
	Queue<IAnimation*> mFreeAnimations;

	unsigned int mFreeAnimationCount; 
	unsigned int mUsingAnimationCount;

private:
	AnimationPool();
	~AnimationPool();

public:

	void Clear();
	void Recycle(IAnimation* animation);
	IAnimation* GetAnimation();

public:
	int GetUsingCount() const { return mUsingAnimationCount; };
	int GetFreeCount() const { return mFreeAnimationCount; };
};


