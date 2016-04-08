#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuarticEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		QuarticEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuarticEaseInOutAction(void){}
	public:
		virtual QuarticEaseInOutAction<TTarget>* Clone()const override
		{
			return new QuarticEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual QuarticEaseInOutAction<TTarget>* Reverse()const override
		{
			return new QuarticEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuarticEaseInOutAction<TTarget>* Create(QuarticEaseInOutAction<TTarget>* innerAction)
		{
			return new QuarticEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuarticEaseInOut(percent);
		}
	};
}
MEDUSA_END;
