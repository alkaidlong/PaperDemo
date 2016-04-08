#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuinticEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuinticEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuinticEaseInOutAction(void){}
	public:
		virtual QuinticEaseInOutAction<TTarget>* Clone()const override
		{
			return new QuinticEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuinticEaseInOutAction<TTarget>* Reverse()const override
		{
			return new QuinticEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuinticEaseInOutAction<TTarget>* Create(QuinticEaseInOutAction<TTarget>* innerAction)
		{
			return new QuinticEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuinticEaseInOut(percent);
		}
	};
}
MEDUSA_END;
