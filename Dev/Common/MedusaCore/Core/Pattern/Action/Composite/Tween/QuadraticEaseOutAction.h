#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuadraticEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuadraticEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuadraticEaseOutAction(void){}
	public:
		virtual QuadraticEaseOutAction<TTarget>* Clone()const override
		{
			return new QuadraticEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuadraticEaseOutAction<TTarget>* Reverse()const override
		{
			return new QuadraticEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuadraticEaseOutAction<TTarget>* Create(QuadraticEaseOutAction<TTarget>* innerAction)
		{
			return new QuadraticEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuadraticEaseOut(percent);
		}
	};
}
MEDUSA_END;
