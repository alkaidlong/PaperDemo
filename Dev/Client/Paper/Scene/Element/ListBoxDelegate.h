#pragma once

#include "Core/Proto/Client/LayerEditor.pb.h"
#include "Scene/INode.h"
#include "Engine/Extension/GUI/CCScrollView/CCScrollView.h"
#include "Engine/Extension/GUI/CCScrollView/CCTableView.h"
#include "Engine/Extension/GUI/CCScrollView/CCTableViewCell.h"
#include "Core/Pattern/Event.h"





typedef Pattern::Delegate<void (cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )> ListBoxTouchDelegateHandler;
typedef Pattern::Event<void (cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch )> ListBoxTouchEventHandler;

class ListBoxDelegate : public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
	ListBoxDelegate();
	virtual ~ListBoxDelegate(void);
	virtual bool Initialize();
public:

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch);

	virtual bool tableViewBeginTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch);
	virtual bool tableViewMovedTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch);
	virtual bool tableViewEndedTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch);
	virtual bool tableViewCancelledTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell,CCTouch *pTouch);

	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	void SetItemCount(unsigned int val){ mItemCount = val; };
	void SetItemSize(const CCSize& val){ mItemSize = val; };
	void SetItemFileID( const CoreProto::FileId& fileID );

	bool GetInputEnabled() const { return mInputEnabled; }
	void SetInputEnabled(bool val) { mInputEnabled = val; }

	void RegisterSelectItemEvent( Pattern::Delegate<void (CCLayer* layer,unsigned int index )> val ){ mSeleceItemEvent+=val; };
	void RegisterTouchItemEvent(ListBoxTouchDelegateHandler val){mTouchItemEvent+=val;};
	
	void RegisterTouchItemBeginEvent(ListBoxTouchDelegateHandler val){mTouchItemBeginEvent+=val;};
	void RegisterTouchItemMovedEvent(ListBoxTouchDelegateHandler val){mTouchItemMovedEvent+=val;};
	void RegisterTouchItemEndedEvent(ListBoxTouchDelegateHandler val){mTouchItemEndedEvent+=val;};
	void RegisterTouchItemCancelledEvent(ListBoxTouchDelegateHandler val){mTouchItemCancelledEvent+=val;};
	void SetCCTableViewCellDataDelegate(CCTableViewCellDataDelegate val) { mCCTableViewCellDataDelegate = val; }

protected:
	CoreProto::FileId mItemFileID;
	unsigned int mItemCount;
	CCSize mItemSize;
	Pattern::Event<void (CCLayer* layer,unsigned int index )> mSeleceItemEvent;
	ListBoxTouchEventHandler mTouchItemEvent;

	ListBoxTouchEventHandler mTouchItemBeginEvent;
	ListBoxTouchEventHandler mTouchItemMovedEvent;
	ListBoxTouchEventHandler mTouchItemEndedEvent;
	ListBoxTouchEventHandler mTouchItemCancelledEvent;
	CCTableViewCellDataDelegate mCCTableViewCellDataDelegate;;
	bool mInputEnabled;
};


