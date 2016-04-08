
#include "Scene/Gesture/DoubleTapGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"


DoubleTapGestureRecognizer::DoubleTapGestureRecognizer( INode* node ,float maxDuration/*=0.25f*/,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags),mMaxDuration(maxDuration)
{
	mBeganTouch=Touch::Zero;
	mFirstSuccessTouch=Touch::Zero;
}


DoubleTapGestureRecognizer::~DoubleTapGestureRecognizer(void)
{
	mNode=NULL;
}

void DoubleTapGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.GetFirstValidTouch();
			SetState(GestureState::Begin);
		}
		break;
	case GestureState::Begin:
		break;
	case GestureState::Recognizing:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.GetFirstValidTouch();
		}
		break;
	default:
		break;
	}

}

void DoubleTapGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
		{
			if (!e.IsValid())
			{
				SetState(GestureState::Failed);
				mBeganTouch=Touch::Zero;
			}
		}
		break;
	default:
		break;
	}

}

void DoubleTapGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			if (e.IsValid()&&e.FindValidTouchById(mBeganTouch.Id)!=NULL)
			{
				mFirstSuccessTouch=*e.FindValidTouchById(mBeganTouch.Id);
				SetState(GestureState::Recognizing);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherRecognizers();
				mBeginTimeStamp=0.f;
				return;	//DO NOT set to none
			}
			break;
		}
	case GestureState::Recognizing:
		{
			if (e.IsValid()&&e.FindValidTouchById(mBeganTouch.Id)!=NULL&&mBeginTimeStamp<=mMaxDuration)
			{
				SetState(GestureState::Valid);

				DoubleTapGestureEventArg tapEventArg(this,e.GetFirstValidTouch(),mBeginTimeStamp);
				OnDoubleTap(mNode,tapEventArg);
				SetState(GestureState::None);
				mBeganTouch=Touch::Zero;
				mFirstSuccessTouch=Touch::Zero;
				
			}
			e.Handled=true;
			CancelOtherRecognizers();
		}
		break;
	default:
		break;
	}

	SetState(GestureState::None);

}

void DoubleTapGestureRecognizer::TryFireEvent( TouchEventArg& e )
{
	if (e.IsValid())
	{
		DoubleTapGestureEventArg tapEventArg(this,e.GetFirstValidTouch(),mBeginTimeStamp);
		OnDoubleTap(mNode,tapEventArg);
		e.Handled=tapEventArg.Handled;
	}
}

void DoubleTapGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	SetState(GestureState::None);
	Reset();
}

bool DoubleTapGestureRecognizer::IsValid() const
{
	return mState==GestureState::Valid;
}

void DoubleTapGestureRecognizer::Reset()
{
	SetState(GestureState::None);
	mBeginTimeStamp=0.f;
	mBeganTouch=Touch::Zero;
	mFirstSuccessTouch=Touch::Zero;

}

bool DoubleTapGestureRecognizer::Update(float dt)
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		mBeginTimeStamp+=dt;
		break;
	case GestureState::Recognizing:
		mBeginTimeStamp+=dt;

		if (mBeginTimeStamp>mMaxDuration)
		{
			SetState(GestureState::None);
			mBeginTimeStamp=0.f;
			TapGestureEventArg tapEventArg(this,mFirstSuccessTouch);
			OnTap(mNode,tapEventArg);
			CancelOtherRecognizers();
			mFirstSuccessTouch=Touch::Zero;
		}

		break;
	case GestureState::Valid:

	default:
		break;
	}

	return true;
}



