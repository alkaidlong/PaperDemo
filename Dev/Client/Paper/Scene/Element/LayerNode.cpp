
#include "LayerNode.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



LayerNode::LayerNode():INode(StringRef::Empty)
{
}


LayerNode::~LayerNode(void)
{
}

bool LayerNode::Initialize()
{
	return true;
}


Rect2F LayerNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F LayerNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

void LayerNode::SetProtoData( const CoreProto::Editor::Layer& val )
{
	mProtoData = val;
	SetName(val.id());

	Size2F originalSize=Size2F(val.size().width(),val.size().height());
	setContentSize(CCSize(originalSize.Width,originalSize.Height));
	
	m_bIgnoreAnchorPointForPosition = false;

}

void LayerNode::SetProtoData( const CoreProto::Editor::LayerRef& val )
{
	SetName(val.id());

	Point2F newAnchorPoint=Point2F(val.anchor().x(),val.anchor().y());

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

bool LayerNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}




