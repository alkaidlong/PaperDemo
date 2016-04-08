
#include "Game/Battle/UI/BattleMissionProgressLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Event/InputDispatcher.h"
#include "Core/Pattern/Event.h"
#include "Engine/Animation/AnimationManager.h"
#include "Scene/Element/FrameNode.h"

BattleMissionProgressLayer::BattleMissionProgressLayer(const IEventArg& e/*=IEventArg::Empty*/)
{

}

BattleMissionProgressLayer::~BattleMissionProgressLayer()
{

}

bool BattleMissionProgressLayer::Uninitialize()
{
	FOR_EACH_COLLECTION(i,mSprites)
	{
		SpriteNode* removeChild = (*i).Value;
		RemoveChild( removeChild );
	}
	mSprites.Clear();
	return true;
}

void BattleMissionProgressLayer::SetElementPosition(uint id,float pos)
{
	const float widthBG = ((SpriteNode*)FindChild("BG"))->getContentSize().width;
	mSprites[id]->setPositionX(widthBG*pos);
}

void BattleMissionProgressLayer::AddElement(uint id,RoleType team,float pos)
{
	SpriteNode* element;
	switch (team)
	{
	case RoleType::Player:
		element = (SpriteNode*)FindChild("Player");
		break;
	case RoleType::NPC:
		element = (SpriteNode*)FindChild("NPC");
		break;
	case RoleType::Monster:
		element = (SpriteNode*)FindChild("Monster");
		break;
	case RoleType::Boss:
		element = (SpriteNode*)FindChild("Boss");
		break;
	default:
		break;
	}

	SpriteNode* copyElement = element->Clone();
	copyElement->setVisible(true);
	StackString<64> name;
	name.Format("%d",id);
	copyElement->SetName(name);
	mSprites.Add(id,copyElement);
	AddChild(copyElement);
	SetElementPosition(id,pos);
}

void BattleMissionProgressLayer::RemoveElement(uint id)
{
	SpriteNode* removeChild = mSprites[id];
	RemoveChild( removeChild );
	mSprites.RemoveKey(id);
}


IMPLEMENT_REGISTER_LAYER(BattleMissionProgressLayer,"BattleMissionProgress.layer");
