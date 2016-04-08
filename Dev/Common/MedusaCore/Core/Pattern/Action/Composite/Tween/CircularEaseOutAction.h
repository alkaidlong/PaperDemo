#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CircularEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		CircularEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CircularEaseOutAction(void){}
	public:
		virtual CircularEaseOutAction<TTarget>* Clone()const override
		{
			return new CircularEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual CircularEaseOutAction<TTarget>* Reverse()const override
		{
			return new CircularEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CircularEaseOutAction<TTarget>* Create(CircularEaseOutAction<TTarget>* innerAction)
		{
			return new CircularEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CircularEaseOut(percent);
		}
	};
}
MEDUSA_END;
