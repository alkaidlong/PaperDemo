#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/MockMessageHandler.h"
#include "Core/Log/Log.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Profile/AutoStopWatch.h"

MEDUSA_BEGIN;

MockMessageHandler::MockMessageHandler(size_t id,StringRef hostName, ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey)
	:IMessageHandler(id,hostName,port,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey)
{

}

MockMessageHandler::~MockMessageHandler()
{

}


void MockMessageHandler::Process()
{
	AutoStopWatch autoTotalStopWatch(mTotalStopWatch);
	while(mMessageQueue.GetCount()>0)
	{
		IMessage* message=mMessageQueue.Head();
		mMessageQueue.Pop();
		SendMessage(message);
		SAFE_RELEASE(message);
	}
}

IMessage* MockMessageHandler::SendMessage( IMessage* message )
{
	
	FireUIEventAsync(message->GetSendHandler(),message);

	message->Mock();
	message->SetState(MessageState::Completed);
	if (!message->HasResponse())
	{
		Log::LogErrorFormat("Cannot implement Mock on message:%s",message->GetRTTIClass().GetClassName().c_str());
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->GetReceiveHandler(),message);
		return message;
	}

	message->SetState(MessageState::Completed);
	StringRef expectedResponseClassName=message->GetResponseClassName();
	Log::LogInfoFormat("Receive:%s",expectedResponseClassName.c_str());
	FireUIEventAsync(message->GetReceiveHandler(),message);

	return message;

}





MEDUSA_END;
