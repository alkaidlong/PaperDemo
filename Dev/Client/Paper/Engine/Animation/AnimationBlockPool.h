#pragma once


#include "Engine/Animation/AnimationBlock.h"
#include "Core/IO/FileId.h"
#include "Core/Collection/Queue.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Threading/Lock.h"

class AnimationBlockPool
{
	friend class AnimationManager;
private:
	Dictionary<FileId,Queue<AnimationBlock*>*> mFreeBlocks;
	unsigned int mFreeBlocksCount; 
	unsigned int mUsingBlocksCount;

private:
	AnimationBlockPool();
	~AnimationBlockPool();

public:
	void Clear();
	void Recycle(AnimationBlock* block);
	AnimationBlock* GetBlock( const FileId& fileID ,unsigned int blockID );

public:
	int GetUsingCount() const { return mUsingBlocksCount; };
	int GetFreeCount() const { return mFreeBlocksCount; };
private:
	Mutex mMutex;
};

