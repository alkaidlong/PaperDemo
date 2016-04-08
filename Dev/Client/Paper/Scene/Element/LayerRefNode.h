#pragma once

#include "Scene/INode.h"

MEDUSA_BEGIN;

class LayerRefNode :public INode,public CCLayer
{
public:
	LayerRefNode(StringRef name=StringRef::Empty);
	virtual ~LayerRefNode(void);
	virtual bool Initialize();
public:
	void SetProtoData(const CoreProto::Editor::LayerRef& val) { mProtoData = val; }

protected:
	CoreProto::Editor::LayerRef mProtoData;
};

MEDUSA_END;
