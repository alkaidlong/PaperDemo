#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/IMessageHandler.h"

MEDUSA_BEGIN;

class MockMessageHandler:public IMessageHandler
{
public:
	MockMessageHandler(size_t id,StringRef hostName, ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey);
	virtual ~MockMessageHandler();
protected:
	IMessage* SendMessage(IMessage* message);

public:
	virtual void Process();
};
MEDUSA_END;
