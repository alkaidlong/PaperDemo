
#include "SpriteNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



SpriteNode::SpriteNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


SpriteNode::~SpriteNode(void)
{
}

bool SpriteNode::Initialize()
{
	return true;
}

void SpriteNode::SetProtoData( const CoreProto::Editor::Image& val )
{
	mProtoData = val;
	SetName(val.id());
	
	FileSystemOrderItem* orderItem=ResourceManager::Instance().InitSprite(this,val.file(),val.size());
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("SpriteNode:Cannot find image:%s",val.file().file().name().c_str());
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
	setZOrder(val.zorder());
	setFlipX(val.isfilpx());
	setFlipY(val.isfilpy());
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
	setTag(val.tag());
}

bool SpriteNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}

Rect2F SpriteNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F SpriteNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

SpriteNode* SpriteNode::Clone() const
{
	SpriteNode* sprite=new SpriteNode();
	sprite->autorelease();

	sprite->SetProtoData(mProtoData);
	sprite->Initialize();
	return sprite;
}

void SpriteNode::ReloadSprite( const FileId& fileID )
{
	ResourceManager::Instance().ReloadSprite(this,fileID);
}

Medusa::FileId SpriteNode::GetDefaultClickEffect() const
{
	if (mProtoData.has_clickeffect())
	{
		return mProtoData.clickeffect().c_str();
	}
	return Medusa::FileId::Empty;
}



