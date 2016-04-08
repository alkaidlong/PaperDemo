
#include "AnimationPool.h"
#include "Engine/Resource/ResourceManager.h"

AnimationPool::AnimationPool()
{
	mFreeAnimationCount = 0; 
	mUsingAnimationCount = 0;
}

AnimationPool::~AnimationPool()
{

}

void AnimationPool::Clear()
{
	FOR_EACH_COLLECTION(i,mFreeAnimations)
	{
		IAnimation* ani=*i;
		ani->release();
	}
	mFreeAnimations.Clear();
}

void AnimationPool::Recycle(IAnimation* animation)
{
	Log::Assert(animation!=NULL,"animation is NULL!");
	animation->retain();
	animation->UnInitialize();
	mFreeAnimations.Push(animation);
	animation->setFlipX(false);
	animation->setFlipY(false);
	animation->setScale(1.0f);
	animation->setOpacity( 255 );
	ccColor4B color;
	color.a = 0;
	color.b = 0;
	color.g = 0;
	color.r = 0;
	animation->SetDeltaColor(color);
	animation->setColor(ccc3(255,255,255));
	mFreeAnimationCount ++;
	mUsingAnimationCount --;
}

IAnimation* AnimationPool::GetAnimation()
{
	IAnimation* animation = NULL;
	mUsingAnimationCount ++;

 	if( ! mFreeAnimations.IsEmpty() )
 	{
 		mFreeAnimationCount--;
 		animation = mFreeAnimations.Head();
 		mFreeAnimations.Pop();
 		animation->setVisible(true);
		animation->autorelease();
		animation->SetAnimationState(IAnimation::AnimationInit);
 		return animation;
 	}
	animation = new IAnimation();
	animation->autorelease();
	return animation;
}
