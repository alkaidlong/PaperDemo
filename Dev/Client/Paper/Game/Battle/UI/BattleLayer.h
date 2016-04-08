#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/SpriteNode.h"
#include "Scene/Element/ButtonNode.h"
#include "Game/Battle/UI/BattleMissionProgressLayer.h"
#include "Game/Battle/UI/BattleSkillButtonLayer.h"
#include "Game/Battle/UI/BattlefieldLayer.h"
USING_MEDUSA;

class IAnimation;

class BattleLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	BattleLayer(const IEventArg& e=IEventArg::Empty);
	~BattleLayer();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	void AddAnimationToBattlefield(int frameID,IAnimation* ani);
	FrameNode* GetBattlefieldFrame(int frameID);//-1,0,1
	BattleSkillButtonLayer* GetSkillButton(int index);
	void AddBGLayer(LayerNode* node);
	BattleMissionProgressLayer* GetMissionProgressLayer() { return mMissionProgressLayer; } 
protected:
	void OnPauseButton(INode* sender,TapGestureEventArg& e);
private:
	ButtonNode* mPauseButton;
	BattleMissionProgressLayer* mMissionProgressLayer;
	BattlefieldLayer* mBattlefieldLayer;
};
