#include "Game/Battle/UI/BattleSkillButtonLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Animation/IAnimation.h"
#include "Game/Battle/Logic/Role.h"
#include "Game/Battle/BattleManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/Proto/Client/LayerEditor.pb.h"

BattleSkillButtonLayer::BattleSkillButtonLayer( const IEventArg& e/*=IEventArg::Empty*/ )
{
	mButtonEffect = NULL;
	mMaxPercentageValue = 99.9f;
	mRole = NULL;
	mCurMP = 0;
	mCurHP = 0;
	mMaxMP = 0;
	mMaxHP = 0;
}

BattleSkillButtonLayer::~BattleSkillButtonLayer()
{

}

bool BattleSkillButtonLayer::Initialize()
{

	return true;
}

void BattleSkillButtonLayer::Initialize( Role* role )
{
	setVisible(true);
	mRole = role;
	
	mMaxMP = mRole->GetProperty().GetCurProperty().magicalproperty().maxvalue();
	mMaxHP = mRole->GetProperty().GetCurProperty().physicalproperty().maxvalue();

	FrameNode* roleIconFrame = (FrameNode*)FindChild("HeroIconFrame");
	Log::AssertNotNull(roleIconFrame,"HeroIconFrame");
	mRoleIcon = LayerEditor::Instance().CreateSpriteNode( this,roleIconFrame,"RoleIcon.png",FileId(mRole->GetFaceName()));
	roleIconFrame->EnableInput(true);

	FrameNode* qualityFrame = (FrameNode*)FindChild("QualityFrame");
	Log::AssertNotNull(qualityFrame,"QualityFrame");
	mQuality = LayerEditor::Instance().CreateSpriteNode( this,qualityFrame,"HeroQualityFrame.png",role->GetColorFileID());

	FrameNode* effectFrame = (FrameNode*)FindChild("CdEffectFrame");
	Log::AssertNotNull(effectFrame,"CdEffectFrame");

	mButtonEffect = ResourceManager::Instance().CreateAnimation(effectFrame,FileId("UIFrameRollYellow.ani"));
	mButtonEffect->Run();
	mButtonEffect->setVisible(false);
	mButtonEffect->setAnchorPoint(CCPointZero);
	mButtonEffect->setPosition(CCPointZero);

	mBloodProgress = (ProgressBarNode*)FindChild("BloodProgressBar");
	Log::AssertNotNull(mBloodProgress,"BloodProgressBar");

	mBloodWhiteProgressBar = (ProgressBarNode*)FindChild("BloodWhiteProgressBar");
	Log::AssertNotNull(mBloodWhiteProgressBar,"BloodWhiteProgressBar");

	mBloodReductionProgressBar = (ProgressBarNode*)FindChild("BloodReductionProgressBar");
	Log::AssertNotNull(mBloodReductionProgressBar,"BloodReductionProgressBar");

	mEnergyProgress = (ProgressBarNode*)FindChild("EnergyProgressBar");
	Log::AssertNotNull(mEnergyProgress,"EnergyProgressBar");

	mEnergyWhiteProgressBar = (ProgressBarNode*)FindChild("EnergyWhiteProgressBar");
	Log::AssertNotNull(mEnergyWhiteProgressBar,"EnergyWhiteProgressBar");

	mEnergyReductionProgressBar = (ProgressBarNode*)FindChild("EnergyReductionProgressBar");
	Log::AssertNotNull(mEnergyReductionProgressBar,"EnergyReductionProgressBar");

	UpdateBlood();
	UpdateEnergy();

	AddTapGestureHandler("HeroIconFrame",TapEventHandler(this,&BattleSkillButtonLayer::OnTirggerCallback));
	EnableInput(false);
}

bool BattleSkillButtonLayer::Uninitialize()
{
	return true;
}

bool BattleSkillButtonLayer::Update(float dt)
{
	RETURN_TRUE_IF_NULL(mRole);
	UpdateEnergy();
	UpdateBlood();
	if( mCurMP < mDesMP )
	{
		float timeP = dt/BattleManager::Instance().EnergyTime();
		float deltaMP = timeP*mMaxMP;
		mCurMP = Math::Min((float)mDesMP,(float)mCurMP+deltaMP);
		float percentage = (float)mCurMP/mMaxMP;
		percentage = Math::Clamp(percentage,0.0f,1.0f);
		mEnergyProgress->setPercentage(percentage*mMaxPercentageValue);
	}
	else if( mCurMP > mDesMP )
	{
		float timeP = dt/BattleManager::Instance().EnergyTime();
		float deltaMP = timeP*mMaxMP;
		mCurMP = Math::Max((float)mDesMP,(float)mCurMP-deltaMP);
		float percentage = (float)mCurMP/mMaxMP;
		percentage = Math::Clamp(percentage,0.0f,1.0f);
		mEnergyReductionProgressBar->setPercentage(percentage*mMaxPercentageValue);
	}

	if( mCurHP < mDesHP )
	{
		float timeP = dt/BattleManager::Instance().BloodTime();
		float deltaHP = timeP*mMaxHP;
		mCurHP = Math::Min((float)mDesHP,(float)mCurHP+deltaHP);
		float percentage = (float)mCurHP/mMaxHP;
		percentage = Math::Clamp(percentage,0.0f,1.0f);
		mBloodProgress->setPercentage(percentage*mMaxPercentageValue);
	}
	else if( mCurHP > mDesHP )
	{
		float timeP = dt/BattleManager::Instance().BloodTime();
		float deltaHP = timeP*mMaxHP;
		mCurHP = Math::Max((float)mDesHP,(float)mCurHP-deltaHP);
		float percentage = (float)mCurHP/mMaxHP;
		percentage = Math::Clamp(percentage,0.0f,1.0f);
		mBloodReductionProgressBar->setPercentage(percentage*mMaxPercentageValue);
	}
	return true;
}

void BattleSkillButtonLayer::OnTirggerCallback( INode* sender,TapGestureEventArg& )
{

}

void BattleSkillButtonLayer::ClearEnergy()
{
	mDesMP = 0;
	mButtonEffect->setVisible(false);
	EnableInput(false);
}

void BattleSkillButtonLayer::ClearBlood()
{
	mDesHP = 0;
	mButtonEffect->setVisible(false);
	EnableInput(false);
	mRoleIcon->SetRenderFlag(RenderFlag::Grayscale);
	mQuality->SetRenderFlag(RenderFlag::Grayscale);
}

void BattleSkillButtonLayer::UpdateEnergy()
{
	RETURN_IF_NULL(mRole);
	mDesMP = mRole->GetMP();
	
	if( mCurMP < mDesMP )
	{
		float percentage = ((float)mDesMP/mMaxMP);

		percentage = Math::Clamp(percentage,0.0f,1.0f);

		mEnergyReductionProgressBar->setPercentage(percentage*mMaxPercentageValue);
	}
	else if( mCurMP > mDesMP )
	{
		float percentage = ((float)mDesMP/mMaxMP);

		percentage = Math::Clamp(percentage,0.0f,1.0f);

		mEnergyProgress->setPercentage(percentage*mMaxPercentageValue);
	}

	if(mDesMP >= mMaxMP)
	{
		mDesMP = mMaxMP;
		if(mRole->CanTirggerSkill())
		{
			EnableInput(false);
			mButtonEffect->setVisible(false);
		}
		else
		{
			EnableInput(true);
			mButtonEffect->setVisible(true);
		}
	}
	else
	{
		EnableInput(false);
		mButtonEffect->setVisible(false);
	}
}

void BattleSkillButtonLayer::UpdateBlood()
{
	RETURN_IF_NULL(mRole);
	mDesHP = mRole->GetHP();

	if( mCurHP < mDesHP )
	{
		float percentage = (float)mDesHP/mMaxHP;

		percentage = Math::Clamp(percentage,0.0f,1.0f);

		mBloodReductionProgressBar->setPercentage(percentage*mMaxPercentageValue);
	}
	else if( mCurHP > mDesHP )
	{
		float percentage = (float)mDesHP/mMaxHP;

		percentage = Math::Clamp(percentage,0.0f,1.0f);

		mBloodProgress->setPercentage(percentage*mMaxPercentageValue);
	}
}

IMPLEMENT_REGISTER_LAYER(BattleSkillButtonLayer,"BattleSkillButton.layer");

