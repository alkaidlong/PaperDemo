#pragma once
#include "Core/Pattern/Action/Composite/BaseSingleCompositeAction.h"
#include "Core/Pattern/Action/BaseFiniteAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class RepeatedForeverAction:public BaseSingleCompositeAction<TTarget>
	{
	public:
		RepeatedForeverAction(IAction<TTarget>* innerAction):BaseSingleCompositeAction(innerAction){}
		virtual ~RepeatedForeverAction(void){}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(BaseSingleCompositeAction<TTarget>::Update(dt));
			switch (mInnerAction->GetType())
			{
			case ActionType::Instant:
				mInnerAction->Start();
				break;
			case ActionType::Finite:
				{
					BaseFiniteAction<TTarget>& action=(BaseFiniteAction<TTarget>&)(*mInnerAction);
					action.Update(dt);
					if (action.IsDone())
					{
						float exceed=action.GetElapsed()-action.GetDuration();
						action.Start();
						action.Update(exceed);
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

	};
}
MEDUSA_END;
