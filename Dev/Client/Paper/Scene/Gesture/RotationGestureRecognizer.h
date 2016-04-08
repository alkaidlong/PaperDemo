#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
USING_MEDUSA;

class RotationGestureRecognizer:public IGestureRecognizer
{
public:
	RotationGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None):IGestureRecognizer(node,flags){}
	virtual ~RotationGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Rotation;}
};



