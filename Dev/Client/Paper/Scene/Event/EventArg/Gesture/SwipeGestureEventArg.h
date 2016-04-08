#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
#include "Scene/Gesture/IGestureRecognizer.h"

USING_MEDUSA;

class SwipeGestureEventArg:public BaseGestureEventArg
{
public:
	SwipeGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~SwipeGestureEventArg(void){}
	Touch TouchInfo;
};

typedef Pattern::Delegate<void (INode* sender,SwipeGestureEventArg&)> SwipeEventHandler;




