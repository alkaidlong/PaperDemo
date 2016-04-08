#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/PanGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PanBeginGestureEventArg.h"
#include "Scene/Event/EventArg/Gesture/PanEndGestureEventArg.h"


USING_MEDUSA;
class PanGestureRecognizer:public IGestureRecognizer
{
    
public:
	PanGestureRecognizer(INode* node, float minDistance,GestureFlags flags=GestureFlags::None);
	virtual ~PanGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Pan;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);

	const Point2F& GetMovement() const { return mMovement; }

	virtual bool IsValid()const;
	virtual void Reset();

	Pattern::Event<void (INode* sender,PanGestureEventArg&)> OnPan;
	Pattern::Event<void (INode* sender,PanBeginGestureEventArg&)> OnBegin;
	Pattern::Event<void (INode* sender,PanEndGestureEventArg&)> OnEnd;

	
private:
	float mMinDistance;
    Point2F mCurCenter;
    Point2F mMovement;


};



