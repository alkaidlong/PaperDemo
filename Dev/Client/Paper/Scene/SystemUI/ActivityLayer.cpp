
#include "Scene/SystemUI/ActivityLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Event/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Core/IO/Updater/FileUpdater.h"

#include "Scene/SceneManager.h"
#include "Scene/IScene.h"

#include "Scene/Element/SpriteNode.h"

ActivityLayer::ActivityLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
	mActivityIndicatorCount=0;
}

ActivityLayer::~ActivityLayer()
{
}

bool ActivityLayer::Initialize()
{
	mNode=(SpriteNode*)FindChild("Loading1");
	Log::AssertNotNull(mNode,"Loading1");

	setZOrder(INT_MAX);
	EnableInput(false);
	return true;
}

bool ActivityLayer::Uninitialize()
{
	mNode->stopAllActions();
	CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);

	return true;
}

void ActivityLayer::Show()
{
	++mActivityIndicatorCount;

	if (isVisible()==false)
	{
		setVisible(true);
		//start action

		CCRotateBy* rotateAction=CCRotateBy::create(1.f,360.f);
		CCRepeatForever* rep= CCRepeatForever::create(rotateAction);
		mNode->runAction(rep);

		CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(false);
	}
}

void ActivityLayer::Hide()
{
	--mActivityIndicatorCount;
	if (mActivityIndicatorCount<=0)
	{
		mActivityIndicatorCount = 0;
		setVisible(false);
		mNode->stopAllActions();
		//stop action
		CCDirector::sharedDirector()->getTouchDispatcher()->setDispatchEvents(true);
	}
}


IMPLEMENT_REGISTER_LAYER(ActivityLayer,"Activity.layer");

