
#include "Scene/Gesture/PinchGestureRecognizer.h"
#include "Scene/INode.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/Event/EventArg/Gesture/PinchGestureEventArg.h"



PinchGestureRecognizer::PinchGestureRecognizer( INode* node,GestureFlags flags/*=GestureFlags::None*/ ) :IGestureRecognizer(node,flags)
{
	Reset();
}

PinchGestureRecognizer::~PinchGestureRecognizer(void)
{
	mNode = NULL;
}

void PinchGestureRecognizer::TouchesBegan(TouchEventArg& e)
{
	switch(mState)
	{
	case GestureState::None:
	case GestureState::Recognizing:
		mTouchEventArg.MergeValidTouches(e);
		if (mTouchEventArg.GetValidTouchCount()<2)
		{
			SetState(GestureState::Recognizing);
		}
		else
		{
			SetState(GestureState::Begin);
			const List<Touch>& touches=mTouchEventArg.GetValidTouches();
			mPinchEndDistance = mPinchBeginDistance = Point2F::Distance(touches[0].Pos,touches[1].Pos);
		}
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		
		break;
	default:
		break;
	}



}

void PinchGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		{
			mTouchEventArg.MoveValidTouches(e);

			SetState(GestureState::Valid);
			mPinchBeginDistance = mPinchEndDistance;
			const List<Touch>& touches=mTouchEventArg.GetValidTouches();
			mPinchEndDistance = Point2F::Distance(touches[0].Pos,touches[1].Pos);

			//reset anchor
			CCNode* ccNode=mNode->GetDrawCCNode();
			Point2F p1 = touches[0].Pos;
			Point2F p2 = touches[1].Pos;
			Point2F middlePoint = p1 + (p2 - p1) * 0.5f;

			PinchGestureEventArg t(this,GetScaleFactor(),middlePoint);
			OnPinch(mNode,t);

			e.Handled=true;
			CancelOtherRecognizers();

		}
		break;
	default:
		break;
	}


}

void PinchGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	mTouchEventArg.RemoveValidTouches(e);
	switch(mState)
	{
	case GestureState::None:
	case GestureState::Recognizing:
		{
			mState=GestureState::Failed;
			Reset();
		}
		break;
	case GestureState::Begin:
	case GestureState::Valid:
		{
			if (mTouchEventArg.GetValidTouchCount() == 0)
			{
				SetState(GestureState::End);
				Reset();
			}
			else if (mTouchEventArg.GetValidTouchCount() == 1)
			{
				SetState(GestureState::Recognizing);
			}
		}
		break;
	default:
		break;
	}


}

void PinchGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	mState=GestureState::None;
	Reset();
}

bool PinchGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Valid:
		return true;
	default:
		return false;
	}
}

void PinchGestureRecognizer::Reset()
{
	SetState(GestureState::None);
	mPinchEndDistance = 0.f;
	mPinchBeginDistance = 0.f;
	mTouchEventArg.Clear();
}


