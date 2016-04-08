#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Net/Socket/SocketDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Profile/StopWatch.h"

MEDUSA_BEGIN;



enum class MessageError
{
	Success=0,
	ConnectFail=-1,

};

//None->ReadyForSend->Running	(->ReadyForNext->NextRunning)	->Completed/ConnectFail

enum class MessageState
{
	ConnectFail=-1,
	None=0,
	ReadyForSend=1,
	Running=2,
	ReadyForNext=3,
	NextRunning=4,
	Completed=5,
};

enum class MessageType
{
	Request=0,
	Custom=2
};


STRONG_FLAGS_6(MessageErrorReportSuppress,ConnectFail,AuthFailed,ServerFailed,SwitchUI,UpdateLogic,HideActivityIndicator);


class IMessage:public Pattern::RTTIObject
{
	MEDUSA_DECLARE_RTTI(IMessage);
public:
	typedef Pattern::Delegate<void (IMessage* sender,MessageEventArg)> MessageEventHandler;

	IMessage();
	virtual ~IMessage(void);
public:
	void Retain();
	void Release();
	bool IsDead()const{return mRefCount==0;}
	virtual StringRef GetResponseClassName()const{return NULL;}				
public:
	MessageEventHandler& GetSendHandler()  { return mSendHandler; }
	void SetSendHandler(const MessageEventHandler& val) { mSendHandler = val; }

	MessageEventHandler& GetReceiveHandler()  { return mReceiveHandler; }
	void SetReceiveHandler(const MessageEventHandler& val) { mReceiveHandler = val; }

	MessageEventHandler& GetCompleteHandler()  { return mCompleteHandler; }
	void SetCompleteHandler(const MessageEventHandler& val) { mCompleteHandler = val; }

	MessageEventHandler& GetRootHandler() { return mRootHandler; }
	void SetRootHandler(const MessageEventHandler& val) { mRootHandler = val; }

	void SetError(MessageError val) { mError = val; }
	void SetError(Socket::SocketError::SocketError_t val);
	virtual int GetServerError()const=0;
	virtual int GetCustomError()const=0;


	MessageState GetState() const { return mState; }
	void SetState(MessageState val) { mState = val; }

	float GetTimeout() const { return mTimeout; }
	void SetTimeout(float val) { mTimeout = val;mTimeLeft=mTimeout; }


	virtual bool HasResponse()const{return false;}
	virtual bool IsResultOk()const=0;

	bool IsTimeout()const{return mTimeLeft<0.f;}
	virtual MessageType GetType()const=0;

	virtual MemoryByteData SerializeRequest()const{return MemoryByteData::Empty;};
	virtual void ParseFromRequest(MemoryByteData data){};
	virtual void PrintRequest()const{};

	virtual MemoryByteData SerializeResponse()const{return MemoryByteData::Empty;};
	virtual void ParseFromResponse(MemoryByteData data){};
	virtual void PrintResponse()const{};

	void Send();
	void Send(MessageEventHandler handler);

	size_t GetHandlerId() const { return mHandlerId; }
	void SetHandlerId(size_t val) { mHandlerId = val; }

	bool IsSubMessage() const { return mIsSubMessage; }
	void SetIsSubMessage(bool val) { mIsSubMessage = val; }

	MessageErrorReportSuppress GetErrorReportSuppress() const { return mErrorReportSuppress; }
	void SetErrorReportSuppress(MessageErrorReportSuppress val) { mErrorReportSuppress = val; }

	int GetSocketError() const { return mSocketError; }
	void SetSocketError(int val) { mSocketError = val; }

	bool IsProfileEnabled() const { return mIsProfileEnabled; }
	void EnableProfile(bool val) { mIsProfileEnabled = val; }
	float GetSendElapsedMilliseconds() const { return mSendElapsedMilliseconds; }
	void SetSendElapsedMilliseconds(float val) { mSendElapsedMilliseconds = val; }

	float GetReceiveElapsedMilliseconds() const { return mReceiveElapsedMilliseconds; }
	void SetReceiveElapsedMilliseconds(float val) { mReceiveElapsedMilliseconds = val; }

	float GetTotalElapsedMilliseconds() const { return mTotalStopWatch.GetElapsedMilliseconds(); }
public:
	virtual void PrepareReadyForSend();
	virtual void PrepareToNextRunning();
	virtual void BeforeEnd();
	virtual void Mock(){}

	virtual void Update(float dt);
protected:
	MessageError GetError() const { return mError; }
protected:
	size_t mHandlerId;
	void* mUserData;

	MessageEventHandler mSendHandler;
	MessageEventHandler mReceiveHandler;
	MessageEventHandler mCompleteHandler;
	MessageEventHandler mRootHandler;

	MessageError mError;
	MessageState mState;
	int mSocketError;
	
	float mTimeout;
	float mTimeLeft;

	bool mIsProfileEnabled;
	
	StopWatch mTotalStopWatch;	//从开始创建到处理完毕的时间
	float mSendElapsedMilliseconds;	//发送的时间
	float mReceiveElapsedMilliseconds;	//接收的时间
	size_t mRefCount;
	bool mIsSubMessage;

	MessageErrorReportSuppress mErrorReportSuppress;


};

MEDUSA_END;
