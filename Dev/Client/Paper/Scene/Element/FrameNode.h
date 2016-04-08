#pragma once

#include "Scene/INode.h"

USING_MEDUSA;

class FrameNode :public INode,public CCNode
{
public:
	FrameNode(StringRef name=StringRef::Empty);
	virtual ~FrameNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual FrameNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::Frame;}
public:
	void SetProtoData(const CoreProto::Editor::Frame& val);
	const CoreProto::Editor::Frame& GetProtoData()const;
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);

	virtual Medusa::FileId GetDefaultClickEffect()const;

protected:
	CoreProto::Editor::Frame mProtoData;
};


