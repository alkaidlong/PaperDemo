#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ElasticEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		ElasticEaseInOutAction(BaseFiniteAction<TTarget>* innerAction,float period):BaseTweenAction(innerAction),mPeriod(period){}
		virtual ~ElasticEaseInOutAction(void){}
	public:
		virtual ElasticEaseInOutAction<TTarget>* Clone()const override
		{
			return new ElasticEaseInOutAction<TTarget>(this->mInnerAction,mPeriod);
		}
		virtual ElasticEaseInOutAction<TTarget>* Reverse()const override
		{
			return new ElasticEaseInOutAction<TTarget>(this->mInnerAction->Reverse(),mPeriod);
		}

		static ElasticEaseInOutAction<TTarget>* Create(ElasticEaseInOutAction<TTarget>* innerAction,float period)
		{
			return new ElasticEaseInOutAction<TTarget>(innerAction,period);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ElasticEaseInOut(percent,mPeriod);
		}
	private:
		float mPeriod;
	};
}
MEDUSA_END;
