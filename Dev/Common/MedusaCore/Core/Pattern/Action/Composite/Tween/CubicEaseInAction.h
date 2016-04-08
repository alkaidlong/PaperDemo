#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class CubicEaseInAction:public BaseTweenAction<TTarget>
	{
	public:
		CubicEaseInAction(BaseFiniteAction<TTarget>* innerAction):BaseTweenAction(innerAction){}
		virtual ~CubicEaseInAction(void){}
	public:
		virtual CubicEaseInAction<TTarget>* Clone()const override
		{
			return new CubicEaseInAction<TTarget>(this->mInnerAction);
		}
		virtual CubicEaseInAction<TTarget>* Reverse()const override
		{
			return new CubicEaseInAction<TTarget>(this->mInnerAction->Reverse());
		}

		static CubicEaseInAction<TTarget>* Create(CubicEaseInAction<TTarget>* innerAction)
		{
			return new CubicEaseInAction<TTarget>(innerAction);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::CubicEaseIn(percent);
		}
	};
}
MEDUSA_END;
