#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Geometry/GeometryDefines.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Range.h"
#include "Core/Pattern/IUpdatable.h"

MEDUSA_BEGIN;

class IScrollMathModel:public Pattern::IUpdatable
{
public:
	enum class ScrollState
	{
		None,
		Begin,
		StaticMove,
		Scrolling,
		Spring,
		End
	};
public:
	IScrollMathModel(DirectionMask direction=DirectionMask::All);
	virtual ~IScrollMathModel(void);
public:
	DirectionMask GetDirection() const { return mDirection; }
	virtual void SetDirection(DirectionMask val) { mDirection = val; }
	bool IsVertical()const;
	bool IsHorizontal()const;

	ScrollState GetState() const { return mState; }

	const Size2F& GetSize() const { return mSize; }
	const Rect2F& GetTargetBoundingBox() const { return mTargetBoundingBox; }

	float GetHorizontalScrollBarOffset()const;
	float GetVerticalScrollBarOffset()const;
	Point2F GetScrollBarOffset()const;
	const Point2F& GetOffset()const{return mTargetBoundingBox.Origin;}

	Point2F GetMovement()const{return mTargetBoundingBox.Origin-mPrevTargetBoundingBox.Origin;}
	void ApplyMovement(){mPrevTargetBoundingBox=mTargetBoundingBox;}
	Point2F GetTotalMovment()const;
	bool IsRectVisible(const Rect2F& rect)const;

	float GetHorizontalScrollBarWidth()const;
	float GetVerticalScrollBarHeight()const;

	bool NeedHorizontalScrollBar()const;
	bool NeedVerticalScrollBar()const;

	void InitializeBoundingBox(const Size2F& selfSize,const Rect2F& targetBoundingBox);
	float ExpandBoundingBox(const Size2F& sizeAdded);
	float CollapseBoundingBox(const Size2F& sizeRemoved);
	float UpdateBoundingBox(const Size2F& originalSize,const Size2F& newSize);


	virtual void Focus();
	virtual void Move(Point2F movement);
	virtual void Release();
	virtual void Scroll(Point2F initialVelocity);

	virtual void ScrollTo(Point2F offset);
	virtual void ScrollBy(Point2F movement);
	virtual void ScrollToStart();
	virtual void ScrollToEnd();
protected:
	virtual bool NeedSpring()const;
	virtual void OnUpdateSpringLimit();
	virtual void OnUpdate();
	virtual void OnScrollingEnd();

protected:
	DirectionMask mDirection;
	ScrollState mState;
	
	Size2F mSize;
	Rect2F mTargetBoundingBox;
	Rect2F mPrevTargetBoundingBox;


	//limit bound
	RangeF mStaticLimitX;	//cache
	RangeF mStaticLimitY;	//cache

	RangeF mSpringLimitX;	//cache
	RangeF mSpringLimitY;	//cache

	float mInitialVelocityFactor;
	Point2F mCurrentVelocity;	//cache
};

MEDUSA_END;
