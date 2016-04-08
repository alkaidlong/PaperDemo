#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BackEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		BackEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BackEaseInAction(void){}
	public:
		virtual BackEaseInAction<TTarget>* Clone()const override
		{
			return new BackEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual BackEaseInAction<TTarget>* Reverse()const override
		{
			return new BackEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BackEaseInAction<TTarget>* Create(BackEaseInAction<TTarget>* innerAction)
		{
			return new BackEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BackEaseIn(percent);
		}
	};
}
MEDUSA_END;
