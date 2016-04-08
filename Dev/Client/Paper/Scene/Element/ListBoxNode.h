#pragma once

#include "Scene/INode.h"
#include "Scene/Element/ListBoxDelegate.h"
#include "Scene/Element/LayerNode.h"


USING_MEDUSA;

class ListBoxNode : public INode , public cocos2d::extension::CCTableView
{
public:
	ListBoxNode(StringRef name=StringRef::Empty);
	virtual ~ListBoxNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();
	ListBoxDelegate* GetListBoxDelegate()const{return mListBoxDelegate;}
	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual ListBoxNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::List;}
public:
	void SetProtoData(const CoreProto::Editor::ListBox& val);
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);
	virtual bool EnableInput(bool val);
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
public:
	virtual bool EnterRecursively();
	virtual bool ExitRecursively();
	virtual bool UpdateLogicRecursively();
	virtual bool ResetLogicRecursively();
 public:
	void SetItemCount(unsigned int val){mListBoxDelegate->SetItemCount(val);}
 	void SetDelegate( ListBoxDelegate* del ){ mListBoxDelegate = del; setDelegate(mListBoxDelegate);setDataSource(mListBoxDelegate); }
	void RegisterSelectItemEvent( Pattern::Delegate<void (CCLayer* layer,unsigned int index )> val ){ mListBoxDelegate->RegisterSelectItemEvent(val); }
	void RegisterTouchItemEvent(ListBoxTouchDelegateHandler val){mListBoxDelegate->RegisterTouchItemEvent(val);}

	void RegisterTouchItemBeginEvent(ListBoxTouchDelegateHandler val){mListBoxDelegate->RegisterTouchItemBeginEvent(val);}
	void RegisterTouchItemMovedEvent(ListBoxTouchDelegateHandler val){mListBoxDelegate->RegisterTouchItemMovedEvent(val);}
	void RegisterTouchItemEndedEvent(ListBoxTouchDelegateHandler val){mListBoxDelegate->RegisterTouchItemEndedEvent(val);}
	void RegisterTouchItemCancelledEvent(ListBoxTouchDelegateHandler val){mListBoxDelegate->RegisterTouchItemCancelledEvent(val);}
	void SetCCTableViewCellDataDelegate(CCTableViewCellDataDelegate val) { mListBoxDelegate->SetCCTableViewCellDataDelegate(val); }

	
	void UpdateCell();
	void UpdateCellAtIndex(uint idx);

	LayerNode* GetElement(uint idx);

	void ScrollView(int count = 1);
	uint GetViewCellCount();
protected:
	CoreProto::Editor::ListBox mProtoData;
	ListBoxDelegate* mListBoxDelegate;

};



