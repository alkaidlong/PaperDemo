#pragma once
#include "Scene/Element/LayerNode.h"
USING_MEDUSA;


class NormalLayerNode :public LayerNode
{
public:
	NormalLayerNode(const IEventArg& e=IEventArg::Empty);
	virtual ~NormalLayerNode(void);
	virtual bool Initialize();
	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual NormalLayerNode* Clone() const;

	virtual StringRef GetProtoName()const{return mLayerProtoName;}
	void SetProtoName(const StringRef& val) { mLayerProtoName = val; }
	virtual  ElementType GetElementType()const{return ElementType::Layer;}
private:
	HeapString mLayerProtoName;
};


