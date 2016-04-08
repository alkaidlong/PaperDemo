#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/LongPressBeganGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/LongPressFailedGestureEventArg.h"

USING_MEDUSA;

class LongPressGestureRecognizer:public IGestureRecognizer
{
	
public:
	LongPressGestureRecognizer(INode* node,float minPressDuration,float allowMovement,GestureFlags flags=GestureFlags::None);
	virtual ~LongPressGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::LongPress;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual bool Update(float dt);
	virtual void Reset();
	virtual bool IsValid()const;

	typedef Pattern::Delegate<void (INode* sender,LongPressBeganGestureEventArg&)> LongPressBeganEventHandler;
	typedef Pattern::Delegate<void (INode* sender,LongPressFailedGestureEventArg&)> LongPressFailedEventHandler;

	Pattern::Event<void (INode* sender,LongPressBeganGestureEventArg&)> OnLongPressBegan;
	Pattern::Event<void (INode* sender,LongPressFailedGestureEventArg&)> OnLongPressFailed;


private:
	float mMinPressDuration;
	float mAllowMovement;

	Touch mBeganTouch;
	float mBeginTimeStamp;
};



