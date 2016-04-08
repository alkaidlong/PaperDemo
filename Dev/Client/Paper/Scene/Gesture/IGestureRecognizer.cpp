
#include "Scene/Gesture/IGestureRecognizer.h"
#include "Core/Geometry/Point3.h"
#include "Scene/INode.h"


IGestureRecognizer::IGestureRecognizer( INode* node ,GestureFlags flags/*=GestureFlags::None*/,const FileId& audioEffect/*=FileId::Empty*/) 
	:mNode(node),mState(GestureState::None),mFlags(flags),mAudioEffect(audioEffect)
{

}

IGestureRecognizer::~IGestureRecognizer(void)
{
	mNode=NULL;
}

void IGestureRecognizer::SetIsDisabled( bool val )
{
	if(val)
	{
		mState=GestureState::Disabled;
	}
	else
	{
		mState=GestureState::None;
	}
}

bool IGestureRecognizer::IsValidTouch( const Touch& touch ) const
{
	Point2F pos=mNode->TransformPoint(touch.Pos);
	const Rect2F& boundingBox=mNode->GetBoundingBox();
	return boundingBox.Contains(pos);
}

Touch IGestureRecognizer::TransformToNodeSpace( const Touch& touch ) const
{
	Point2F pos=mNode->TransformPoint(touch.Pos);
	return Touch(touch.Id,pos);
}

bool IGestureRecognizer::TryTransformToNodeSpace( const Touch& touch,Touch& outTouch ) const
{
	Point2F pos=mNode->TransformPoint(touch.Pos);
	const Rect2F& boundingBox=mNode->GetBoundingBox();
	if(boundingBox.Contains(pos))
	{
		outTouch=touch;
		return true;
	}
	return false;
}

bool IGestureRecognizer::HasValidTouch( const List<Touch>& touches ) const
{
	const Rect2F& boundingBox=mNode->GetBoundingBox();
	FOR_EACH_COLLECTION(i,touches)
	{
		auto touch=*i;
		Point2F pos=mNode->TransformPoint(touch.Pos);
		if (boundingBox.Contains(pos))
		{
			return true;
		}
	}

	return false;
}

void IGestureRecognizer::SetState( GestureState state )
{
	StateChangedEvent(mState,state);
	mState = state;
}

void IGestureRecognizer::CancelOtherRecognizers()
{
	if (mNode!=NULL)
	{
		mNode->CancelOtherRecognizers(this);
	}
}


