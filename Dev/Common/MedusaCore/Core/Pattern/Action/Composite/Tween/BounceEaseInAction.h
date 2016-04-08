#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BounceEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		BounceEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BounceEaseInAction(void){}
	public:
		virtual BounceEaseInAction<TTarget>* Clone()const override
		{
			return new BounceEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual BounceEaseInAction<TTarget>* Reverse()const override
		{
			return new BounceEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BounceEaseInAction<TTarget>* Create(BounceEaseInAction<TTarget>* innerAction)
		{
			return new BounceEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BounceEaseIn(percent);
		}
	};
}
MEDUSA_END;
