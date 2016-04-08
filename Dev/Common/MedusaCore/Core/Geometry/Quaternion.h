#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Point4.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"



MEDUSA_BEGIN;

/*
单位四元数
Q 表示轴-角对，设轴为N=(Nx,Ny,Nz),角度为α
则:
Q=[v w]=[x,y,z,w]=[cos(α/2),N*sin(α/2)]

w=cos(α/2)
x=sin(α/2)*Nx
y=sin(α/2)*Ny
z=sin(α/2)*Nz

四元数乘法：
[w1 v1][w2 v2]=[w1w2-v1v2,w1v2+w2v1+ v2 x v1]
表示旋转:
p=[0,(x,y,z)]
q=旋转四元数
p'=qpq-1 用于旋转p到p'
如果连接a,b两个旋转
有 p'= b(apa-1)b-1=(ba)p(ba)-1
注意：这个旋转从右向左发生的，所以与我们正常的思维顺序相反

但如果我们重新定义四元数的乘法：
[w1 v1][w2 v2]=[w1w2-v1v2,w1v2+w2v1+ v1 x v2]
注意我们这里只改变了v1和v2叉乘的顺序，使得
p'=q'pq
p'=(ab)-1p(ab)
这样旋转的顺序就是自左向右的
*/
class EulerAngle;
class Matrix3;



class Quaternion
{
public:
	union
	{
		float Buffer[4];
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
	};

	
	const static Quaternion Zero;
	const static Quaternion Identity;

public:
	Quaternion(void){}
	Quaternion(float x,float y,float z,float w):X(x),Y(y),Z(z),W(w){}
	Quaternion(const float* items):X(*items),Y(*(items+1)),Z(*(items+2)),W(*(items+3)){}
	Quaternion(const Quaternion& q):X(q.X),Y(q.Y),Z(q.Z),W(q.W){}
	Quaternion(const Point3F& point):X(point.X),Y(point.Y),Z(point.Z),W(0.f){}
	Quaternion(const Point3F& normalVector,float angle);


	Quaternion& operator=(const Quaternion& q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
	Quaternion& operator=(float val){X=val;Y=val;Z=val;W=val;return *this;}
	Quaternion& operator=(const Point3F& point){X=point.X;Y=point.Y;Z=point.Z;W=0.f;return *this;}


	
	bool operator==(const Quaternion& q)const{return Math::IsEqual(X,q.X)&&Math::IsEqual(Y,q.Y)&&Math::IsEqual(Z,q.Z)&&Math::IsEqual(W,q.W);}
	bool operator!=(const Quaternion& q)const{return !operator==(q);}
	bool operator>(const Quaternion& q)const{return X>q.X&&Y>q.Y&&Z>q.Z&&W>q.W;}
	bool operator<(const Quaternion& q)const{return X<q.X&&Y<q.Y&&Z<q.Z&&W<q.W;}
	bool operator>=(const Quaternion& q)const{return X>=q.X&&Y>=q.Y&&Z>=q.Z&&W>=q.W;}
	bool operator<=(const Quaternion& q)const{return X<=q.X&&Y<=q.Y&&Z<=q.Z&&W<=q.W;}
	
	Quaternion operator+(const Quaternion& q)const{return Quaternion(X+q.X,Y+q.Y,Z+q.Z,W+q.W);}
	Quaternion operator-(const Quaternion& q)const{return Quaternion(X-q.X,Y-q.Y,Z-q.Z,W-q.W);}
	Quaternion& operator+=(const Quaternion& q){X+=q.X;Y+=q.Y;Z+=q.Z;W+=q.W;return *this;}
	Quaternion& operator-=(const Quaternion& q){X-=q.X;Y-=q.Y;Z-=q.Z;W-=q.W;return *this;}
	
	Quaternion operator*(const Quaternion& q)const;
	Quaternion& operator*=(const Quaternion& q);
	
	friend Quaternion operator*(float delta,const Quaternion& q){return Quaternion(delta*q.X,delta*q.Y,delta*q.Z,delta*q.W);}
	Quaternion operator*(float delta)const{return Quaternion(X*delta,Y*delta,Z*delta,W*delta);}
	Quaternion operator/(float delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Quaternion(X/delta,Y/delta,Z/delta,W/delta);}
	Quaternion& operator*=(float delta){X*=delta;Y*=delta;Z*=delta;W*=delta;return *this;}
	Quaternion& operator/=(float delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;Z/=delta;W/=delta;return *this;}

	Quaternion& operator++(){++X;++Y;++Z;++W;return *this;}
	Quaternion& operator--(){--X;--Y;--Z;--W;return *this;}

	Quaternion operator++(int){Quaternion orign=*this;++X;++Y;++Z;++W;return orign;}
	Quaternion operator--(int){Quaternion orign=*this;--X;--Y;--Z;--W;return orign;}

	Quaternion operator-()const{return Quaternion(-X,-Y,-Z,-W);}
	

	
	bool operator==(float val)const{return Math::IsEqual(X,val)&&Math::IsEqual(Y,val)&&Math::IsEqual(Z,val)&&Math::IsEqual(W,val);}
	bool operator!=(float val)const{return !operator==(val);}
	bool operator>(float val)const{return X>val&&Y>val&&Z>val&&W>val;}
	bool operator<(float val)const{return X<val&&Y<val&&Z<val&&W<val;}
	bool operator>=(float val)const{return X>=val&&Y>=val&&Z>=val&&W>=val;}
	bool operator<=(float val)const{return X<=val&&Y<=val&&Z<=val&&W<=val;}
	
	friend  bool operator==(float val,const Quaternion& q){return q==val;}
	friend  bool operator!=(float val,const Quaternion& q){return q!=val;}
	friend  bool operator>(float val,const Quaternion& q){return q<=val;}
	friend  bool operator<(float val,const Quaternion& q){return q>=val;}
	friend  bool operator>=(float val,const Quaternion& q){return q<val;}
	friend  bool operator<=(float val,const Quaternion& q){return q>val;}

	float Length()const{return 1.f;}
	Point3F ToPoint()const{return Point3F(X,Y,Z);}
public:
	float DotMultiply(const Quaternion& q)const{return X*q.X+Y*q.Y+Z*q.Z+W*q.W;}
	Quaternion Sub(const Quaternion& q)const;

	Quaternion Conjugate()const
	{
		return Quaternion(-X,-Y,-Z,W);
	}

	Quaternion Inverse()const
	{
		return Quaternion(-X,-Y,-Z,W);
	}

	Point3F Tranform(const Point3F& point)const;


	static Quaternion CreateFromEuler(const EulerAngle& angle);
	static Quaternion CreateFromMatrix(const Matrix3& m);
	static Quaternion CreateFromMatrix(const Matrix43& m);
	static Quaternion CreateFromMatrix(const Matrix4& m);

	static Quaternion Slerp(const Quaternion& begin,const Quaternion& end,float t);
	void ConvertToAxisAngle(Point3F& outNormalVector,float& outAngle);

	void Normalize();
};


MEDUSA_END;
