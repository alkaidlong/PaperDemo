
#include "NormalLayerNode.h"



NormalLayerNode::NormalLayerNode(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}


NormalLayerNode::~NormalLayerNode(void)
{
}

bool NormalLayerNode::Initialize()
{
	return true;
}

NormalLayerNode* NormalLayerNode::Clone() const
{
	NormalLayerNode* normalLayer=new NormalLayerNode();
	normalLayer->autorelease();

	normalLayer->SetProtoData(mProtoData);
	normalLayer->Initialize();
	return normalLayer;
}




