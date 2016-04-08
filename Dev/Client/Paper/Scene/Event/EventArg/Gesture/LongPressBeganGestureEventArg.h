#pragma once

#include "BaseGestureEventArg.h"

USING_MEDUSA;

class LongPressBeganGestureEventArg:public BaseGestureEventArg
{
public:
	LongPressBeganGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~LongPressBeganGestureEventArg(void){}
};




