#pragma once
#include "Core/Event/EventArg/IEventArg.h"

class INode;
class IGestureRecognizer;
USING_MEDUSA;

class BaseGestureEventArg:public IEventArg
{
public:
	BaseGestureEventArg(IGestureRecognizer* recognizer):Recognizer(recognizer){}
	virtual ~BaseGestureEventArg(void){}
	IGestureRecognizer* Recognizer;
};

