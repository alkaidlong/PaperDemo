#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class RateEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		RateEaseInOutAction(BaseFiniteAction<TTarget>* innerAction,float rate):BaseTweenAction(innerAction),mRate(rate){}
		virtual ~RateEaseInOutAction(void){}
	public:
		virtual RateEaseInOutAction<TTarget>* Clone()const override
		{
			return new RateEaseInOutAction<TTarget>(this->mInnerAction,mRate);
		}
		virtual RateEaseInOutAction<TTarget>* Reverse()const override
		{
			return new RateEaseInOutAction<TTarget>(this->mInnerAction->Reverse(),1.f/mRate);
		}

		static RateEaseInOutAction<TTarget>* Create(RateEaseInOutAction<TTarget>* innerAction,float rate)
		{
			return new RateEaseInOutAction<TTarget>(innerAction,rate);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::RateEaseInOut(percent,mRate);
		}
	private:
		float mRate;
	};
}
MEDUSA_END;
