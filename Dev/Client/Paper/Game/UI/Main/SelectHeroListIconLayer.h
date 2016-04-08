#pragma once
#include "Scene/Element/LayerNode.h"
USING_MEDUSA;

#include "Game/UI/Main/HeroIconLayer.h"
#include "Scene/Element/SpriteNode.h"

class Role;
//this class is used to implement logic codes

enum class SelectHeroIconStatus
{
	Normal,
	Selected,
	Disabled,
};

class SelectHeroListIconLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	SelectHeroListIconLayer(const IEventArg& e=IEventArg::Empty);
	~SelectHeroListIconLayer();

	virtual bool Initialize();
	virtual bool Uninitialize();

	void SetHeroInfo(const Role* role);

	void SetIsShowBackground(bool isShow);
	void SetIconStatus(SelectHeroIconStatus status);

	const Role* GetRoleData() const { return mRoleData; }
protected:
	void OnButtonTap(INode* sender,TapGestureEventArg& e);

private:
	HeroIconLayer* mHeroIcon;

	SpriteNode* mBackgroundImage;

	SelectHeroIconStatus mStatus;
	SpriteNode* mSelectImage;
	SpriteNode* mDisabledImage;

	const Role* mRoleData;
};
