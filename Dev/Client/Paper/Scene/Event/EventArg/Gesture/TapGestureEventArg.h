#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
USING_MEDUSA;

class TapGestureEventArg:public BaseGestureEventArg
{
public:
	TapGestureEventArg(IGestureRecognizer* recognizer,const Touch& touch):BaseGestureEventArg(recognizer),TouchInfo(touch){}
	virtual ~TapGestureEventArg(void){}
	Touch TouchInfo;
};

typedef Pattern::Delegate<void (INode* sender,TapGestureEventArg&)> TapEventHandler;




