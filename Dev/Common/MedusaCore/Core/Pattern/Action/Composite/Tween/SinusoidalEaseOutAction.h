#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class SinusoidalEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		SinusoidalEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~SinusoidalEaseOutAction(void){}
	public:
		virtual SinusoidalEaseOutAction<TTarget>* Clone()const override
		{
			return new SinusoidalEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual SinusoidalEaseOutAction<TTarget>* Reverse()const override
		{
			return new SinusoidalEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static SinusoidalEaseOutAction<TTarget>* Create(SinusoidalEaseOutAction<TTarget>* innerAction)
		{
			return new SinusoidalEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::SinusoidalEaseOut(percent);
		}
	};
}
MEDUSA_END;
