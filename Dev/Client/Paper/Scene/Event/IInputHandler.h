#pragma once

#include "Core/Pattern/IUpdatable.h"


class TouchEventArg;
class KeyDownEventArg;
class KeyUpEventArg;
class CharInputEventArg;
class ScrollEventArg;
USING_MEDUSA;

enum class InputType
{
	Tap=1,			//���
	Pinch=2,		//���
	Rotation=4,		//��ת
	Swipe=8,		//�����������ƶ�
	Pan=16,			//���ƣ������ƶ�
	LongPress=32,	//����
	Drag = 64,
	DoubleTap=128,
};

class IInputHandler:public Pattern::IUpdatable
{
public:
	virtual ~IInputHandler(){}
	virtual void TouchesBegan(TouchEventArg& e){}
	virtual void TouchesMoved(TouchEventArg& e){}
	virtual void TouchesEnded(TouchEventArg& e){}
	virtual void TouchesCancelled(TouchEventArg& e){}
	virtual void TryFireEvent(TouchEventArg& e){}


	virtual void KeyDown(KeyDownEventArg& e){}
	virtual void KeyUp(KeyUpEventArg& e){}
	virtual void CharInput(CharInputEventArg& e){}
	virtual void Scroll(ScrollEventArg& e){}

	virtual void Reset(){}
	virtual bool IsFocus()const{return false;}
};


