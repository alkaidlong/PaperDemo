#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ExponentialEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		ExponentialEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~ExponentialEaseInOutAction(void){}
	public:
		virtual ExponentialEaseInOutAction<TTarget>* Clone()const override
		{
			return new ExponentialEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual ExponentialEaseInOutAction<TTarget>* Reverse()const override
		{
			return new ExponentialEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static ExponentialEaseInOutAction<TTarget>* Create(ExponentialEaseInOutAction<TTarget>* innerAction)
		{
			return new ExponentialEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ExponentialEaseInOut(percent);
		}
	};
}
MEDUSA_END;
