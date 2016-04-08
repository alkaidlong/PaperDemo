#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/TapGestureEventArg.h"

USING_MEDUSA;


class TapGestureRecognizer:public IGestureRecognizer
{
public:
	TapGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None,const FileId& audioEffect=FileId::Empty);
	virtual ~TapGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Tap;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void TryFireEvent(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();


	Pattern::Event<void (INode* sender,TapGestureEventArg&)> OnTap;
private:
	Touch mBeganTouch;
};



