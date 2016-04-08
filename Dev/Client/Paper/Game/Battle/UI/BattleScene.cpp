#include "Game/Battle/UI/BattleScene.h"
#include "Game/Battle/UI/Battlelayer.h"
#include "Game/Battle/UI/BattlePauseLayer.h"
#include "Game/Battle/BattleManager.h"
#include "Scene/SceneManager.h"

BattleScene::BattleScene():IScene()
{
	
}


BattleScene::~BattleScene(void)
{
	
}

bool BattleScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Initialize());
	SetName("BattleScene");
	BattleLayer* battleLayer = PushLayer<BattleLayer>();
	BattleManager::Instance().SetBattleLayer(battleLayer);
	return true;
}

bool BattleScene::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Uninitialize());
	
	return true;
}

bool BattleScene::PauseBattle()
{
	BattleManager::Instance().Pause();
	SceneManager::Instance().GetRunningScene()->PushLayer<BattlePauseLayer>(LayerPushFlags::ShowPrevLayer);
	return true;
}

