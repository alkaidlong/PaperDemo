#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/TextureVertex.h"
#include "Core/Geometry/ShapeVertex.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

template<typename T>
class Quad
{
public:
	T LeftBottom;
    T RightBottom;
    T RightTop;
    T LeftTop;

	Quad(){}
	Quad(const T& val)
		:LeftBottom(val),LeftTop(val),RightBottom(val),RightTop(val)
	{

	}
	void SetAll(const T& val)
	{
		LeftBottom=val;
		LeftTop=val;
		RightBottom=val;
		RightTop=val;
	}

	void ResetZero()
	{
		//memset(Buffer,0,sizeof(T)*4);
	}

	Quad(const T& leftBottom,const T& leftTop,const T& rightBottom,const T& rightTop)
		:LeftBottom(leftBottom),LeftTop(leftTop),RightBottom(rightBottom),RightTop(rightTop){}

	template<typename T1>
	Quad(const Quad<T1>& quad):LeftBottom(quad.LeftBottom),LeftTop(quad.LeftTop),RightBottom(quad.RightBottom),RightTop(quad.RightTop){}

	template<typename T1>
	Quad(const Array<T1,4>& items):LeftBottom(items[0]),RightBottom(items[1]),RightTop(items[2]),LeftTop(items[3]){}

	template<typename T1>
	Quad& operator=(const Quad<T1>& quad){LeftBottom=quad.LeftBottom;LeftTop=quad.LeftTop;RightBottom=quad.RightBottom;RightTop=quad.RightTop;return *this;}

	template<typename T1>
	Quad& operator=(const Array<T1,4>& items){LeftBottom=items[0];RightBottom=items[1];RightTop=items[2];LeftTop=items[3];return *this;}


	template<typename T1>
	bool operator==(const Quad<T1>& quad)const{return Math::IsEqual(LeftBottom,quad.LeftBottom)&&Math::IsEqual(LeftTop,quad.LeftTop)&&Math::IsEqual(RightBottom,quad.RightBottom)&&Math::IsEqual(RightTop,quad.RightTop);}
	template<typename T1>
	bool operator!=(const Quad<T1>& quad)const{return !operator==(quad);}
};

//[PRE_DECLARE_BEGIN]
typedef Quad<Color4F> QuadColor;
typedef Quad<Point2<float> > QuadTexCoord;
typedef Quad<Point3<float> > QuadVertex3;
typedef Quad<Point2<float> > QuadVertex2;
typedef Quad<TextureVertex> QuadTextureVertex;
typedef Quad<ShapeVertex> QuadShapeVertex;

//[PRE_DECLARE_END]


MEDUSA_END;
