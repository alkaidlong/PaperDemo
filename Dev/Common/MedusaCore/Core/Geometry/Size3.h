#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Geometry/Size2.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"

MEDUSA_BEGIN;
template<typename T>
class Size3
{
public:
	union
	{
		T Buffer[3];
		struct
		{
			T Width;
			T Height;
			T Depth;
		};
	};


	
	const static Size3 Zero;
public:
	Size3(void){}
	Size3(T width,T height,T depth):Width(width),Height(height),Depth(depth){}
	template<typename T1>
	Size3(const Size3<T1>& size):Width((T)size.Width),Height((T)size.Height),Depth((T)size.Depth){}

	template<typename T1>
	Size3(const Size2<T1>& size):Width((T)size.Width),Height((T)size.Height),Depth((T)0){}

	template<typename T1>
	explicit Size3(T1 val):Width((T)val),Height((T)val),Depth((T)val){}

	template<typename T1>
	Size3& operator=(const Size3<T1>& size){Width=(T)size.Width;Height=(T)size.Height;Depth=(T)size.Depth;return *this;}
	template<typename T1>
	Size3& operator=(const Size2<T1>& size){Width=(T)size.Width;Height=(T)size.Height;Depth=(T)0;return *this;}

	template<typename T1>
	Size3& operator=(T1 val){Width=(T)val;Height=(T)val;Depth=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Size3<T1>& size)const{return Math::IsEqual(Width,size.Width)&&Math::IsEqual(Height,size.Height)&&Math::IsEqual(Depth,size.Depth);}
	template<typename T1>
	bool operator!=(const Size3<T1>& size)const{return !operator==(size);}
	template<typename T1>
	bool operator>(const Size3<T1>& size)const{return Width>size.Width&&Height>size.Height&&Depth>size.Depth;}
	template<typename T1>
	bool operator<(const Size3<T1>& size)const{return Width<size.Width&&Height<size.Height&&Depth<size.Depth;}
	template<typename T1>
	bool operator>=(const Size3<T1>& size)const{return Width>=size.Width&&Height>=size.Height&&Depth>=size.Depth;}
	template<typename T1>
	bool operator<=(const Size3<T1>& size)const{return Width<=size.Width&&Height<=size.Height&&Depth<=size.Depth;}

	template<typename T1>
	Size3 operator+(const Size3<T1>& size)const{return Size3(Width+size.Width,Height+size.Height,Depth+size.Depth);}
	template<typename T1>
	Size3 operator-(const Size3<T1>& size)const{return Size3(Width-size.Width,Height-size.Height,Depth-size.Depth);}
	template<typename T1>
	Size3& operator+=(const Size3<T1>& size){Width+=size.Width;Height+=size.Height;Depth+=size.Depth;return *this;}
	template<typename T1>
	Size3& operator-=(const Size3<T1>& size){Width-=size.Width;Height-=size.Height;Depth-=size.Depth;return *this;}

	template<typename T1>
	Size3 operator*(T1 delta)const{return Size3(Width*delta,Height*delta,Depth*delta);}
	template<typename T1>
	Size3& operator*=(T1 delta){Width*=delta;Height*=delta;Depth*=delta;return *this;}

	template<typename T1>
	Size3 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Size3(Width/delta,Height/delta,Depth/delta);}
	template<typename T1>
	Size3& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Width/=delta;Height/=delta;Depth/=delta;return *this;}

	template<typename T1>
	Size3 operator+(T1 delta)const{return Size3(Width+delta,Height+delta,Depth+delta);}
	template<typename T1>
	Size3& operator+=(T1 delta){Width+=delta;Height+=delta;Depth+=delta;return *this;}

	template<typename T1>
	Size3 operator-(T1 delta)const{return Size3(Width-delta,Height-delta,Depth-delta);}
	template<typename T1>
	Size3& operator-=(T1 delta){Width-=delta;Height-=delta;Depth-=delta;return *this;}

	Size3 operator<<(uint32 delta)const{return Size3(Width<<delta,Height<<delta,Depth<<delta);}
	Size3& operator<<=(uint32 delta){Width<<=delta;Height<<=delta;Depth<<=delta;return *this;}

	Size3 operator>>(uint32 delta)const{return Size3(Width>>delta,Height>>delta,Depth>>delta);}
	Size3& operator>>=(uint32 delta){Width>>=delta;Height>>=delta;Depth>>=delta;return *this;}


	Size3& operator++(){++Width;++Height;++Depth;return *this;}
	Size3& operator--(){--Width;--Height;--Depth;return *this;}

	Size3 operator++(int){Size3 orign=*this;++Width;++Height;++Depth;return orign;}
	Size3 operator--(int){Size3 orign=*this;--Width;--Height;--Depth;return orign;}

	template<typename T1>
	friend  Size3 operator*(T1 delta,const Size3<T>& size){return Size3(delta*size.Width,delta*size.Height,delta*size.Depth);}

	Size2<T> To2D()const{return Size2<T>(Width,Height);}
	bool IsEmpty()const{return Math::IsZero(Width)||Math::IsZero(Height)||Math::IsZero(Depth);}
	T Volume()const{return Width*Height*Depth;}
	intp GetHashCode()const{return HashUtility::Hash(Buffer);}

	static Size3 LinearInterpolate(const Size3& begin,const Size3& end,float blend)
	{
		return Size2<T>(Math::LinearInterpolate(begin.Width,end.Width,blend),Math::LinearInterpolate(begin.Height,end.Height,blend),Math::LinearInterpolate(begin.Depth,end.Depth,blend));
	}
};

template<typename T>
WEAK_MULTIPLE_DEFINE const Size3<T> Size3<T>::Zero(0,0,0);

//[PRE_DECLARE_BEGIN]
typedef Size3<uint32> Size3U;
typedef Size3<int> Size3I;
typedef Size3<float> Size3F;
//[PRE_DECLARE_END]

#define msize3u(x,y,z) Size3U(x,y,z)
#define msize3i(x,y,z) Size3I(x,y,z)
#define msize3(x,y,z) Size3F(x,y,z)

MEDUSA_END;
