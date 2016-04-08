
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Config/SkillConfig.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/String/StringTable/StringTable.h"


SkillConfig::~SkillConfig()
{
	Unload();
}

bool SkillConfig::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData(FileId("SkillConfig.bin"));
	return LoadFromData(data);
}

bool SkillConfig::LoadFromData(MemoryByteData data)
{
	Unload();
	
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));
	FOR_EACH_COLLECTION_STL(i,mConfig.skillconfigitems())
	{
		const ServerProto::Config::SkillConfigItem& item=*i;
		mItemDict.Add(item.id(),&item);
	}
	return true;
}

void SkillConfig::Unload()
{
	mConfig.Clear();
	mItemDict.Clear();
}

const ServerProto::Config::SkillConfigItem* SkillConfig::GetSkillConfigItem( uint id )const
{
	const ServerProto::Config::SkillConfigItem* result= mItemDict.TryGetValueWithFailed(id,NULL);
	if (result==NULL)
	{
		Log::LogErrorFormat("Cannot find skill by id:%d",id);
	}
	return result;
}