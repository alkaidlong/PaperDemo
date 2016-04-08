
#include "Scene/Gesture/DragGestureRecognizer.h"
#include "Scene/Event/EventArg/TouchEventArg.h"


DragGestureRecognizer::DragGestureRecognizer( INode* node, float minDistance,GestureFlags flags/*=GestureFlags::None*/) 
	:IGestureRecognizer(node,flags)
{
	Reset();
	mMinDistance = minDistance;
	mBeganTouch=Touch::Zero;
}


DragGestureRecognizer::~DragGestureRecognizer(void)
{
	mNode = NULL;
}

void DragGestureRecognizer::TouchesBegan( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		if (e.IsValid())
		{
			mBeganTouch=e.GetFirstValidTouch();
            SetState(GestureState::Begin);
			DragBeganGestureEventArg dragBeganGestureEventArg(this,mBeganTouch);
			OnDragBegan(mNode,dragBeganGestureEventArg);
			e.Handled=dragBeganGestureEventArg.Handled;
		}
		break;
	default:
		break;
	}
    
}

void DragGestureRecognizer::TouchesMoved( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
        {
			auto nextTouch=e.FindValidTouchById(mBeganTouch.Id);
			if (nextTouch!=NULL)
			{
				Point2F movement = nextTouch->Pos-mBeganTouch.Pos;
				if (movement.Length() > mMinDistance)
				{
					// Valid
					SetState(GestureState::Valid);

					DragingGestureEventArg dragingGestureEventArg(this,*nextTouch,movement);
					OnDraging(mNode,dragingGestureEventArg);
					e.Handled=true;
					CancelOtherRecognizers();

				}
				else
				{
					// Recognizing
					SetState(GestureState::Recognizing);
				}

			}
           
        }
        break;
	case GestureState::Valid:
		{
			auto validTouch=e.FindValidTouchById(mBeganTouch.Id);
			if (validTouch!=NULL)
			{
				Point2F movement = validTouch->Pos-mBeganTouch.Pos;
				DragingGestureEventArg dragingGestureEventArg(this,*validTouch,movement);
				OnDraging(mNode,dragingGestureEventArg);
				e.Handled=true;
				CancelOtherRecognizers();

			}
		}
		break;
	default:
		break;
	}
}

void DragGestureRecognizer::TouchesEnded( TouchEventArg& e )
{
	switch(mState)
	{
	case GestureState::None:
		{
			SetState(GestureState::Failed);
			DragFailedGestureEventArg dragFailedGestureEventArg(this);
			OnDragFailed(mNode,dragFailedGestureEventArg);
            Reset();
		}
		break;
	case GestureState::Begin:
	case GestureState::Recognizing:
	case GestureState::Valid:
		{
			auto validTouch=e.FindValidTouchById(mBeganTouch.Id);
			if (validTouch!=NULL)
			{
				Point2F movement = validTouch->Pos-mBeganTouch.Pos;
				DragEndGestureEventArg dragEndGestureEventArg(this,*validTouch);
				OnDragEnd(mNode,dragEndGestureEventArg);
				e.Handled=true;
			}
		}
		break;
	default:
		break;
	}

}

void DragGestureRecognizer::TouchesCancelled( TouchEventArg& e )
{
	Reset();
}

bool DragGestureRecognizer::IsValid() const
{
	switch(mState)
	{
	case GestureState::Valid:
		return true;
	default:
		return false;
	}
}

void DragGestureRecognizer::Reset()
{
	SetState( GestureState::None);
	mBeganTouch=Touch::Zero;
}


