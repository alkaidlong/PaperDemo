
#include "Scene/SceneManager.h"
#include "Scene/IScene.h"
#include "Core/Log/Log.h"
#include "Scene/Editor/LayerEditor.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/Event/UIEventDispatcher.h"

SceneManager::SceneManager(void)
{
	mRunningScene=NULL;
}


SceneManager::~SceneManager(void)
{
	Uninitialize();
}


void SceneManager::Uninitialize()
{
	mRunningScene=NULL;
	SAFE_DELETE_COLLECTION(mScenes);
}


void SceneManager::PushScene( IScene* scene )
{
	if (scene==mRunningScene||mScenes.Contains(scene))
	{
		Log::LogError("scene has been already pushed.");
		return;
	}

	if (mRunningScene!=NULL)	//
	{
		mScenes.Push(mRunningScene);
		mRunningScene->Uninitialize();
		UIEventDispatcher::Instance().Dispatch();	//maybe some async delete layer callback need to handle first
		CCDirector::sharedDirector()->popScene();
		ResourceManager::Instance().Shrink();
		CCDirector::sharedDirector()->pushScene(scene);

	}
	else
	{
		LayerEditor::Instance().BeginProtoCache();
		CCDirector::sharedDirector()->runWithScene(scene);
	}

	
	mRunningScene=scene;

}

IScene* SceneManager::PopScene()
{
	RETURN_NULL_IF_NULL(mRunningScene);

	UIEventDispatcher::Instance().Dispatch();	//maybe some async delete layer callback need to handle first

	CCDirector::sharedDirector()->popScene();
	mRunningScene->Uninitialize();
	ResourceManager::Instance().Shrink();

	IScene* prevRunningScene=mRunningScene;

	if (!mScenes.IsEmpty())
	{
		mRunningScene=mScenes.Pop();
		CCDirector::sharedDirector()->pushScene(mRunningScene);
	}
	else
	{
		mRunningScene=NULL;
	}

	return prevRunningScene;
}

IScene* SceneManager::ReplaceScene( IScene* scene,bool isClearAnimation )
{
	if (scene==mRunningScene||mScenes.Contains(scene))
	{
		Log::LogError("scene has been already pushed.");
		return NULL;
	}

	if (mRunningScene!=NULL)	//
	{
		UIEventDispatcher::Instance().Dispatch();	//maybe some async delete layer callback need to handle first
		CCDirector::sharedDirector()->popScene();
		mRunningScene->Uninitialize();

		ResourceManager::Instance().Shrink(isClearAnimation);
	}

	IScene* prevRunningScene=mRunningScene;
	mRunningScene=scene;
	CCDirector::sharedDirector()->pushScene(mRunningScene);

	return prevRunningScene;
}

void SceneManager::Update( float dt )
{
	if (mRunningScene!=NULL)
	{
		mRunningScene->UpdateRecursively(dt);
	}
}





