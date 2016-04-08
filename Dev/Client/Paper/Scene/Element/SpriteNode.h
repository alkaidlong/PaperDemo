#pragma once

#include "Scene/INode.h"

USING_MEDUSA;

class SpriteNode :public INode,public CCSprite
{
public:
	SpriteNode(StringRef name=StringRef::Empty);
	virtual ~SpriteNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual SpriteNode* Clone()const;
	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	const CoreProto::Editor::Image& GetProtoData()const{return mProtoData;}
	CoreProto::Editor::Image* GetProtoDataMutable(){return &mProtoData;}
	void ReloadSprite(const FileId& fileID);
	virtual  ElementType GetElementType()const{return ElementType::Sprite;}
public:
	void SetProtoData(const CoreProto::Editor::Image& val);
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);

	virtual Medusa::FileId GetDefaultClickEffect()const;

protected:
	CoreProto::Editor::Image mProtoData;

};


