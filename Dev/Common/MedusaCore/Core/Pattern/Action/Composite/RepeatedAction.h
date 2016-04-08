#pragma once
#include "Core/Pattern/Action/Composite/BaseSingleCompositeAction.h"
#include "Core/Pattern/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class RepeatedAction:public BaseSingleCompositeAction<TTarget>
	{
	public:
		RepeatedAction(IAction<TTarget>* innerAction,int count):BaseSingleCompositeAction(innerAction),mCount(count){}
		virtual ~RepeatedAction(void){}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Update(dt));
			switch (mInnerAction->GetType())
			{
			case ActionType::Instant:
				mInnerAction->Start();
				--mCount;
				if (mCount<=0)
				{
					ForceSetState(Pattern::RunningState::Done);
				}

				break;
			case ActionType::Finite:
				{
					BaseFiniteAction<TTarget>& action=(BaseFiniteAction<TTarget>&)(*mInnerAction);
					action.Update(dt);
					if (action.IsDone())
					{
						--mCount;
						if (mCount<=0)
						{
							ForceSetState(Pattern::RunningState::Done);
						}
						else
						{
							float exceed=action.GetElapsed()-action.GetDuration();
							action.Start();
							action.Update(exceed);

						}
					}
				}
				break;
			case ActionType::Infinite:
				mInnerAction->Update(dt);

				break;
			default:
				break;
			}

			return true;
		}
	private:
		int mCount;
	};
}
MEDUSA_END;
