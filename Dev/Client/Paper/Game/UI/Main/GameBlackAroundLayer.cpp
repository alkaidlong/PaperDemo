
#include "Game/UI/Main/GameBlackAroundLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Event/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Core/IO/Updater/FileUpdater.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/IO/FileId.h"
#include "Config/PaperConfig.h"
GameBlackAroundLayer::GameBlackAroundLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
	mSpriteNodeUp=NULL;
	mSpriteNodeDown=NULL;
	mSpriteNodeLeft=NULL;
	mSpriteNodeRight=NULL;
}

GameBlackAroundLayer::~GameBlackAroundLayer()
{
}

bool GameBlackAroundLayer::Initialize()
{
	mSpriteNodeUp = (SpriteNode*)FindChild("SpriteNodeUp");
	Log::AssertNotNull(mSpriteNodeUp,"SpriteNodeUp");
	mSpriteNodeUp->setVisible(false);
	mSpriteNodeDown = (SpriteNode*)FindChild("SpriteNodeDown");
	Log::AssertNotNull(mSpriteNodeDown,"SpriteNodeDown");
	mSpriteNodeDown->setVisible(false);
	mSpriteNodeLeft = (SpriteNode*)FindChild("SpriteNodeLeft");
	Log::AssertNotNull(mSpriteNodeLeft,"SpriteNodeLeft");
	mSpriteNodeLeft->setVisible(false);
	mSpriteNodeRight = (SpriteNode*)FindChild("SpriteNodeRight");
	Log::AssertNotNull(mSpriteNodeRight,"SpriteNodeRight");
	mSpriteNodeRight->setVisible(false);
	CreateAllAroundSpritePosition();
	return true;
}

bool GameBlackAroundLayer::Uninitialize()
{
	return true;
}

void GameBlackAroundLayer::CreateAllAroundSpritePosition()
{
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	Size2F designSize=PaperConfig::Instance().GetDesignWinSize();
	CCSize winSize=pEGLView->getFrameSize();
	CCSize visibleSize=CCSize(pEGLView->m_obViewPortRect.size.width,pEGLView->m_obViewPortRect.size.height);
	float scaleX=designSize.Width/winSize.width;
	float scaleY=designSize.Height/winSize.height;


	if (visibleSize.height<winSize.height)
	{//ÉÏÏÂºÚ±ß
		CCSize sizeUp;
		
		sizeUp.width=(winSize.width*scaleX);
		sizeUp.height=((winSize.height-visibleSize.height)/2*scaleY);
		mSpriteNodeUp->setContentSize(sizeUp);
		mSpriteNodeUp->ReCalculateScaleNineVertices();
		mSpriteNodeUp->setAnchorPoint(ccp(0,0));

		mSpriteNodeUp->setPosition(ccp(0,(winSize.height-visibleSize.height)/2*scaleY+visibleSize.height*scaleY));
		mSpriteNodeUp->setVisible(true);
		//////////////////////////////////////////////////////////////////////////
		
		CCSize sizeDown;
		sizeDown.width=(winSize.width*scaleX);
		sizeDown.height=((winSize.height-visibleSize.height)/2*scaleY);

		mSpriteNodeDown->setContentSize(sizeDown);
		mSpriteNodeDown->ReCalculateScaleNineVertices();
		mSpriteNodeDown->setAnchorPoint(ccp(0,0));
		mSpriteNodeDown->setPosition(ccp(0,0));
		mSpriteNodeDown->setVisible(true);
		CCDirector::sharedDirector()->SetGameBlackAroundLayer((CCLayer*)this);
	}
	else if(visibleSize.width<winSize.width)
	{//×óÓÒºÚ±ß

		CCSize sizeLeft;
		sizeLeft.width=(winSize.width-visibleSize.width)*scaleX/2;
		sizeLeft.height=winSize.height*scaleY;
		mSpriteNodeLeft->setContentSize(sizeLeft);
		mSpriteNodeLeft->ReCalculateScaleNineVertices();
		mSpriteNodeLeft->setAnchorPoint(ccp(0,0));
		mSpriteNodeLeft->setPosition(ccp(0,0));
		mSpriteNodeLeft->setVisible(true);
		//////////////////////////////////////////////////////////////////////////
		CCSize sizeRight;
		sizeRight.width=((winSize.width-visibleSize.width)*scaleX/2);
		sizeRight.height=(winSize.height*scaleY);
		mSpriteNodeRight->setContentSize(sizeRight);
		mSpriteNodeRight->ReCalculateScaleNineVertices();
		mSpriteNodeRight->setAnchorPoint(ccp(0,0));
		mSpriteNodeRight->setPosition(ccp(visibleSize.width*scaleX+(winSize.width-visibleSize.width)*scaleX/2,0));
		mSpriteNodeRight->setVisible(true);
		CCDirector::sharedDirector()->SetGameBlackAroundLayer((CCLayer*)this);
	}
}


IMPLEMENT_REGISTER_LAYER(GameBlackAroundLayer,"GameBlackAround.layer");