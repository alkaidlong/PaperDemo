#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"

USING_MEDUSA;

class DragEndGestureEventArg:public BaseGestureEventArg
{
public:
	DragEndGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~DragEndGestureEventArg(void){}
	Touch TouchInfo;
};




