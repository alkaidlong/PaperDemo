
#include "AnimationBlockPool.h"
#include "Engine/Resource/ResourceManager.h"

AnimationBlockPool::AnimationBlockPool()
{
	mFreeBlocksCount = 0; 
	mUsingBlocksCount = 0;
}

AnimationBlockPool::~AnimationBlockPool()
{

}

void AnimationBlockPool::Clear()
{
	FOR_EACH_COLLECTION(i,mFreeBlocks)
	{
		Queue<AnimationBlock*>* que = (*i).Value;
		uint count=que->GetCount();
		FOR_EACH_COLLECTION(j,*que)
		{
			AnimationBlock* block=*j;
			block->release();
			//SAFE_DELETE(block);
			--count;
		}


		if (count!=0)
		{
			Log::LogError("Memory Leak");
		}
		SAFE_DELETE(que);

		//SAFE_DELETE_COLLECTION(*que);
	}
	mFreeBlocks.Clear();
	mFreeBlocksCount=0;
}

void AnimationBlockPool::Recycle(AnimationBlock* block)
{
	Lock lock(mMutex);
	Log::Assert(block!=NULL,"model is NULL!");
	//block->retain();
	block->UnInitialize();

	block->setOpacity( 255 );
	ccColor4B color;
	color.a = 0;
	color.b = 0;
	color.g = 0;
	color.r = 0;
	block->SetDeltaColor(color);
	block->setColor(ccc3(255,255,255));
	block->setOpacity( 255 );
	

	Queue<AnimationBlock*>* blockQueue = mFreeBlocks.TryGetValueWithFailed(block->GetFileID(),NULL);
	if (blockQueue==NULL)
	{
		blockQueue=new Queue<AnimationBlock*>();
		mFreeBlocks.Add(block->GetFileID(),blockQueue);
	}

	blockQueue->Push(block);
	mFreeBlocksCount ++;
	mUsingBlocksCount--;
}

AnimationBlock* AnimationBlockPool::GetBlock(const FileId& fileID ,unsigned int blockID )
{

	AnimationBlock* block;

	Queue<AnimationBlock*>* blockQueue = mFreeBlocks.TryGetValueWithFailed(fileID,NULL);
	if (blockQueue!=NULL)
	{
		if(!blockQueue->IsEmpty())
		{
			Lock lock(mMutex);

			block = blockQueue->Head();
			blockQueue->Pop();
			mUsingBlocksCount ++;
			mFreeBlocksCount--;
			block->setVisible(true);
			block->Initialize(blockID);
			//block->release();
			return block;
		}
	}

	block = new AnimationBlock();
	//block->autorelease();
	block->Initialize(fileID,blockID);
	return block;
}
