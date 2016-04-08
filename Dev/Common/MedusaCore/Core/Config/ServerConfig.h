#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/Proto/Client/ServerConfig.pb.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class ServerConfig:public Pattern::Singleton<ServerConfig>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<ServerConfig>;
private:
	ServerConfig(){}
	~ServerConfig();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();

	const CoreProto::ServerConfigItem* GetServerConfigItem(uint id)const;

	int GetServerCount()const{return mConfig.items_size();}

private:
	CoreProto::ServerConfig mConfig;
	Dictionary<uint,const CoreProto::ServerConfigItem*> mItemDict;

};

MEDUSA_END;
