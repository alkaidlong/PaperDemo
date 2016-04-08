#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Matrix2.h"


MEDUSA_BEGIN;

Point2F Matrix2::Transform( const Point2F& point ) const
{
#if MEDUSA_IS_OPENGL==1
	return Point2F( A * point.X + B * point.Y + TX,C * point.X + D * point.Y + TY);
#else
	return Point2F( A * point.X + C * point.Y + TX,B * point.X + D * point.Y + TY);
#endif
}

QuadVertex2 Matrix2::Transform( const QuadVertex2& quad ) const
{
	QuadVertex2 result;
	result.LeftBottom = Transform(quad.LeftBottom);
	result.LeftTop = Transform(quad.LeftTop);
	result.RightBottom = Transform(quad.RightBottom);
	result.RightTop = Transform(quad.RightTop);
	return result;
}

QuadVertex2 Matrix2::Transform( const Rect2F& rect ) const
{
	QuadVertex2 quad(rect.LeftBottom(),rect.LeftTop(),rect.RightBottom(),rect.RightTop());
	return Transform(quad);
}


void Matrix2::Multiply( const Matrix2& other ) 
{
	Matrix2 result;
#if MEDUSA_IS_OPENGL==1
	result.A=other.A*A+other.B*C;
	result.B=other.A*B+other.B*D;
	result.C=other.C*A+other.D*C;
	result.D=other.C*B+other.D*D;
	result.TX=other.TX*A+other.TY*C;
	result.TY=other.TX*B+other.TY*D;
#else
	result.A=A*other.A+B*other.C;
	result.B=A*other.B+B*other.D;
	result.C=C*other.A+D*other.C;
	result.D=C*other.B+D*other.D;
	result.TX=TX*other.A+TY*other.C;
	result.TY=TX*other.B+TY*other.D;
#endif
	*this=result;
}

void Matrix2::Invert() 
{
	float determinant = 1 / (A * D - B * C);
	float a=determinant * D;
	float b=-determinant * B;
	float c=-determinant * C;
	float d=determinant * A;
	float tx=determinant * (C * TY - D * TX);
	float ty=determinant * (B * TX - A * TY);
	A=a;
	B=b;
	C=c;
	D=d;
	TX=tx;
	TY=ty;
}

bool Matrix2::IsIdentity() const
{
	return true;
}

bool Matrix2::IsInvertible() const
{
	return true;
}

Point2F Matrix2::GetPosition() const
{
	return Point2F(TX,TY);
}

Scale2F Matrix2::GetScale() const
{
	return Scale2F::One;
}

float Matrix2::GetRotation() const
{
	return 0.f;
}


const Matrix2 Matrix2::Zero=Matrix2(0.f,0.f,0.f,0.f,
	0.f,0.f);

const Matrix2 Matrix2::Identity=Matrix2(1.f,0.f,0.f,1.f,
	0.f,0.f);


MEDUSA_END;
