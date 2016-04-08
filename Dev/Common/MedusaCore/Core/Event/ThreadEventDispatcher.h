#pragma once
#include "Core/Event/WorkItem.h"
#include "Core/Threading/Thread.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Queue.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class ThreadEventDispatcher:public Pattern::Singleton<ThreadEventDispatcher>
{
	friend class Pattern::Singleton<ThreadEventDispatcher>;
public:
	typedef Pattern::Delegate<void (void* sender,IEventArg)> DefaultHandler;
	typedef WorkItem<void,IEventArg> DefaultWorkItem;
public:
	void Start();
	void Stop();

	void Clear();

	template<typename TSender,typename TEventArg>
	void FireEvent(typename WorkItem<TSender,TEventArg>::HandlerType handler,TSender* sender,const TEventArg& eventArg)
	{
		if (handler.IsValid())
		{
			mThreadEvent.Enter();

			WorkItem<TSender,TEventArg>* item=new WorkItem<TSender,TEventArg>(handler,sender,eventArg);
			mWorkItems.Push(item);

			mThreadEvent.Set();
			mThreadEvent.Leave();

		}
	}

	void FireEventDefault(DefaultHandler handler)
	{
		if (handler.IsValid())
		{
			mThreadEvent.Enter();

			DefaultWorkItem* item=new DefaultWorkItem(handler,(void*)NULL,IEventArg::Empty);
			mWorkItems.Push(item);

			mThreadEvent.Set();
			mThreadEvent.Leave();
		}
	}

private:
	ThreadEventDispatcher(void);
	~ThreadEventDispatcher(void);
private:
	static void ProcessEvents(Thread& thread);
	void ProcessEventsHelper(Thread& thread);
private:
	Queue<Pattern::IExecutable*> mWorkItems;
	Thread mThread;
	ThreadEvent mThreadEvent;
};


MEDUSA_END;