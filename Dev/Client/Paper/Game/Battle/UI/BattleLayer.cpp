#include "Game/Battle/UI/BattleLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Game/Battle/BattleManager.h"
#include "Game/PaperGame.h"

BattleLayer::BattleLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{

}

BattleLayer::~BattleLayer()
{
}

bool BattleLayer::Initialize()
{
	mPauseButton=(ButtonNode*)FindChild("PauseButton");
	mPauseButton->AddTapGestureHandler(TapEventHandler(this,&BattleLayer::OnPauseButton));

	mBattlefieldLayer = (BattlefieldLayer*)FindChild("Battlefield");

	mMissionProgressLayer = (BattleMissionProgressLayer*)FindChild("MissionProgress");
	return true;
}

void BattleLayer::OnPauseButton(INode* sender,TapGestureEventArg& e)
{
	BattleManager::Instance().Uninitialize();
	PaperGame::Instance().SwitchToSelectRole();
}

bool BattleLayer::Uninitialize()
{
	return true;
}

BattleSkillButtonLayer* BattleLayer::GetSkillButton(int index)
{
	StackString<64> name;
	name.Format("SkillButton%d",index);
	return (BattleSkillButtonLayer*)FindChild(name);
}

void BattleLayer::AddBGLayer(LayerNode* node)
{
	mBattlefieldLayer->AddChild(node);
}

void BattleLayer::AddAnimationToBattlefield(int frameID,IAnimation* ani)
{
	mBattlefieldLayer->AddAnimationToBattlefield(frameID,ani);
}

FrameNode* BattleLayer::GetBattlefieldFrame(int frameID)
{
	return mBattlefieldLayer->GetBattlefieldFrame(frameID);
}

IMPLEMENT_REGISTER_LAYER(BattleLayer,"Battle.layer");