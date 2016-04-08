#pragma once
#include "Core/Pattern/Action/Composite/BaseSingleCompositeAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	/*
	Changes the speed of an action, making it take longer (speed>1)
	or less (speed<1) time.
	Useful to simulate 'slow motion' or 'fast forward' effect.
	*/

	template<typename TTarget>
	class SpeedAction:public BaseSingleCompositeAction<TTarget>
	{
	public:
		SpeedAction(IAction<TTarget>* innerAction,float speed):BaseSingleCompositeAction(innerAction),mSpeed(speed){}
		virtual ~SpeedAction(void){}
	protected:
		virtual float TransformUpdateDuration(float dt)const{return dt*mSpeed;}
	private:
		float mSpeed;
	};
}
MEDUSA_END;
