
#include "ButtonNode.h"
#include "Scene/Event/InputManager.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Scene/Event/InputDispatcher.h"



ButtonNode::ButtonNode(StringRef name/*=StringRef::Empty*/):INode(name)
{
	mState=ButtonState::Normal;
	mInputEnabled=true;
}


ButtonNode::~ButtonNode(void)
{
}

bool ButtonNode::Initialize()
{
	mInputDispatcher=InputManager::Instance().Register(this);
	TapGestureRecognizer* recognizer;
	if (mProtoData.has_clickeffect())
	{
		recognizer= mInputDispatcher->AddTapGestureRecognizer(mProtoData.clickeffect().c_str());
	}
	else
	{
		recognizer= mInputDispatcher->AddTapGestureRecognizer();
	}
	if (recognizer!=NULL)
	{
		GestureStateChangedHandler handler(this,&ButtonNode::OnTapStateChanged);
		recognizer->StateChangedEvent.Add(handler);
	}
	return true;
}

void ButtonNode::SetProtoData( const CoreProto::Editor::Button& val )
{
	mProtoData = val;

	SetName(val.id());

	FileSystemOrderItem* orderItem=ResourceManager::Instance().InitSprite(this,val.normalimage(),val.size());
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("Cannot find image:%s",val.normalimage().file().name().c_str());
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
	setZOrder(val.zorder());
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

bool ButtonNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}

void ButtonNode::ReloadContent()
{
	switch (mState)
	{
	case ButtonState::Normal:
		if (mProtoData.has_normalimage())
		{
			SetImage(mProtoData.normalimage());
		}
		break;
	case ButtonState::Selected:
		if (mProtoData.has_selectedimage())
		{
			SetImage(mProtoData.selectedimage());
		}
		break;
	case ButtonState::Disabled:
		if (mProtoData.has_disabledimage())
		{
			SetImage(mProtoData.disabledimage());
		}
		break;

	case ButtonState::DisabledSelected:
		if (mProtoData.has_disabledselectedimage())
		{
			SetImage(mProtoData.disabledselectedimage());
		}
		break;
	}
	
}


void ButtonNode::SetIsSelected(bool selected/* = true*/)
{
	if (selected)
	{
		RETURN_IF(IsSelected());
		SetState(mState==ButtonState::Normal?ButtonState::Selected:ButtonState::DisabledSelected);
	}
	else
	{
		RETURN_IF(!IsSelected());
		SetState(mState==ButtonState::Selected?ButtonState::Normal:ButtonState::Disabled);
	}

}


void ButtonNode::SetIsDisabled(bool disable/* = true*/)
{
	if (disable)
	{
		RETURN_IF(IsDisabled());
		SetState(mState==ButtonState::Normal?ButtonState::Disabled:ButtonState::DisabledSelected);
	}
	else
	{
		RETURN_IF(!IsDisabled());
		SetState(mState==ButtonState::Disabled?ButtonState::Normal:ButtonState::Selected);
	}

}


void ButtonNode::SetState(ButtonState val)
{
	RETURN_IF(mState == val);

	mState = val;
	ReloadContent();
}

void ButtonNode::SetImage( const CoreProto::Editor::ImageFile& image )
{
	//null image is ok
	FileSystemOrderItem* orderItem=ResourceManager::Instance().ReloadSprite(this,image,mProtoData.size());
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("Cannot find image:%s",image.file().name().c_str());
		return;
	}


	Point2F offset=orderItem->GetOffsetOrZero();
	Size2F originalSize=orderItem->GetOriginalSizeOrZero();
	Point2F newAnchorPoint=Point2F(mProtoData.anchor().x(),mProtoData.anchor().y());

	if (offset!=Point2F::Zero)
	{
		CCSize contentSize=getContentSize();
		newAnchorPoint= LayerEditor::CalculateAnchor(newAnchorPoint,offset,Size2F(contentSize.width,contentSize.height),Size2F(contentSize.width,contentSize.height));
	}

	setAnchorPoint(ccp(newAnchorPoint.X,newAnchorPoint.Y));
	
}

Rect2F ButtonNode::GetBoundingBox()
{
	return Rect2F(0.f,0.f,mProtoData.size().width(),mProtoData.size().height());
}

Point2F ButtonNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

void ButtonNode::OnTapStateChanged( GestureState oldState,GestureState newState )
{
	switch (newState)
	{
	case GestureState::Begin:
		SetState(IsDisabled()?ButtonState::DisabledSelected:ButtonState::Selected);
		break;
	case GestureState::End:
		SetState(IsDisabled()?ButtonState::Disabled:ButtonState::Normal);
		break;
	case GestureState::None:
		SetState(IsDisabled()?ButtonState::Disabled:ButtonState::Normal);
		break;
	default:
		break;
	}
}

ButtonNode* ButtonNode::Clone() const
{
	ButtonNode* sprite=new ButtonNode();
	sprite->autorelease();
	sprite->SetProtoData(mProtoData);
	sprite->Initialize();
	return sprite;
}

Medusa::FileId ButtonNode::GetDefaultClickEffect() const
{
	if (mProtoData.has_clickeffect())
	{
		return mProtoData.clickeffect().c_str();
	}
	return Medusa::FileId::Empty;
}



