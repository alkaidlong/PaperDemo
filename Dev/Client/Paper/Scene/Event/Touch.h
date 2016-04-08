#pragma once
#include "Core/Geometry/Point2.h"
USING_MEDUSA;


enum class TouchType
{
	TouchBegan,
	TouchMoved,
	TouchEnd,
	TouchCancelled,
};


class Touch
{
public:
	Touch(int id=0,const Point2F& pos=Point2F::Zero):Id(id),Pos(pos){}
	~Touch(void){}

	bool operator<(const Touch& touch)const{return Id<touch.Id;}
public:
	int Id;
	Point2F Pos;

	const static Touch Zero;
};


