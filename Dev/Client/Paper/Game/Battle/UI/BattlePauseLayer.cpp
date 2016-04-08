#include "Game/Battle/UI/BattlePauseLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Scene/Element/ButtonNode.h"
#include "Game/Battle/BattleManager.h"
#include "Game/PaperGame.h"
#include "Scene/SceneManager.h"
#include "Scene/IScene.h"

BattlePauseLayer::BattlePauseLayer( const IEventArg& e/*=IEventArg::Empty*/ )
{

}

BattlePauseLayer::~BattlePauseLayer()
{

}

bool BattlePauseLayer::Initialize()
{
	if(BattleManager::Instance().EnableExitButton())
	{
		AddTapGestureHandler("ExitButton",TapEventHandler(this,&BattlePauseLayer::OnExit));
	}
	else
	{
		ButtonNode* exitButton = (ButtonNode*)FindChild("ExitButton");
		Log::AssertNotNull(exitButton,"ExitButton");
		exitButton->SetState(ButtonState::Disabled);
		exitButton->EnableInput(false);
	}
	AddTapGestureHandler("BreakButton",TapEventHandler(this,&BattlePauseLayer::OnBreak));
	return true;
}

void BattlePauseLayer::OnExit(INode* sender,TapGestureEventArg&)
{
	PaperGame::Instance().SwitchToSelectRole();
	BattleManager::Instance().Uninitialize();
}

void BattlePauseLayer::OnBreak(INode* sender,TapGestureEventArg&)
{
	SceneManager::Instance().GetRunningScene()->PopLayer();
}

IMPLEMENT_REGISTER_LAYER(BattlePauseLayer,"BattlePause.layer");
