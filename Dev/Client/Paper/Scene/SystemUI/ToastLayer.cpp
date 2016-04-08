
#include "Scene/SystemUI/ToastLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Event/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Core/IO/Updater/FileUpdater.h"

#include "Scene/SceneManager.h"
#include "Scene/IScene.h"
#include "Config/PaperConfig.h"

ToastLayer::ToastLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

ToastLayer::~ToastLayer()
{
	mBackgroundImage->stopAllActions();
}

bool ToastLayer::Initialize()
{
	mLabel = (LabelNode*)FindChildConfidently("InformationLabel");
	mLabel->setOpacity(0);

	mBackgroundImage = (SpriteNode*)FindChildConfidently("PromptBox");
	mBackgroundImage->setOpacity(0);

	EnableInput(false);
	return true;
}

bool ToastLayer::Uninitialize()
{
	return true;
}


void ToastLayer::SetString( StringRef str )
{
	mLabel->setString(str.c_str());
}

void ToastLayer::Run()
{
	CC_NEW_CALLFUNC_MEMBER_VOID(myCallback,ToastLayer,this,OnHide);

	float showTime = PaperConfig::Instance().ToastShowTime();
	
	CCFadeIn* fadeInImage=CCFadeIn::create(0.2f);
	CCDelayTime* delayImage= CCDelayTime::create(showTime);
	CCFadeOut* fadeOutImage=CCFadeOut::create(0.2f);
	CCArray* myArray=CCArray::createWithCapacity(4);
	myArray->addObject(fadeInImage);
	myArray->addObject(delayImage);
	myArray->addObject(fadeOutImage);
	myArray->addObject(myCallback);
	CCSequence* seq=CCSequence::create(myArray);
	mBackgroundImage->runAction(seq);

	CCFadeIn* fadeInLabel=CCFadeIn::create(0.2f);
	CCDelayTime* delayLabel= CCDelayTime::create(showTime);
	CCFadeOut* fadeOutLabel=CCFadeOut::create(0.2f);
	CCArray* actionLabelArray=CCArray::createWithCapacity(3);
	actionLabelArray->addObject(fadeInLabel);
	actionLabelArray->addObject(delayLabel);
	actionLabelArray->addObject(fadeOutLabel);
	CCSequence* seqLabel=CCSequence::create(actionLabelArray);
	mLabel->runAction(seqLabel);
}



void ToastLayer::OnHide( void* )
{
	removeFromParentAndCleanup(true);
}

IMPLEMENT_REGISTER_LAYER(ToastLayer,"Toast.layer");
