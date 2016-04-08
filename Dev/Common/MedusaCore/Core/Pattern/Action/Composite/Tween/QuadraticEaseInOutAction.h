#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuadraticEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuadraticEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuadraticEaseInOutAction(void){}
	public:
		virtual QuadraticEaseInOutAction<TTarget>* Clone()const override
		{
			return new QuadraticEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuadraticEaseInOutAction<TTarget>* Reverse()const override
		{
			return new QuadraticEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuadraticEaseInOutAction<TTarget>* Create(QuadraticEaseInOutAction<TTarget>* innerAction)
		{
			return new QuadraticEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuadraticEaseInOut(percent);
		}
	};
}
MEDUSA_END;
