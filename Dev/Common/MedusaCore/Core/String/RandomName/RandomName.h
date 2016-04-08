#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/Proto/Client/RandomName.pb.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
MEDUSA_BEGIN;

class RandomName:public Pattern::Singleton<RandomName>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<RandomName>;
private:
	RandomName(){}
	~RandomName();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();

	HeapString GetRandomName3(uint seed=0)const;
private:
	CoreProto::RandomNameConfig mConfig;
	Dictionary<size_t,List<const CoreProto::RandomNameConfigItem*>*> mItems;

};
MEDUSA_END;
