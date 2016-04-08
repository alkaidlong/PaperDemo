#pragma once
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Event.h"
USING_MEDUSA;

class IAnimation;

class AnimationEvent
{
	friend class AnimationManager;
public:
	typedef Pattern::Delegate<void ( IAnimation* sender,unsigned int curFrameIndex)> FrameHandler;
	typedef Pattern::Event<void (IAnimation* sender,unsigned int curFrameIndex)> OnceEvent;
private:
	Dictionary<uint,bool> mEventsState;
	Dictionary<uint,FrameHandler> mEvents;
	OnceEvent mBeginEvent;
	OnceEvent mEndEvent;
private:
	AnimationEvent();
	~AnimationEvent();
public:
	void InvokeBeginCallback(IAnimation* sender);
	void InvokeEndCallback(IAnimation* sender);
	void InvokeCallback( unsigned int frameIndex, IAnimation* sender ) ;
	void RegisterEvent( unsigned int frameIndex,FrameHandler frameCallback );
	void RegisterBeginCallback( FrameHandler beginCallback );
	void RegisterEndCallback( FrameHandler endCallback );
	void Reset();
};

