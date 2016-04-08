
#include "Game/UI/Main/SelectHeroListIconLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"


SelectHeroListIconLayer::SelectHeroListIconLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

SelectHeroListIconLayer::~SelectHeroListIconLayer()
{
}

bool SelectHeroListIconLayer::Initialize()
{
	mHeroIcon = (HeroIconLayer*)FindChildConfidently("HeroIconLayerRef");
	mHeroIcon->setVisible(false);

	mBackgroundImage = (SpriteNode*)FindChildConfidently("BackgroundImage");
	mSelectImage = (SpriteNode*)FindChildConfidently("SelectImage");
	mDisabledImage = (SpriteNode*)FindChildConfidently("DisabledImage");

	mRoleData = NULL;

	SetIconStatus(SelectHeroIconStatus::Normal);
	SetIsShowBackground(false);
	return true;
}

bool SelectHeroListIconLayer::Uninitialize()
{
	return true;
}

void SelectHeroListIconLayer::OnButtonTap( INode* sender,TapGestureEventArg& e )
{
	Log::LogInfo("tap");
}

void SelectHeroListIconLayer::SetHeroInfo( const Role* role )
{
	mRoleData = role;
	if (mRoleData!=NULL)
	{
		mHeroIcon->SetIconInfo(mRoleData);
		mHeroIcon->setVisible(true);
	}
	else
	{
		mHeroIcon->setVisible(false);
	}
}

void SelectHeroListIconLayer::SetIsShowBackground( bool isShow )
{
	mBackgroundImage->setVisible(isShow);
}

void SelectHeroListIconLayer::SetIconStatus( SelectHeroIconStatus status )
{
	switch (status)
	{
	case SelectHeroIconStatus::Normal:
		mSelectImage->setVisible(false);
		mDisabledImage->setVisible(false);
		break;
	case SelectHeroIconStatus::Selected:
		mSelectImage->setVisible(true);
		mDisabledImage->setVisible(false);
		break;
	case SelectHeroIconStatus::Disabled:
		mSelectImage->setVisible(false);
		mDisabledImage->setVisible(true);
		break;
	default:
		break;
	}
}

IMPLEMENT_REGISTER_LAYER(SelectHeroListIconLayer,"SelectHeroListIcon.layer");
