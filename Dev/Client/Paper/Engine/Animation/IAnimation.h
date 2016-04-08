#pragma once

#include "Engine/Animation/AnimationBlock.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Animation/AnimationEvent.h"
#include "Core/Math/MathHeader.h"
USING_MEDUSA;


class IAnimation : public CCSprite
{
	friend class AnimationPool;
public:
	enum AnimationState
	{
		AnimationInit,
		AnimationRunning,
		AnimationPause,
		AnimationEnd,
	};

	enum AnimationRunningState
	{
		SequenceRunning,
		InvertedRunning,
	};

public:
	static const int AnimationCallBackFront = Math::IntMinValue;
	static const int AnimationCallBackLast = Math::IntMaxValue;
private:
	volatile AnimationState mState;
	volatile AnimationRunningState mRunningState;
	float mPlaySpeed;
	Dictionary<unsigned int,AnimationBlock*> mBlockDict;
	Dictionary<unsigned int,IAnimation*> mAnimationDict;
	bool mIsPauseOnLastFrame;
protected:

	FileIdStorage mModelFileID;
	const CoreProto::AnimationModel* mModel; 
	Dictionary<HeapString, FileId>* mResDict;

	int mFrameCount;
	float mModelDuration;
	float mEveryFrameTime;
	float mCurrentRunTime;
	unsigned int mCurrentFrameIndex;
	bool mIsRepeat;

private:
	IAnimation();
	void AssertCallbackIndexValid(int frameIndex) const;
	void SetAnimationRunningState(IAnimation::AnimationRunningState val) ;
	const CoreProto::BlockInfo* FindBlockInfoForAnimationModel( uint blockID,uint index );
	const CoreProto::BlockModel* FindBlockModelForAnimationModel( uint blockID,uint index );
	void DifferenceProcessing( CoreProto::BlockInfo& buffInfo,const CoreProto::BlockModel& blockModel );

//keyframe สนำร
	IAnimation* AddAnimationChild( FileId& fileID , const CoreProto::BlockModel& blockModel );
	AnimationBlock* AddBlock( FileId& fileID, const CoreProto::BlockModel& blockModel );
	void RecycleBlock( AnimationBlock* block );
	void RecycleAnimation( unsigned int blockID );
	IAnimation* ReloadAnimationDetection(const CoreProto::BlockModel& blockModel);

	IAnimation* FindAnimationForChildren( unsigned int blockID );
	AnimationBlock* FindBlockForChildren( unsigned int blockID );
	AnimationBlock* FindBlockForChildren( FileId& fileID );
	AnimationBlock* ReloadBlockDetection(const CoreProto::BlockModel& blockModel);

	void UpdateLocation(const CoreProto::BlockInfo& blockmodel);

protected:
	void UpdateChildData();

	void UpdateChildDataHelper();

	void UpdateBlockChildData( const CoreProto::BlockModel& blockModel );
	void UpdateAnimationChildData( const CoreProto::BlockModel& blockModel );
	void SetAnchor( const CoreProto::BlockInfo& blockInfo,AnimationBlock* block );
	AnimationBlock* GetBlock(const HeapString& blockName );
public:

	virtual ~IAnimation();
	bool Initialize( bool isRepeat,int zOrder, const FileId& modelFileID ,const Dictionary<HeapString, FileId>* res = NULL );
	void UnInitialize();
	void RegisterEvent(unsigned int frameIndex,AnimationEvent::FrameHandler frameCallback );
	void End();
	void EndAndPauseOnLastFrame();
	void Run(bool isVisible=true);
	void Pause();
	void Stop();
	void SetSequence();
	void SetInverted();
	void Update(float dt);
	void ReloadAnimation( bool isRepeat,const FileId& resFileID );

public:
	void SetPlaybackSpeed( float speed ){ mPlaySpeed = speed; }
	void SetPlaybackTime( float time );
	virtual void setFlipX( bool isFlipX );
	virtual void setFlipY( bool isFlipY );
	void SetIsRepeat(bool isRepeat){mIsRepeat = isRepeat;}
	void SetResourceMap( const Dictionary<HeapString, FileId>* res );
	const Dictionary<HeapString, FileId>* GetResourceMap(){return mResDict;};
	float GetModelDuration()const{ return mModelDuration; };
	IAnimation::AnimationState GetState() const { return mState; }
	float GetAnimationWidth() const { if(mModel==NULL) {return 0.0f;} return mModel->modelsize().width(); }
	float GetAnimationHeight() const { if(mModel==NULL) {return 0.0f;} return mModel->modelsize().height(); }
	int GetFrameCount() const { return mFrameCount; }
	float GetCurrentRunTime() const { return mCurrentRunTime; }
	void SetCurrentRunTime(float val) { mCurrentRunTime = val; }
	unsigned int GetCurrentFrameIndex() const { return mCurrentFrameIndex; }
	IAnimation::AnimationRunningState GetAnimationRunningState() const { return mRunningState; }
	const FileIdStorage& GetModelLocation() const { return mModelFileID; } 
	void SetAnimationState(IAnimation::AnimationState val) { mState = val; }
	void SetPauseOnLastFrame(bool isPauseOnLastFrame){ mIsPauseOnLastFrame = isPauseOnLastFrame; }
	bool IsPauseOnLastFrame()const{return mIsPauseOnLastFrame; }

	
};

