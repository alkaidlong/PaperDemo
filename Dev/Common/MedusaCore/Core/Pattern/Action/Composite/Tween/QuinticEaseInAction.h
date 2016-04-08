#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuinticEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		QuinticEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuinticEaseInAction(void){}
	public:
		virtual QuinticEaseInAction<TTarget>* Clone()const override
		{
			return new QuinticEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual QuinticEaseInAction<TTarget>* Reverse()const override
		{
			return new QuinticEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuinticEaseInAction<TTarget>* Create(QuinticEaseInAction<TTarget>* innerAction)
		{
			return new QuinticEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuinticEaseIn(percent);
		}
	};
}
MEDUSA_END;
