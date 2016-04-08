#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class SinusoidalEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		SinusoidalEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~SinusoidalEaseInOutAction(void){}
	public:
		virtual SinusoidalEaseInOutAction<TTarget>* Clone()const override
		{
			return new SinusoidalEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual SinusoidalEaseInOutAction<TTarget>* Reverse()const override
		{
			return new SinusoidalEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static SinusoidalEaseInOutAction<TTarget>* Create(SinusoidalEaseInOutAction<TTarget>* innerAction)
		{
			return new SinusoidalEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::SinusoidalEaseInOut(percent);
		}
	};
}
MEDUSA_END;
