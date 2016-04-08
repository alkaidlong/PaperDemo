#include "MedusaCorePreCompiled.h"
#include "Core/String/FuckyString/FuckyString.h"
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;

FuckyString::~FuckyString()
{
	Unload();
}


bool FuckyString::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData("FuckyString.bin");
	return LoadFromData(data);
}

bool FuckyString::LoadFromData(MemoryByteData data)
{
	Unload();
	CoreProto::FuckyString config;
	RETURN_FALSE_IF_FALSE(Proto::ParseFrom(config,data));

	FOR_EACH_COLLECTION_STL(i,config.rootnodes())
	{
		const CoreProto::FuckyStringNode& item=*i;
		FuckyStringNode* node=new FuckyStringNode();
		node->Load(item);
		mRootNodes.Add(item.charval(),node);
	}

	return true;
}

void FuckyString::Unload()
{
	SAFE_DELETE_DICTIONARY_VALUE(mRootNodes);
}

bool FuckyString::IsFucky(StringRef str) const
{
	WHeapString tempStr=StringParser::ToW(str);
	return IsFucky(tempStr);
}

bool FuckyString::IsFucky( WStringRef str ) const
{
	size_t length= str.Length();
	FOR_EACH_SIZE(i,length)
	{
		wchar_t c=str[i];

		FuckyStringNode* node=mRootNodes.TryGetValueWithFailed(c,NULL);
		CONTINUE_IF_NULL(node);

		const Dictionary<wchar_t,FuckyStringNode*>* nodes=node->GetChildsPtr();
		CONTINUE_IF_NULL(nodes);

		for (size_t j=i+1;j<length;++j)
		{
			wchar_t c2=str[j];

			FuckyStringNode* node=nodes->TryGetValueWithFailed(c2,NULL);
			BREAK_IF_NULL(node);

			if (node->IsFucky())
			{
				//最短匹配
				return true;
			}
			else
			{
				nodes=node->GetChildsPtr();
				RETURN_TRUE_IF_NULL(nodes);	//reach the last one
			}
		}
	}

	return false;
}



bool FuckyString::TryClean( WHeapString& str,char replace) const
{
	bool isFucky=false;
	//实现最长匹配
	uint length= static_cast<uint>(str.Length());
	FOR_EACH_SIZE(i,length)
	{
		wchar_t c=str[i];
		FuckyStringNode* node=mRootNodes.TryGetValueWithFailed(c,NULL);
		CONTINUE_IF_NULL(node);

		const Dictionary<wchar_t,FuckyStringNode*>* nodes=node->GetChildsPtr();
		CONTINUE_IF_NULL(nodes);

		size_t matchIndex=0;
		for (size_t j=i+1;j<length;++j)
		{
			wchar_t c2=str[j];
			FuckyStringNode* node=nodes->TryGetValueWithFailed(c2,NULL);
			BREAK_IF_NULL(node);
			if (node->IsFucky())
			{
				matchIndex=j;
			}
			else
			{
				nodes=node->GetChildsPtr();
				if(nodes==NULL)
				{
					matchIndex=j;
					break;
				}

			}
		}

		if (matchIndex>0)
		{
			for (size_t k=i;k<=matchIndex;++k)
			{
				str[k]=replace;
			}

			i=matchIndex;	//will +1 in for later
			isFucky=true;
		}
	}

	return isFucky;
}

MEDUSA_END;
