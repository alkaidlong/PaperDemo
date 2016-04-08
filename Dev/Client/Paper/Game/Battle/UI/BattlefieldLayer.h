#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/FrameNode.h"
USING_MEDUSA;

class IAnimation;

class BattlefieldLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	BattlefieldLayer(const IEventArg& e=IEventArg::Empty);
	~BattlefieldLayer();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	void AddAnimationToBattlefield(int frameID,IAnimation* ani);
	FrameNode* GetBattlefieldFrame(int frameID);//-1,0,1
};
