#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"

MEDUSA_BEGIN;

class TextureVertex
{
public:
	Point3F Position;
	Point3F Normal;
	Point2F Texcoord;
	Color4F Color;

	TextureVertex(){}

	TextureVertex(const Point3F& position,const Point3F& normal,const Point2F& texcoord,const Color4F& color)
		:Position(position),Normal(normal),Texcoord(texcoord),Color(color){}
	
	void ResetZero()
	{
		Position=Point3F::Zero;
		Normal=Point3F::Zero;
		Texcoord=Point2F::Zero;
		Color=Color4F::Zero;
	}

	TextureVertex& operator=(const TextureVertex& vertex){Position=vertex.Position;Normal=vertex.Normal;Texcoord=vertex.Texcoord;Color=vertex.Color;return *this;}
	bool operator==(const TextureVertex& vertex)const{return Position==vertex.Position&&Normal==vertex.Normal&&Texcoord==vertex.Texcoord&&Color==vertex.Color;}
	bool operator!=(const TextureVertex& vertex)const{return !operator==(vertex);}
	intp GetHashCode()const{return Position.GetHashCode()^Normal.GetHashCode()^Texcoord.GetHashCode()^Color.GetHashCode();}
};


MEDUSA_END;
