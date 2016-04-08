#pragma once
#include "Core/Pattern/Action/BaseInstantAction.h"
#include "Core/Pattern/Delegate.h"
MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget>
	class DelegateAction:public Pattern::BaseInstantAction<TTarget>
	{
	public:
		typedef Pattern::Delegate<void (TTarget*)> DelegateType;
	public:
		DelegateAction(DelegateType func):mDelegate(func){}
		virtual ~DelegateAction(void){}
		virtual ActionType GetType()const{return ActionType::Instant;}
	public:
		virtual DelegateAction* Clone()const override{return new DelegateAction(mDelegate);}
		virtual DelegateAction* Reverse()const override{return new DelegateAction(mDelegate);}
		static DelegateAction* Create(DelegateType func){return new DelegateAction(mDelegate);}
	protected:
		virtual bool OnAction()
		{
			if(mDelegate.IsValid())
			{
				mDelegate(mTarget);
			}
			return true;
		}
	protected:
		DelegateType mDelegate;

	};

}
MEDUSA_END;
