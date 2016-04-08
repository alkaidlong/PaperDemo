#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/IRunnable.h"
#include "Core/Collection/Stack.h"
class IScene;
USING_MEDUSA;

class SceneManager:public Pattern::Singleton<SceneManager>
{
	friend class Pattern::Singleton<SceneManager>;
	SceneManager(void);
	~SceneManager(void);

public:
	void Uninitialize();
public:
	IScene* GetRunningScene()const{return mRunningScene;}
	void PushScene(IScene* scene);
	IScene* PopScene();
	IScene* ReplaceScene(IScene* scene,bool isClearAnimation=true);

	void Update(float dt);
protected:
	Stack<IScene*> mScenes;	//scene stack
	IScene* mRunningScene;	//weak ptr
};


