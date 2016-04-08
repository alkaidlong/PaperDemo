#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/DefaultRunnable.h"
MEDUSA_BEGIN;


namespace Pattern
{

	DefaultRunnable::DefaultRunnable( Pattern::RunningState state/*=Pattern::RunningState::Running*/ ):mState(state)
	{

	}


	DefaultRunnable::~DefaultRunnable()
	{

	}

	bool DefaultRunnable::Start()
	{
		switch(mState)
		{
		case Pattern::RunningState::None:
			mState=Pattern::RunningState::Running;
			return true;
		case Pattern::RunningState::Running:
			return true;
		case Pattern::RunningState::Paused:
			return false;
		case Pattern::RunningState::Done:
			mState=Pattern::RunningState::Running;
			return true;
		}
		return false;
	}

	bool DefaultRunnable::Pause()
	{
		switch(mState)
		{
		case Pattern::RunningState::None:
			return false;
		case Pattern::RunningState::Running:
			mState=Pattern::RunningState::Paused;
			return true;
		case Pattern::RunningState::Paused:
			return true;
		case Pattern::RunningState::Done:
			return false;
		}
		return false;
	}

	bool DefaultRunnable::Resume()
	{
		switch(mState)
		{
		case Pattern::RunningState::None:
			return false;
		case Pattern::RunningState::Paused:
			mState=Pattern::RunningState::Running;
			return true;
		case Pattern::RunningState::Running:
			return true;
		case Pattern::RunningState::Done:
			return false;
		}
		return false;
	}

	bool DefaultRunnable::Stop()
	{
		mState=Pattern::RunningState::Done;
		return true;
	}

	bool DefaultRunnable::Reset()
	{
		mState=Pattern::RunningState::None;
		return true;
	}

	void DefaultRunnable::ForceSetState(Pattern::RunningState val)
	{
		mState=val;
	}

}

MEDUSA_END;