#pragma once
#include "Core/Pattern/Action/BaseInfiniteAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BaseSingleCompositeAction:public BaseInfiniteAction<TTarget>
	{
	public:
		BaseSingleCompositeAction(IAction<TTarget>* innerAction):mInnerAction(innerAction){}
		virtual ~BaseSingleCompositeAction(void){SAFE_DELETE(mInnerAction);}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Update(dt));
			float newDT=TransformUpdateDuration(dt);
			return mInnerAction->Update(newDT);
		}

		virtual Pattern::RunningState GetState() const { return mInnerAction->GetState(); }
		virtual bool IsRunning()const{return mInnerAction->IsRunning();}
		virtual bool IsDone()const{return mInnerAction->IsDone();}

		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Start());
			return mInnerAction->Start();
		}
		virtual bool Pause()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Pause());
			return mInnerAction->Pause();
		}
		virtual bool Resume()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Resume());
			return mInnerAction->Resume();
		}
		virtual bool Stop()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Stop());
			return mInnerAction->Stop();
		}
		virtual bool Reset()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Reset());
			return mInnerAction->Reset();
		}

		virtual bool Initialize(TTarget* target)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Initialize(target));
			return mInnerAction->Initialize(target);
		}
	protected:
		virtual float TransformUpdateDuration(float dt)const{return dt;}
	protected:
		IAction<TTarget>* mInnerAction;
	};
}
MEDUSA_END;
