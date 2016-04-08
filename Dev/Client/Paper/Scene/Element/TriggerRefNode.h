#pragma once

#include "Scene/INode.h"

USING_MEDUSA;

class TriggerRefNode :public INode,public CCObject
{
public:
	TriggerRefNode(StringRef name=StringRef::Empty);
	virtual ~TriggerRefNode(void);
	virtual bool Initialize();
	virtual const CCNode* GetDrawCCNode()const{return NULL;}
	virtual CCNode* GetDrawCCNode(){return NULL;}
	virtual TriggerRefNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::Node;}

public:
	void SetProtoData(const CoreProto::Editor::TriggerRef& val) { mProtoData = val; }

protected:
	CoreProto::Editor::TriggerRef mProtoData;
};


