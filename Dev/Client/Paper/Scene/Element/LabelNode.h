#pragma once

#include "Scene/INode.h"


USING_MEDUSA;
class LabelNode :public INode,public cocos2d::CCLabelTTF
{
public:
	LabelNode(StringRef name=StringRef::Empty);
	virtual ~LabelNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual LabelNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::Label;}
public:
	void SetProtoData(const CoreProto::Editor::Label& val);
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);
protected:
	CoreProto::Editor::Label mProtoData;
};


