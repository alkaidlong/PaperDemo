#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Net/Socket/ClientSocket.h"
#include "Core/String/HeapString.h"
#include "Core/Message/Handler/IMessageHandler.h"
#include "Core/IO/Stream/MemoryStream.h"

MEDUSA_BEGIN;

class TcpMessageHandler:public IMessageHandler
{
public:
	TcpMessageHandler(size_t id,StringRef inHostName, ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey);
	virtual ~TcpMessageHandler();
public:
	virtual void Process();

	Socket::ClientSocket& GetSocket();
protected:
	IMessage* SendMessage(IMessage* message);
	void FailSocket(IMessage* message);
	bool OnReceiveCompeleteCheck(IStream& stream);
	void GiveUpAllMessages();
protected:
	Socket::ClientSocket mSocket;
	HeapString mHostName;
	ushort mPort;

	const static int mInitialMessageBufferSize=4096;	//4K

	MemoryStream mSendMessageStream;
	MemoryStream mReceiveMessageStream;

};
MEDUSA_END;
