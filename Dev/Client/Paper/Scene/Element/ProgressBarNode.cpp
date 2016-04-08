
#include "ProgressBarNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



ProgressBarNode::ProgressBarNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


ProgressBarNode::~ProgressBarNode(void)
{
}

bool ProgressBarNode::Initialize()
{
	return true;
}

void ProgressBarNode::SetProtoData( const CoreProto::Editor::ProgressBar& val )
{
	mProtoData = val;
	SetName(val.id());

	CCSprite* sprite=new CCSprite();
	sprite->autorelease();
	FileSystemOrderItem* orderItem=ResourceManager::Instance().InitSprite(sprite,val.image(),val.size());
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("ProgressBarNode:Cannot find image:%s",val.image().file().name().c_str());
		return;
	}

	if(!initWithSprite(sprite))
	{
		Log::LogErrorFormat("Cannot init progress bar:%s",val.id().c_str());
		return;
	}


	Point2F offset=orderItem->GetOffsetOrZero();
	Size2F originalSize=orderItem->GetOriginalSizeOrZero();
	Point2F newAnchorPoint=Point2F(val.anchor().x(),val.anchor().y());

	if (offset!=Point2F::Zero)
	{
		CCSize contentSize=getContentSize();
		newAnchorPoint= LayerEditor::CalculateAnchor(newAnchorPoint,offset,Size2F(contentSize.width,contentSize.height),Size2F(contentSize.width,contentSize.height));
	}

	//setFlipX(val.isfilpx());
	//setFlipY(val.isfilpy());
	setZOrder(val.zorder());
	setVisible(val.isvisible());
	setAnchorPoint(ccp(newAnchorPoint.X,newAnchorPoint.Y));
	if (val.has_scale())
	{
		setScaleX(val.scale().x());
		setScaleY(val.scale().y());
	}
	else
	{
		setScale(1.f);
	}

	setRotation(val.rotation());
	SetRenderFlag((RenderFlag)val.renderflag());

	if (val.isproportionpoint())
	{
		CCSize winSize= CCDirector::sharedDirector()->getWinSizeInPixels();

		setPosition(ccp(val.position().x()*winSize.width,val.position().y()*winSize.height));
	}
	else
	{
		setPosition(ccp(val.position().x(),val.position().y()));
	}
	
	setPercentage(100.f);

	
	setType((CCProgressTimerType)val.type());

	CCPoint midPos = ccp(val.midpoint().x(),val.midpoint().y());
	if (getType() == kCCProgressTimerTypeRadial)
	{
		midPos.x = Math::Clamp(midPos.x,0.001f,0.9999f);
		midPos.y = Math::Clamp(midPos.y,0.001f,0.9999f);
	}
	setMidpoint(midPos);
	setBarChangeRate(ccp(val.changerate().x(),val.changerate().y()));
	setTag(val.tag());
}

bool ProgressBarNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}

Rect2F ProgressBarNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F ProgressBarNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

void ProgressBarNode::GoToPercentage( float val, float duration /*=0.f*/,ProgressChangedHandler* handler/*=NULL*/ )
{
	if (handler!=NULL)
	{
		mProgressChangedHandler=handler;
	}

	float progressDuration = Math::IsZero(duration) ? (val / 100.f * mProtoData.duration()) : duration;

	CCProgressFromTo* progressTo = CCProgressFromTo::create(progressDuration,getPercentage(),val);
	CC_NEW_CALLFUNC_MEMBER(callback, ProgressBarNode,float, this, OnAchievePercentageCallback,val);
	runAction(CCSequence::createWithTwoActions(progressTo, callback));
}

void ProgressBarNode::GoByPercentage( float val, float duration /*= 0.f*/,ProgressChangedHandler* handler/*=NULL*/ )
{
	if (handler!=NULL)
	{
		mProgressChangedHandler=handler;
	}

	float progressDuration = Math::IsZero(duration) ? (val / 100.f * mProtoData.duration()) : duration;

	CCProgressBy* progressTo = CCProgressBy::create(progressDuration, val);
	CC_NEW_CALLFUNC_MEMBER(callback, ProgressBarNode,float, this, OnAchievePercentageCallback,val);
	runAction(CCSequence::createWithTwoActions(progressTo, callback));
}

void ProgressBarNode::OnAchievePercentageCallback( float val)
{
	if (!mProgressChangedHandler.IsNull())
	{
		mProgressChangedHandler(val);
	}
}

ProgressBarNode* ProgressBarNode::Clone() const
{
	ProgressBarNode* progressBar=new ProgressBarNode();
	progressBar->autorelease();

	progressBar->SetProtoData(mProtoData);
	progressBar->Initialize();
	return progressBar;
}




