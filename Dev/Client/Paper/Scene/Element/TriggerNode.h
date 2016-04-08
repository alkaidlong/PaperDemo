#pragma once

#include "Scene/INode.h"

USING_MEDUSA;

class TriggerNode :public INode,public CCObject
{
public:
	TriggerNode(StringRef name=StringRef::Empty);
	virtual ~TriggerNode(void);
	virtual bool Initialize();
	virtual const CCNode* GetDrawCCNode()const{return NULL;}
	virtual CCNode* GetDrawCCNode(){return NULL;}
	virtual TriggerNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::Node;}
public:
	void SetProtoData(const CoreProto::Editor::Trigger& val) { mProtoData = val; }

protected:
	CoreProto::Editor::Trigger mProtoData;
};


