#pragma once

#include "Engine/Animation/AnimationBlockPool.h"
#include "Engine/Animation/AnimationModelManager.h"
#include "Engine/Animation/AnimationPool.h"
#include "Core/Pattern/Singleton.h"
#include "Core/IO/FileId.h"
#include "Core/Threading/Thread.h"
USING_MEDUSA;


class IAnimation;
class AnimationEvent;
class AnimationManager :public Pattern::Singleton< AnimationManager >
{
	friend class Pattern::Singleton<AnimationManager>;
private:
	AnimationManager();
	~AnimationManager();
	void CleanupAnimations( Dictionary<IAnimation*,AnimationEvent*>& clearMap );
	void CleanupEvents();
private:
	Dictionary<IAnimation*,AnimationEvent*> mRunDict;
	Dictionary<IAnimation*,AnimationEvent*> mInitDict;
	List<AnimationEvent*> mEndEvents;
	AnimationBlockPool mBlockPool;
	AnimationPool mAnimationPool;

public:
	IAnimation* CreateAnimation();
	IAnimation* CreateAnimation( bool isRepeat , int zOrder , const FileId& fileID , const Dictionary<HeapString, FileId> *res = NULL  );
	void ReloadAnimation( IAnimation* animation, bool isRepeat , int zOrder , const FileId& fileID , const Dictionary<HeapString, FileId> *res = NULL );
	void RegisterEvent( IAnimation* animation, int frameIndex,AnimationEvent::FrameHandler animationEvent );
	void ResetEvent(IAnimation* animation);
	void AddAnimation(IAnimation* animation );
	void RemoveAnimation(IAnimation* animation,bool isRecyle=true);
	void MergeAnimation();

	void PauseAll();
	void RunAll();


	void Clear();
	void Update(float dt);

	void UnInitialize();

	void Shrink();
	AnimationBlockPool& GetBlockPool() { return mBlockPool; }
	AnimationPool& GetAnimationPool(){ return mAnimationPool; }
private:
	Mutex mMutex;
};


