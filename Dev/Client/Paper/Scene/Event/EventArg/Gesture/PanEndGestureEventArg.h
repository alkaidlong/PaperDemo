#pragma once

#include "BaseGestureEventArg.h"
#include "Scene/Event/Touch.h"
#include "Core/Pattern/Delegate.h"
USING_MEDUSA;

class PanEndGestureEventArg:public BaseGestureEventArg
{
public:
	PanEndGestureEventArg(IGestureRecognizer* recognizer):BaseGestureEventArg(recognizer){}
	virtual ~PanEndGestureEventArg(void){}
};

typedef Pattern::Delegate<void (INode* sender,PanEndGestureEventArg&)> PanEndEventHandler;




