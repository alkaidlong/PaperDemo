#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ExponentialEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		ExponentialEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~ExponentialEaseOutAction(void){}
	public:
		virtual ExponentialEaseOutAction<TTarget>* Clone()const override
		{
			return new ExponentialEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual ExponentialEaseOutAction<TTarget>* Reverse()const override
		{
			return new ExponentialEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static ExponentialEaseOutAction<TTarget>* Create(ExponentialEaseOutAction<TTarget>* innerAction)
		{
			return new ExponentialEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ExponentialEase(percent);
		}
	};
}
MEDUSA_END;
