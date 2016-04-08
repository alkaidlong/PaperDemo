
#include "Engine/Animation/AnimationEvent.h"
#include "Core/Log/Log.h"
#include "Engine/Animation/IAnimation.h"

void AnimationEvent::InvokeCallback( unsigned int frameIndex , IAnimation* sender )
{
	RETURN_IF_EMPTY(mEvents);
	FOR_EACH_COLLECTION( i,mEvents )
	{
		unsigned int keyIndex = (*i).Key;
		if( keyIndex <= frameIndex && mEventsState.GetValue(keyIndex))
		{
			FrameHandler frameHandler = (*i).Value;
			frameHandler.Invoke(sender,keyIndex);
			mEventsState.SetValue(keyIndex,false);
		}
		else
		{
			continue;
		}
	}
}

void AnimationEvent::InvokeBeginCallback( IAnimation* sender )
{
	mBeginEvent.Invoke(sender,0);
}

void AnimationEvent::InvokeEndCallback( IAnimation* sender )
{
	FOR_EACH_COLLECTION( i,mEvents )
	{
		uint index = (*i).Key;
		if(mEventsState.GetValue(index))
		{
			FrameHandler frameHandler = (*i).Value;
			frameHandler.Invoke(sender,index);
		}
	}
	mEndEvent.Invoke(sender,IAnimation::AnimationCallBackLast);
	mEvents.Clear();
	mEndEvent.Clear();

}

void AnimationEvent::RegisterBeginCallback( FrameHandler beginCallback )
{
 	mBeginEvent += beginCallback;
}

void AnimationEvent::RegisterEndCallback( FrameHandler endCallback )
{
	mEndEvent += endCallback;
}

void AnimationEvent::RegisterEvent(unsigned int frameIndex, FrameHandler frameCallback )
{
	if( !mEvents.ContainsKey(frameIndex) )
	{
		mEvents.Add(frameIndex,frameCallback);
		mEventsState.Add(frameIndex,true);
	}
	else
	{
		Log::AssertFailedFormat("Duplicate register event on frame:%d",frameIndex);
	}
}



AnimationEvent::AnimationEvent()
{

}

AnimationEvent::~AnimationEvent()
{

}

void AnimationEvent::Reset()
{
	FOR_EACH_COLLECTION(i,mEventsState)
	{
		(*i).Value = true;
	}
}
