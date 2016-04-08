#pragma once
#include "BaseGestureEventArg.h"

USING_MEDUSA;
class LongPressFailedGestureEventArg:public BaseGestureEventArg
{
public:
	LongPressFailedGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~LongPressFailedGestureEventArg(void){}
};




