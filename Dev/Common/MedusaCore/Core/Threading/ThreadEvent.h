#pragma once

#include "MedusaCorePreCompiled.h"


MEDUSA_BEGIN;


/*
推荐的pthread_cond_wait()和pthread_cond_signal()使用方式：
pthread_mutex_lock(&m);
while( condition_is_false )
pthread_cond_wait(&cond, &m);
pthread_mutex_unlock(&m);

另一端一般是：
pthread_mutex_lock(&m); // pthread_cond_wait已自动释放锁
......
pthread_cond_signal(&v);
pthread_mutex_unlock(&m); // 释放锁，使得pthread_cond_wait可以自动再次获得锁

pthread_cond_wait()函数的返回并不意味着条件的值一定发生了变化（有可能是假唤醒），也可能是函数出错返回，因此必须重新检查条件的值，比如用while()来确认.
*/


class ThreadEvent
{
public:
	ThreadEvent()
	{
		::pthread_mutex_init(&mMutex,0);
		::pthread_mutexattr_settype(&mAttr,PTHREAD_MUTEX_RECURSIVE);
		::pthread_mutex_init(&mMutex,&mAttr);

		::pthread_cond_init(&mCond,NULL);
	}
	~ThreadEvent()
	{
		::pthread_mutex_destroy(&mMutex);
		::pthread_mutexattr_destroy(&mAttr);

		::pthread_cond_destroy(&mCond);

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


	void Set()
	{
		::pthread_cond_signal(&mCond);
	}

	void SetAll()
	{
		::pthread_cond_broadcast(&mCond);
	}


	bool Wait()
	{
		//unlock mutex
		//lock at cond

		//after return

		//unlock cond
		//lock mutex

		return ::pthread_cond_wait(&mCond,&mMutex)==0;
	}

	bool WaitTimeout(int seconds,bool& outIsTimeout)
	{
		timespec absTime;
		absTime.tv_sec=(long)time(NULL)+seconds;
		absTime.tv_nsec=0;

		int result= pthread_cond_timedwait(&mCond,&mMutex,&absTime);
		outIsTimeout=result==ETIMEDOUT;
		return result==0;
	}

private:
	ThreadEvent(const ThreadEvent &);
	ThreadEvent& operator=(const ThreadEvent &);
private:
	pthread_cond_t mCond;
	pthread_mutex_t mMutex;
	pthread_mutexattr_t mAttr;


};


MEDUSA_END;
