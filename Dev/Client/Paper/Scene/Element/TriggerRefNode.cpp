
#include "TriggerRefNode.h"



TriggerRefNode::TriggerRefNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


TriggerRefNode::~TriggerRefNode(void)
{
}

bool TriggerRefNode::Initialize()
{
	return true;
}

TriggerRefNode* TriggerRefNode::Clone() const
{
	TriggerRefNode* triggerRef=new TriggerRefNode();
	triggerRef->autorelease();

	triggerRef->SetProtoData(mProtoData);
	triggerRef->Initialize();
	return triggerRef;
}



