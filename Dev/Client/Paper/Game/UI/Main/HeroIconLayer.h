#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/FrameNode.h"
#include "Scene/Element/SpriteNode.h"
#include "Scene/Element/LabelNode.h"

USING_MEDUSA;

//this class is used to implement logic codes

class Role;
class HeroIconLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	HeroIconLayer(const IEventArg& e=IEventArg::Empty);
	~HeroIconLayer();

	virtual bool Initialize();
	virtual bool Uninitialize();

	void SetIconInfo(const Role* role);
protected:

private:
	SpriteNode* mFaceIcon;
	SpriteNode* mColorIcon;

	LabelNode* mLevelLabel;

};
