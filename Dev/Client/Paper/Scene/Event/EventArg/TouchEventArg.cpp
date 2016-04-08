
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/INode.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Log/Log.h"


TouchEventArg::~TouchEventArg(void)
{
}


void TouchEventArg::UpdateValidTouches( INode* node )
{
	mLocalTouches.Clear();
	mValidTouches.Clear();
	Rect2F boundingBox=node->GetBoundingBox();
	if (boundingBox!=Rect2F::Zero)
	{
		FOR_EACH_COLLECTION(i,mWorldTouches)
		{
			auto touch=*i;
			Point2F pos=node->TransformPoint(touch.Pos);
			Touch localTouch(touch.Id,pos);
			mLocalTouches.Add(localTouch);
			if (boundingBox.Contains(pos))
			{
				mValidTouches.Add(localTouch);
			}
		}
	}
	else
	{
		FOR_EACH_COLLECTION(i,mWorldTouches)
		{
			auto touch=*i;
			Point2F pos=node->TransformPoint(touch.Pos);
			Touch localTouch(touch.Id,pos);
			mLocalTouches.Add(localTouch);
			mValidTouches.Add(localTouch);

		}
	}

}

Point2F TouchEventArg::GetValidMiddlePoint() const
{
	uint count=mValidTouches.GetCount();
	switch(count)
	{
	case 0:
		return Point2F::Zero;
	case 1:
		return mValidTouches[0].Pos;
	default:
		{
			Point2F result=Point2F::Zero;
			FOR_EACH_COLLECTION(i,mValidTouches)
			{
				const Point2F& point=(*i).Pos;
				result.X+=point.X;
				result.Y+=point.Y;
			}

			result.X/=count;
			result.Y/=count;

			return result;
		}
	}

}

Point2F TouchEventArg::GetMiddlePoint() const
{
	uint count=mWorldTouches.GetCount();
	switch(count)
	{
	case 0:
		return Point2F::Zero;
	case 1:
		return mWorldTouches[0].Pos;
	default:
		{
			Point2F result;
			FOR_EACH_COLLECTION(i,mWorldTouches)
			{
				const Point2F& point=(*i).Pos;
				result.X+=point.X;
				result.Y+=point.Y;
			}

			result.X/=count;
			result.Y/=count;

			return result;
		}
	}

}



const Touch* TouchEventArg::FindWorldTouchById( int id ) const
{
	FOR_EACH_COLLECTION(i,mWorldTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return NULL;
}

const Touch* TouchEventArg::FindLocalTouchById( int id ) const
{
	FOR_EACH_COLLECTION(i,mLocalTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return NULL;
}

const Touch* TouchEventArg::FindValidTouchById( int id ) const
{
	FOR_EACH_COLLECTION(i,mValidTouches)
	{
		const Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return NULL;
}

Touch* TouchEventArg::FindValidTouchById(int id)
{
	FOR_EACH_COLLECTION(i,mValidTouches)
	{
		Touch& touch=*i;
		if (touch.Id==id)
		{
			return &touch;
		}
	}

	return NULL;
}

void TouchEventArg::PrintDebugString()
{
	FOR_EACH_COLLECTION(i,mWorldTouches)
	{
		const Touch& touch=*i;
		Log::LogInfoFormat("WorldTouch:%d (%f,%f)",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	FOR_EACH_COLLECTION(i,mLocalTouches)
	{
		const Touch& touch=*i;
		Log::LogInfoFormat("LocalTouch:%d (%f,%f)",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
	FOR_EACH_COLLECTION(i,mValidTouches)
	{
		const Touch& touch=*i;
		Log::LogInfoFormat("ValidTouch:%d (%f,%f)",touch.Id,touch.Pos.X,touch.Pos.Y);
	}
}

void TouchEventArg::Clear()
{
	mWorldTouches.Clear();
	mLocalTouches.Clear();
	mValidTouches.Clear();
}

void TouchEventArg::MergeValidTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.GetValidTouches();
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidTouchById(touch.Id);
		if (originalTouch==NULL)
		{
			AddValidTouch(touch);
		}
		else
		{
			*originalTouch=touch;
		}
	}
}

void TouchEventArg::MoveValidTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.GetValidTouches();
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidTouchById(touch.Id);
		if (originalTouch!=NULL)
		{
			*originalTouch=touch;
		}
	}
}

void TouchEventArg::RemoveValidTouches(const TouchEventArg& e)
{
	const List<Touch>& touches=e.GetWorldTouches();	//remove all even move out of view
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		Touch* originalTouch=FindValidTouchById(touch.Id);
		if (originalTouch!=NULL)
		{
			mValidTouches.Remove(touch);
		}
	}
}


