#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Collection/Queue.h"
#include "Core/Message/IMessage.h"
#include "Core/String/HeapString.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Proto/Client/FileList.pb.h"

MEDUSA_BEGIN;

class IMessageHandler
{
public:
	IMessageHandler(size_t id,StringRef hostName, ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey);
	virtual ~IMessageHandler();
public:
	size_t GetId() const { return mId; }
	virtual void Push(IMessage* message);
	virtual void Process()=0;
	
	bool IsEmpty()const{return mMessageQueue.IsEmpty();}

	uint RetryTimes() const { return mRetryTimes; }
	void SetRetryTimes(uint val) { mRetryTimes = val; }

	uint RetryInternal() const { return mRetryInternal; }
	void SetRetryInternal(uint val) { mRetryInternal = val; }

	float GetTotalElapsedMilliseconds()const{return mTotalStopWatch.GetElapsedMilliseconds();}
	float GetConnectElapsedMilliseconds()const{return mConnectStopWatch.GetElapsedMilliseconds();}

protected:
	void FireUIEventAsync(IMessage::MessageEventHandler handler,IMessage* message);
protected:
	size_t mId;
	HeapString mHostName;
	ushort mPort;

	Queue<IMessage*> mMessageQueue;
	uint mRetryTimes;
	uint mRetryInternal;

	StopWatch mTotalStopWatch;
	StopWatch mConnectStopWatch;
	StopWatch mSendStopWatch;
	StopWatch mReceiveStopWatch;

	uint mMessageVersion;
	CoreProto::FileList::FileCoder::FileCoderType mSendCoderType;
	CoreProto::FileList::FileCoder::FileCoderType mReceiveCoderType;

	MemoryByteData mMessageEncryptKey;
	ICoder* mSendCoder;
	ICoder* mReceiveCoder;

};



MEDUSA_END;
