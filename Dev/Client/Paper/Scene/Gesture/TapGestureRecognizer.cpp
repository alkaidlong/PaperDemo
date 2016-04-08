
#include "Scene/Gesture/TapGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Engine/Audio/AudioManager.h"


TapGestureRecognizer::TapGestureRecognizer( INode* node ,GestureFlags flags/*=GestureFlags::None*/,const FileId& audioEffect/*=FileId::Empty*/) 
	:IGestureRecognizer(node,flags,audioEffect)
{
	mBeganTouch=Touch::Zero;
}


TapGestureRecognizer::~TapGestureRecognizer(void)
{
	mNode=NULL;
}

void TapGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsOneFingerValid())
		{
			mBeganTouch=e.GetFirstValidTouch();
			SetState(GestureState::Begin);
			if (mFlags.HasFlag(GestureFlags::SuppressTouchBegan))
			{
				e.Handled=true;
			}
		}
		break;
	case GestureState::Begin:
		break;
	default:
		break;
	}

}

void TapGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			if (!e.IsValid())
			{
				SetState(GestureState::Failed);
				mBeganTouch=Touch::Zero;
				//e.Handled=true;

			}
		}
		break;
	default:
		break;
	}

}

void TapGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
		{
			if (e.IsValid()&&e.FindValidTouchById(mBeganTouch.Id)!=NULL)
			{
				if (!mFlags.HasFlag(GestureFlags::SuppressAudio))
				{
					AudioManager::Instance().PlayEffect(mAudioEffect.ToFileId());
				}

				SetState(GestureState::Valid);
				TapGestureEventArg tapEventArg(this,e.GetFirstValidTouch());
				OnTap(mNode,tapEventArg);
				SetState(GestureState::None);
				mBeganTouch=Touch::Zero;
				e.Handled=true;
				CancelOtherRecognizers();

			}
		}
		break;
	default:
		break;
	}

	SetState(GestureState::None);
}

void TapGestureRecognizer::TryFireEvent( TouchEventArg& e )
{
	if (e.IsValid())
	{
		TapGestureEventArg tapEventArg(this,e.GetFirstValidTouch());
		OnTap(mNode,tapEventArg);
		e.Handled=tapEventArg.Handled;
	}
}

void TapGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	SetState(GestureState::None);
}

bool TapGestureRecognizer::IsValid() const
{
	return mState==GestureState::Valid;
}

void TapGestureRecognizer::Reset()
{
	SetState(GestureState::None);
}



