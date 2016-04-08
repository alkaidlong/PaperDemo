#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BounceEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		BounceEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BounceEaseOutAction(void){}
	public:
		virtual BounceEaseOutAction<TTarget>* Clone()const override
		{
			return new BounceEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual BounceEaseOutAction<TTarget>* Reverse()const override
		{
			return new BounceEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BounceEaseOutAction<TTarget>* Create(BounceEaseOutAction<TTarget>* innerAction)
		{
			return new BounceEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BounceEaseOut(percent);
		}
	};
}
MEDUSA_END;
