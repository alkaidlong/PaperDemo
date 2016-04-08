#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BackEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		BackEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BackEaseOutAction(void){}
	public:
		virtual BackEaseOutAction<TTarget>* Clone()const override
		{
			return new BackEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual BackEaseOutAction<TTarget>* Reverse()const override
		{
			return new BackEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BackEaseOutAction<TTarget>* Create(BackEaseOutAction<TTarget>* innerAction)
		{
			return new BackEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BackEaseOut(percent);
		}
	};
}
MEDUSA_END;
