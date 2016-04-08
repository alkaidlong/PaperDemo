#pragma once

#include "BaseGestureEventArg.h"

USING_MEDUSA;

class DragFailedGestureEventArg:public BaseGestureEventArg
{
public:
	DragFailedGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~DragFailedGestureEventArg(void){}
};




