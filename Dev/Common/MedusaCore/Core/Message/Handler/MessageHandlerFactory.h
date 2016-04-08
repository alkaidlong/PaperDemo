#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "Core/Message/Handler/IMessageHandler.h"
#include "Core/Proto/Client/ServerConfig.pb.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Message/Handler/MockMessageHandler.h"


MEDUSA_BEGIN;


class MessageHandlerFactory:public Pattern::MapObjectFactory<CoreProto::ServerConfigItem::ServerType,IMessageHandler*(size_t,StringRef,ushort,uint,uint,uint,CoreProto::FileList::FileCoder::FileCoderType,CoreProto::FileList::FileCoder::FileCoderType,const MemoryByteData&)>
{
public:
	using Pattern::MapObjectFactory<CoreProto::ServerConfigItem::ServerType,IMessageHandler*(size_t,StringRef,ushort,uint,uint,uint,CoreProto::FileList::FileCoder::FileCoderType,CoreProto::FileList::FileCoder::FileCoderType,const MemoryByteData&)>::Create;
private:
	MessageHandlerFactory()
	{
		Register<TcpMessageHandler>(CoreProto::ServerConfigItem::TcpServer);
		Register<MockMessageHandler>(CoreProto::ServerConfigItem::MockServer);
	}
	~MessageHandlerFactory(){}
public:
	static MessageHandlerFactory& Instance()
	{
		static MessageHandlerFactory factory;
		return factory;
	}



};

MEDUSA_END;
