#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class ExponentialEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		ExponentialEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~ExponentialEaseInAction(void){}
	public:
		virtual ExponentialEaseInAction<TTarget>* Clone()const override
		{
			return new ExponentialEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual ExponentialEaseInAction<TTarget>* Reverse()const override
		{
			return new ExponentialEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static ExponentialEaseInAction<TTarget>* Create(ExponentialEaseInAction<TTarget>* innerAction)
		{
			return new ExponentialEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::ExponentialEaseIn(percent);
		}
	};
}
MEDUSA_END;
