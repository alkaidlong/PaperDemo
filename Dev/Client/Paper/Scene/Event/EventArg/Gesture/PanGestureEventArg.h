#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
USING_MEDUSA;

class PanGestureEventArg:public BaseGestureEventArg
{
public:
	PanGestureEventArg(IGestureRecognizer* recognizer,const Point2F& movement):BaseGestureEventArg(recognizer),Movement(movement){}
	virtual ~PanGestureEventArg(void){}
	Point2F Movement;
};

typedef Pattern::Delegate<void (INode* sender,PanGestureEventArg&)> PanEventHandler;




