
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Config/BufferConfig.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/String/StringTable/StringTable.h"


BufferConfig::~BufferConfig()
{
	Unload();
}

bool BufferConfig::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData(FileId("BufferConfig.bin"));
	return LoadFromData(data);
}

bool BufferConfig::LoadFromData(MemoryByteData data)
{
	Unload();
	
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));
	FOR_EACH_COLLECTION_STL(i,mConfig.bufferconfigitems())
	{
		const ServerProto::Config::BufferConfigItem& item=*i;
		mItemDict.Add(item.id(),&item);
	}
	return true;
}

void BufferConfig::Unload()
{
	mConfig.Clear();
	mItemDict.Clear();
}

const ServerProto::Config::BufferConfigItem* BufferConfig::GetBufferConfigItem( uint id )const
{
	const ServerProto::Config::BufferConfigItem* result= mItemDict.TryGetValueWithFailed(id,NULL);
	if (result==NULL)
	{
		Log::LogErrorFormat("Cannot find skill by id:%d",id);
	}
	return result;
}