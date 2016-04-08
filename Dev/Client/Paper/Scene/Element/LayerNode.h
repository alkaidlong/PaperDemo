#pragma once
#include "Scene/INode.h"
#include "Core/Pattern/StaticConstructor.h"


USING_MEDUSA;

class LayerNode :public INode,public CCLayer
{
public:
	LayerNode();
	virtual ~LayerNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}

	virtual StringRef GetProtoName()const=0;
	void SetProtoData(const CoreProto::Editor::LayerRef& val);
	void SetProtoData(const CoreProto::Editor::Layer& val);
	const CoreProto::Editor::Layer& GetProtoData() const { return mProtoData; }

	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);
	virtual bool IsCreateElement(StringRef id)const{return true;}
	virtual  ElementType GetElementType()const{return ElementType::Layer;}
protected:
	CoreProto::Editor::Layer mProtoData;
};

#define DECLARE_REGISTER_LAYER() 													\
public:																				\
	virtual StringRef GetProtoName()const{return mStaticLayerProtoName;}									\
	static const StringRef& ClassGetProtoName(){return mStaticLayerProtoName;}									\
private:																				\
	const static StringRef mStaticLayerProtoName;							\
	const static Pattern::StaticConstructor mStaticConstructor;							\
	static void SelfRegisterStaticCallback();

#define IMPLEMENT_REGISTER_LAYER(className,layout) 																					 \
	const StringRef className::mStaticLayerProtoName=layout;					 \
	const Pattern::StaticConstructor className::mStaticConstructor=Pattern::StaticConstructor(SelfRegisterStaticCallback);					 \
	void className::SelfRegisterStaticCallback(){LayerFactory::Instance().Register<className>(layout);}





