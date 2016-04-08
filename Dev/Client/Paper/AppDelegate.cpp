
#include "AppDelegate.h"
#include "Game/PaperGame.h"
#include "Config/PaperConfig.h"
#include "Core/Log/Log.h"
#include "Scene/IScene.h"
USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	bool isDebug;
#ifndef MEDUSA_DEBUG
	isDebug=false;
#endif

#ifdef MEDUSA_WINDOWS
	isDebug=true;
#endif

	pDirector->setOpenGLView(pEGLView);
	pDirector->setDisplayStats(isDebug);
	pDirector->setAnimationInterval(1.0 / 60); 
	Size2F designSize=PaperConfig::Instance().GetDesignWinSize();
	pEGLView->setDesignResolutionSize(designSize.Width,designSize.Height,kResolutionShowAll);
	PaperGame::Instance().InitRoles();
	PaperGame::Instance().StartWithGameBlackAround();
	PaperGame::Instance().StartWithSelectRole();
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();

    PaperGame::Instance().EnterBackGround();
	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
		
	CCDirector::sharedDirector()->startAnimation();
    PaperGame::Instance().EnterForeground();
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::applicationWillTerminate()
{
}
