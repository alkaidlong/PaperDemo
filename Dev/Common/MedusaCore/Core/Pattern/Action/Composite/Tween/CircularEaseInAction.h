#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CircularEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		CircularEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CircularEaseInAction(void){}
	public:
		virtual CircularEaseInAction<TTarget>* Clone()const override
		{
			return new CircularEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual CircularEaseInAction<TTarget>* Reverse()const override
		{
			return new CircularEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CircularEaseInAction<TTarget>* Create(CircularEaseInAction<TTarget>* innerAction)
		{
			return new CircularEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CircularEaseIn(percent);
		}
	};
}
MEDUSA_END;
