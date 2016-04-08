
#include "Scene/Gesture/SwipeGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Core/Math/MathHeader.h"


SwipeGestureRecognizer::SwipeGestureRecognizer( INode* node,GestureDirection direction ,float minMoveDuration,float minMovement,float minVelocity,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	mDirection=direction;
	mPrevPos=Point2F::Zero;
	mCurPos=Point2F::Zero;
	mBeginPos=Point2F::Zero;
	mBeginTimeStamp=0.f;
	mBeforeTimeStamp=mBeginTimeStamp;
	mMinMoveDuration=minMoveDuration;
	mMinMovement=minMovement;
	mMinVelocity=minVelocity;
}


SwipeGestureRecognizer::~SwipeGestureRecognizer(void)
{
	mNode=NULL;
}

void SwipeGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
// 	switch(mState)
// 	{
// 	case GestureState::None:
// 		if (e.IsValid())
// 		{
// 			mBeginPos=e.GetMiddlePoint();
// 			mPrevPos=mBeginPos;
// 			mBeginTimeStamp=0.f;
// 			mBeforeTimeStamp = mBeginTimeStamp;
// 			mState=GestureState::Begin;
// 			e.Handled=true;
// 			mTarget.Invoke(&e);
// 		}
// 		break;
// 	default:
// 		break;
// 	}
}

void SwipeGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
//	switch(mState)
//	{
//	case GestureState::None:
//		break;
//	case GestureState::Begin:
//		{
//			if (mBeginTimeStamp<mMinMoveDuration)
//			{
//				//don't move
//
//			}
//			else
//			{
//				//first move
//				mState=GestureState::Valid;
//				mCurPos=e.GetMiddlePoint();
//				e.SetUIGestureRecognizer(this);
//				e.SetNode(mNode);
//				mTarget.Invoke(&e);
//				// Record the current velocity
//				mCurVelocity = ccpSub(mCurPos, mPrevPos);
//				mPrevPos=mCurPos;
//				e.SetIsCancelled(true);
//			}
//		
//		}
//
//		break;
//
//	case GestureState::Valid:
//		{
//			//first move
//			mCurPos=e.GetMiddlePoint();
//			e.SetUIGestureRecognizer(this);
//			e.SetNode(mNode);
//			mTarget.Invoke(&e);
//			// Record the current velocity
//			mCurVelocity = ccpSub(mCurPos, mPrevPos);
//			mPrevPos=mCurPos;
//			e.SetIsCancelled(true);
//		}
//		break;
//	default:
//		break;
//	}
//	return true;
}

void SwipeGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
//	switch(mState)
//	{
//	case GestureState::None:
//	case GestureState::Begin:
//		{
//			mState=GestureState::Failed;
//			e.SetUIGestureRecognizer(this);
//			e.SetNode(mNode);
//			mTarget.Invoke(&e);
//		}
//		break;
//	case GestureState::Valid:
//		{
//			mCurPos=e.GetMiddlePoint();
//			float totalMovement=GetTotalMovement();
//			float velocity=GetVelocity();
//			if (fabs(totalMovement)>mMinMovement||velocity>mMinVelocity)
//			{
//				mState=GestureState::End;
//				e.SetUIGestureRecognizer(this);
//				e.SetNode(mNode);
//				mTarget.Invoke(&e);
//				mPrevPos=mCurPos;
//
//				e.SetIsCancelled(true);
//				e.ResetOtherGestureRecursively();
//			}
//
//		}
//		break;
//	default:
//		break;
//	}
//
	mState=GestureState::None;
}

void SwipeGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	mState=GestureState::None;
}

bool SwipeGestureRecognizer::Update( float dt )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		mBeforeTimeStamp = mBeginTimeStamp;
		mBeginTimeStamp+=dt;
		break;
		break;
	default:
		break;
	}

	return true;
}

float SwipeGestureRecognizer::GetVelocity() const
{
	float distance=GetTotalMovement();

	if (distance<0.000001f)
	{
		return 0.f;
	}

	if (mBeginTimeStamp>0.000001f)
	{
		return distance/mBeginTimeStamp;
	}

	return Math::FloatMaxValue;
}

float SwipeGestureRecognizer::GetInstantVelocity() const
{
	float dt = mBeginTimeStamp - mBeforeTimeStamp;
	if (dt>0.000001f)
	{
		switch(mDirection)
		{
		case GestureDirection::Horizontal:
			return GetMovement().X / dt;
		case GestureDirection::Vertical:
			return GetMovement().Y / dt;
		}
	}
	return Math::FloatMaxValue;
}

float SwipeGestureRecognizer::GetGestureDirectionMovement() const
{
	switch(mDirection)
	{
	case GestureDirection::Horizontal:
		return mCurPos.X - mPrevPos.X;
	case GestureDirection::Vertical:
		return mCurPos.Y - mPrevPos.Y;
	default:
		return 0.0f;
	}
}

float SwipeGestureRecognizer::GetCurrentFrameDuration() const
{
	return mBeginTimeStamp - mBeforeTimeStamp;
}

Point2F SwipeGestureRecognizer::GetMovement() const
{
	Point2F movement(mCurPos.X-mPrevPos.X,mCurPos.Y-mPrevPos.Y);
	return GetMovement(movement);
}

float SwipeGestureRecognizer::GetTotalMovement() const
{
	Point2F movePoint(mCurPos.X-mBeginPos.X,mCurPos.Y-mBeginPos.Y);
	Point2F movement= GetMovement(movePoint);
	float distance=sqrt(movement.X*movement.X+movement.Y*movement.Y);
	return distance;
}


Point2F SwipeGestureRecognizer::GetMovement(const Point2F& movement) const
{
	/*switch(mDirection)
	{
	case GestureDirection::Horizontal:
	return ccp(movement.X,0.f);
	break;
	case GestureDirection::Vertical:
	return ccp(0.f,movement.y);
	break;
	}*/

	return Point2F::Zero;
}

bool SwipeGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Begin:
	case GestureState::Valid:
	case GestureState::End:
		return true;
	default:
		return false;
	}
}



