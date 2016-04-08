#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/String/FuckyString/FuckyStringNode.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/ILoadable.h"

MEDUSA_BEGIN;

class FuckyString:public Pattern::Singleton<FuckyString>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<FuckyString>;
private:
	FuckyString(){}
	~FuckyString();
public:
	bool Initialize();

	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();


	bool IsFucky(StringRef str)const;
	bool IsFucky(WStringRef str)const;
	bool TryClean(WHeapString& str,char replace='*')const;
private:
	Dictionary<wchar_t,FuckyStringNode*> mRootNodes;

};
MEDUSA_END;
