#pragma once
#include "Core/Pattern/Action/IAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BaseFiniteAction:public Pattern::IAction<TTarget>
	{
	public:
		BaseFiniteAction(float duration):mDuration(duration),mElapsed(0.f)
		{
			MEDUSA_ASSERT_FALSE(mDuration==0,"");
			MEDUSA_ASSERT_FALSE(Math::IsZero(duration),"");
		}
		virtual ~BaseFiniteAction(void){}
		virtual ActionType GetType()const{return ActionType::Finite;}

	public:
		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
			mElapsed=0.f;

			return true;
		}
		virtual bool Stop()
		{
			RETURN_FALSE_IF_FALSE(DefaultRunnable::Stop());
			mElapsed=0.f;
			return true;
		}
		virtual bool Reset()
		{
			RETURN_FALSE_IF_FALSE(DefaultRunnable::Reset());
			mElapsed=0.f;
			return true;
		}

		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(IAction<TTarget>::Update(dt));

			mElapsed+=dt;
			if (mElapsed>mDuration)
			{
				ForceSetState(Pattern::RunningState::Done);
			}
			return true;
		}
		float GetPercent()const{return Math::Min(mElapsed/mDuration,1.f);}
		float GetDuration() const { return mDuration; }
		float GetElapsed() const { return mElapsed; }

	protected:
		const float mDuration;
		float mElapsed;
	};

}
MEDUSA_END;
