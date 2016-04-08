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
	Tap=1,			//点击
	Pinch=2,		//捏合
	Rotation=4,		//旋转
	Swipe=8,		//滑动，快速移动
	Pan=16,			//拖移，慢速移动
	LongPress=32,	//长按
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


