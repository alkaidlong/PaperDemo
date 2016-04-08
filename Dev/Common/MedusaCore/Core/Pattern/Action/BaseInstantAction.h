#pragma once
#include "Core/Pattern/Action/IAction.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget>
	class BaseInstantAction:public Pattern::IAction<TTarget>
	{
	public:
		BaseInstantAction(void){}
		virtual ~BaseInstantAction(void){}
		virtual ActionType GetType()const{return ActionType::Instant;}
	public:
		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
			bool result=OnAction();
			ForceSetState(Pattern::RunningState::Done);
			return result;
		}
	protected:
		virtual bool OnAction()=0;
	};

}
MEDUSA_END;
