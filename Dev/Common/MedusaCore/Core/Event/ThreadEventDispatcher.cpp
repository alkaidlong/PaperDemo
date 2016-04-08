#include "MedusaCorePreCompiled.h"
#include "ThreadEventDispatcher.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


ThreadEventDispatcher::ThreadEventDispatcher(void):mThread(ThreadCallback(ThreadEventDispatcher::ProcessEvents),NULL)
{
	mThread.SetUserData(this);
	mThread.SetCallback(ThreadCallback(ThreadEventDispatcher::ProcessEvents));
}


ThreadEventDispatcher::~ThreadEventDispatcher(void)
{
	Clear();
}


void ThreadEventDispatcher::Clear()
{
	mThreadEvent.Enter();

	while(!mWorkItems.IsEmpty())
	{
		Pattern::IExecutable* item=mWorkItems.Head();
		item->Execute();
		SAFE_DELETE(item);
		mWorkItems.Pop();
	}

	mThreadEvent.Leave();

}


void ThreadEventDispatcher::ProcessEvents( Thread& thread )
{
	ThreadEventDispatcher* threadEventDispather=(ThreadEventDispatcher*) thread.GetUserData();
	while(true)
	{
		threadEventDispather->ProcessEventsHelper(thread);
		//Thread::Sleep(0);
		if(thread.IsCanceled())
		{
			break;
		}
	}

}

void ThreadEventDispatcher::ProcessEventsHelper(Thread& thread)
{
	mThreadEvent.Enter();

	while(mWorkItems.IsEmpty()&&!thread.IsCanceled())
	{
		mThreadEvent.Wait();
	}

	while(!mWorkItems.IsEmpty())
	{
		Pattern::IExecutable* item=mWorkItems.Head();
		item->Execute();
		SAFE_DELETE(item);
		mWorkItems.Pop();
	}

	mThreadEvent.Leave();

}

void ThreadEventDispatcher::Start()
{
	mThread.Start();
}

void ThreadEventDispatcher::Stop()
{
	mThread.PrepareToCancel();

	mThreadEvent.Enter();
	mThreadEvent.Set();
	mThreadEvent.Leave();

	mThread.Join();
}

MEDUSA_END;