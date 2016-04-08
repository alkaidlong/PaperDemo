
#include "Scene/Gesture/LongPressGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"


LongPressGestureRecognizer::LongPressGestureRecognizer( INode* node,float minPressDuration,float allowMovement ,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	mMinPressDuration=minPressDuration;
	mAllowMovement=allowMovement;
	mBeginTimeStamp=0.f;
	mState=GestureState::None;
	mBeganTouch=Touch::Zero;
}


LongPressGestureRecognizer::~LongPressGestureRecognizer(void)
{
	mNode=NULL;
}


void LongPressGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.GetFirstValidTouch();
			mBeginTimeStamp=0.f;
			SetState(GestureState::Begin);
		}
		break;
	case GestureState::Valid:
		break;
	default:
		break;
	}

}

void LongPressGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			auto nextTouch=e.FindValidTouchById(mBeganTouch.Id);
			if (nextTouch!=NULL)
			{
				float distance=Point2F::Distance(mBeganTouch.Pos,nextTouch->Pos);
				if (distance>mAllowMovement)
				{
					SetState(GestureState::None);
				}
			}
		}

		break;
	case GestureState::Valid:
		break;
	default:
		break;
	}
	
}

void LongPressGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
	case GestureState::Begin:
		{
			SetState(GestureState::Failed);

			LongPressFailedGestureEventArg longPressFailedGestureEventArg(this);
			OnLongPressFailed(mNode,longPressFailedGestureEventArg);
			e.Handled=longPressFailedGestureEventArg.Handled;
		}

		break;
	case GestureState::Valid:
		{
			SetState(GestureState::End);
		}
		
		break;
	default:
		break;
	}

	SetState(GestureState::None);

}

void LongPressGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	SetState(GestureState::None);
}

bool LongPressGestureRecognizer::Update( float dt )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		mBeginTimeStamp+=dt;
		if (mBeginTimeStamp>mMinPressDuration)
		{
			SetState(GestureState::Valid);
			mBeginTimeStamp=0.f;

			LongPressBeganGestureEventArg longPressBeganGestureEventArg(this);
			OnLongPressBegan(mNode,longPressBeganGestureEventArg);
			CancelOtherRecognizers();

		}

		break;
	case GestureState::Valid:

	default:
		break;
	}

	return true;

}

void LongPressGestureRecognizer::Reset()
{
	mBeginTimeStamp=0.f;
	SetState(GestureState::None);
	mBeganTouch=Touch::Zero;
}

bool LongPressGestureRecognizer::IsValid() const
{
	return mState==GestureState::Valid;
}

