#pragma once

#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;

class Lock
{
public:
	Lock(Mutex& mutex):mMutex(mutex)
	{
		mMutex.Enter();
	}
	~Lock()
	{
		mMutex.Leave();
	}
private:
	Lock(const Lock &);
	Lock& operator=(const Lock &);
private:
	Mutex& mMutex;
};

MEDUSA_END;
