#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
USING_MEDUSA;

class PanBeginGestureEventArg:public BaseGestureEventArg
{
public:
	PanBeginGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~PanBeginGestureEventArg(void){}
};

typedef Pattern::Delegate<void (INode* sender,PanBeginGestureEventArg&)> PanBeginEventHandler;




