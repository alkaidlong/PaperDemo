#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class RateEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		RateEaseInAction(BaseFiniteAction<TTarget>* innerAction,float rate):BaseTweenAction(innerAction),mRate(rate){}
		virtual ~RateEaseInAction(void){}
	public:
		virtual RateEaseInAction<TTarget>* Clone()const override
		{
			return new RateEaseInAction<TTarget>(this->mInnerAction,mRate);
		}
		virtual RateEaseInAction<TTarget>* Reverse()const override
		{
			return new RateEaseInAction<TTarget>(this->mInnerAction->Reverse(),1.f/mRate);
		}

		static RateEaseInAction<TTarget>* Create(RateEaseInAction<TTarget>* innerAction,float rate)
		{
			return new RateEaseInAction<TTarget>(innerAction,rate);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::RateEaseIn(percent,mRate);
		}
	private:
		float mRate;
	};
}
MEDUSA_END;
