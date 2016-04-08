#pragma once
#include "Core/Pattern/DefaultRunnable.h"
#include "Core/Pattern/IClone.h"

MEDUSA_BEGIN;

enum class ActionType
{
	Instant,
	Finite,
	Infinite
};

namespace Pattern
{
	template<typename TTarget>
	class IAction
		:public Pattern::IClone<IAction<TTarget>>,
		public Pattern::DefaultRunnable
		
	{
	public:
		IAction(void):mTarget(NULL),mTag(0){}
		virtual ~IAction(void){}
		virtual ActionType GetType()const=0;

	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(IsRunning());
			return true;
		}

		TTarget* GetTarget() const { return mTarget; }
		void SetTarget(TTarget* val) { mTarget = val; }

		int GetTag() const { return mTag; }
		void SetTag(int val) { mTag = val; }

		virtual bool Initialize(TTarget* target){mTarget=target;return true;}
		virtual IAction<TTarget>* Reverse()const{MEDUSA_ASSERT_NOT_IMPLEMENT();return NULL;}
			 
	protected:
		TTarget* mTarget;
		int mTag;
	};
}
MEDUSA_END;
