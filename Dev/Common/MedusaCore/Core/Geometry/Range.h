#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/MathHeader.h"
#include "Core/Utility/Utility.h"



MEDUSA_BEGIN;

template<typename T>
class Range
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T Min;
			T Max;
		};
	};
	
	const static Range Init;
public:
	Range(void):Min(Math::Values<T>::Max),Max(Math::Values<T>::Min){}
	Range(T min,T max):Min(min),Max(max){MEDUSA_ASSERT_LESS_EQUAL(min,max,"Invalid range.");}

	template<typename T1>
	Range(const Range<T1>& range):Min((T)range.Min),Max((T)range.Max){}

	template<typename T1>
	explicit Range(T1 val):Min((T)val),Max((T)val){}

	template<typename T1>
	Range& operator=(const Range<T1>& range){Min=(T)range.Min;Max=(T)range.Max;return *this;}
	template<typename T1>
	Range& operator=(T1 val){Min=(T)val;Max=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Range<T1>& range)const{return Math::IsEqual(Min,range.Min)&&Math::IsEqual(Max,range.Max);}
	template<typename T1>
	bool operator!=(const Range<T1>& range)const{return !operator==(range);}
	template<typename T1>
	bool operator>(const Range<T1>& range)const{return Min>range.Min&&Max>range.Max;}
	template<typename T1>
	bool operator<(const Range<T1>& range)const{return Min<range.Min&&Max<range.Max;}
	template<typename T1>
	bool operator>=(const Range<T1>& range)const{return Min>=range.Min&&Max>=range.Max;}
	template<typename T1>
	bool operator<=(const Range<T1>& range)const{return Min<=range.Min&&Max<=range.Max;}

	intp GetHashCode()const{return HashUtility::Hash(Buffer);}

	
	void ExpandMin(T val)
	{
		if (Min>val)
		{
			Min=val;
		}
	}

	void ShrinkMin(T val)
	{
		if (Min<val)
		{
			Min=val;
		}
	}


	void ExpandMax(T val)
	{
		if (Max<val)
		{
			Max=val;
		}
	}
	
	void ShrinkMax(T val)
	{
		if (Max>val)
		{
			Max=val;
		}
	}

	void Expand(T val)
	{
		ExpandMin(val);
		ExpandMax(val);
	}

	void ExpandRange(T from,T to)
	{
		ExpandMin(from);
		ExpandMax(to);
	}

	void ExpandRangeFrom(T from,T to)
	{
		ExpandMin(from);
		Max=to;
	}

	
	bool Contains(T val)const
	{
		return val>=Min&&val<=Max;
	}
	void Reset()
	{
		Min=Math::Values<T>::Max;
		Max=Math::Values<T>::Min;
	}

	bool IsEmpty()const
	{
		return Min>=Max;
	}

	T Length()const
	{
		return Max-Min;
	}

	T Count()const
	{
		return Max-Min+1;
	}

	T GetMovement(T to)const
	{
		T d1=to-Min;
		T d2=to-Max;
		return (Math::Abs(d1)<Math::Abs(d2))?d1:d2;
	}
};

template<typename T>
WEAK_MULTIPLE_DEFINE const Range<T> Range<T>::Init;

//[PRE_DECLARE_BEGIN]
typedef Range<int> RangeI;
typedef Range<uint32> RangeU;

typedef Range<float> RangeF;
//[PRE_DECLARE_END]
MEDUSA_END;
