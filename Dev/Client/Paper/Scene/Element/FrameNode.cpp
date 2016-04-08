
#include "FrameNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



FrameNode::FrameNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


FrameNode::~FrameNode(void)
{
}

bool FrameNode::Initialize()
{
	return true;
}

void FrameNode::SetProtoData( const CoreProto::Editor::Frame& val )
{
	mProtoData = val;
	SetName(val.id());
	this->setContentSize(CCSize(val.size().width(),val.size().height()));
	Point2F newAnchorPoint=Point2F(val.anchor().x(),val.anchor().y());
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

	setZOrder(val.zorder());
	setRotation(val.rotation());

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

bool FrameNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}

const CoreProto::Editor::Frame& FrameNode::GetProtoData() const
{
	return mProtoData;
}

Rect2F FrameNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F FrameNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

FrameNode* FrameNode::Clone() const
{
	FrameNode* frame=new FrameNode();
	frame->autorelease();

	frame->SetProtoData(mProtoData);
	frame->Initialize();
	return frame;

}

Medusa::FileId FrameNode::GetDefaultClickEffect() const
{
	if (mProtoData.has_clickeffect())
	{
		return mProtoData.clickeffect().c_str();
	}
	return Medusa::FileId::Empty;
}


