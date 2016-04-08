#include "MedusaCorePreCompiled.h"
#include "IScrollMathModel.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


IScrollMathModel::IScrollMathModel( DirectionMask direction/*=DirectionMask::All*/)
	:mDirection(direction),
	mSize(Size2F::Zero),
	mTargetBoundingBox(Rect2F::Zero),
	mPrevTargetBoundingBox(Rect2F::Zero),
	mCurrentVelocity(Point2F::Zero),
	mInitialVelocityFactor(0.8f),
	mStaticLimitX(0.f),
	mStaticLimitY(0.f),
	mSpringLimitX(0),
	mSpringLimitY(0),
	mState(ScrollState::None)
{

}

IScrollMathModel::~IScrollMathModel( void )
{

}

bool IScrollMathModel::IsVertical() const
{
	return mDirection==DirectionMask::Vertical;
}

bool IScrollMathModel::IsHorizontal() const
{
	return mDirection==DirectionMask::Horizontal;
}

void IScrollMathModel::InitializeBoundingBox(const Size2F& selfSize,const Rect2F& targetBoundingBox)
{
	mSize=selfSize;
	mTargetBoundingBox=targetBoundingBox;
	mPrevTargetBoundingBox=mTargetBoundingBox;
	OnUpdate();
}


float IScrollMathModel::ExpandBoundingBox(const Size2F& sizeAdded)
{
	float result=0.f;
	if (IsVertical())
	{
		mTargetBoundingBox.Origin.Y-=sizeAdded.Height;
		mTargetBoundingBox.Size.Height+=sizeAdded.Height;
		result=-sizeAdded.Height;
	}
	else
	{
		mTargetBoundingBox.Origin.X+=sizeAdded.Width;
		mTargetBoundingBox.Size.Width+=sizeAdded.Width;
		result=sizeAdded.Width;

	}

	mPrevTargetBoundingBox=mTargetBoundingBox;
	OnUpdate();
	return result;
}

float IScrollMathModel::CollapseBoundingBox(const Size2F& sizeRemoved)
{
	float result=0.f;

	if (IsVertical())
	{
		mTargetBoundingBox.Origin.Y+=sizeRemoved.Height;
		mTargetBoundingBox.Size.Height-=sizeRemoved.Height;
		result=sizeRemoved.Height;

	}
	else
	{
		mTargetBoundingBox.Origin.X-=sizeRemoved.Width;
		mTargetBoundingBox.Size.Width-=sizeRemoved.Width;
		result=-sizeRemoved.Width;

	}

	mPrevTargetBoundingBox=mTargetBoundingBox;
	OnUpdate();
	return result;

}


float IScrollMathModel::UpdateBoundingBox(const Size2F& originalSize,const Size2F& newSize)
{
	float result=0.f;

	if (IsVertical())
	{
		float deltaHeight=newSize.Height-originalSize.Height;
		mTargetBoundingBox.Origin.Y-=deltaHeight;
		mTargetBoundingBox.Size.Height+=deltaHeight;
		result=deltaHeight;
	}
	else
	{
		float deltaWidth=newSize.Width-originalSize.Width;
		mTargetBoundingBox.Origin.X+=deltaWidth;
		mTargetBoundingBox.Size.Width+=deltaWidth;
		result=deltaWidth;
	}

	mPrevTargetBoundingBox=mTargetBoundingBox;
	OnUpdate();
	return result;
}

Point2F IScrollMathModel::GetTotalMovment() const
{
	if (IsVertical())
	{
		float initY=mSize.Height-mTargetBoundingBox.Size.Height;
		return mTargetBoundingBox.Origin-mpp(0.f,initY);
	}
	else
	{
		float initX=mSize.Width-mTargetBoundingBox.Size.Width;
		return mTargetBoundingBox.Origin-mpp(initX,0.f);
	}
	
}

bool IScrollMathModel::IsRectVisible(const Rect2F& rect) const
{
	Point2F totalMovement=GetTotalMovment();
	if (mDirection==DirectionMask::Vertical)
	{
		float bottom=rect.Bottom()+totalMovement.Y;
		float top=rect.Top()+totalMovement.Y;

		return (bottom>=0.f&&bottom<=mSize.Height)||(top>=0.f&&top<=mSize.Height);
	}
	else if(mDirection==DirectionMask::Horizontal)
	{
		float left=rect.Left()+totalMovement.X;
		float right=rect.Right()+totalMovement.X;
		return (left>=0.f&&left<=mSize.Width)||(right>=0.f&&right<=mSize.Width);

	}
	else
	{
		Rect2F copy=rect;
		copy.Origin+=totalMovement;
		return rect.IsIntersect(Rect2F(Point2F::Zero,mSize));
	}
}


float IScrollMathModel::GetHorizontalScrollBarOffset() const
{
	float offset=mSize.Width*(Math::Abs(mTargetBoundingBox.Origin.X))/mTargetBoundingBox.Size.Width;
	offset=Math::ClampAboveZero(offset);
	return offset;
}

float IScrollMathModel::GetVerticalScrollBarOffset() const
{
	float offset=mSize.Height*(Math::Abs(mTargetBoundingBox.Origin.Y))/mTargetBoundingBox.Size.Height;
	offset=Math::ClampAboveZero(offset);
	return offset;
}

Point2F IScrollMathModel::GetScrollBarOffset() const
{
	return mpp(GetHorizontalScrollBarOffset(),GetVerticalScrollBarOffset());
}

float IScrollMathModel::GetHorizontalScrollBarWidth() const
{
	float percent=mSize.Width/mTargetBoundingBox.Size.Width;
	float scrollBarWidth=percent*=mSize.Width;
	return scrollBarWidth;
}

float IScrollMathModel::GetVerticalScrollBarHeight() const
{
	float percent=mSize.Height/mTargetBoundingBox.Size.Height;
	float scrollBarHeight=percent*=mSize.Height;
	return scrollBarHeight;
}

bool IScrollMathModel::NeedHorizontalScrollBar() const
{
	return mTargetBoundingBox.Size.Width>mSize.Width;
}

bool IScrollMathModel::NeedVerticalScrollBar() const
{
	return mTargetBoundingBox.Size.Height>mSize.Height;
}

void IScrollMathModel::Scroll(Point2F initialVelocity)
{
	mCurrentVelocity=initialVelocity*mInitialVelocityFactor;
	mState=ScrollState::Scrolling;

}

void IScrollMathModel::Focus()
{
	mState=ScrollState::Begin;
	mCurrentVelocity=Point2F::Zero;
}

void IScrollMathModel::Release()
{
	mCurrentVelocity=Point2F::Zero;
	if (NeedSpring())
	{
		mState=ScrollState::Spring;
	}
	else
	{
		mState=ScrollState::End;
	}

}

void IScrollMathModel::Move(Point2F movement)
{
	mState=ScrollState::StaticMove;
	ScrollBy(movement);
}

void IScrollMathModel::ScrollTo(Point2F offset)
{
	mTargetBoundingBox.Origin=offset;
	mTargetBoundingBox.Origin.X=Math::Clamp(mTargetBoundingBox.Origin.X,mSpringLimitX.Min,mSpringLimitX.Max);
	mTargetBoundingBox.Origin.Y=Math::Clamp(mTargetBoundingBox.Origin.Y,mSpringLimitY.Min,mSpringLimitY.Max);
}

void IScrollMathModel::ScrollBy(Point2F movement)
{
	mTargetBoundingBox.Origin+=movement;
	mTargetBoundingBox.Origin.X=Math::Clamp(mTargetBoundingBox.Origin.X,mSpringLimitX.Min,mSpringLimitX.Max);
	mTargetBoundingBox.Origin.Y=Math::Clamp(mTargetBoundingBox.Origin.Y,mSpringLimitY.Min,mSpringLimitY.Max);

}

void IScrollMathModel::ScrollToStart()
{
	if (IsVertical())
	{
		mTargetBoundingBox.Origin.Y=mSize.Height-mTargetBoundingBox.Size.Height;
		mTargetBoundingBox.Origin.X=0.f;
	}
	else
	{
		mTargetBoundingBox.Origin=Point2F::Zero;
	}
	
}

void IScrollMathModel::ScrollToEnd()
{
	if (IsVertical())
	{
		mTargetBoundingBox.Origin=Point2F::Zero;
	}
	else
	{
		mTargetBoundingBox.Origin.Y=0.f;
		mTargetBoundingBox.Origin.X=mSize.Width-mTargetBoundingBox.Size.Width;
	}

}


void IScrollMathModel::OnUpdate()
{
	if (mTargetBoundingBox.IsEmpty())
	{
		mStaticLimitX=0.f;
		mStaticLimitY=0.f;
	}
	else
	{
		//calculate limit
		float xDiff=mSize.Width-mTargetBoundingBox.Size.Width;
		if (xDiff>0.f)
		{
			mStaticLimitX.Min=0.f;
			mStaticLimitX.Max=xDiff;
		}
		else
		{
			mStaticLimitX.Min=xDiff;
			mStaticLimitX.Max=0.f;
		}


		float yDiff=mSize.Height-mTargetBoundingBox.Size.Height;
		if (yDiff>0.f)
		{
			mStaticLimitY.Min=0.f;
			mStaticLimitY.Max=yDiff;
		}
		else
		{
			mStaticLimitY.Min=yDiff;
			mStaticLimitY.Max=0.f;
		}

	}

	OnUpdateSpringLimit();
	
}

void IScrollMathModel::OnUpdateSpringLimit()
{
	mSpringLimitX=mStaticLimitX;
	mSpringLimitY=mStaticLimitY;
}

bool IScrollMathModel::NeedSpring() const
{
	//horizontal
	if (mDirection.HasFlag(DirectionMask::Horizontal))
	{
		float left=mTargetBoundingBox.Left();
		return !mStaticLimitX.Contains(left);
	}

	//vertical
	if (mDirection.HasFlag(DirectionMask::Vertical))
	{
		float bottom=mTargetBoundingBox.Bottom();
		return !mStaticLimitY.Contains(bottom);
	}

	return false;

}

void IScrollMathModel::OnScrollingEnd()
{
	//horizontal
	if (mDirection.HasFlag(DirectionMask::Horizontal))
	{
		float left=mTargetBoundingBox.Left();
		float movement=mStaticLimitX.GetMovement(left);
		ScrollBy(mpp(-movement,0.f));
	}

	//vertical
	if (mDirection.HasFlag(DirectionMask::Vertical))
	{
		float bottom=mTargetBoundingBox.Bottom();
		float movement=mStaticLimitY.GetMovement(bottom);
		ScrollBy(mpp(0.f,-movement));
	}
}




MEDUSA_END;
