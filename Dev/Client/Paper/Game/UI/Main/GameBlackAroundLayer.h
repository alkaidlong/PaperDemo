#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/SpriteNode.h"
USING_MEDUSA;

//this class is used to implement logic codes
class GameBlackAroundLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	GameBlackAroundLayer(const IEventArg& e=IEventArg::Empty);
	~GameBlackAroundLayer();

	virtual bool Initialize();
	virtual bool Uninitialize();

protected:
	void CreateAllAroundSpritePosition();
	SpriteNode* mSpriteNodeUp;
	SpriteNode* mSpriteNodeDown;
	SpriteNode* mSpriteNodeLeft;
	SpriteNode* mSpriteNodeRight;

};
