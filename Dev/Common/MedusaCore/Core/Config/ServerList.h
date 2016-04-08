#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/Proto/Client/ServerList.pb.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Proto/Client/ServerConfig.pb.h"
#include "Core/Proto/Client/FileList.pb.h"

MEDUSA_BEGIN;

class ServerList:public Pattern::Singleton<ServerList>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<ServerList>;
private:
	ServerList(){}
	~ServerList();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();

	const CoreProto::ServerListItem* GetServerListItem(uint id)const;
	const CoreProto::ServerListItem* GetServerListItemByIndex(uint index)const;
	const CoreProto::ServerListItem* GetFirstServerListItem()const;

	int GetServerCount()const{return mConfig.items_size();}
	void UpdateMessageServer(uint serverListId,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey)const;

	void InitializeMessageServer(uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey)const;

	int GetServerIdWithUsage(uint serverListId,::Medusa::CoreProto::ServerUsageType usageType)const;
private:
	CoreProto::ServerList mConfig;
	Dictionary<uint,const CoreProto::ServerListItem*> mItemDict;

};

MEDUSA_END;
