
#include "Game/UI/Main/HeroIconLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Core/IO/Updater/FileUpdater.h"
#include "Scene/Editor/LayerEditor.h"
#include "Game/Battle/Logic/Role.h"

HeroIconLayer::HeroIconLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

HeroIconLayer::~HeroIconLayer()
{
}

bool HeroIconLayer::Initialize()
{
	mFaceIcon = NULL;
	mColorIcon = NULL;

	mLevelLabel = (LabelNode*)FindChildConfidently("LevelLabel");
	return true;
}

bool HeroIconLayer::Uninitialize()
{
	return true;
}

void HeroIconLayer::SetIconInfo( const Role* role )
{
	if (mFaceIcon==NULL)
	{
		mFaceIcon = LayerEditor::Instance().CreateSpriteNode(this,(FrameNode*)FindChildConfidently("RoleHeadFrame"),"FaceIcon",role->GetFaceName());
	}
	else
	{
		mFaceIcon->ReloadSprite(role->GetFaceName());
	}

	if (mColorIcon==NULL)
	{
		mColorIcon = LayerEditor::Instance().CreateSpriteNode(this,(FrameNode*)FindChildConfidently("RoleColorFrame"),"ColorIcon",FileId("HeroQualityFrame.png",role->GetColorID()));
	}
	else
	{
		mColorIcon->ReloadSprite(FileId("HeroQualityFrame.png",role->GetColorID()));
	}

	mLevelLabel->setString(StringParser::ToString(role->GetProperty().GetRoleLevel()).c_str());
}


IMPLEMENT_REGISTER_LAYER(HeroIconLayer,"HeroIcon.layer");