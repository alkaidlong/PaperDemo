
#include "ListBoxDelegate.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Engine/Resource/ResourceManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Scene/Element/LayerNode.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/Event/InputManager.h"


ListBoxDelegate::ListBoxDelegate( )
{
	mItemCount = 0;
	mInputEnabled = true;
}

ListBoxDelegate::~ListBoxDelegate( void )
{

}

bool ListBoxDelegate::Initialize()
{
	return true;
}

void ListBoxDelegate::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )
{
	if (mInputEnabled)
	{
		mTouchItemEvent.Invoke(table,cell,pTouch);
	}
}


bool ListBoxDelegate::tableViewBeginTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )
{
	if (mInputEnabled)
	{
		mTouchItemBeginEvent.Invoke(table,cell,pTouch);

		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		TouchEventArg touchEventArg;
		CCPoint point=pTouch->getLocation();
		touchEventArg.AddTouch(Touch(pTouch->getID(),Point2F(point.x,point.y)));
		InputManager::Instance().TouchesBeganHelper(layer,touchEventArg);
		return touchEventArg.Handled;
	}
	else
	{
		return false;
	}
}

bool ListBoxDelegate::tableViewMovedTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )
{
	if (mInputEnabled)
	{
		mTouchItemMovedEvent.Invoke(table,cell,pTouch);

		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		TouchEventArg touchEventArg;
		CCPoint point=pTouch->getLocation();
		touchEventArg.AddTouch(Touch(pTouch->getID(),Point2F(point.x,point.y)));
		InputManager::Instance().TouchesMovedHelper(layer,touchEventArg);
		return touchEventArg.Handled;
	}
	else
	{
		return false;
	}
}


bool ListBoxDelegate::tableViewEndedTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )
{
	if (mInputEnabled)
	{
		mTouchItemEndedEvent.Invoke(table,cell,pTouch);

		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		TouchEventArg touchEventArg;
		CCPoint point=pTouch->getLocation();
		touchEventArg.AddTouch(Touch(pTouch->getID(),Point2F(point.x,point.y)));
		InputManager::Instance().TouchesEndedHelper(layer,touchEventArg);
		return touchEventArg.Handled;
	}
	else
	{
		return false;
	}

}


bool ListBoxDelegate::tableViewCancelledTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )
{
	if (mInputEnabled)
	{
		mTouchItemCancelledEvent.Invoke(table,cell,pTouch);

		LayerNode* layer =(LayerNode*)cell->getChildren()->objectAtIndex(0);
		TouchEventArg touchEventArg;
		CCPoint point=pTouch->getLocation();
		touchEventArg.AddTouch(Touch(pTouch->getID(),Point2F(point.x,point.y)));
		InputManager::Instance().TouchesCancelledHelper(layer,touchEventArg);
		return touchEventArg.Handled;
	}
	else
	{
		return false;
	}

}


cocos2d::CCSize ListBoxDelegate::tableCellSizeForIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = table->cellAtIndex(idx);
	if (cell==NULL)
	{
		return mItemSize;
	}
	LayerNode* layer= (LayerNode*)cell->getChildByTag(idx);
	return layer->getContentSize();
}

cocos2d::extension::CCTableViewCell* ListBoxDelegate::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = table->cellAtIndex(idx);
	LayerNode* layer ;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		cell->setIdx(idx);
		cell->SetDataDelegate(mCCTableViewCellDataDelegate);

		layer = LayerEditor::Instance().CreateLayer(mItemFileID);
		layer->SetName(StringParser::ToString(idx));
		layer->setTag(idx);
		layer->autorelease();
		layer->retain();
		cell->addChild(layer,0);
		layer->OnCreated();
		layer->Initialize();
		layer->UpdateLogic();
	}
 	else
 	{
 		layer = (LayerNode*)cell->getChildByTag(idx);
		layer->UpdateLogicRecursively();
 	}
	mSeleceItemEvent.Invoke(layer,idx);
	return cell;
}

unsigned int ListBoxDelegate::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return mItemCount;
}

void ListBoxDelegate::SetItemFileID( const CoreProto::FileId& fileID )
{
	mItemFileID.set_name(fileID.name()); 
	mItemFileID.set_order(fileID.order());
	mItemFileID.set_tag(fileID.tag());

	const CoreProto::Editor::Layer* layer = LayerEditor::Instance().GetProtoData(fileID);
	SetItemSize(CCSizeMake(layer->size().width(),layer->size().height()));

}
