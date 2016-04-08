#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class QuarticEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		QuarticEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~QuarticEaseInAction(void){}
	public:
		virtual QuarticEaseInAction<TTarget>* Clone()const override
		{
			return new QuarticEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual QuarticEaseInAction<TTarget>* Reverse()const override
		{
			return new QuarticEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static QuarticEaseInAction<TTarget>* Create(QuarticEaseInAction<TTarget>* innerAction)
		{
			return new QuarticEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::QuarticEaseIn(percent);
		}
	};
}
MEDUSA_END;
