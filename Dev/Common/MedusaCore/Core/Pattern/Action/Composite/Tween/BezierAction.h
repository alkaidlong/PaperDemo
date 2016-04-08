#pragma once
#include "Core/Pattern/Action/Composite/Tween/BaseTweenAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BezierAction:public BaseTweenAction<TTarget>
	{
	public:
		BezierAction(BaseFiniteAction<TTarget>* innerAction,float p0,float p1,float p2,float p3):BaseTweenAction(innerAction),mP0(p0),mP1(p1),mP2(p2),mP3(p3){}
		virtual ~BezierAction(void){}
	public:
		virtual BezierAction<TTarget>* Clone()const override
		{
			return new BezierAction<TTarget>(this->mInnerAction,mP0,mP1,mP2,mP3);
		}
		virtual BezierAction<TTarget>* Reverse()const override
		{
			return new BezierAction<TTarget>(this->mInnerAction->Reverse(),mP3,mP2,mP1,mP0);
		}

		static BezierAction<TTarget>* Create(BezierAction<TTarget>* innerAction,float p0,float p1,float p2,float p3)
		{
			return new BezierAction<TTarget>(innerAction,p0,p1,p2,p3);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const override
		{
			return Math::Tween::Bezier(percent,mP0,mP1,mP2,mP3);
		}
	private:
		float mP0;
		float mP1;
		float mP2;
		float mP3;
	};
}
MEDUSA_END;
