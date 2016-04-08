#include "MedusaCorePreCompiled.h"
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Core/Config/ServerConfig.h"
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;

ServerConfig::~ServerConfig()
{
	Unload();
}


bool ServerConfig::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData("ServerConfig.bin");
	return LoadFromData(data);
}

bool ServerConfig::LoadFromData(MemoryByteData data)
{
	Unload();

	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));

	FOR_EACH_COLLECTION_STL(i,mConfig.items())
	{
		const CoreProto::ServerConfigItem& item=*i;
		mItemDict.Add(item.id(),&item);
	}

	return true;
}

void ServerConfig::Unload()
{
	mConfig.Clear();
	mItemDict.Clear();
}

const CoreProto::ServerConfigItem* ServerConfig::GetServerConfigItem( uint id )const
{
	return mItemDict.TryGetValueWithFailed(id,NULL);
}



MEDUSA_END;
