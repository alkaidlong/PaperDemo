#pragma once
#include "Core/Pattern/Action/BaseInstantAction.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Compile/TypeTraits.h"
MEDUSA_BEGIN;

namespace Pattern
{
	template<typename TTarget,typename TArg>
	class ArgDelegateAction:public Pattern::BaseInstantAction<TTarget>
	{
	public:
		typedef Pattern::Delegate<void (TTarget*,TArg)> DelegateType;
		typedef typename Compile::TypeTraits<TArg>::ParameterType TArgParameterType;
	public:
		ArgDelegateAction(DelegateType func,TArgParameterType arg):mDelegate(func),mArg(arg){}
		virtual ~ArgDelegateAction(void){}
		virtual ActionType GetType()const{return ActionType::Instant;}
	public:
		virtual ArgDelegateAction* Clone()const override{return new ArgDelegateAction(mDelegate,mArg);}
		virtual ArgDelegateAction* Reverse()const override{return new ArgDelegateAction(mDelegate,mArg);}
		static ArgDelegateAction* Create(DelegateType func,TArgParameterType arg){return new ArgDelegateAction(mDelegate,arg);}
	protected:
		virtual bool OnAction()
		{
			if(mDelegate.IsValid())
			{
				mDelegate(mTarget,mArg);
			}
			return true;
		}
	protected:
		DelegateType mDelegate;
		TArg mArg;

	};

}
MEDUSA_END;
