#pragma once

#include "Scene/INode.h"

USING_MEDUSA;

class BMPLabelNode :public INode,public cocos2d::CCLabelBMFont
{
public:
	BMPLabelNode(StringRef name=StringRef::Empty);
	virtual ~BMPLabelNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual BMPLabelNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::BMPLabel;}
public:
	void SetProtoData(const CoreProto::Editor::Label& val);
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);

private:
	virtual CCTexture2D* OnCreateTexture(const std::string& textureName);

protected:
	CoreProto::Editor::Label mProtoData;
};


