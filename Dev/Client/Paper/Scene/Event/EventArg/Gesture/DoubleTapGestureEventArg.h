#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
class INode;
USING_MEDUSA;

class DoubleTapGestureEventArg:public BaseGestureEventArg
{
public:
	DoubleTapGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch,float duration):BaseGestureEventArg(recognizer),TouchInfo(touch),Duration(duration){}
	virtual ~DoubleTapGestureEventArg(void){}
	Touch TouchInfo;
	float Duration;
};

typedef Pattern::Delegate<void (INode* sender,DoubleTapGestureEventArg&)> DoubleTapEventHandler;




