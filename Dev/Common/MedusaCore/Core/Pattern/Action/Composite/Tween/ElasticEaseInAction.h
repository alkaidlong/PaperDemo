#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ElasticEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		ElasticEaseInAction(BaseFiniteAction<TTarget>* innerAction,float period):BaseTweenAction(innerAction),mPeriod(period){}
		virtual ~ElasticEaseInAction(void){}
	public:
		virtual ElasticEaseInAction<TTarget>* Clone()const override
		{
			return new ElasticEaseInAction<TTarget>(this->mInnerAction,mPeriod);
		}
		virtual ElasticEaseInAction<TTarget>* Reverse()const override
		{
			return new ElasticEaseInAction<TTarget>(this->mInnerAction->Reverse(),mPeriod);
		}

		static ElasticEaseInAction<TTarget>* Create(ElasticEaseInAction<TTarget>* innerAction,float period)
		{
			return new ElasticEaseInAction<TTarget>(innerAction,period);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ElasticEaseIn(percent,mPeriod);
		}
	private:
		float mPeriod;
	};
}
MEDUSA_END;
