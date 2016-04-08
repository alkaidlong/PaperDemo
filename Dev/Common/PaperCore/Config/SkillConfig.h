#pragma  once

#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Proto/Server/Config/SkillConfig.pb.h"
#include "Core/Collection/Dictionary.h"

USING_MEDUSA;

class SkillConfig:public Pattern::Singleton<SkillConfig>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<SkillConfig>;
private:
	SkillConfig(){}
	~SkillConfig();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();
	const ServerProto::Config::SkillConfigItem* GetSkillConfigItem(uint id)const;

private:
	ServerProto::Config::SkillConfig mConfig;
	Dictionary<uint,const ServerProto::Config::SkillConfigItem*> mItemDict;
};
