#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CubicEaseInOutAction:public BaseTweenAction<TTarget>
	{
	public:
		CubicEaseInOutAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CubicEaseInOutAction(void){}
	public:
		virtual CubicEaseInOutAction<TTarget>* Clone()const override
		{
			return new CubicEaseInOutAction<TTarget>(this->mInnerAction);
		}
		virtual CubicEaseInOutAction<TTarget>* Reverse()const override
		{
			return new CubicEaseInOutAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CubicEaseInOutAction<TTarget>* Create(CubicEaseInOutAction<TTarget>* innerAction)
		{
			return new CubicEaseInOutAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CubicEaseInOut(percent);
		}
	};
}
MEDUSA_END;
