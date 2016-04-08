#pragma once
#include "Core/Pattern/Action/BaseFiniteAction.h"


MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget,typename TAnimation>
	class BaseAnimationAction:public Pattern::BaseFiniteAction<TTarget>
	{
	public:
		BaseAnimationAction(TAnimation* animation,float duration)
			:Pattern::BaseFiniteAction<TTarget>(duration<0.f?animation->GetDuration():duration),mAnimation(animation){}
	protected:
		TAnimation* mAnimation;
	};
}
MEDUSA_END;
