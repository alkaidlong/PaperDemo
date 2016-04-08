
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Config/RoleConfig.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/String/StringTable/StringTable.h"


RoleConfig::~RoleConfig()
{
	Unload();
}

bool RoleConfig::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData(FileId("RoleConfig.bin"));
	return LoadFromData(data);
}

bool RoleConfig::LoadFromData(MemoryByteData data)
{
	Unload();
	
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));
	FOR_EACH_COLLECTION_STL(i,mConfig.roleconfigitems())
	{
		const ServerProto::Config::RoleConfigItem& item=*i;
		mItemDict.Add(item.id(),&item);
	}
	return true;
}

void RoleConfig::Unload()
{
	mConfig.Clear();
	mItemDict.Clear();
}

const ServerProto::Config::RoleConfigItem* RoleConfig::GetRoleConfigItem( uint id )const
{
	const ServerProto::Config::RoleConfigItem* result= mItemDict.TryGetValueWithFailed(id,NULL);
	if (result==NULL)
	{
		Log::LogErrorFormat("Cannot find Role by id:%d",id);
	}
	return result;
}