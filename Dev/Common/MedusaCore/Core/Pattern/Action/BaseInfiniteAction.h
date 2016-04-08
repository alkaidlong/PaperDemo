#pragma once
#include "Core/Pattern/Action/IAction.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget>
	class BaseInfiniteAction:public Pattern::IAction<TTarget>
	{
	public:
		BaseInfiniteAction(void){}
		virtual ~BaseInfiniteAction(void){}
		virtual ActionType GetType()const{return ActionType::Infinite;}
	};
}
MEDUSA_END;
