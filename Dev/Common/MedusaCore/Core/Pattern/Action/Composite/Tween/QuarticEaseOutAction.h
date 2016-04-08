#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuarticEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuarticEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuarticEaseOutAction(void){}
	public:
		virtual QuarticEaseOutAction<TTarget>* Clone()const override
		{
			return new QuarticEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuarticEaseOutAction<TTarget>* Reverse()const override
		{
			return new QuarticEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuarticEaseOutAction<TTarget>* Create(QuarticEaseOutAction<TTarget>* innerAction)
		{
			return new QuarticEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuarticEaseOut(percent);
		}
	};
}
MEDUSA_END;
