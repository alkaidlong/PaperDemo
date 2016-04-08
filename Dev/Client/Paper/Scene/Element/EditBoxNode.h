#pragma once

#include "Scene/INode.h"
#include "Engine/Extension/cocos-ext.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Delegate.h"

USING_MEDUSA;

class EditBoxNode :public INode,public CCEditBox
{
public:
	EditBoxNode(StringRef name=StringRef::Empty);
	virtual ~EditBoxNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}

	virtual EditBoxNode* Clone()const;
	virtual  ElementType GetElementType()const{return ElementType::EditBox;}
	virtual void OnTouchDown(){mTouchDownEvent.Invoke();}
	virtual void OnInputEnd(){mEndEvent.Invoke();}
public:
	void SetProtoData(const CoreProto::Editor::EditBox& val);
	void AddTouchEvent(Pattern::Delegate<void ()> touchEvent){ mTouchDownEvent+=touchEvent; }
	void AddEndEvent(Pattern::Delegate<void ()> endEvent){ mEndEvent+=endEvent; }
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);
protected:
	CoreProto::Editor::EditBox mProtoData;
	Pattern::Event<void ()> mTouchDownEvent;
	Pattern::Event<void ()> mEndEvent;
};


