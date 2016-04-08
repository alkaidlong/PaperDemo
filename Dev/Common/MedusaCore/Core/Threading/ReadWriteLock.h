#pragma once

#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;


class ReadWriteLock
{
public:
	ReadWriteLock()
	{
		pthread_rwlock_init(&mLock,NULL);
	}
	~ReadWriteLock()
	{
		pthread_rwlock_destroy(&mLock);
	}

	void BeginRead()
	{
		::pthread_rwlock_rdlock(&mLock);
	}

	void TryBeginRead()
	{
		::pthread_rwlock_tryrdlock(&mLock);
	}

	bool BeginReadTimeout(int seconds,bool& outIsTimeout)
	{
		timespec absTime;
		absTime.tv_sec=(long)time(NULL)+seconds;
		absTime.tv_nsec=0;

        return 0;
		//int result= pthread_rwlock_timedrdlock(&mLock,&absTime);
		//outIsTimeout=result==ETIMEDOUT;
		//return result==0;
	}

	void EndRead()
	{
		pthread_rwlock_unlock(&mLock);
	}

	void BeginWrite()
	{
		pthread_rwlock_wrlock(&mLock);
	}

	void TryBeginWrite()
	{
		::pthread_rwlock_trywrlock(&mLock);
	}

	bool BeginWriteTimeout(int seconds,bool& outIsTimeout)
	{
		timespec absTime;
		absTime.tv_sec=(long)time(NULL)+seconds;
		absTime.tv_nsec=0;

        return 0;
		//int result= pthread_rwlock_timedwrlock(&mLock,&absTime);
		//outIsTimeout=result==ETIMEDOUT;
		//return result==0;
	}

	void EndWrite()
	{
		pthread_rwlock_unlock(&mLock);
	}

private:
	ReadWriteLock(const ReadWriteLock &);
	ReadWriteLock& operator=(const ReadWriteLock &);
private:
	pthread_rwlock_t mLock;
};


MEDUSA_END;
