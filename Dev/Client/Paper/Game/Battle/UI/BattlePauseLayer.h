#pragma once
#include "Scene/Element/LayerNode.h"
USING_MEDUSA;

class BattlePauseLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	BattlePauseLayer(const IEventArg& e=IEventArg::Empty);
	~BattlePauseLayer();
public:
	virtual bool Initialize();
	virtual bool IsModal()const{return true;};
public:
	void OnExit(INode* sender,TapGestureEventArg&);
	void OnBreak(INode* sender,TapGestureEventArg&);
};
