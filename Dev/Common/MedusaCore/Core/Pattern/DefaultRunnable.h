#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/IRunnable.h"
MEDUSA_BEGIN;


namespace Pattern
{
	class DefaultRunnable:public IRunnable
	{
	public:
		DefaultRunnable(Pattern::RunningState state=Pattern::RunningState::Running);
		virtual ~DefaultRunnable();
	public:
		virtual Pattern::RunningState GetState() const { return mState; }
		virtual bool IsRunning()const{return mState==Pattern::RunningState::Running;}
		virtual bool IsDone()const{return mState==Pattern::RunningState::Done;}
		virtual bool Start();
		virtual bool Pause();
		virtual bool Resume();
		virtual bool Stop();
		virtual bool Reset();
	protected:
		void ForceSetState(Pattern::RunningState val);
	protected:
		Pattern::RunningState mState;
	};
}

MEDUSA_END;