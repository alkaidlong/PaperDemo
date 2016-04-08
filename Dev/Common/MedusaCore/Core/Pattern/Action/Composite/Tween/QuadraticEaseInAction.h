#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuadraticEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		QuadraticEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuadraticEaseInAction(void){}
	public:
		virtual QuadraticEaseInAction<TTarget>* Clone()const override
		{
			return new QuadraticEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual QuadraticEaseInAction<TTarget>* Reverse()const override
		{
			return new QuadraticEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuadraticEaseInAction<TTarget>* Create(QuadraticEaseInAction<TTarget>* innerAction)
		{
			return new QuadraticEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuadraticEaseIn(percent);
		}
	};
}
MEDUSA_END;
