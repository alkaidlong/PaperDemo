#pragma once
#include "Core/Pattern/Action/BasefiniteAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BaseTweenAction:public BaseFiniteAction<TTarget>
	{
	public:
		BaseTweenAction(BaseFiniteAction<TTarget>* innerAction):BaseFiniteAction(innerAction->GetDuration()),mInnerAction(innerAction){}
		virtual ~BaseTweenAction(void){SAFE_DELETE(mInnerAction);}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(IAction<TTarget>::Update(dt));
			float curPercent=this->GetPercent();
			mElapsed+=dt;
			float nowPercent=this->GetPercent();
			nowPercent=TransformUpdatePercent(nowPercent);
			float newDT=(nowPercent-curPercent)*mDuration;

			if (mElapsed>mDuration)
			{
				ForceSetState(Pattern::RunningState::Done);
			}

			return mInnerAction->Update(newDT);
		}

		virtual Pattern::RunningState GetState() const { return mInnerAction->GetState(); }
		virtual bool IsRunning()const{return mInnerAction->IsRunning();}
		virtual bool IsDone()const{return mInnerAction->IsDone();}

		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Start());
			return mInnerAction->Start();
		}
		virtual bool Pause()
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Pause());
			return mInnerAction->Pause();
		}
		virtual bool Resume()
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Resume());
			return mInnerAction->Resume();
		}
		virtual bool Stop()
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Stop());
			return mInnerAction->Stop();
		}
		virtual bool Reset()
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Reset());
			return mInnerAction->Reset();
		}

		virtual bool Initialize(TTarget* target)
		{
			RETURN_FALSE_IF_FALSE(BaseFiniteAction<TTarget>::Initialize(target));
			return mInnerAction->Initialize(target);
		}
	protected:
		virtual float TransformUpdatePercent(float percent)const{return percent;}
	protected:
		BaseFiniteAction<TTarget>* mInnerAction;
	};
}
MEDUSA_END;
