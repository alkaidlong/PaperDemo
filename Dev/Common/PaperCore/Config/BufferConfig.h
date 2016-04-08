#pragma  once

#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Proto/Server/Config/BufferConfig.pb.h"
#include "Core/Collection/Dictionary.h"

USING_MEDUSA;

class BufferConfig:public Pattern::Singleton<BufferConfig>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<BufferConfig>;
private:
	BufferConfig(){}
	~BufferConfig();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();
	const ServerProto::Config::BufferConfigItem* GetBufferConfigItem(uint id)const;

private:
	ServerProto::Config::BufferConfig mConfig;
	Dictionary<uint,const ServerProto::Config::BufferConfigItem*> mItemDict;
};
