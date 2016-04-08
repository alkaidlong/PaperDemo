
#include "BMPLabelNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



BMPLabelNode::BMPLabelNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


BMPLabelNode::~BMPLabelNode(void)
{
}

bool BMPLabelNode::Initialize()
{
	return true;
}

void BMPLabelNode::SetProtoData( const CoreProto::Editor::Label& val )
{
	mProtoData = val;

	SetName(val.id());
	const CoreProto::FileId& fileId=val.fontname();
	HeapString fontRealPath=FileSystem::Instance().GetReadFilePath(fileId);

	CCSize size=CCSize(val.size().width(),val.size().height());

	CCTextAlignment alignmentHorizontal=kCCTextAlignmentCenter;
	CCVerticalTextAlignment alignmentVertical = kCCVerticalTextAlignmentCenter;
	switch (val.alignmenttype())
	{
	case CoreProto::Editor::TextAlignmentType::LeftTop:
		alignmentHorizontal = kCCTextAlignmentLeft;
		alignmentVertical = kCCVerticalTextAlignmentTop;
		break;
	case CoreProto::Editor::TextAlignmentType::MiddleTop:
		alignmentHorizontal = kCCTextAlignmentCenter;
		alignmentVertical = kCCVerticalTextAlignmentTop;
		break;
	case CoreProto::Editor::TextAlignmentType::RightTop:
		alignmentHorizontal = kCCTextAlignmentRight;
		alignmentVertical = kCCVerticalTextAlignmentTop;
		break;
	case CoreProto::Editor::TextAlignmentType::LeftCenter:
		alignmentHorizontal = kCCTextAlignmentLeft;
		alignmentVertical = kCCVerticalTextAlignmentCenter;
		break;
	case CoreProto::Editor::TextAlignmentType::MiddleCenter:
		alignmentHorizontal = kCCTextAlignmentCenter;
		alignmentVertical = kCCVerticalTextAlignmentCenter;
		break;
	case CoreProto::Editor::TextAlignmentType::RightCenter:
		alignmentHorizontal = kCCTextAlignmentRight;
		alignmentVertical = kCCVerticalTextAlignmentCenter;
		break;
	case CoreProto::Editor::TextAlignmentType::LeftBottom:
		alignmentHorizontal = kCCTextAlignmentLeft;
		alignmentVertical = kCCVerticalTextAlignmentBottom;
		break;
	case CoreProto::Editor::TextAlignmentType::MiddleBottom:
		alignmentHorizontal = kCCTextAlignmentCenter;
		alignmentVertical = kCCVerticalTextAlignmentBottom;
		break;
	case CoreProto::Editor::TextAlignmentType::RightBottom:
		alignmentHorizontal = kCCTextAlignmentRight;
		alignmentVertical = kCCVerticalTextAlignmentBottom;
		break;
	default:
		break;	
	};

	

	if (!initWithString(val.text().c_str(),fontRealPath.c_str(),kCCLabelAutomaticWidth,alignmentHorizontal))
	{
		Log::LogErrorFormat("Cannot init BMP label:%s",fileId.name().c_str());
	}

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

	if (val.has_color()==false)
	{
		setColor(ccc3(255,255,255));
		setOpacity(255);
	}
	else
	{
		setColor(ccc3(val.color().r(),val.color().g(),val.color().b()));
		setOpacity(val.color().a());
	}
	setTag(val.tag());
	
}

bool BMPLabelNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}

Rect2F BMPLabelNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F BMPLabelNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

BMPLabelNode* BMPLabelNode::Clone() const
{
	BMPLabelNode* label=new BMPLabelNode();
	label->autorelease();

	label->SetProtoData(mProtoData);
	label->Initialize();
	return label;
}

CCTexture2D* BMPLabelNode::OnCreateTexture( const std::string& textureName )
{
	return ResourceManager::Instance().LoadTexture(textureName.c_str());
}




