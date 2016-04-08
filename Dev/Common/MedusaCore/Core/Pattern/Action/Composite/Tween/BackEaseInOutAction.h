#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BackEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		BackEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~BackEaseInOutAction(void){}
	public:
		virtual BackEaseInOutAction<TTarget>* Clone()const override
		{
			return new BackEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual BackEaseInOutAction<TTarget>* Reverse()const override
		{
			return new BackEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static BackEaseInOutAction<TTarget>* Create(BackEaseInOutAction<TTarget>* innerAction)
		{
			return new BackEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::BackEaseInOut(percent);
		}
	};
}
MEDUSA_END;
