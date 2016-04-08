#pragma once

#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

class Semaphore
{
public:
	Semaphore(bool isShared,unsigned int initialValue)
	{
		sem_init(&mSem,isShared?1:0,initialValue);
	}
	~Semaphore()
	{
		sem_destroy(&mSem);
	}


	void Post()
	{
		sem_post(&mSem);
	}

	void PostMultiple(int count)
	{
		//sem_post_multiple(&mSem,count);
	}

	void GetValue(int* outValue)
	{
		sem_getvalue(&mSem,outValue);
	}

	void Wait()
	{
		sem_wait(&mSem);
	}

	void TryWait()
	{
		sem_trywait(&mSem);

	}

	void WaitTime(const timespec* absTime)
	{
		//sem_timedwait(&mSem,absTime);
	}


private:
	Semaphore(const Semaphore &);
	Semaphore& operator=(const Semaphore &);
private:
	sem_t mSem;

};


MEDUSA_END;
