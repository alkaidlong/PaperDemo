#pragma once

#include "Core/Collection/List.h"
#include "Core/Geometry/Point2.h"
#include "Scene/Event/Touch.h"
#include "Core/Event/EventArg/IEventArg.h"
USING_MEDUSA;
class INode;

class TouchEventArg:public IEventArg
{
public:
	TouchEventArg(const List<Touch>& touches)
		:mWorldTouches(touches)
	{
	}

	TouchEventArg(const Touch& touch)
	{
		mWorldTouches.Add(touch);
	}
	TouchEventArg()
	{
	}
	
	virtual ~TouchEventArg(void);

	void AddTouch(const Touch& touch){mWorldTouches.Add(touch);}

	void UpdateValidTouches(INode* node);

	const List<Touch>& GetWorldTouches()const  { return mWorldTouches; }
	bool IsOneFinger()const{return mWorldTouches.GetCount()==1;}
	bool IsTwoFinger()const{return mWorldTouches.GetCount()==2;}
	bool IsMultipleTouching()const{return mWorldTouches.GetCount()>=2;}
	const Touch& GetFirstWorldTouch()const{return mWorldTouches.First();}
	uint GetWorldTouchCount()const{return mWorldTouches.GetCount();}


	const List<Touch>& GetLocalTouches()const{ return mLocalTouches; }
	const Touch& GetFirstLocalTouch()const{return mLocalTouches.First();}
	uint GetLocalTouchCount()const{return mLocalTouches.GetCount();}

	void AddValidTouch(const Touch& touch){mValidTouches.Add(touch);}

	void MergeValidTouches(const TouchEventArg& e);
	void MoveValidTouches(const TouchEventArg& e);
	void RemoveValidTouches(const TouchEventArg& e);

	const List<Touch>& GetValidTouches()const  { return mValidTouches; }
	bool IsValid()const{return !mValidTouches.IsEmpty();}
	bool IsOneFingerValid()const{return mValidTouches.GetCount()==1;}
	bool IsTwoFingerValid()const{return mValidTouches.GetCount()==2;}
	const Touch& GetFirstValidTouch()const{return mValidTouches.First();}
	uint GetValidTouchCount()const{return mValidTouches.GetCount();}

	Point2F GetValidMiddlePoint()const;
	Point2F GetMiddlePoint()const;

	// To Confirm the IGestureRecognizer which will handle the TOUCH event

	const Touch* FindWorldTouchById(int id)const;
	const Touch* FindLocalTouchById(int id)const;
	const Touch* FindValidTouchById(int id)const;
	Touch* FindValidTouchById(int id);

	void PrintDebugString();

	void Clear();
protected:

protected:
	List<Touch> mWorldTouches;
	List<Touch> mLocalTouches;
	List<Touch> mValidTouches;


};



