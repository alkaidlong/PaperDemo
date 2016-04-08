#include "MedusaCorePreCompiled.h"
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Core/Config/ServerList.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/Message/MessageDispatcher.h"
#include "Core/Config/ServerConfig.h"



MEDUSA_BEGIN;

ServerList::~ServerList()
{
	Unload();
}


bool ServerList::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData("ServerList.bin");
	return LoadFromData(data);
}

bool ServerList::LoadFromData(MemoryByteData data)
{
	Unload();
	
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));

	FOR_EACH_COLLECTION_STL(i,mConfig.items())
	{
		const CoreProto::ServerListItem& item=*i;
		mItemDict.Add(item.id(),&item);
	}

	return true;
}

void ServerList::Unload()
{
	mConfig.Clear();
	mItemDict.Clear();
}

const CoreProto::ServerListItem* ServerList::GetServerListItem( uint id )const
{
	return mItemDict.TryGetValueWithFailed(id,NULL);
}

const CoreProto::ServerListItem* ServerList::GetServerListItemByIndex( uint index ) const
{
	return &mConfig.items(index);
}

const CoreProto::ServerListItem* ServerList::GetFirstServerListItem() const
{
	if (mConfig.items_size()>0)
	{
		return &mConfig.items(0);
	}
	else
	{
		Log::AssertFailed("Server list is empty!!");
		return NULL;
	}
}

void ServerList::UpdateMessageServer( uint serverListId ,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey) const
{
	const CoreProto::ServerListItem* item= GetServerListItem(serverListId);
	if (item!=NULL)
	{
		MessageDispatcher::Instance().ClearUp();


		FOR_EACH_COLLECTION_STL(i,item->serverusages())
		{
			const CoreProto::ServerUsageItem& usageItem=*i;
			const CoreProto::ServerConfigItem* item=ServerConfig::Instance().GetServerConfigItem(usageItem.serverid());
			if (item!=NULL)
			{
				MessageDispatcher::Instance().AddMessageServer(item->type(),(uint)usageItem.usage(),item->address(),item->port(),retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey);
			}
			else
			{
				Log::AssertFailedFormat("Cannot find server by id:%d",usageItem.serverid());
			}
		}
	}
	else
	{
		Log::LogErrorFormat("Cannot find server list by id:%d",serverListId);
	}
}

void ServerList::InitializeMessageServer(uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey) const
{
	if(mConfig.items_size()>0)
	{
		 uint serverId=mConfig.items(0).id();
		 UpdateMessageServer(serverId,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey);
	}

}

int ServerList::GetServerIdWithUsage(uint serverListId,::Medusa::CoreProto::ServerUsageType usageType) const
{
	const CoreProto::ServerListItem* item= GetServerListItem(serverListId);
	if (item!=NULL)
	{
		FOR_EACH_COLLECTION_STL(i,item->serverusages())
		{
			const CoreProto::ServerUsageItem& usageItem=*i;
			if (usageItem.usage()==usageType)
			{
				return usageItem.serverid();
			}
		}
	}
	return -1;
}

MEDUSA_END;
