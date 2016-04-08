#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class SinusoidalEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		SinusoidalEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~SinusoidalEaseInAction(void){}
	public:
		virtual SinusoidalEaseInAction<TTarget>* Clone()const override
		{
			return new SinusoidalEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual SinusoidalEaseInAction<TTarget>* Reverse()const override
		{
			return new SinusoidalEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static SinusoidalEaseInAction<TTarget>* Create(SinusoidalEaseInAction<TTarget>* innerAction)
		{
			return new SinusoidalEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::SinusoidalEaseIn(percent);
		}
	};
}
MEDUSA_END;
