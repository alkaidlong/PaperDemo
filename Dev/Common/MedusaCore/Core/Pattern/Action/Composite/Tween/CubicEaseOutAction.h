#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CubicEaseOutAction:public BaseTweenAction<TTarget>
	{
	public:
		CubicEaseOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CubicEaseOutAction(void){}
	public:
		virtual CubicEaseOutAction<TTarget>* Clone()const override
		{
			return new CubicEaseOutAction<TTarget>(this->mInnerAction);
		}
		virtual CubicEaseOutAction<TTarget>* Reverse()const override
		{
			return new CubicEaseOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CubicEaseOutAction<TTarget>* Create(CubicEaseOutAction<TTarget>* innerAction)
		{
			return new CubicEaseOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CubicEaseOut(percent);
		}
	};
}
MEDUSA_END;
