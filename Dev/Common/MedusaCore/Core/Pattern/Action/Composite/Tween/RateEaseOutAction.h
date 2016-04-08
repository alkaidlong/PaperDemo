#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class RateEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		RateEaseOutAction(BaseFiniteAction<TTarget>* innerAction,float rate):BaseTweenAction(innerAction),mRate(rate){}
		virtual ~RateEaseOutAction(void){}
	public:
		virtual RateEaseOutAction<TTarget>* Clone()const override
		{
			return new RateEaseOutAction<TTarget>(this->mInnerAction,mRate);
		}
		virtual RateEaseOutAction<TTarget>* Reverse()const override
		{
			return new RateEaseOutAction<TTarget>(this->mInnerAction->Reverse(),1.f/mRate);
		}

		static RateEaseOutAction<TTarget>* Create(RateEaseOutAction<TTarget>* innerAction,float rate)
		{
			return new RateEaseOutAction<TTarget>(innerAction,rate);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::RateEaseOut(percent,mRate);
		}
	private:
		float mRate;
	};
}
MEDUSA_END;
