
#include "Scene/Gesture/PanGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"


PanGestureRecognizer::PanGestureRecognizer( INode* node, float minDistance,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	Reset();
	mMinDistance = minDistance;
}


PanGestureRecognizer::~PanGestureRecognizer(void)
{
	mNode = NULL;
}

void PanGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidTouches(e);

			mCurCenter = mTouchEventArg.GetValidMiddlePoint();
			SetState(GestureState::Begin);
			PanBeginGestureEventArg t(this);
			OnBegin(mNode,t);
		}
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		if (e.IsValid())
		{
			mTouchEventArg.MergeValidTouches(e);

			mCurCenter = mTouchEventArg.GetValidMiddlePoint();
			SetState(GestureState::Begin);
			PanBeginGestureEventArg t(this);
			OnBegin(mNode,t);
		}
		break;
	default:
		break;
	}

}

void PanGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
		{
			mTouchEventArg.MoveValidTouches(e);

			Point2F curCenter = mTouchEventArg.GetValidMiddlePoint();
			mMovement = curCenter - mCurCenter;
			float distance =mMovement.Length();
			if (distance > mMinDistance)
			{
				// Valid
				SetState(GestureState::Valid);
				mCurCenter = curCenter;
				e.Handled=true;
				PanGestureEventArg t(this,mMovement);
				OnPan(mNode,t);
				CancelOtherRecognizers();
			}
			else
			{
				// Recognizing
				SetState(GestureState::Recognizing);
				mMovement = Point2F::Zero;
			}
		}
		break;
	case GestureState::Valid:
		{
			mTouchEventArg.MoveValidTouches(e);

			Point2F curCenter = mTouchEventArg.GetValidMiddlePoint();
			mMovement = curCenter - mCurCenter;
			mCurCenter = curCenter;
			e.Handled=true;
			PanGestureEventArg t(this,mMovement);
			OnPan(mNode,t);
			CancelOtherRecognizers();

		}
		break;
	default:
		break;
	}
}

void PanGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	mTouchEventArg.RemoveValidTouches(e);

	switch(mState)
	{
	case GestureState::None:
		{
			mState=GestureState::Failed;
			Reset();
			PanEndGestureEventArg t(this);
			OnEnd(mNode,t);
			e.Handled=true;
		}
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
	case GestureState::Valid:
		{
			Reset();
			PanEndGestureEventArg t(this);
			OnEnd(mNode,t);
			e.Handled=true;
		}
		break;
	default:
		break;
	}

}

void PanGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	Reset();
}

bool PanGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Valid:
		return true;
	default:
		return false;
	}
}


void PanGestureRecognizer::Reset()
{
	SetState(GestureState::None);
	mMovement = Point2F::Zero;
	mCurCenter = Point2F::Zero;
	mTouchEventArg.Clear();
}


