#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"

#include "Core/Collection/Dictionary.h"
#include "Core/Collection/LinkedList.h"
#include "Core/Proto/Client/ServerConfig.pb.h"
#include "Core/Proto/Client/FileList.pb.h"

#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class MessageDispatcher:public Pattern::Singleton<MessageDispatcher>,public Pattern::IInitializable
{
	friend class Pattern::Singleton<MessageDispatcher>;
	MessageDispatcher(void);
	~MessageDispatcher(void);
public:
	void ClearUp();
	void AddMessageHandler(IMessageHandler* handler);
	void RemoveMessageHandler(size_t serverId);

	void AddMessageServer(CoreProto::ServerConfigItem::ServerType serverType,size_t id,StringRef address,ushort port,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey);

	virtual bool Initialize();
	virtual bool Uninitialize();

	void Start();
	void Stop();
	void Send(IMessage* message);
	void Update(float dt);

	void ShowDebugInfo(IMessage* message);

	typedef Pattern::Delegate<void ( const StringRef&)> DebugInfoUpdateDelegate;
	Pattern::Event<void ( const StringRef&)> OnDebugInfoUpdated;
private:
	static void OnMessageThread(Thread& thread);
	void ProcessMessage(Thread& thread);
protected:
	Thread mThread;
	LinkedList<IMessage*> mMessages;
	Dictionary<size_t,IMessageHandler*> mMessageHandlers;
	StackString<256> mDebugInfo;

	ThreadEvent mThreadEvent;

};

MEDUSA_END;
