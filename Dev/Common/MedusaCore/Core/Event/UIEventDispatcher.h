#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Queue.h"
#include "Core/Event/WorkItem.h"
#include "Core/Threading/Mutex.h"
#include "Core/Threading/Lock.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class UIEventDispatcher:public Pattern::Singleton<UIEventDispatcher>
{
	friend class Pattern::Singleton<UIEventDispatcher>;
public:
	typedef Pattern::Delegate<void (void* sender,IEventArg)> DefaultHandler;
	typedef WorkItem<void,IEventArg> DefaultWorkItem;
public:
	void Dispatch();
	void Clear();
	void ClearWithoutRun();


	template<typename TSender,typename TEventArg>
	void FireEvent(typename WorkItem<TSender,TEventArg>::HandlerType handler,TSender* sender,TEventArg eventArg)
	{
		if (handler.IsValid()&&eventArg!=NULL)
		{
			handler.Invoke(sender,eventArg);
		}
	}

	void FireEventDefault(DefaultHandler handler)
	{
		if (handler.IsValid())
		{
			handler.Invoke(NULL,IEventArg::Empty);
		}
	}

	template<typename TSender,typename TEventArg>
	void FireEventAsync(typename WorkItem<TSender,TEventArg>::HandlerType handler,TSender* sender,TEventArg eventArg)
	{
		Lock lock(mMutex);
		if (handler.IsValid())
		{
			WorkItem<TSender,TEventArg>* item=new WorkItem<TSender,TEventArg>(handler,sender,eventArg);
			mPongWorkItemsPtr->Push(item);
		}
	}

	void FireEventAsyncDefault(DefaultHandler handler)
	{
		Lock lock(mMutex);
		if (handler.IsValid())
		{
			DefaultWorkItem* item=new DefaultWorkItem(handler,(void*)NULL,IEventArg::Empty);
			mPongWorkItemsPtr->Push(item);
		}
	}
private:
	UIEventDispatcher(void);
	~UIEventDispatcher(void);

protected:
	Queue<Pattern::IExecutable*> mPingWorkItems;	//add ping-pong work items to support fire event async on self's running
	Queue<Pattern::IExecutable*> mPongWorkItems;
	Queue<Pattern::IExecutable*>* mPingWorkItemsPtr;
	Queue<Pattern::IExecutable*>* mPongWorkItemsPtr;


	Mutex mMutex;
};


MEDUSA_END;