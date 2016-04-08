#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Memory/Memory.h"
#include "Core/Geometry/Size2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Scale2.h"
#include "Core/Geometry/Quad.h"

#include "Core/Geometry/GeometryDefines.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"

MEDUSA_BEGIN;


class Matrix2
{
public:
	const static Matrix2 Zero;
	const static Matrix2 Identity;
	const static byte Size=6;
public:
	inline Matrix2(void){}
	inline Matrix2(const float* items)
	{
		Memory::Copy(Items,items,Size);
	}
	//No need this because C++ will produce default copy-assignment for us
	
	inline Matrix2(const Matrix2& matrix){Memory::Copy(Items,matrix.Items,Size);}
	inline Matrix2& operator=(const Matrix2& matrix){Memory::Copy(Items,matrix.Items,Size); return *this;}

	//in row-major
	inline Matrix2(float a,float b,float c,float d,float tx,float ty)
		:A(a),B(b),C(c),D(d),TX(tx),TY(ty)
	{
		
	}

	float* GetItems(){return Items;}
	const float* const GetItems()const{return Items;}

	//inline operator float*(){return Items;}
	//inline operator const float*()const{return Items;}

	inline float& operator[](uint32 index){return Items[index];}
	inline const float& operator[](uint32 index)const{return Items[index];}


	inline bool operator==(const Matrix2& matrix)const{return memcmp(Items,matrix.GetItems(),sizeof(Matrix2))==0;}
	inline bool operator!=(const Matrix2& matrix)const{return memcmp(Items,matrix.GetItems(),sizeof(Matrix2))!=0;}

public:

	inline Matrix2 operator*(const Matrix2& matrix)const
	{
		Matrix2 ret=*this;
		ret.Multiply(matrix);
		return ret;
	}
	inline Matrix2& operator*=(const Matrix2& matrix)
	{
		Multiply(matrix);
		return *this;
	}
public:

	Point2F Transform(const Point2F& point)const;
	QuadVertex2 Transform(const QuadVertex2& quad)const;
	QuadVertex2 Transform(const Rect2F& rect)const;


	
	void Multiply(const Matrix2& other);
	void Invert();

	void ResetIdentity(){*this=Identity;}
	void ResetZero(){*this=Zero;}

	bool IsIdentity()const;
	bool IsInvertible()const;

	Point2F GetPosition()const;
	Scale2F GetScale()const;
	float GetRotation()const; 
	intp GetHashCode()const{return HashUtility::Hash(Items);}

public:

	union
	{
		float Items[Size];

		struct
		{

#if MEDUSA_IS_OPENGL==1
			/*
			a c tx
			b d ty
			0 0 1
			*/
			float A;float C;float TX;
			float B;float D;float TY;
			
#else
		/*
			a b 0
			c d 0
			tx ty 1
			*/
			float A;float B;
			float C;float D;
			float TX;float TY;
#endif
		};
	};
};



MEDUSA_END;
