#include "MedusaCorePreCompiled.h"
#include "MessageDispatcher.h"
#include "Core/Log/Log.h"
#include "Core/Threading/Lock.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Profile/StopWatch.h"

MEDUSA_BEGIN;


MessageDispatcher::MessageDispatcher(void)
{
	mThread.SetCallback(ThreadCallback(OnMessageThread));
}


MessageDispatcher::~MessageDispatcher(void)
{
	ClearUp();
}

bool MessageDispatcher::Initialize()
{
	return Socket::ISocket::InitializeAPI();

}

bool MessageDispatcher::Uninitialize()
{
	return Socket::ISocket::UninitializeAPI();
}

void MessageDispatcher::AddMessageServer( CoreProto::ServerConfigItem::ServerType serverType,size_t id,StringRef address,ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey )
{
	RemoveMessageHandler(id);
	IMessageHandler* loginHandler=MessageHandlerFactory::Instance().Create(serverType,id,address,port,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey);
	AddMessageHandler(loginHandler);
}


void MessageDispatcher::ClearUp()
{
	mThreadEvent.Enter();

	SAFE_DELETE_DICTIONARY_VALUE(mMessageHandlers);
	SAFE_DELETE_COLLECTION(mMessages);

	mThreadEvent.Leave();
}


void MessageDispatcher::AddMessageHandler( IMessageHandler* handler )
{
	mThreadEvent.Enter();

	if (mMessageHandlers.ContainsKey(handler->GetId()))
	{
		Log::AssertFailedFormat("Duplicate handler by id %zuu",handler->GetId());
	}

	mMessageHandlers.Add(handler->GetId(),handler);
	mThreadEvent.Leave();
}


void MessageDispatcher::RemoveMessageHandler( size_t handlerId )
{
	mThreadEvent.Enter();

	IMessageHandler* server=mMessageHandlers.TryGetValueWithFailed(handlerId,NULL);
	if (server!=NULL)
	{
		mMessageHandlers.RemoveKey(handlerId);
		SAFE_DELETE(server);
	}

	mThreadEvent.Leave();
}


void MessageDispatcher::Start()
{
	mThread.Start();
}

void MessageDispatcher::Stop()
{
	//mThread.Kill(0);
	mThread.PrepareToCancel();


	mThreadEvent.Enter();
	mThreadEvent.Set();
	mThreadEvent.Leave();

	mThread.Join();

}


void MessageDispatcher::Send( IMessage* message )
{
	LOG_ASSERT_NOT_NULL(message);

	size_t handlerId=message->GetHandlerId();
	if(mMessageHandlers.ContainsKey(handlerId))
	{
		message->Retain();	//ref:2
		mMessages.Add(message);
	}
	else
	{
		Log::AssertFailedFormat("Invalid message handler Id:%zuu",handlerId);
	}
	
}


void MessageDispatcher::OnMessageThread( Thread& thread )
{
	while(true)
	{
		MessageDispatcher::Instance().ProcessMessage(thread);
		//Thread::Sleep(0);
		if(thread.IsCanceled())
		{
			break;
		}
	}

}

void MessageDispatcher::ProcessMessage(Thread& thread)
{
	mThreadEvent.Enter();

	while(true)
	{
		bool hasMessages=false;
		FOR_EACH_COLLECTION(i,mMessageHandlers)
		{
			IMessageHandler* handler=(*i).Value;
			 if(!handler->IsEmpty())
			 {
				 hasMessages=true;
				 break;
			 }
		}

        if (hasMessages)
        {
            break;
        }
        else
        {
            if (!thread.IsCanceled())
            {
                mThreadEvent.Wait();
            }
            else
            {
                break;
            }
        }
		

	}

	FOR_EACH_COLLECTION(i,mMessageHandlers)
	{
		IMessageHandler* handler=(*i).Value;
		handler->Process();
	}

	mThreadEvent.Leave();
}


void MessageDispatcher::Update( float dt )
{
	//running on UI thread
	LinkedList<IMessage*>::NodePtr node=mMessages.FirstNode();
	while(node!=NULL&&node->Value!=NULL)
	{
		IMessage* message=node->Value;
		switch(message->GetState())
		{
		case MessageState::None:
			message->PrepareReadyForSend();
			node=node->Next;
			break;
		case MessageState::ReadyForSend:
			{
				mThreadEvent.Enter();
				IMessageHandler* messageHandler=mMessageHandlers[message->GetHandlerId()];	//had checked before
				messageHandler->Push(message);	//ref:3
				message->SetState(MessageState::Running);
				node=node->Next;

				mThreadEvent.Set();
				mThreadEvent.Leave();
			}
			break;
		case MessageState::Running:
			message->Update(dt);
			node=node->Next;
			break;
		case MessageState::ReadyForNext:
			message->PrepareToNextRunning();
			node=node->Next;
			break;
		case MessageState::NextRunning:
			message->Update(dt);
			node=node->Next;
			break;
		case MessageState::Completed:
		case MessageState::ConnectFail:
			{
				if (!message->IsSubMessage())
				{
					message->BeforeEnd();

					//show debug info
					ShowDebugInfo(message);
				}

				node=mMessages.Delete(node);
				SAFE_RELEASE(message);	//ref:0
				break;
			}

		}
	}

}

void MessageDispatcher::ShowDebugInfo(IMessage* message)
{
	RETURN_IF_FALSE(message->IsProfileEnabled());

	StringRef messageName=message->GetRTTIClass().GetClassName();

	Log::LogInfoFormat("%s Total:%.3f Send:%.3f Receive:%.3f",messageName.c_str(),message->GetTotalElapsedMilliseconds(),message->GetSendElapsedMilliseconds(),message->GetReceiveElapsedMilliseconds());
	mDebugInfo.Format("%.3f %.3f %.3f",message->GetTotalElapsedMilliseconds(),message->GetSendElapsedMilliseconds(),message->GetReceiveElapsedMilliseconds());
	OnDebugInfoUpdated(mDebugInfo);
}



MEDUSA_END;
