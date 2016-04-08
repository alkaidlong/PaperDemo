#include "MedusaCorePreCompiled.h"
#include "SpringScrollMathModel.h"

MEDUSA_BEGIN;


SpringScrollMathModel::SpringScrollMathModel( DirectionMask direction/*=DirectionMask::All*/)
	:IScrollMathModel(direction),
	mSpringSizePercent(mpp(0.2f,0.2f)),
	mSpringFactor(100.f),
	mDampingFactor(0.8f),
	mDampingStartFactor(100.f)
{

}

SpringScrollMathModel::~SpringScrollMathModel( void )
{

}


void SpringScrollMathModel::OnUpdateSpringLimit()
{
	if (mTargetBoundingBox.IsEmpty())
	{
		mSpringLimitX=mStaticLimitX;
		mSpringLimitY=mStaticLimitY;
	}
	else
	{
		Point2F springOffset=mpp(mSize.Width*mSpringSizePercent.X,mSize.Height*mSpringSizePercent.Y);

		mSpringLimitX.Min=mStaticLimitX.Min-springOffset.X;
		mSpringLimitX.Max=mStaticLimitX.Max+springOffset.X;

		mSpringLimitY.Min=mStaticLimitY.Min-springOffset.Y;
		mSpringLimitY.Max=mStaticLimitY.Max+springOffset.Y;
	}
}

bool SpringScrollMathModel::Update(float dt)
{
	switch (mState)
	{
	case IScrollMathModel::ScrollState::None:
	case IScrollMathModel::ScrollState::Begin:
	case IScrollMathModel::ScrollState::StaticMove:
	case IScrollMathModel::ScrollState::End:
		return false;
	case IScrollMathModel::ScrollState::Scrolling:
		{
			Point2F a=CalculateScrollAccelerate();

			Point2F deltaVelocity=a*dt;
			mCurrentVelocity+=a*dt;
			bool isStopX=Math::IsEqualSign(mCurrentVelocity.X,deltaVelocity.X);
			bool isStopY=Math::IsEqualSign(mCurrentVelocity.Y,deltaVelocity.Y);
			if (isStopX)
			{
				mCurrentVelocity.X=0.f;
			}
			if (isStopY)
			{
				mCurrentVelocity.Y=0.f;
			}

			Point2F movement=mCurrentVelocity*dt;
			if (movement==Point2F::Zero)
			{
				mState=ScrollState::End;
			}
			else
			{
				ScrollBy(movement);
			}
			
			if (NeedSpring())
			{
				mCurrentVelocity=Point2F::Zero;
				mState=ScrollState::Spring;
			}
		}

		break;
	case IScrollMathModel::ScrollState::Spring:
		{
			Point2F a=CalculateSpringAccelerate();
			
			mCurrentVelocity+=a*dt;
			Point2F movement=mCurrentVelocity*dt;
			ScrollBy(movement);
			if (!NeedSpring())
			{
				OnScrollingEnd();
				mState=ScrollState::End;
			}
		}
		break;
	default:
		break;
	}

	return true;
}


Point2F SpringScrollMathModel::CalculateScrollAccelerate() const
{
	Point2F a=Point2F::Zero;
	//horizontal
	if (mDirection.HasFlag(DirectionMask::Horizontal))
	{
		a.X=Math::InverseSign(mCurrentVelocity.X)*mDampingStartFactor-mDampingFactor*mCurrentVelocity.X;
	}

	//vertical
	if (mDirection.HasFlag(DirectionMask::Vertical))
	{
		a.Y=Math::InverseSign(mCurrentVelocity.Y)*mDampingStartFactor-mDampingFactor*mCurrentVelocity.Y;
	}

	return a;
}


Point2F SpringScrollMathModel::CalculateSpringAccelerate() const
{
	Point2F a=Point2F::Zero;
	//horizontal
	if (mDirection.HasFlag(DirectionMask::Horizontal))
	{
		float left=mTargetBoundingBox.Left();
		if (left<mStaticLimitX.Min)
		{
			a.X=mSpringFactor*(mStaticLimitX.Min-left);
		}
		else if(left>mStaticLimitX.Max)
		{
			a.X=mSpringFactor*(mSpringLimitX.Max-left);
		}
		else
		{
			a.X=-mDampingStartFactor-mDampingFactor*mCurrentVelocity.X;
		}
	}

	//vertical
	if (mDirection.HasFlag(DirectionMask::Vertical))
	{
		float bottom=mTargetBoundingBox.Bottom();
		if (bottom<mStaticLimitY.Min)
		{
			a.Y=mSpringFactor*(mStaticLimitY.Min-bottom);
		}
		else if(bottom>mStaticLimitY.Max)
		{
			a.Y=mSpringFactor*(mStaticLimitY.Max-bottom);
		}
		else
		{
			a.Y=-mDampingStartFactor-mDampingFactor*mCurrentVelocity.Y;
		}
	}

	return a;
}

MEDUSA_END;
