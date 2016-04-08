#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point3.h"

MEDUSA_BEGIN;

class ShapeVertex
{
public:
	Point3F Position;
	Color4F Color;

	ShapeVertex(){}

	ShapeVertex(const Point3F& position,const Color4F& color)
		:Position(position),Color(color){}
	
	void ResetZero()
	{
		Position=Point3F::Zero;
		Color=Color4F::Zero;
	}

	ShapeVertex& operator=(const ShapeVertex& vertex){Position=vertex.Position;Color=vertex.Color;return *this;}
	bool operator==(const ShapeVertex& vertex)const{return Position==vertex.Position&&Color==vertex.Color;}
	bool operator!=(const ShapeVertex& vertex)const{return !operator==(vertex);}
	intp GetHashCode()const{return Position.GetHashCode()^Color.GetHashCode();}
};


MEDUSA_END;
