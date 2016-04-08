
#include "MainScene.h"
#include "Core/Log/Log.h"
#include "Scene/IScene.h"
#include "Scene/SceneManager.h"

#include "Game/UI/Main/SelectHeroLayer.h"


MainScene::MainScene():IScene()
{

}

MainScene::~MainScene(void)
{

}

bool MainScene::Initialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Initialize());

	return true;
}

bool MainScene::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(IScene::Uninitialize());

	return true;
}


bool MainScene::SwitchToSelectRole()
{
	PopAllLayer();
	PushLayer<SelectHeroLayer>();
	return true;
}

bool MainScene::SwitchToBattle()
{
	return true;
}
