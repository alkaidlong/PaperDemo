#include "MedusaCorePreCompiled.h"
#include "Core/String/RandomName/RandomName.h"
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/Math/Random.h"

MEDUSA_BEGIN;

RandomName::~RandomName()
{
	Unload();
}


bool RandomName::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData("RandomName.bin");
	return LoadFromData(data);
}

bool RandomName::LoadFromData(MemoryByteData data)
{
	Unload();
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(mConfig,data));

	FOR_EACH_COLLECTION_STL(i,mConfig.items())
	{
		const CoreProto::RandomNameConfigItem& item=*i;

		List<const CoreProto::RandomNameConfigItem*>* itemList=mItems.TryGetValueWithFailed(item.position(),NULL);
		if (itemList==NULL)
		{
			itemList=new List<const CoreProto::RandomNameConfigItem*>();
			mItems.Add(item.position(),itemList);
		}

		itemList->Add(&item);
	}

	return true;
}

void RandomName::Unload()
{
	SAFE_DELETE_DICTIONARY_VALUE(mItems);
}

HeapString RandomName::GetRandomName3(uint seed/*=0*/) const
{
	Random random(seed);
	List<const CoreProto::RandomNameConfigItem*>* items0=mItems.TryGetValueWithFailed(0,NULL);
	List<const CoreProto::RandomNameConfigItem*>* items1=mItems.TryGetValueWithFailed(1,NULL);
	List<const CoreProto::RandomNameConfigItem*>* items2=mItems.TryGetValueWithFailed(2,NULL);
	HeapString result;
	if (items0!=NULL&&!items0->IsEmpty())
	{
		intp index=random.Next(static_cast<int>(items0->GetCount())-1);
		result+=items0->Get(index)->value().c_str();
	}
	bool has1=random.NextBool();
	if (items1!=NULL&&!items1->IsEmpty()&&has1)
	{
		intp index=random.Next(static_cast<int>(items1->GetCount())-1);
		result+=items1->Get(index)->value().c_str();
	}

	if (items2!=NULL&&!items2->IsEmpty())
	{
		intp index=random.Next(static_cast<int>(items2->GetCount())-1);
		result+=items2->Get(index)->value().c_str();
	}

	return result;

}

MEDUSA_END;
