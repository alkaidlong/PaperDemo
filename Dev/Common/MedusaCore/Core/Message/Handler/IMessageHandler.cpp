#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/IMessageHandler.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/Message/MessageEventArg.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Coder/CoderFactory.h"


MEDUSA_BEGIN;

IMessageHandler::IMessageHandler(size_t id,StringRef hostName, ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey)
	:mId(id),mHostName(hostName),mPort(port),mRetryTimes(retryTimes),mRetryInternal(retryInternal),mMessageVersion(messageVersion),mSendCoderType(sendCoderType),mReceiveCoderType(receiveCoderType),mMessageEncryptKey(encryptKey)
{
	mTotalStopWatch.SetName("MessageTotalTime");
	mConnectStopWatch.SetName("MessageConnect");
	mSendStopWatch.SetName("MessageSend");
	mReceiveStopWatch.SetName("MessageReceive");

#ifndef MEDUSA_DEBUG
	mTotalStopWatch.Enable(false);
	mConnectStopWatch.Enable(false);
	mSendStopWatch.Enable(false);
	mReceiveStopWatch.Enable(false);
#endif

	UserDataEventArg<MemoryByteData> userDataKey(encryptKey);
	/*mSendCoder=new XOREncoder(encryptKey);
	mReceiveCoder=new XORDecoder(encryptKey);*/

	mSendCoder=CoderFactory::Instance().Create(mSendCoderType,userDataKey);
	mReceiveCoder=CoderFactory::Instance().Create(mReceiveCoderType,userDataKey);

}

IMessageHandler::~IMessageHandler()
{
	SAFE_DELETE(mSendCoder);
	SAFE_DELETE(mReceiveCoder);
}

void IMessageHandler::Push( IMessage* message )
{
	SAFE_RETAIN(message);
	mMessageQueue.Push(message);
}

void IMessageHandler::FireUIEventAsync( IMessage::MessageEventHandler handler,IMessage* message )
{
	if (handler.IsValid())
	{
		MessageEventArg eventArg(message);
		UIEventDispatcher::Instance().FireEventAsync(handler,message,eventArg);
	}
}

MEDUSA_END;
