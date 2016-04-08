#pragma once
#include "Scene/Event/IInputHandler.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Singleton.h"
class INode;
class InputDispatcher;


USING_MEDUSA;

class InputManager:public Pattern::Singleton<InputManager>,public IInputHandler
{
	friend class Pattern::Singleton<InputManager>;
	InputManager();
	~InputManager();
public:
	InputDispatcher* Register(INode* node);
	void Unregister(InputDispatcher* dispatcher);

	void SetDirty() { mIsDirty = true; }

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void KeyDown(KeyDownEventArg& e);
	virtual void KeyUp(KeyUpEventArg& e);
	virtual void CharInput(CharInputEventArg& e);
	virtual void Scroll(ScrollEventArg& e);

	virtual bool Update(float dt);

	void TouchesBeganHelper(INode* node,TouchEventArg& e);
	void TouchesMovedHelper(INode* node,TouchEventArg& e);
	void TouchesEndedHelper(INode* node,TouchEventArg& e);
	void TouchesCancelledHelper(INode* node,TouchEventArg& e);
	void TryFireEventHelper(INode* node,TouchEventArg& e);

private:
	void UpdateInputPassingRecursively();

	void KeyDownHelper(INode* node,KeyDownEventArg& e);
	void KeyUpHelper(INode* node,KeyUpEventArg& e);
	void CharInputHelper(INode* node,CharInputEventArg& e);
	void ScrollHelper(INode* node,ScrollEventArg& e);
private:
	Dictionary<INode*,InputDispatcher*> mDispatchers;
	bool mIsDirty;
};


