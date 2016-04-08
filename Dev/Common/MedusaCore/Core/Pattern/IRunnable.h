#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/EnumPattern.h"
MEDUSA_BEGIN;


namespace Pattern
{
	/*
	None	=>	Running,Done
	Running	=>	Paused,Done,None
	Paused	=>	Running,Done,None
	Done	=>	None,Running
	*/

	enum class RunningState
	{
		Done=-2,
		Paused=-1,
		None=0,
		Running=1
	};

	struct IRunnable
	{
		virtual ~IRunnable(){}
		virtual Pattern::RunningState GetState() const=0;
		virtual bool IsRunning()const=0;
		virtual bool IsDone()const=0;
		virtual bool Start()=0;
		virtual bool Pause()=0;
		virtual bool Resume()=0;
		virtual bool Stop()=0;
		virtual bool Reset()=0;
	};
}

MEDUSA_END;