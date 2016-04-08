#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/DragBeganGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/DragingGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/DragEndGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/DragFailedGestureEventArg.h"
USING_MEDUSA;


class DragGestureRecognizer: public IGestureRecognizer
{
    
public:
	DragGestureRecognizer(INode* node, float delta,GestureFlags flags=GestureFlags::None);
	virtual ~DragGestureRecognizer(void);
	virtual InputType GetInputType() const{ return InputType::Drag; }

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();

	Pattern::Event<void (INode* sender,DragBeganGestureEventArg&)> OnDragBegan;
	Pattern::Event<void (INode* sender,DragingGestureEventArg&)> OnDraging;
	Pattern::Event<void (INode* sender,DragEndGestureEventArg&)> OnDragEnd;
	Pattern::Event<void (INode* sender,DragFailedGestureEventArg&)> OnDragFailed;

private:
	float mMinDistance;
	Touch mBeganTouch;
};



