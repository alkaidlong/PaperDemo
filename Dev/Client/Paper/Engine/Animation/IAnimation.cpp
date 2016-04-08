
#include "IAnimation.h"
#include "AnimationManager.h"
#include "AnimationBlockPool.h"
#include "Core/String/StringParser.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"

IAnimation::IAnimation()
	:mState(AnimationInit),
	mRunningState(SequenceRunning),
	mModel(NULL),
	mModelDuration(0),
	mCurrentFrameIndex(0),
	mEveryFrameTime(0.0f),
	mCurrentRunTime(0.0f),
	mPlaySpeed(1.0f),
	mIsRepeat(false),
	mFrameCount(0),
	mResDict(NULL),
	mIsPauseOnLastFrame(false)
{
	init();
}

IAnimation::~IAnimation()
{
	SAFE_DELETE(mResDict);
}



bool IAnimation::Initialize( bool isRepeat,int zOrder, const FileId& modelFileID ,const Dictionary<HeapString, FileId>* res /*= NULL */ )
{
	mState=AnimationInit;
	mIsRepeat = isRepeat;
	SetResourceMap(res);
	m_nZOrder = zOrder;
	m_nTag = zOrder;
	mModelFileID = modelFileID;
	mModel = AnimationModelManager::Instance().GetModel(modelFileID);
	Log::AssertFormat(mModel!=NULL," AnimationModel is NULL!  name : %s ,order : %zu ",modelFileID.Name.c_str(),modelFileID.Order);
	int count = mModel->frames().size();
	int rate = mModel->framerate();

	mModelDuration = (count/(float)rate);
	mEveryFrameTime = 1.0f/(float)rate;
	mCurrentRunTime = 0.0f;
	mCurrentFrameIndex = 0;
	mPlaySpeed = 1.0f;
	mFrameCount = count;
	setContentSize(CCSize(mModel->modelsize().width(),mModel->modelsize().height()));
	setVisible(false);
	UpdateChildData();
	setAnchorPoint(CCPointZero);
	mIsPauseOnLastFrame = false;
	return true;
}

void IAnimation::UnInitialize()
{
	FOR_EACH_COLLECTION( i,mBlockDict )
	{
		AnimationBlock* block = (*i).Value;
		AnimationManager::Instance().GetBlockPool().Recycle(block);
	}

	FOR_EACH_COLLECTION(i,mAnimationDict)
	{
		IAnimation* ani=(*i).Value;
		ani->End();
	}
	setTag(0);
	removeFromParentAndCleanup(true);
	removeAllChildrenWithCleanup(true);
	mIsPauseOnLastFrame = false;
	mBlockDict.Clear();
	mAnimationDict.Clear();
	SAFE_DELETE(mResDict);
	mModel = NULL;
}

void IAnimation::End()
{
	if( mIsPauseOnLastFrame )
	{
		SetAnimationState(AnimationPause);
		return;
	}
	SetAnimationState(AnimationEnd);
}

void IAnimation::EndAndPauseOnLastFrame()
{
	Run();
	SetPauseOnLastFrame(true); 
	switch(mRunningState)
	{
	case SequenceRunning:
		mCurrentRunTime=mModelDuration;
		mCurrentFrameIndex = (unsigned int)mModel->frames().size()-1;
		break;
	case InvertedRunning:
		mCurrentFrameIndex = 0;
		mCurrentRunTime=0.f;
		break;
	}		
	UpdateChildData();
	End();
}

void IAnimation::AssertCallbackIndexValid( int frameIndex ) const
{
	if( frameIndex < 0 && frameIndex != AnimationCallBackFront )
	{
		Log::AssertFailed("Illegal value frameIndex!");
	}
	else if( frameIndex >= mFrameCount && frameIndex != AnimationCallBackLast)
	{
		Log::AssertFailed("Illegal value frameIndex!");
	}
}

const CoreProto::BlockInfo* IAnimation::FindBlockInfoForAnimationModel( uint blockID,uint index )
{
	const CoreProto::BlockModel* blockModel = FindBlockModelForAnimationModel(blockID,index);
	return &(blockModel->info());
}

const CoreProto::BlockModel* IAnimation::FindBlockModelForAnimationModel( uint blockID,uint index )
{
	Log::Assert(index < (uint)mModel->frames().size(),"IAnimation frame Index subscript out of bounds!");	
	const CoreProto::FrameModel& frame = mModel->frames(index);
	FOR_EACH_COLLECTION_STL( i ,frame.blocks() )
	{
		//TODO:优化：1，工具中排序blockid，代码中实现二分查找
		if( i->blockid() == blockID )
		{
			return &(*i);
		}
	}
	Log::AssertFailed("Did not find the specified block!");	
	return NULL;
}

void IAnimation::DifferenceProcessing( CoreProto::BlockInfo& buffInfo,const CoreProto::BlockModel& blockModel )
{
	unsigned int blockID = blockModel.blockid();
	unsigned int prevIndex;
	unsigned int nextIndex;
	switch(mRunningState)
	{
	case SequenceRunning:
		prevIndex = blockModel.prevkeyframeindex();
		nextIndex = blockModel.nextkeyframeindex();
		break;
	case InvertedRunning:
		nextIndex = blockModel.prevkeyframeindex();
		prevIndex = blockModel.nextkeyframeindex();
		break;
	}

	const CoreProto::BlockInfo* prevInfo = FindBlockInfoForAnimationModel( blockID,prevIndex );
	const CoreProto::BlockInfo* nextInfo = FindBlockInfoForAnimationModel( blockID,nextIndex );

	float currentTimeRatio = 0; 

	if(nextIndex != prevIndex)
	{
		currentTimeRatio = (mCurrentRunTime - (float)prevIndex*mEveryFrameTime)/(((float)nextIndex-(float)prevIndex)*mEveryFrameTime);
	}

	buffInfo.mutable_pos()->set_x( prevInfo->pos().x() + ((nextInfo->pos().x()-prevInfo->pos().x())*currentTimeRatio) );
	buffInfo.mutable_pos()->set_y( prevInfo->pos().y() + ((nextInfo->pos().y()-prevInfo->pos().y())*currentTimeRatio) );

	float prevSkewX = prevInfo->skew().x();
	float nextSkewX = nextInfo->skew().x();
	float tempSkewX = nextSkewX-prevSkewX;
	float unsSkewX = fabs(tempSkewX);

	if( unsSkewX >180.0f)//角度差值就近原则
	{
		tempSkewX = 360.0f-unsSkewX;
		if(prevSkewX<nextSkewX)
		{
			tempSkewX = -tempSkewX;
		}
	}
	float skewx = prevSkewX+tempSkewX*currentTimeRatio;
	buffInfo.mutable_skew()->set_x(skewx);

	float prevSkewY = prevInfo->skew().y();
	float nextSkewY = nextInfo->skew().y();
	float tempSkewY = nextSkewY-prevSkewY;
	float unsSkewY = fabs(tempSkewY);

	if( unsSkewY >180.0f)//角度差值就近原则
	{
		tempSkewY = 360.0f-unsSkewY;
		if(prevSkewY<nextSkewY)
		{
			tempSkewY = -tempSkewY;
		}
	}
	float skewy = prevSkewY+tempSkewY*currentTimeRatio;
	buffInfo.mutable_skew()->set_y(skewy);

	buffInfo.mutable_scale()->set_x( prevInfo->scale().x()+ ((nextInfo->scale().x()-prevInfo->scale().x() )*currentTimeRatio) );
	buffInfo.mutable_scale()->set_y( prevInfo->scale().y()+ ((nextInfo->scale().y()-prevInfo->scale().y() )*currentTimeRatio) );
	buffInfo.set_zorder( nextInfo->zorder());

	if(prevInfo->has_colormultiplier() || nextInfo->has_colormultiplier())
	{
		ccColor3B color = getColor();
		GLubyte opacity = getOpacity();
		CoreProto::ColorF prevColor;
		CoreProto::ColorF nextColor;
		CoreProto::ColorF aniColor;

		aniColor.set_a(((float)opacity/255.0f));
		aniColor.set_r(((float)color.r/255.0f));
		aniColor.set_g(((float)color.g/255.0f));
		aniColor.set_b(((float)color.b/255.0f));

		if(prevInfo->has_colormultiplier())
		{
			prevColor = prevInfo->colormultiplier();
		}
		else
		{
			prevColor.set_a(1.0f*aniColor.a());
			prevColor.set_r(1.0f*aniColor.r());
			prevColor.set_g(1.0f*aniColor.g());
			prevColor.set_b(1.0f*aniColor.b());
		}
		if(nextInfo->has_colormultiplier())
		{
			nextColor = nextInfo->colormultiplier();
		}
		else
		{
			nextColor.set_a(1.0f*aniColor.a());
			nextColor.set_r(1.0f*aniColor.r());
			nextColor.set_g(1.0f*aniColor.g());
			nextColor.set_b(1.0f*aniColor.b());
		}

		buffInfo.mutable_colormultiplier()->set_a( (prevColor.a()+ ((nextColor.a()-prevColor.a() )*currentTimeRatio))*aniColor.a() );
		buffInfo.mutable_colormultiplier()->set_r( (prevColor.r()+ ((nextColor.r()-prevColor.r() )*currentTimeRatio))*aniColor.r() );
		buffInfo.mutable_colormultiplier()->set_g( (prevColor.g()+ ((nextColor.g()-prevColor.g() )*currentTimeRatio))*aniColor.g() );
		buffInfo.mutable_colormultiplier()->set_b( (prevColor.b()+ ((nextColor.b()-prevColor.b() )*currentTimeRatio))*aniColor.b() );
	}

	if(prevInfo->has_coloroffset() || nextInfo->has_coloroffset())
	{
		CoreProto::ColorF prevColor;
		CoreProto::ColorF nextColor;
		if(prevInfo->has_coloroffset())
		{
			prevColor = prevInfo->coloroffset();
		}
		if(nextInfo->has_coloroffset())
		{
			nextColor = nextInfo->coloroffset();
		}

		buffInfo.mutable_coloroffset()->set_a( prevColor.a()+ ((nextColor.a()-prevColor.a() )*currentTimeRatio) );
		buffInfo.mutable_coloroffset()->set_r( prevColor.r()+ ((nextColor.r()-prevColor.r() )*currentTimeRatio) );
		buffInfo.mutable_coloroffset()->set_g( prevColor.g()+ ((nextColor.g()-prevColor.g() )*currentTimeRatio) );
		buffInfo.mutable_coloroffset()->set_b( prevColor.b()+ ((nextColor.b()-prevColor.b() )*currentTimeRatio) );
	}
}

IAnimation* IAnimation::AddAnimationChild( FileId& fileID , const CoreProto::BlockModel& blockModel )
{
	const CoreProto::BlockInfo& blockInfo = blockModel.info();
	IAnimation* ani = AnimationManager::Instance().CreateAnimation(mIsRepeat,blockInfo.zorder(),fileID);
	addChild(ani,blockInfo.zorder(),blockInfo.zorder());
	ani->setAnchorPoint(getAnchorPoint());
	mAnimationDict.Add(blockModel.blockid(),ani);
	ani->Run();
	return ani;
}

AnimationBlock* IAnimation::AddBlock( FileId& fileID, const CoreProto::BlockModel& blockModel )
{
	uint blockID = blockModel.blockid();
	AnimationBlock* block  = AnimationManager::Instance().GetBlockPool().GetBlock(fileID,blockID);
	if(!mBlockDict.ContainsKey(blockID))
	{
		mBlockDict.Add(blockID,block);
	}
	else
	{
		Log::AssertFailedFormat("Duplicate block id:%d",blockID);
		return NULL;
	}
	//block 在获取时得到一个默认锚点
	//在设置flip的时候是需要通过实际锚点计算出当前锚点，所以计算步骤是
	//1，通过block宽高和默认锚点计算出实际锚点，函数SetAnchor
	//2，设置flip
	SetAnchor(blockModel.info(),block);
	block->setFlipX(isFlipX());
	block->setFlipY(isFlipY());
	block->setColor(getColor());
	block->setOpacity(getOpacity());
	addChild(block,blockModel.info().zorder(),blockModel.info().zorder());
	return block;
}

void IAnimation::RecycleBlock( AnimationBlock* block )
{
	bool isSuccess=mBlockDict.RemoveKey(block->GetBlockID());
	if (!isSuccess)
	{
		Log::AssertFormat(isSuccess,"Failed to remove animation block:%d",block->GetBlockID());
	}
	AnimationManager::Instance().GetBlockPool().Recycle(block);
}

void IAnimation::RecycleAnimation( unsigned int blockID )
{
	if(mAnimationDict.ContainsKey(blockID))
	{
		AnimationManager::Instance().RemoveAnimation(mAnimationDict.GetValue(blockID));
		mAnimationDict.RemoveKey(blockID);
	}
}

IAnimation* IAnimation::ReloadAnimationDetection( const CoreProto::BlockModel& blockModel )
{
	FileId fileID;
	const CoreProto::BlockModel* model;
	uint blockID = blockModel.blockid();
	IAnimation* ani = FindAnimationForChildren(blockID);
	uint imageIndex = -1;
	switch( blockModel.framevalue() )
	{
	case CoreProto::KeyFrame:
		imageIndex = blockModel.imageindex();
		model = &blockModel;
		break;
	default:
		return ani;
	}

	const CoreProto::FileId& fileIDData = mModel->components(imageIndex).fileid();
	fileID.Name = fileIDData.name();
	fileID.mTag = fileIDData.tag();
	fileID.Order = fileIDData.order();

	if( fileID.IsValid() )
	{
		if( ani != NULL )
		{
			RecycleAnimation(blockID);
		}
		ani = AddAnimationChild(fileID,*model);
	}

	return ani;
}

IAnimation* IAnimation::FindAnimationForChildren( unsigned int blockID )
{
	return mAnimationDict.TryGetValueWithFailed(blockID,NULL);
}

AnimationBlock* IAnimation::FindBlockForChildren( unsigned int blockID )
{
	return mBlockDict.TryGetValueWithFailed(blockID,NULL);
}

AnimationBlock* IAnimation::FindBlockForChildren( FileId& fileID )
{
	CCObject* pObject = NULL;
	AnimationBlock* block = NULL;

	CCARRAY_FOREACH(m_pChildren, pObject)
	{
		block = (AnimationBlock*)pObject;
		if( block->GetFileID() == fileID )
		{
			return block;
		}
	}
	return NULL;
}

AnimationBlock* IAnimation::ReloadBlockDetection( const CoreProto::BlockModel& blockModel )
{
	FileId fileID;
	const CoreProto::BlockModel* model;
	uint blockID = blockModel.blockid();
	AnimationBlock* block = FindBlockForChildren(blockID);
	uint imageIndex = -1;
	switch( blockModel.framevalue() )
	{
	case CoreProto::KeyFrame:
		imageIndex = blockModel.imageindex();
		model = &blockModel;
		break;
	case CoreProto::TweenFrame:
		{
			uint prevIndex = 0;
			switch(mRunningState)
			{
			case SequenceRunning:
				prevIndex = blockModel.prevkeyframeindex();
				break;
			case InvertedRunning:
				prevIndex = blockModel.nextkeyframeindex();
				break;
			}
			model = FindBlockModelForAnimationModel(blockID,prevIndex);
			imageIndex = model->imageindex();
		}
		break;
	default:
		break;
	}

	const CoreProto::FileId& fileIDData = mModel->components(imageIndex).fileid();

	if(mResDict == NULL)
	{
		fileID.Name = fileIDData.name();
		fileID.mTag = fileIDData.tag();
		fileID.Order = fileIDData.order();
	}
	else
	{
		if(mResDict->ContainsOtherKey( StringRef(fileIDData.name().c_str()),HashUtility::HashString(fileIDData.name().c_str()) ))
		{
			fileID = fileIDData;
		}
		else
		{
			if( block != NULL )
			{
				RecycleBlock(block);
				block = NULL;
			}
		}
	}

	if( fileID.IsValid() )
	{
		if( block != NULL )
		{
			if( block->GetFileID() != fileID )
			{
				RecycleBlock(block);
				if (model->blockid()==block->GetBlockID()&&mBlockDict.ContainsKey(block->GetBlockID()))
				{
					Log::AssertFailedFormat("Invalid duplicate block id:%d",block->GetBlockID());
				}
				block = AddBlock(fileID,*model);
			}
		}
		else
		{
			block = AddBlock(fileID,*model);
		}
	}

	return block;
}

void IAnimation::UpdateLocation( const CoreProto::BlockInfo& blockmodel )
{
	const CoreProto::PointF &point = blockmodel.pos();
	CCPoint pointInPixels(point.x(),point.y());
	const CoreProto::PointF &skew = blockmodel.skew();
	float skewx = skew.x();
	float skewy = skew.y();

	if( isFlipX() )
	{
		pointInPixels.x = -point.x();
		skewx = 360 - skewx;
		skewy = 360 - skewy;
	}

	if( isFlipY() )
	{
		pointInPixels.y = -point.y();
		skewx = 360 - skewx;
		skewy = 360 - skewy;
	}

	setPosition(pointInPixels);
	setSkewX(skewx);
	setSkewY(skewy);

	const CoreProto::ScaleF &scale = blockmodel.scale();
	setScaleX(scale.x());
	setScaleY(scale.y());

	if(blockmodel.has_colormultiplier())
	{
		setOpacity( (unsigned char)(blockmodel.colormultiplier().a()*255) );
		ccColor3B color = ccc3(255,255,255);
		color.r *= blockmodel.colormultiplier().r();
		color.g *= blockmodel.colormultiplier().g();
		color.b *= blockmodel.colormultiplier().b();
		setColor(color);
	}

	if (blockmodel.has_coloroffset())
	{
		ccColor4B color4;
		color4.a = blockmodel.coloroffset().a() ;
		color4.r = blockmodel.coloroffset().r() ;
		color4.g = blockmodel.coloroffset().g() ;
		color4.b = blockmodel.coloroffset().b() ;
		SetDeltaColor(color4);
	}


	if( blockmodel.zorder() != getZOrder() )
	{
		getParent()->reorderChild(this,blockmodel.zorder());
	}
}

void IAnimation::RegisterEvent( unsigned int frameIndex,AnimationEvent::FrameHandler frameCallback )
{
	RETURN_IF(mModel==NULL);
	AssertCallbackIndexValid(frameIndex);
	AnimationManager::Instance().RegisterEvent(this,frameIndex,frameCallback);
}

void IAnimation::Run(bool isVisible)
{
	setVisible(isVisible);
	SetAnimationState(AnimationRunning);
}

void IAnimation::Pause()
{
	SetAnimationState(AnimationPause);
}

void IAnimation::Stop()
{
	if( mState == AnimationInit )
	{
		return;
	}
	mCurrentRunTime = 0.0f;
	SetAnimationState(AnimationInit);
}

void IAnimation::SetSequence()
{
	if( mRunningState == SequenceRunning )
	{
		return;
	}
	SetAnimationRunningState(SequenceRunning);
}

void IAnimation::SetInverted()
{
	if( mRunningState == InvertedRunning )
	{
		return;
	}
	SetAnimationRunningState(InvertedRunning);
}

void IAnimation::Update( float dt )
{
	switch(mState)
	{
	case AnimationInit:
		break;
	case AnimationRunning:
		{
			RETURN_IF_NULL(mModel);
			switch(mRunningState)
			{
			case SequenceRunning:
				mCurrentRunTime += dt * mPlaySpeed;
				break;
			case InvertedRunning:
				mCurrentRunTime -= dt * mPlaySpeed;
				break;
			}
			UpdateChildData();
		}
		break;
	case AnimationPause:
		break;
	default:
		break;
	}
}

void IAnimation::SetAnchor( const CoreProto::BlockInfo& blockInfo,AnimationBlock* block )
{
	const FileSystemOrderItem* blockData = block->GetOrderItem();
	Point2F anchorPoint;
	if (blockData->HasOffset())
	{
		anchorPoint = LayerEditor::CalculateAnchor(Point2F(blockInfo.anchor().x(),blockInfo.anchor().y()),blockData->GetOffsetOrZero(),blockData->GetOriginalSizeOrZero(),blockData->GetTextureRectOrZero().Size);
	}
	else
	{
		anchorPoint.X = blockInfo.anchor().x();
		anchorPoint.Y = blockInfo.anchor().y();
	}

	block->setAnchorPoint(ccp(anchorPoint.X,anchorPoint.Y));
}

void IAnimation::ReloadAnimation( bool isRepeat,const FileId& resFileID )
{
	AnimationManager::Instance().ReloadAnimation(this,isRepeat,getZOrder(),resFileID,mResDict);
}

void IAnimation::UpdateChildData()
{
	while( mRunningState == SequenceRunning ? mCurrentRunTime >= mModelDuration : mCurrentRunTime <= 0 )
	{
		if(mIsRepeat)
		{
			switch(mRunningState)
			{
			case SequenceRunning:
				mCurrentRunTime -= mModelDuration;
				break;
			case InvertedRunning:
				mCurrentRunTime += mModelDuration;
				break;
			}

			AnimationManager::Instance().ResetEvent(this);
			FOR_EACH_COLLECTION(i,mBlockDict)
			{
				AnimationBlock* bloak = (*i).Value;
				bloak->Initialize();
			}

		}
		else
		{
			UpdateChildDataHelper();
			End();
			return;
		}
	}

	UpdateChildDataHelper();

}

void IAnimation::UpdateChildDataHelper()
{
	mCurrentFrameIndex = (unsigned int)(mCurrentRunTime/mEveryFrameTime );
	unsigned int frameSize = (unsigned int)mModel->frames().size();
	switch(mRunningState)
	{
	case SequenceRunning:
		mCurrentFrameIndex = Math::Clamp(mCurrentFrameIndex,(uint)0,frameSize-1);
		break;
	case InvertedRunning:
		mCurrentFrameIndex = Math::Clamp(mCurrentFrameIndex,(uint)0,frameSize-1);
		break;
	}

	Log::AssertFormat(mCurrentFrameIndex<frameSize,"UpdateChildData  CurrentFrameIndex Error");

	const ::google::protobuf::RepeatedPtrField< ::CoreProto::BlockModel >& blocks = mModel->frames(mCurrentFrameIndex).blocks();
	FOR_EACH_COLLECTION_STL(i,blocks)
	{
		const CoreProto::FileId& fileIDData = mModel->components(i->imageindex()).fileid();
		StringRef resName(fileIDData.name());

		if( resName.EndWith(".ani"))
		{
			UpdateAnimationChildData(*i);
		}
		else
		{
			UpdateBlockChildData(*i);
		}
	}
}

void IAnimation::UpdateBlockChildData( const CoreProto::BlockModel& blockModel )
{
	AnimationBlock* block = NULL;
	uint blockID = blockModel.blockid();

	switch( blockModel.framevalue() )
	{
	case CoreProto::EmptyFrame:
		{
			block = FindBlockForChildren(blockID);
			if(block!=NULL)
			{
				RecycleBlock(block);
				break;
			}
		}
		break;
	case CoreProto::KeyFrame:
	case CoreProto::TweenFrame:
		{
			block = ReloadBlockDetection(blockModel);
			if(block!=NULL)
			{
				CoreProto::BlockInfo buffInfo;
				DifferenceProcessing( buffInfo,blockModel );
				block->update(buffInfo);
			}
		}
		break;
	}
}

void IAnimation::UpdateAnimationChildData( const CoreProto::BlockModel& blockModel )
{
	IAnimation* ani = NULL;
	switch( blockModel.framevalue() )
	{
	case CoreProto::KeyFrame:

		ani = ReloadAnimationDetection(blockModel);
		if(ani!= NULL)
		{
			ani->UpdateLocation(blockModel.info());
		}

		break;
	case CoreProto::TweenFrame:
		{
			ani = ReloadAnimationDetection(blockModel);
			if(ani!= NULL)
			{
				CoreProto::BlockInfo buffInfo;
				DifferenceProcessing( buffInfo,blockModel );
				ani->UpdateLocation(buffInfo);
			}
		}
		break;
	default:
		break;
	}
}

void IAnimation::setFlipX( bool isFlipX )
{
	if( m_bFlipX != isFlipX )
	{
		m_bFlipX = isFlipX;
		
		FOR_EACH_COLLECTION(i,mBlockDict)
		{
			AnimationBlock* pBlock = (*i).Value;
			pBlock->setFlipX(m_bFlipX);
		}

		FOR_EACH_COLLECTION(i,mAnimationDict)
		{
			IAnimation* pAnimation = (*i).Value;
			pAnimation->setFlipY(m_bFlipX);
		}

		Update(0);

	}
}

void IAnimation::setFlipY( bool isFlipY )
{
	if( m_bFlipY != isFlipY )
	{
 		m_bFlipY = isFlipY;

		FOR_EACH_COLLECTION(i,mBlockDict)
		{
			AnimationBlock* pBlock = (*i).Value;
			pBlock->setFlipX(m_bFlipY);
		}

		FOR_EACH_COLLECTION(i,mAnimationDict)
		{
			IAnimation* pAnimation = (*i).Value;
			pAnimation->setFlipY(m_bFlipY);
		}
		Update(0);
	}
}

void IAnimation::SetResourceMap( const Dictionary<HeapString, FileId>* res )
{
	RETURN_IF(mResDict==res);
	SAFE_DELETE(mResDict);
	if (res!=NULL)
	{
		mResDict = new Dictionary<HeapString, FileId>;
		FOR_EACH_COLLECTION(i,*res)
		{
			mResDict->Add((*i).Key,(*i).Value);
		}
	}
}

AnimationBlock* IAnimation::GetBlock( const HeapString& blockName )
{
	FileId* fileID = mResDict->TryGetValue(blockName);
	if(fileID!=NULL)
	{
		return FindBlockForChildren(*fileID);
	}
	return NULL;
}

void IAnimation::SetPlaybackTime( float time )
{
	mPlaySpeed = mModelDuration/time; 
}

void IAnimation::SetAnimationRunningState(AnimationRunningState val)
{
	mRunningState = val;
	mCurrentRunTime = mModelDuration-mCurrentRunTime;
	UpdateChildData();
}
