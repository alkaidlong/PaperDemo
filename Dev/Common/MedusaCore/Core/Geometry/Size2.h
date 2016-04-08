#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/HashUtility.h"



MEDUSA_BEGIN;

template<typename T>
class Size2
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T Width;
			T Height;
		};
	};

	
	const static Size2 Zero;
	const static Size2 One;

public:
	Size2(void){}
	Size2(T width,T height):Width(width),Height(height){}

	template<typename T1>
	Size2(const Size2<T1>& size):Width((T)size.Width),Height((T)size.Height){}

	template<typename T1>
	explicit Size2(T1 val):Width((T)val),Height((T)val){}

	template<typename T1>
	Size2& operator=(const Size2<T1>& size){Width=(T)size.Width;Height=(T)size.Height;return *this;}
	template<typename T1>
	Size2& operator=(T1 val){Width=(T)val;Height=(T)val;return *this;}

	bool operator==(const Size2& size)const{return Math::IsEqual(Width,size.Width)&&Math::IsEqual(Height,size.Height);}

	template<typename T1>
	bool operator==(const Size2<T1>& size)const{return Math::IsEqual(Width,size.Width)&&Math::IsEqual(Height,size.Height);}
	template<typename T1>
	bool operator!=(const Size2<T1>& size)const{return !operator==(size);}
	template<typename T1>
	bool operator>(const Size2<T1>& size)const{return Width>size.Width&&Height>size.Height;}
	template<typename T1>
	bool operator<(const Size2<T1>& size)const{return Width<size.Width&&Height<size.Height;}
	template<typename T1>
	bool operator>=(const Size2<T1>& size)const{return Width>=size.Width&&Height>=size.Height;}
	template<typename T1>
	bool operator<=(const Size2<T1>& size)const{return Width<=size.Width&&Height<=size.Height;}

	template<typename T1>
	Size2 operator+(const Size2<T1>& size)const{return Size2(Width+size.Width,Height+size.Height);}
	template<typename T1>
	Size2 operator-(const Size2<T1>& size)const{return Size2(Width-size.Width,Height-size.Height);}
	template<typename T1>
	Size2& operator+=(const Size2<T1>& size){Width+=size.Width;Height+=size.Height;return *this;}
	template<typename T1>
	Size2& operator-=(const Size2<T1>& size){Width-=size.Width;Height-=size.Height;return *this;}

	template<typename T1>
	Size2 operator*(T1 delta)const{return Size2(Width*delta,Height*delta);}
	template<typename T1>
	Size2& operator*=(T1 delta){Width*=delta;Height*=delta;return *this;}

	template<typename T1>
	Size2 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Size2(Width/delta,Height/delta);}
	template<typename T1>
	Size2& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Width/=delta;Height/=delta;return *this;}

	template<typename T1>
	Size2 operator+(T1 delta)const{return Size2(Width+delta,Height+delta);}
	template<typename T1>
	Size2& operator+=(T1 delta){Width+=delta;Height+=delta;return *this;}

	template<typename T1>
	Size2 operator-(T1 delta)const{return Size2(Width-delta,Height-delta);}
	template<typename T1>
	Size2& operator-=(T1 delta){Width-=delta;Height-=delta;return *this;}

	Size2 operator<<(uint32 delta)const{return Size2(Width<<delta,Height<<delta);}
	Size2& operator<<=(uint32 delta){Width<<=delta;Height<<=delta;return *this;}

	Size2 operator>>(uint32 delta)const{return Size2(Width>>delta,Height>>delta);}
	Size2& operator>>=(uint32 delta){Width>>=delta;Height>>=delta;return *this;}

	Size2& operator++(){++Width;++Height;return *this;}
	Size2& operator--(){--Width;--Height;return *this;}

	Size2 operator++(int){Size2 orign=*this;++Width;++Height;return orign;}
	Size2 operator--(int){Size2 orign=*this;--Width;--Height;return orign;}

	template<typename T1>
	friend Size2 operator*(T1 delta,const Size2<T>& size){return Size2(delta*size.Width,delta*size.Height);}

	Size2 Flip()const{return Size2(Height,Width);}
	float Length()const{return Math::Sqrt((float)(Width*Width+Height*Height));}
	T Area()const{return Width*Height;}
	intp GetHashCode()const{return HashUtility::Hash(Buffer);}
	bool IsEmpty()const{return Math::IsZero(Width)||Math::IsZero(Height);}

	static Size2 LinearInterpolate(const Size2& begin,const Size2& end,float blend)
	{
		return Size2(Math::LinearInterpolate(begin.Width,end.Width,blend),Math::LinearInterpolate(begin.Height,end.Height,blend));
	}
};

template<typename T>
WEAK_MULTIPLE_DEFINE const Size2<T> Size2<T>::Zero(0,0);
template<typename T>
WEAK_MULTIPLE_DEFINE const Size2<T> Size2<T>::One(1,1);

//[PRE_DECLARE_BEGIN]
typedef Size2<int> Size2I;
typedef Size2<uint32> Size2U;

typedef Size2<float> Size2F;
//[PRE_DECLARE_END]

#define msizeu(x,y) Size2U(x,y)
#define msizei(x,y) Size2I(x,y)
#define msize(x,y) Size2F(x,y)

MEDUSA_END;
