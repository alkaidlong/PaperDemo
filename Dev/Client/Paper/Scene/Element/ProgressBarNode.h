#pragma once

#include "Scene/INode.h"
#include "Core/Math/MathHeader.h"
#include "Core/Pattern/Delegate.h"


USING_MEDUSA;

typedef Pattern::Delegate<void (float)>  ProgressChangedHandler;

class ProgressBarNode :public INode,public cocos2d::CCProgressTimer
{
public:
	ProgressBarNode(StringRef name=StringRef::Empty);
	virtual ~ProgressBarNode(void);
	virtual bool Initialize();
	virtual bool OnCreated();

	virtual const CCNode* GetDrawCCNode()const{return this;}
	virtual CCNode* GetDrawCCNode(){return this;}
	virtual ProgressBarNode* Clone() const;
	virtual  ElementType GetElementType()const{return ElementType::ProgressBar;}
public:
	void SetProtoData(const CoreProto::Editor::ProgressBar& val);
	virtual Rect2F GetBoundingBox();
	virtual Point2F TransformPoint(Point2F pos);

	const CoreProto::Editor::ProgressBar& GetProtoData(){return mProtoData;} 
	void GoToPercentage(float val, float duration =0.f,ProgressChangedHandler* handler=NULL);
	void GoByPercentage(float val, float duration = 0.f,ProgressChangedHandler* handler=NULL);
protected:
	void OnAchievePercentageCallback(float val);
protected:
	CoreProto::Editor::ProgressBar mProtoData;
	ProgressChangedHandler mProgressChangedHandler;
};


