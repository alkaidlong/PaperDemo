#include "MedusaCorePreCompiled.h"
#include "Core/String/FuckyString/FuckyStringNode.h"

MEDUSA_BEGIN;

FuckyStringNode::FuckyStringNode():mChar(0),mIsFucky(false),mChilds(NULL)
{

}

FuckyStringNode::~FuckyStringNode(void)
{
	if (mChilds!=NULL)
	{
		SAFE_DELETE_DICTIONARY_VALUE(*mChilds);
		SAFE_DELETE(mChilds);
	}
}



bool FuckyStringNode::Load( const CoreProto::FuckyStringNode& item )
{
	mChar=item.charval();
	mIsFucky=item.isfucky();
	if (item.childs().size()>0)
	{
		mChilds=new Dictionary<wchar_t,FuckyStringNode*>();
	}

	FOR_EACH_COLLECTION_STL(i,item.childs())
	{
		const CoreProto::FuckyStringNode& item=*i;
		FuckyStringNode* node=new FuckyStringNode();
		node->Load(item);
		mChilds->Add(item.charval(),node);
	}
	
	return true;
}
MEDUSA_END;
