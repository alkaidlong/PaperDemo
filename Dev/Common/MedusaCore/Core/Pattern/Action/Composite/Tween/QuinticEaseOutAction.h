#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuinticEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuinticEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuinticEaseOutAction(void){}
	public:
		virtual QuinticEaseOutAction<TTarget>* Clone()const override
		{
			return new QuinticEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuinticEaseOutAction<TTarget>* Reverse()const override
		{
			return new QuinticEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuinticEaseOutAction<TTarget>* Create(QuinticEaseOutAction<TTarget>* innerAction)
		{
			return new QuinticEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuinticEaseOut(percent);
		}
	};
}
MEDUSA_END;
