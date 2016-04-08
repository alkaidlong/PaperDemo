#pragma once
#include "Core/Pattern/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget>
	class DelayAction:public Pattern::BaseFiniteAction<TTarget>
	{
	public:
		DelayAction(float duration):BaseFiniteAction(duration){}
		virtual ~DelayAction(void){}
		virtual ActionType GetType()const{return ActionType::Finite;}
	public:
		virtual DelayAction* Clone()const override{return new DelayAction(this->mDuration);}
		virtual DelayAction* Reverse()const override{return new DelayAction(this->mDuration);}
		static DelayAction* Create(float duration){return new DelayAction(duration);}
	};

}
MEDUSA_END;
