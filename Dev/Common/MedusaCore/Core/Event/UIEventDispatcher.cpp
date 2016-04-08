#include "MedusaCorePreCompiled.h"
#include "UIEventDispatcher.h"
#include "Core/Log/Log.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;


UIEventDispatcher::UIEventDispatcher(void)
{
	mPingWorkItemsPtr=&mPingWorkItems;
	mPongWorkItemsPtr=&mPongWorkItems;

}


UIEventDispatcher::~UIEventDispatcher(void)
{
	ClearWithoutRun();
}

void UIEventDispatcher::Dispatch()
{
	Memory::Swap(mPingWorkItemsPtr,mPongWorkItemsPtr);

	while(!mPingWorkItemsPtr->IsEmpty())
	{
		Pattern::IExecutable* item=mPingWorkItemsPtr->Head();
		mPingWorkItemsPtr->Pop();
		item->Execute();
		SAFE_DELETE(item);
	}

}


void UIEventDispatcher::Clear()
{
	while(!mPingWorkItemsPtr->IsEmpty())
	{
		Pattern::IExecutable* item=mPingWorkItemsPtr->Head();
		mPingWorkItemsPtr->Pop();
		item->Execute();
		SAFE_DELETE(item);
	}

	while(!mPongWorkItemsPtr->IsEmpty())
	{
		Pattern::IExecutable* item=mPongWorkItemsPtr->Head();
		mPongWorkItemsPtr->Pop();
		item->Execute();
		SAFE_DELETE(item);
	}
}

void UIEventDispatcher::ClearWithoutRun()
{
	while(!mPingWorkItemsPtr->IsEmpty())
	{
		Pattern::IExecutable* item=mPingWorkItemsPtr->Head();
		mPingWorkItemsPtr->Pop();
		SAFE_DELETE(item);
	}

	while(!mPongWorkItemsPtr->IsEmpty())
	{
		Pattern::IExecutable* item=mPongWorkItemsPtr->Head();
		mPongWorkItemsPtr->Pop();
		SAFE_DELETE(item);
	}
}


MEDUSA_END;