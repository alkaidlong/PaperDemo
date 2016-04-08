#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget>
	struct IActionRunnable
	{
		bool HasActionByTag(int tag)const{return FindActionByTag(tag)!=NULL;}

		virtual IAction<TTarget>* RunAction(IAction<TTarget>* action)=0;
		virtual IAction<TTarget>* FindActionByTag(int tag)=0;

		virtual void PauseAllActions()=0;
		virtual void ResumeAllActions()=0;
		virtual void StopAllActions()=0;

		virtual void PauseActionByTag(int tag)=0;
		virtual void ResumeActionByTag(int tag)=0;
		virtual void StopActionByTag(int tag)=0;

	};
}

MEDUSA_END;