#pragma once

#include "MedusaCorePreCompiled.h"


MEDUSA_BEGIN;


class Mutex
{
public:
	Mutex()
	{
		::pthread_mutexattr_init(&mAttr);
		::pthread_mutexattr_settype(&mAttr,PTHREAD_MUTEX_RECURSIVE);
		::pthread_mutex_init(&mMutex,&mAttr);
	}
	~Mutex()
	{
		::pthread_mutex_destroy(&mMutex);
		::pthread_mutexattr_destroy(&mAttr);
	}

	void Enter()
	{
		::pthread_mutex_lock(&mMutex);
	}

	void TryEnter()
	{
		::pthread_mutex_trylock(&mMutex);
	}
	void Leave()
	{
		::pthread_mutex_unlock(&mMutex);
	}
private:
	Mutex(const Mutex &);
	Mutex& operator=(const Mutex &);
private:
	pthread_mutex_t mMutex;
	pthread_mutexattr_t mAttr;
};


MEDUSA_END;
