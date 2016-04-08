#pragma once

#include "Scene/INode.h"
#include "Scene/Gesture/IGestureRecognizer.h"
USING_MEDUSA;


enum class ButtonState
{
	Normal = 0,
	Selected = 1,
	Disabled = 2,
	DisabledSelected=3
};


class ButtonNode :public INode,public CCSprite
{
public:
	ButtonNode(StringRef name=StringRef::Empty);
	virtual ~ButtonNode(void);

	virtual ButtonNode* Clone() const;
	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}


	virtual bool Initialize();
	virtual bool OnCreated();

	void SetProtoData(const CoreProto::Editor::Button& val);

	void ReloadContent();

	bool IsDisabled() const { return mState == ButtonState::Disabled||mState==ButtonState::DisabledSelected; }
	void SetIsDisabled(bool disable = true);

	bool IsSelected() const { return mState == ButtonState::Selected||mState==ButtonState::DisabledSelected; }
	void SetIsSelected(bool selected = true);

	ButtonState GetState() const { return mState; }
	void SetState(ButtonState val);

	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);

	CoreProto::Editor::Button& GetProtoData() { return mProtoData; }

	virtual  ElementType GetElementType()const{return ElementType::Button;}

	virtual Medusa::FileId GetDefaultClickEffect()const;

protected:
	void SetImage(const CoreProto::Editor::ImageFile& image);
	void OnTapStateChanged(GestureState oldState,GestureState newState);
protected:
	CoreProto::Editor::Button mProtoData;
	
	bool mIsTouchBegin;
	ButtonState mState;


};


