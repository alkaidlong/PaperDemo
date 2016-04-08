#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CircularEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		CircularEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CircularEaseInOutAction(void){}
	public:
		virtual CircularEaseInOutAction<TTarget>* Clone()const override
		{
			return new CircularEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual CircularEaseInOutAction<TTarget>* Reverse()const override
		{
			return new CircularEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CircularEaseInOutAction<TTarget>* Create(CircularEaseInOutAction<TTarget>* innerAction)
		{
			return new CircularEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CircularEaseInOut(percent);
		}
	};
}
MEDUSA_END;
