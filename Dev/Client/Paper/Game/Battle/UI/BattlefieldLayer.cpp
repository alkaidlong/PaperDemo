#include "Game/Battle/UI/BattlefieldLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Engine/Animation/IAnimation.h"

BattlefieldLayer::BattlefieldLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{

}

BattlefieldLayer::~BattlefieldLayer()
{
}

bool BattlefieldLayer::Initialize()
{
	return true;
}


bool BattlefieldLayer::Uninitialize()
{
	return true;
}

void BattlefieldLayer::AddAnimationToBattlefield(int frameID,IAnimation* ani)
{
	FrameNode* frame = GetBattlefieldFrame(frameID);
	frame->addChild(ani);
}

FrameNode* BattlefieldLayer::GetBattlefieldFrame(int frameID)
{
	StackString<64> name;
	name.Format("ShowFrame%d",frameID);
	return (FrameNode*)FindChild(name);
}

IMPLEMENT_REGISTER_LAYER(BattlefieldLayer,"Battlefield.layer");