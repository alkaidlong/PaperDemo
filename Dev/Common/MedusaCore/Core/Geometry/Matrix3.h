#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Memory/Memory.h"
#include "Core/Pattern/LazyValue.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point4.h"
#include "Core/Geometry/Size3.h"
#include "Core/Geometry/Cube.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Rotation3.h"

#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Quad.h"

#include "Core/Geometry/GeometryDefines.h"
#include "Core/String/HeapString.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"

MEDUSA_BEGIN;

/*

[m11,m12,m13]
[m21,m22,m23]
[m31,m32,m33]

v'=v*S*R*T	Append
transform prepend
*/
class EulerAngle;
class Quaternion;
class Matrix4;
class Matrix43;


class Matrix3
{
public:
	inline Matrix3(void){}
	inline Matrix3(const float* items)
	{
		Memory::Copy(M,items,Size);
	}
	//No need this because C++ will produce default copy-assignment for us
	//inline Matrix3(const Matrix3& matrix);
	//inline Matrix3& operator=(const Matrix3& matrix);

	//in row-major
	inline Matrix3(float m11,float m12,float m13,
		float m21,float m22,float m23,
		float m31,float m32,float m33,bool isTransposed=false)
	{
		if (isTransposed)
		{
			M11=m11;M12=m21;M13=m31;
			M21=m12;M22=m22;M23=m32;
			M31=m13;M32=m23;M33=m33;
		}
		else
		{
			M11=m11;M12=m12;M13=m13;
			M21=m21;M22=m22;M23=m23;
			M31=m31;M32=m32;M33=m33;
		}
	}


	explicit Matrix3(const Matrix4& m,bool isTransposed=false);
	Matrix3& operator=(const Matrix4& m);

	explicit Matrix3(const Matrix43& m,bool isTransposed=false);
	Matrix3& operator=(const Matrix43& m);

	float* Items(){return M;}
	const float* const Items()const{return M;}

	float& operator[](byte index){return M[index];}
	const float& operator[](byte index)const{return M[index];}

	inline float& operator()(byte row,byte column){return M[row*ColumnSize+column];}
	inline const float& operator()(byte row,byte column)const{return M[row*ColumnSize+column];}

	Point3F Row(byte row)const{return Point3F(M+ColumnSize*row);}
	void SetRow(byte row,const Point3F& val);

	Point3F Column(byte column);
	void SetColumn(byte column,const Point3F& val);
	
	bool operator==(const Matrix3& matrix)const;
	bool operator!=(const Matrix3& matrix)const;
	bool IsIdentity()const;
	bool IsZero()const;
public:
	inline Matrix3 operator*(const Matrix3& matrix)const
	{
		Matrix3 ret=*this;
		ret.Append(matrix);
		return ret;
	}
	inline Matrix3& operator*=(const Matrix3& matrix)
	{
		Append(matrix);
		return *this;
	}

	intp GetHashCode()const
	{
		return HashUtility::Hash(M);
	}

public:
	Matrix3& Multiply(const Matrix3& m,MatrixOrder order);
	Matrix3& Append(const Matrix3& m);
	Matrix3& Prepend(const Matrix3& m);
	
	inline void LoadIdentity(){*this=Identity;}
	inline void LoadZero(){*this=Zero;}

	Point3F Transform(const Point3F& point)const;

	HeapString ToString()const;
	float Determinant()const;

#pragma region Transform
public:
	Matrix3& Inverse();
	Matrix3& Transpose();
	Matrix3& Scale(const Scale3F& scale);
	Matrix3& RotateXYZ(const Rotation3F& rotation);
	Matrix3& RotateX(float angle);
	Matrix3& RotateY(float angle);
	Matrix3& RotateZ(float angle);
	Matrix3& RotateEuler(const EulerAngle& angle);

	Matrix3& FlipX();
	Matrix3& FlipY();
	Matrix3& FlipZ();

	Matrix3 CreateInverse();
	Matrix3 CreateTranspose();

	static Matrix3 CreateScale(const Scale3F& scale);
	static Matrix3 CreateScaleAxis(const Point3F& axis,float scale);
	static Matrix3 CreateRotateXYZ(const Rotation3F& rotation);
	static Matrix3 CreateRotateX(float angle);
	static Matrix3 CreateRotateY(float angle);
	static Matrix3 CreateRotateZ(float angle);
	static Matrix3 CreateRotateAxis(const Point3F& axis,float angle);
	static Matrix3 CreateFromEuler(const EulerAngle& angle);
	static Matrix3 CreateFromQuaternion(const Quaternion& q);
	static Matrix3 CreateProjectToXY();
	static Matrix3 CreateProjectToXZ();
	static Matrix3 CreateProjectToYZ();
	static Matrix3 CreateProjectToPlane(const Point3F& normal);
	static Matrix3 CreateFlipX();
	static Matrix3 CreateFlipY();
	static Matrix3 CreateFlipZ();
	static Matrix3 CreateFlipByPlane(const Point3F& normal);
	static Matrix3 CreateShear(float xy,float xz,float yx,float yz,float zx,float zy);
	
#pragma endregion Transform

public:
	const static Matrix3 Zero;
	const static Matrix3 Identity;
	const static byte Size=9;
	const static byte RowSize=3;
	const static byte ColumnSize=3;

	union
	{
		float M[Size];

		struct
		{
			float M11;float M12;float M13;
			float M21;float M22;float M23;
			float M31;float M32;float M33;
		};
	};
	
};

//[PRE_DECLARE_BEGIN]
typedef Pattern::LazyValue<Matrix3> LazyMatrix3;
//[PRE_DECLARE_END]
MEDUSA_END;
