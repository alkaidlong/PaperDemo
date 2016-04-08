#pragma once
#include "Scene/Event/IInputHandler.h"
#include "Core/Collection/Dictionary.h"
#include "Scene/Gesture/TapGestureRecognizer.h"
#include "Scene/Gesture/DragGestureRecognizer.h"
#include "Scene/Gesture/LongPressGestureRecognizer.h"
#include "Scene/Gesture/PanGestureRecognizer.h"
#include "Scene/Gesture/PinchGestureRecognizer.h"
#include "Scene/Gesture/RotationGestureRecognizer.h"
#include "Scene/Gesture/SwipeGestureRecognizer.h"
#include "Scene/Gesture/DoubleTapGestureRecognizer.h"
#include "Scene/Gesture/IGestureRecognizer.h"

USING_MEDUSA;

class InputDispatcher:public IInputHandler
{
public:
	InputDispatcher(INode* node);
	~InputDispatcher();
public:
	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void TryFireEvent(TouchEventArg& e);

	virtual void KeyDown(KeyDownEventArg& e);
	virtual void KeyUp(KeyUpEventArg& e);
	virtual void CharInput(CharInputEventArg& e);
	virtual void Scroll(ScrollEventArg& e);
	virtual bool Update(float dt);
	virtual void Reset();

public:
	TapGestureRecognizer* AddTapGestureRecognizer(const FileId& audioEffect=FileId::Empty,GestureFlags flags=GestureFlags::None);
	SwipeGestureRecognizer* AddSwipeGestureRecognizer(GestureDirection direction,float minMoveDuration, float minMovement,float minVelocity,GestureFlags flags=GestureFlags::None);
	PanGestureRecognizer* AddPanGestureRecognizer(float minDistance,GestureFlags flags=GestureFlags::None);
	PinchGestureRecognizer* AddPinchGestureRecognizer(GestureFlags flags=GestureFlags::None);
	DoubleTapGestureRecognizer* AddDoubleTapGestureRecognizer(float maxDuration,GestureFlags flags=GestureFlags::None);


public:
	void CancelOtherRecognizers(IGestureRecognizer* self);

	bool AddTapGestureHandler(TapEventHandler handler,const FileId& audioEffect=FileId::Empty,GestureFlags flags=GestureFlags::None);
	bool RemoveTapGestureHandler(TapEventHandler handler);
	bool RemoveAllTapGestureHandler();

	bool AddSwipeGestureHandler(SwipeEventHandler handler,GestureDirection direction,float minMoveDuration, float minMovement,float minVelocity,GestureFlags flags=GestureFlags::None);
	bool RemoveSwipeGestureHandler(SwipeEventHandler handler);
	bool RemoveAllSwipeGestureHandler();

	bool AddPanGestureHandler(PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler,float minDistance,GestureFlags flags=GestureFlags::None);
	bool RemovePanGestureHandler(PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler);
	bool RemoveAllPanGestureHandler();

	bool AddPinchGestureHandler(PinchEventHandler handler,GestureFlags flags=GestureFlags::None);
	bool RemovePinchGestureHandler(PinchEventHandler handler);
	bool RemoveAllPinchGestureHandler();


	bool AddDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration,GestureFlags flags=GestureFlags::None);
	bool RemoveDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler);
	bool RemoveAllDoubleTapGestureHandler();

	//bool RegisterLongPressGesture(LongPressGestureRecognizer target,float minPressDuration,float allowMovement,bool enableTouch=true);

	/*bool RegisterTapGesture(const string& id,EventTarget target,bool enableTouch=true);

	bool RegisterLongPressGesture(EventTarget target,float minPressDuration,float allowMovement,bool enableTouch=true);
	bool RegisterLongPressGesture(const string& id,EventTarget target,float minPressDuration,float allowMovement,bool enableTouch=true);


	bool RegisterDragGesture(EventTarget target, float minDistance=0, bool enableTouch=true);
	bool RegisterDragGesture(const string& id, EventTarget target, float minDistance=0, bool enableTouch=true);

	bool RegisterSwipeGesture(EventTarget target,GestureDirection::GestureDirection_t direction,float minMoveDuration, float minMovement,float minVelocity,bool enableTouch=true);
	bool RegisterSwipeGesture(const string& id,EventTarget target,GestureDirection::GestureDirection_t direction,float minMoveDuration, float minMovement,float minVelocity,bool enableTouch=true);*/

	INode* GetNode() const { return mNode; }
private:
	IInputHandler* FindFocusHandler()const;
private:
	Dictionary<InputType,IInputHandler*,SafeEnumHashCoder<InputType> > mHandlers;
	INode* mNode;
};


