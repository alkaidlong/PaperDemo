#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"

USING_MEDUSA;

class DragingGestureEventArg:public BaseGestureEventArg
{
public:
	DragingGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch,Point2F movement):BaseGestureEventArg(recognizer),TouchInfo(touch),Movement(movement){}
	virtual ~DragingGestureEventArg(void){}
	Touch TouchInfo;
	Point2F Movement;
};




