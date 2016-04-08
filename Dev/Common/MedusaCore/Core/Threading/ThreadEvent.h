#pragma once

#include "MedusaCorePreCompiled.h"


MEDUSA_BEGIN;


/*
�Ƽ���pthread_cond_wait()��pthread_cond_signal()ʹ�÷�ʽ��
pthread_mutex_lock(&m);
while( condition_is_false )
pthread_cond_wait(&cond, &m);
pthread_mutex_unlock(&m);

��һ��һ���ǣ�
pthread_mutex_lock(&m); // pthread_cond_wait���Զ��ͷ���
......
pthread_cond_signal(&v);
pthread_mutex_unlock(&m); // �ͷ�����ʹ��pthread_cond_wait�����Զ��ٴλ����

pthread_cond_wait()�����ķ��ز�����ζ��������ֵһ�������˱仯���п����Ǽٻ��ѣ���Ҳ�����Ǻ��������أ���˱������¼��������ֵ��������while()��ȷ��.
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
