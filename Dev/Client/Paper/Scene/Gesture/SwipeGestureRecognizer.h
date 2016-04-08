#pragma once
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Scene/Event/EventArg/Gesture/SwipeGestureEventArg.h"
USING_MEDUSA;

class SwipeGestureRecognizer:public IGestureRecognizer
{
public:
	SwipeGestureRecognizer(INode* node,GestureDirection direction,float minMoveDuration, float minMovement,float minVelocity,GestureFlags flags=GestureFlags::None);
	virtual ~SwipeGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Swipe;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual bool IsValid()const;

	virtual bool Update(float dt);

	const Point2F& GetPrevPos() const { return mPrevPos; }
	const Point2F& GetCurPos() const { return mCurPos; }
	const Point2F& GetBeginPos() const { return mBeginPos; }

	Point2F GetMovement()const;
	float GetTotalMovement()const;
	float GetGestureDirectionMovement()const;

	float GetVelocity()const;
	float GetInstantVelocity()const;
	float GetCurrentFrameDuration()const;

	Point2F CurVelocity() const { return mCurVelocity; }

	Pattern::Event<void (INode* sender,SwipeGestureEventArg&)> OnSwipe;
private:
	Point2F GetMovement(const Point2F& movement)const;

private:
	Point2F mPrevPos;
	Point2F mCurPos;
	Point2F mBeginPos;
	GestureDirection mDirection;
	float mBeginTimeStamp;
	float mBeforeTimeStamp;
	float mMinMoveDuration;
	float mMinMovement;
	float mMinVelocity;

private:
	// Current Velocity
	Point2F mCurVelocity;
	
};



