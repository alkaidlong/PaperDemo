#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
USING_MEDUSA;

class PinchGestureEventArg:public BaseGestureEventArg
{
public:
	PinchGestureEventArg(IGestureRecognizer* recognizer,float scaleFactor,Point2F middlePoint):BaseGestureEventArg(recognizer),ScaleFactor(scaleFactor),MiddlePoint(middlePoint){}
	virtual ~PinchGestureEventArg(void){}
	float ScaleFactor;
	Point2F MiddlePoint;
};

typedef Pattern::Delegate<void (INode* sender,PinchGestureEventArg&)> PinchEventHandler;




