
#include "EditBoxNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"



EditBoxNode::EditBoxNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


EditBoxNode::~EditBoxNode(void)
{
}

bool EditBoxNode::Initialize()
{
	return true;
}

void EditBoxNode::SetProtoData( const CoreProto::Editor::EditBox& val )
{
	mProtoData = val;
	const CoreProto::FileId& fileId=val.fontname();
	HeapString fontRealPath=FileSystem::Instance().GetReadFilePath(fileId);


	SetName(val.id());
	CCScale9Sprite* sprite=new CCScale9Sprite();
	sprite->autorelease();
	FileSystemOrderItem* orderItem=ResourceManager::Instance().InitScaleNineSprite(sprite,val.backgroundimage());
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("EditBoxNode:Cannot find image:%s",val.backgroundimage().file().name().c_str());
		return;
	}

	CCSize size=CCSize(val.size().width(),val.size().height());

	if (!initWithSizeAndBackgroundSprite(size,sprite))
	{
		Log::LogErrorFormat("EditBoxNode:Cannot find image:%s",val.id().c_str());
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

	this->setText(val.text().c_str());
	this->setFont(fontRealPath.c_str(),val.fontsize());
	if (val.has_color())
	{
		this->setFontColor(ccc3(val.color().r(),val.color().g(),val.color().b()));
	}
	this->setInputMode((EditBoxInputMode)val.inputmode());
	this->setInputFlag((EditBoxInputFlag)val.inputflag());
	this->setMaxLength(val.characternum());
	this->setReturnType((KeyboardReturnType)val.keyboardreturntype());
	setTag(val.tag());
}

bool EditBoxNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}


Rect2F EditBoxNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F EditBoxNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

EditBoxNode* EditBoxNode::Clone() const
{
	EditBoxNode* editBoxNode=new EditBoxNode();
	editBoxNode->autorelease();

	editBoxNode->SetProtoData(mProtoData);
	editBoxNode->Initialize();
	return editBoxNode;
}



