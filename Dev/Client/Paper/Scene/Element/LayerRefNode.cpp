#include "Platform/Platform.h"
#include "LayerRefNode.h"

MEDUSA_BEGIN;

LayerRefNode::LayerRefNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


LayerRefNode::~LayerRefNode(void)
{
}

bool LayerRefNode::Initialize()
{
	return true;
}


MEDUSA_END;
