
#include "ListBoxNode.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/ListBoxDelegate.h"


ListBoxNode::ListBoxNode( StringRef name ):INode(name)
{
	
}

ListBoxNode::~ListBoxNode( void )
{
	SAFE_DELETE(mListBoxDelegate);
}

bool ListBoxNode::Initialize()
{
	const CoreProto::SizeU& size = mProtoData.size();
	const CoreProto::PointF point = mProtoData.position();
	initWithViewSize(CCSizeMake(size.width(), size.height()), NULL);
	setDirection((CCScrollViewDirection)mProtoData.direction());
	setPosition(ccp(point.x(),point.y()));
	setZOrder(mProtoData.zorder());
	setVerticalFillOrder((CCTableViewVerticalFillOrder)mProtoData.ordertype());
	SetDelegate(new ListBoxDelegate());
	mListBoxDelegate->SetItemFileID(mProtoData.itemfileid());
	_updateCellPositions();
	_updateContentSize();
	return true;
}

void ListBoxNode::SetProtoData( const CoreProto::Editor::ListBox& val )
{
	mProtoData = val;
	SetName(val.id());
	setTag(val.tag());
}

bool ListBoxNode::OnCreated()
{
	if (mProtoData.has_scissorbox())
	{
		const CoreProto::RectF& rect= mProtoData.scissorbox();
		SetScissorBox(CCRectMake(rect.origin().x(),rect.origin().y(),rect.size().width(),rect.size().height()));
	}
	return true;
}


Rect2F ListBoxNode::GetBoundingBox()
{
	CCSize size= this->getContentSize();
	return Rect2F(0.f,0.f,size.width,size.height);
}

Point2F ListBoxNode::TransformPoint( Point2F pos )
{
	CCPoint result= this->convertToNodeSpace(ccp(pos.X,pos.Y));
	return Point2F(result.x,result.y);
}

ListBoxNode* ListBoxNode::Clone() const
{
	ListBoxNode* listBox=new ListBoxNode();
	listBox->autorelease();

	listBox->SetProtoData(mProtoData);
	listBox->Initialize();
	return listBox;
}

void ListBoxNode::UpdateCell()
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* cell = (CCTableViewCell*)pObj;
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->UpdateLogicRecursively();
	}
}

void ListBoxNode::UpdateCellAtIndex( uint idx )
{
	if (m_pIndices->find(idx) != m_pIndices->end())
	{
		CCTableViewCell* cell = (CCTableViewCell *)m_pCellsUsed->objectWithObjectID(idx);
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->UpdateLogicRecursively();
	}
}

bool ListBoxNode::UpdateLogicRecursively()
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* cell = (CCTableViewCell*)pObj;
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->UpdateLogicRecursively();
	}

	RETURN_FALSE_IF_FALSE(UpdateLogic());

	return true;
}

bool ListBoxNode::EnterRecursively()
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* cell = (CCTableViewCell*)pObj;
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->EnterRecursively();
	}
	return true;
}

bool ListBoxNode::ExitRecursively()
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* cell = (CCTableViewCell*)pObj;
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->ExitRecursively();
	}
	return true;
}

bool ListBoxNode::ResetLogicRecursively()
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(m_pCellsUsed, pObj)
	{
		CCTableViewCell* cell = (CCTableViewCell*)pObj;
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		layer->ResetLogicRecursively();
	}
	return true;
}

bool ListBoxNode::EnableInput( bool val )
{
	mListBoxDelegate->SetInputEnabled(val);
	setTouchEnabled(val);
	return true;
}

LayerNode* ListBoxNode::GetElement( uint idx )
{
	if (m_pIndices->find(idx) != m_pIndices->end())
	{
		CCTableViewCell* cell = (CCTableViewCell *)m_pCellsUsed->objectWithObjectID(idx);
		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		return layer;
	}
	return NULL;
}

void ListBoxNode::ScrollView( int count /*= 1*/ )
{
	int cellsCount = m_pDataSource->numberOfCellsInTableView(this);
	m_vCellsPositions.resize(cellsCount + 1, 0.0);
	if (cellsCount > 0)
	{
		const CCSize cellSizeCell = m_pDataSource->tableCellSizeForIndex(this, 0);
		float currentPos = 0;
		switch (this->getDirection())
		{
		case kCCScrollViewDirectionHorizontal:
			{
				currentPos += cellSizeCell.width*count;
				setContentOffset(ccp(-currentPos,0));
			}
			break;
		default:
			{
				currentPos += cellSizeCell.height*count;
				setContentOffset(ccp(0,this->minContainerOffset().y+currentPos));
			}
			break;
		}
	}
}

uint ListBoxNode::GetViewCellCount()
{
	const CoreProto::SizeU& size = mProtoData.size();
	CCSize viewSize = CCSizeMake(size.width(),size.height());

	const CCSize cellSizeCell = m_pDataSource->tableCellSizeForIndex(this, 0);
	switch (this->getDirection())
	{
	case kCCScrollViewDirectionHorizontal://ºáµÄ
		{
			return (uint)(viewSize.width/cellSizeCell.width);
		}
		break;
	default://ÊúµÄ
		{
			return (uint)(viewSize.height/cellSizeCell.height);
		}
		break;
	}
}
