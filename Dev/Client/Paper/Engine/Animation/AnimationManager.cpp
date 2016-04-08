
#include "AnimationManager.h"
#include "Engine/Animation/IAnimation.h"
#include "Engine/Animation/AnimationEvent.h"
#include "Core/Profile/ProfileSample.h"
#include "Engine/Resource/ResourceManager.h"


AnimationManager::AnimationManager()
{

}

AnimationManager::~AnimationManager()
{

}

void AnimationManager::CleanupAnimations( Dictionary<IAnimation*,AnimationEvent*>& clearMap )
{
	FOR_EACH_COLLECTION(i,clearMap)
	{
		IAnimation* ani=(*i).Key;
		mAnimationPool.Recycle((*i).Key);
		delete (*i).Value;
		ani->release();
	}
	clearMap.Clear();
}

void AnimationManager::CleanupEvents()
{
	SAFE_DELETE_COLLECTION(mEndEvents);
}

void AnimationManager::UnInitialize()
{
	Clear();
	mAnimationPool.Clear();
	mBlockPool.Clear();
	CleanupEvents();
}

void AnimationManager::Clear()
{
	CleanupAnimations(mRunDict);
	CleanupAnimations(mInitDict);
}

IAnimation* AnimationManager::CreateAnimation( bool isRepeat , int zOrder , const FileId& fileID , const Dictionary<HeapString, FileId> *res /*= NULL */ )
{
	IAnimation* ani = mAnimationPool.GetAnimation();
	ani->Initialize(isRepeat,zOrder,fileID,res);	
	AddAnimation(ani);
	return ani;
}

IAnimation* AnimationManager::CreateAnimation()
{
	IAnimation* ani = mAnimationPool.GetAnimation();
	AddAnimation(ani);
	return ani;
}

void AnimationManager::ReloadAnimation( IAnimation* animation, bool isRepeat , int zOrder , const FileId& fileID , const Dictionary<HeapString, FileId> *res /*= NULL */ )
{
	bool isInRunDict=false;
	bool isInInitDict=false;
	{
		Lock lock(mMutex);
		if(mRunDict.ContainsKey(animation))
		{
			mEndEvents.Add( mRunDict.GetValue(animation) );
			mRunDict.RemoveKey(animation);
			isInRunDict=true;
		}
		else if(mInitDict.ContainsKey(animation))
		{
			mEndEvents.Add( mInitDict.GetValue(animation) );
			mInitDict.RemoveKey(animation);
			isInInitDict=true;
		}
		else
		{
			Log::AssertFailedFormat("Cannot reload animation:%x not in dict",(intp)animation);
			return;
		}
	}

	animation->Initialize(isRepeat,zOrder,fileID,res);

	{
		Lock lock(mMutex);
		if(isInRunDict)
		{
			mRunDict.Add(animation,new AnimationEvent());
		}
		else if(isInInitDict)
		{
			mInitDict.Add(animation,new AnimationEvent());
		}
	}
	
}

void AnimationManager::RegisterEvent( IAnimation* animation, int frameIndex,AnimationEvent::FrameHandler animationEvent )
{
	AnimationEvent* eventItem = mInitDict.TryGetValueWithFailed(animation,NULL);
	if(eventItem == NULL)
	{
		eventItem = mRunDict.TryGetValueWithFailed(animation,NULL);
		if( eventItem == NULL )
		{
			Log::AssertFailed("Register event failed!");
			return;
		}
	}

	if( frameIndex == IAnimation::AnimationCallBackFront )
	{
		eventItem->RegisterBeginCallback(animationEvent);
	}
	else if( frameIndex == IAnimation::AnimationCallBackLast )
	{
		eventItem->RegisterEndCallback(animationEvent);
	}
	else
	{
		eventItem->RegisterEvent( frameIndex, animationEvent );	
	}
}

void AnimationManager::ResetEvent( IAnimation* animation )
{
	if(mRunDict.ContainsKey(animation))
	{
		AnimationEvent* eve = mRunDict.GetValue(animation);
		eve->Reset();
	}
	else
	{
		if(mInitDict.ContainsKey(animation))
		{
			AnimationEvent* eve = mInitDict.GetValue(animation);
			eve->Reset();
		}
	}
}

void AnimationManager::AddAnimation( IAnimation* animation )
{
	Lock lock(mMutex);
	if(!mInitDict.ContainsKey(animation))
	{
		mInitDict.Add(animation,new AnimationEvent());
		animation->retain();
	}
	else
	{
		Log::AssertFailed("Animation already exists!");
	}
}

void AnimationManager::RemoveAnimation( IAnimation* animation ,bool isRecyle/*=true*/)
{
	Lock lock(mMutex);

	if(mRunDict.ContainsKey(animation))
	{
		AnimationEvent* eve = mRunDict.GetValue(animation);
		mRunDict.RemoveKey(animation);

		if (isRecyle)
		{
			mAnimationPool.Recycle(animation);
			animation->release();

		}
		else
		{
			animation->UnInitialize();
			animation->release();
		}
		delete eve;
	}
	else
	{
		if(mInitDict.ContainsKey(animation))
		{
			AnimationEvent* eve = mInitDict.GetValue(animation);
			mInitDict.RemoveKey(animation);
			if (isRecyle)
			{
				mAnimationPool.Recycle(animation);
			}
			else
			{
				animation->UnInitialize();
			}
			animation->release();

			delete eve;
		}
		else
		{
			Log::LogErrorFormat("AnimationManager::RemoveAnimation: Invalid animation");
		}
	}
}

void AnimationManager::MergeAnimation()
{
	FOR_EACH_COLLECTION(i,mInitDict)
	{
		AnimationEvent* eve = (*i).Value;
		IAnimation* ani = (*i).Key;
		if(mRunDict.ContainsKey(ani))
		{
			mRunDict[ani] = eve;
		}
		else
		{
			mRunDict.Add(ani,eve);
			ani->retain();
		}
		eve->InvokeBeginCallback(ani);
		ani->release();
	}
	mInitDict.Clear();
}

void AnimationManager::PauseAll()
{
	FOR_EACH_COLLECTION( i, mRunDict )
	{
		(*i).Key->Pause();
	}
}

void AnimationManager::RunAll()
{
	FOR_EACH_COLLECTION( i, mRunDict )
	{
		IAnimation* ani = (*i).Key;
		ani->Run(ani->isVisible());
	}
}

void AnimationManager::Update( float dt )
{
	Lock lock(mMutex);

	MergeAnimation();

	List<IAnimation*> removeAnimations;

	FOR_EACH_COLLECTION(i,mRunDict)
	{
		IAnimation* ani = (*i).Key;
		AnimationEvent* eve = (*i).Value;
		if(ani -> GetState() == IAnimation::AnimationEnd )
		{
			eve->InvokeEndCallback(ani);//回调函数可能会改变动画状态，所以在回调执行完之后再次判断动画状态
			if( ani->GetState() == IAnimation::AnimationEnd )
			{
				removeAnimations.Add(ani);
				//Log::LogInfoFormat("AnimationManager::Update Remove:%x",ani);

			}
		}
		else if(ani -> GetState() == IAnimation::AnimationPause )
		{
			if (ani->GetCurrentFrameIndex()+1==ani->GetFrameCount()&&ani->IsPauseOnLastFrame())	//reach last frame
			{
				eve->InvokeEndCallback(ani);//回调函数可能会改变动画状态，所以在回调执行完之后再次判断动画状态
			}
			
			if( ani->GetState() == IAnimation::AnimationEnd )
			{
				removeAnimations.Add(ani);
				//Log::LogInfoFormat("AnimationManager::Update Remove:%x",ani);

			}
		}
		else
		{
			ani->Update(dt);
			switch( ani->GetAnimationRunningState() )
			{
			case IAnimation::SequenceRunning:
				eve->InvokeCallback(ani->GetCurrentFrameIndex(),ani);
				break;
			case IAnimation::InvertedRunning:
				eve->InvokeCallback( (ani->GetFrameCount() - ani->GetCurrentFrameIndex() -1 ),ani);
				break;
			}
		}

	}

	FOR_EACH_COLLECTION(i,removeAnimations)
	{
		RemoveAnimation(*i);
	}

	CleanupEvents();
}

void AnimationManager::Shrink()
{
	Clear();
	mAnimationPool.Clear();
	mBlockPool.Clear();
}
