#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;


typedef Pattern::Delegate<void (Thread&)> ThreadCallback;
typedef pthread_t ThreadIdType;

class Thread
{
	enum ThreadState
	{
		None,
		Running,
		Canceled
	};
public:
	Thread(ThreadCallback callback,void* userData=NULL,bool isDetach=false)
		:mCallback(callback),mUserData(userData),mIsDetach(isDetach)
	{
		mResult=NULL;
		mThreadState=None;
	}

	Thread(void* userData=NULL,bool isDetach=false)
		:mUserData(userData),mIsDetach(isDetach)
	{
		mResult=NULL;
		mThreadState=None;
	}

	~Thread(void){}

public:
	static ThreadIdType GetCurrentThreadId()
	{
		return pthread_self();
	}
	static bool IsThreadEqual(ThreadIdType thread1,ThreadIdType thread2)
	{
		return pthread_equal(thread1,thread2)!=0;
	}

	static bool IsInSameThread(ThreadIdType thread)
	{
		return IsThreadEqual(thread,GetCurrentThreadId());
	}

	static void Sleep(int milliSeconds)
	{
#ifdef MEDUSA_WINDOWS
		::Sleep(milliSeconds);
#else
		sleep(milliSeconds);
#endif // WIN32
	}
public:
	bool Start()
	{
		if (mThreadState!=None)
		{
			return true;
		}

		if (mIsDetach)
		{
			pthread_attr_t attr; 
			pthread_attr_init(&attr); 
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
			int result=pthread_create(&mThread,&attr,MyThreadCallback,this);
			pthread_attr_destroy(&attr);
			if (result==0)
			{
				mThreadState=Running;
			}
			return result==0;
		}
		else
		{
			int result=pthread_create(&mThread,NULL,MyThreadCallback,this);
			if (result==0)
			{
				mThreadState=Running;
			}
			return result==0;
		}

	}
	void Stop()
	{
		/// unsupport on android
		assert(0);
		//pthread_cancel(mThread);
	}

	bool Kill(int sig)
	{
		return pthread_kill(mThread,sig)==0;
	}

	bool Detach()
	{
		return pthread_detach(mThread)==0;
	}

	void PrepareToCancel()
	{
		mThreadState=Canceled;
	}

	bool Join()
	{
		mThreadState=Canceled;
		if(pthread_join(mThread,&mResult)==0)
		{
			mThreadState=None;
			return true;
		}

		return false;

	}
	void Exit(void* result=NULL)
	{
		mResult=result;
		pthread_exit(result);
		mThreadState=None;
	}

public:
	void SetCancelState(bool isCancelable,bool& oldIsCancelable)
	{
		/// unsupport on android
		assert(0);
		//int oldState;
		///pthread_setcancelstate(isCancelable?PTHREAD_CANCEL_ENABLE:PTHREAD_CANCEL_DISABLE,&oldState);
		//oldIsCancelable=(oldState==PTHREAD_CANCEL_ENABLE);

	}
	void SetCancelType(bool IsAsynchonous,bool& oldIsAsynchonous)
	{
		/// unsupport on android
		assert(0);
		///int oldState;
		///pthread_setcancelstate(IsAsynchonous?PTHREAD_CANCEL_ASYNCHRONOUS:PTHREAD_CANCEL_DEFERRED,&oldState);
		///oldIsAsynchonous=(oldState==PTHREAD_CANCEL_ASYNCHRONOUS);
	}

	void SetCallback(const ThreadCallback& val) { mCallback = val; }
private:
	static void* MyThreadCallback(void* userData)
	{
		Thread* currentThread=(Thread*)userData;
		currentThread->InvokeCallback();

		return NULL;
	}
	void InvokeCallback()
	{
		if (mCallback.IsValid())
		{
			mCallback(*this);
		}
		//Exit();
	}
public:
	void* GetUserData() const { return mUserData; }
	void SetUserData(void* val) { mUserData = val; }
	void* GetResult() const { return mResult; }
	bool IsRunning()const{return mThreadState!=None;}
	bool IsCanceled()const{return mThreadState==Canceled;}

	Medusa::Thread::ThreadState GetThreadState() const { return mThreadState; }
	void SetThreadState(Medusa::Thread::ThreadState val) { mThreadState = val; }
protected:
	ThreadIdType mThread;
	ThreadCallback mCallback;
	
	void* mUserData;
	void* mResult;
	bool mIsDetach;
	ThreadState mThreadState;
	
};


MEDUSA_END;
