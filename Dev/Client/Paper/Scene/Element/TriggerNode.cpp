
#include "TriggerNode.h"



TriggerNode::TriggerNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


TriggerNode::~TriggerNode(void)
{
}

bool TriggerNode::Initialize()
{
	return true;
}

TriggerNode* TriggerNode::Clone() const
{
	TriggerNode* trigger=new TriggerNode();
	trigger->autorelease();

	trigger->SetProtoData(mProtoData);
	trigger->Initialize();
	return trigger;
}


