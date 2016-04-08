#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/PinchGestureEventArg.h"


USING_MEDUSA;
class PinchGestureRecognizer:public IGestureRecognizer
{
public:
	PinchGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None);
	virtual ~PinchGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Pinch;}

	float GetPinchBeginDistance() const { return mPinchBeginDistance; }
	float GetPinchEndDistance() const { return mPinchEndDistance; }
	float GetScaleFactor()const{return mPinchEndDistance/mPinchBeginDistance;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
    
	virtual bool IsValid()const;
    
    void Reset();
	Pattern::Event<void (INode* sender,PinchGestureEventArg&)> OnPinch;

private:
private:
	float mPinchBeginDistance;
	float mPinchEndDistance;

};



