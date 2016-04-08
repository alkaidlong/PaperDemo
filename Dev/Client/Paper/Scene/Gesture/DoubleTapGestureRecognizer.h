#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/TapGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/DoubleTapGestureEventArg.h"


USING_MEDUSA;


class DoubleTapGestureRecognizer:public IGestureRecognizer
{
public:
	DoubleTapGestureRecognizer(INode* node,float maxDuration=0.25f,GestureFlags flags=GestureFlags::None);
	virtual ~DoubleTapGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::DoubleTap;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void TryFireEvent(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();
	virtual bool Update(float dt);


	Pattern::Event<void (INode* sender,TapGestureEventArg&)> OnTap;
	Pattern::Event<void (INode* sender,DoubleTapGestureEventArg&)> OnDoubleTap;

private:
	Touch mBeganTouch;
	Touch mFirstSuccessTouch;

	float mMaxDuration;
	float mBeginTimeStamp;

};



