#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
USING_MEDUSA;


class DragBeganGestureEventArg:public BaseGestureEventArg
{
public:
	DragBeganGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~DragBeganGestureEventArg(void){}
	Touch TouchInfo;
};




