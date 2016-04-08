#pragma  once

#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Proto/Server/Config/RoleConfig.pb.h"
#include "Core/Collection/Dictionary.h"

USING_MEDUSA;

class RoleConfig:public Pattern::Singleton<RoleConfig>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<RoleConfig>;
private:
	RoleConfig(){}
	~RoleConfig();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();
	const ServerProto::Config::RoleConfigItem* GetRoleConfigItem(uint id)const;

private:
	ServerProto::Config::RoleConfig mConfig;
	Dictionary<uint,const ServerProto::Config::RoleConfigItem*> mItemDict;
};
