#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BounceEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		BounceEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BounceEaseInOutAction(void){}
	public:
		virtual BounceEaseInOutAction<TTarget>* Clone()const override
		{
			return new BounceEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual BounceEaseInOutAction<TTarget>* Reverse()const override
		{
			return new BounceEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BounceEaseInOutAction<TTarget>* Create(BounceEaseInOutAction<TTarget>* innerAction)
		{
			return new BounceEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BounceEaseInOut(percent);
		}
	};
}
MEDUSA_END;
