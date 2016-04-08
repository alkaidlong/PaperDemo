#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ElasticEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		ElasticEaseOutAction(BaseFiniteAction<TTarget>* innerAction,float period):BaseTweenAction(innerAction),mPeriod(period){}
		virtual ~ElasticEaseOutAction(void){}
	public:
		virtual ElasticEaseOutAction<TTarget>* Clone()const override
		{
			return new ElasticEaseOutAction<TTarget>(this->mInnerAction,mPeriod);
		}
		virtual ElasticEaseOutAction<TTarget>* Reverse()const override
		{
			return new ElasticEaseOutAction<TTarget>(this->mInnerAction->Reverse(),mPeriod);
		}

		static ElasticEaseOutAction<TTarget>* Create(ElasticEaseOutAction<TTarget>* innerAction,float period)
		{
			return new ElasticEaseOutAction<TTarget>(innerAction,period);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ElasticEaseOut(percent,mPeriod);
		}
	private:
		float mPeriod;
	};
}
MEDUSA_END;
