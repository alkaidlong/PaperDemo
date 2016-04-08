#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Geometry/Rotation2.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"


MEDUSA_BEGIN;

template<typename T>
class Rotation3
{
public:
	union
	{
		T Buffer[3];
		struct
		{
			T X;
			T Y;
			T Z;
		};
	};

	
	const static Rotation3 Zero;
public:
	Rotation3(void){}
	Rotation3(T x,T y,T z=0):X(x),Y(y),Z(z){}
	Rotation3(const T* items):X(*items),Y(*(items+1)),Z(*(items+2)){}

	template<typename T1>
	Rotation3(const Rotation3<T1>& rotation):X((T)rotation.X),Y((T)rotation.Y),Z((T)rotation.Z){}

	template<typename T1>
	Rotation3(const Rotation2<T1>& rotation):X((T)rotation.X),Y((T)rotation.Y),Z(0){}

	template<typename T1>
	Rotation3& operator=(const Rotation3<T1>& rotation){X=(T)rotation.X;Y=(T)rotation.Y;Z=(T)rotation.Z;return *this;}

	template<typename T1>
	Rotation3& operator=(const Rotation2<T1>& rotation){X=(T)rotation.X;Y=(T)rotation.Y;Z=(T)0;return *this;}

	template<typename T1>
	Rotation3& operator=(T1 val){X=(T)val;Y=(T)val;Z=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Rotation3<T1>& rotation)const{return Math::IsEqual(X,rotation.X)&&Math::IsEqual(Y,rotation.Y)&&Math::IsEqual(Z,rotation.Z);}
	template<typename T1>
	bool operator!=(const Rotation3<T1>& rotation)const{return !operator==(rotation);}
	template<typename T1>
	bool operator>(const Rotation3<T1>& rotation)const{return X>rotation.X&&Y>rotation.Y&&Z>rotation.Z;}
	template<typename T1>
	bool operator<(const Rotation3<T1>& rotation)const{return X<rotation.X&&Y<rotation.Y&&Z<rotation.Z;}
	template<typename T1>
	bool operator>=(const Rotation3<T1>& rotation)const{return X>=rotation.X&&Y>=rotation.Y&&Z>=rotation.Z;}
	template<typename T1>
	bool operator<=(const Rotation3<T1>& rotation)const{return X<=rotation.X&&Y<=rotation.Y&&Z<=rotation.Z;}

	template<typename T1>
	Rotation3 operator+(const Rotation3<T1>& rotation)const{return Rotation3(X+rotation.X,Y+rotation.Y,Z+rotation.Z);}
	template<typename T1>
	Rotation3 operator-(const Rotation3<T1>& rotation)const{return Rotation3(X-rotation.X,Y-rotation.Y,Z-rotation.Z);}
	template<typename T1>
	Rotation3& operator+=(const Rotation3<T1>& rotation){X+=rotation.X;Y+=rotation.Y;Z+=rotation.Z;return *this;}
	template<typename T1>
	Rotation3& operator-=(const Rotation3<T1>& rotation){X-=rotation.X;Y-=rotation.Y;Z-=rotation.Z;return *this;}

	template<typename T1>
	Rotation3 operator*(T1 delta)const{return Rotation3(X*delta,Y*delta,Z*delta);}
	template<typename T1>
	Rotation3 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Rotation3(X/delta,Y/delta,Z/delta);}
	Rotation3 operator<<(uint32 delta)const{return Rotation3(X<<delta,Y<<delta,Z<<delta);}
	Rotation3 operator>>(uint32 delta)const{return Rotation3(X>>delta,Y>>delta,Z>>delta);}

	template<typename T1>
	Rotation3& operator*=(T1 delta){X*=delta;Y*=delta;Z*=delta;return *this;}
	template<typename T1>
	Rotation3& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;Z/=delta;return *this;}
	Rotation3& operator<<=(uint32 delta){X<<=delta;Y<<=delta;Z<<=delta;return *this;}
	Rotation3& operator>>=(uint32 delta){X>>=delta;Y>>=delta;Z>>=delta;return *this;}

	template<typename T1>
	Rotation3 operator+(T1 delta)const{return Rotation3(X+delta,Y+delta,Z+delta);}
	template<typename T1>
	Rotation3 operator-(T1 delta)const{return Rotation3(X-delta,Y-delta,Z-delta);}

	template<typename T1>
	Rotation3& operator+=(T1 delta){X+=delta;Y+=delta;Z+=delta;return *this;}
	template<typename T1>
	Rotation3& operator-=(T1 delta){X-=delta;Y-=delta;Z-=delta;return *this;}

	Rotation3& operator++(){++X;++Y;++Z;return *this;}
	Rotation3& operator--(){--X;--Y;--Z;return *this;}

	Rotation3 operator++(int){Rotation3 orign=*this;++X;++Y;++Z;return orign;}
	Rotation3 operator--(int){Rotation3 orign=*this;--X;--Y;--Z;return orign;}

	template<typename T1>
	friend  Rotation3 operator*(T1 delta,const Rotation3<T>& rotation){return Rotation3(delta*rotation.X,delta*rotation.Y,delta*rotation.Z);}

	Rotation2<T> To2D()const{return Rotation2<T>(X,Y);}
	Rotation3 ToDegree()const{return Rotation3(Math::ToDegree(X),Math::ToDegree(Y),Math::ToDegree(Z));}
	Rotation3 ToRadian()const{return Rotation3(Math::ToRadian(X),Math::ToRadian(Y),Math::ToRadian(Z));}
	Rotation3 CreateInverse()const{return Rotation3(-X,-Y,-Z);}
	intp GetHashCode()const{return HashUtility::Hash(Buffer);}

	static Rotation3 LinearInterpolate(const Rotation3& begin,const Rotation3& end,float blend)
	{
		return Rotation3(Math::LinearInterpolate(begin.X,end.X,blend),Math::LinearInterpolate(begin.Y,end.Y,blend),Math::LinearInterpolate(begin.Z,end.Z,blend));
	}
};

template<typename T>
WEAK_MULTIPLE_DEFINE const Rotation3<T> Rotation3<T>::Zero(0,0,0);

//[PRE_DECLARE_BEGIN]
typedef Rotation3<float> Rotation3F;
//[PRE_DECLARE_END]


#define mrrr(x,y,z) Rotation3F(x,y,z)

MEDUSA_END;
