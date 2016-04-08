#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Memory/Memory.h"


MEDUSA_BEGIN;

template<typename T>
struct STLMapLessPtr
{
	inline bool operator()(const T& str1, const T& str2)const
	{
		return str1<str2;
	}
};

template<typename T>
struct STLMapLessPtrForPointer
{
	inline bool operator()(const T* t1, const T* t2)const
	{
		return t1->Compare(*t2)<0;
	}
};


template<typename T>
struct DefaultCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1<t2)
		{
			return -1;
		}
		else if (t2<t1)
		{
			return 1;
		}
		return 0;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1<t2;
	}
};

template<typename T>
struct CustomCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return t1.Compare(t2);
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1<t2;
	}
};


template<typename T>
struct DefaultCompareForPointer
{
	static int Compare(const T* t1, const T* t2)
	{
		if (*t1<*t2)
		{
			return -1;
		}
		else if (*t2<*t1)
		{
			return 1;
		}
		return 0;
	}

	inline bool operator()(const T* t1, const T* t2)const
	{
		return *t1<*t2;
	}
};

template<typename T>
struct CustomCompareForPointer
{
	static int Compare(const T* t1, const T* t2)
	{
		return t1->Compare(*t2);
	}

	inline bool operator()(const T* t1, const T* t2)const
	{
		return *t1<*t2;
	}
};

template<typename T>
struct InverseCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1<t2)
		{
			return 1;
		}
		else if (t2<t1)
		{
			return -1;
		}
		return 0;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1>t2;
	}
};

template<typename T>
struct InverseCustomCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return t1.Compare(t2);
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1>t2;
	}
};

template<typename T>
struct NoCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		return 0;
	}
};

template<typename T>
struct EqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1==t2)
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1==t2;
	}
};


template<typename T>
struct ObjectEqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1.Equals(t2))
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1.Equals(t2);
	}
};

template<typename T>
struct PointerEqualCompare
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static int Compare(TParameterType t1, TParameterType t2)
	{
		if (t1->Equals(*t2))
		{
			return 0;
		}
		return -1;
	}

	inline bool operator()(const T& t1, const T& t2)const
	{
		return t1->Equals(*t2);
	}
};

template<typename T>
struct DefaultHashCoder
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static intp GetHashCode(TParameterType key)
	{
		return GetHashCodeHelper(key,Compile::Bool2Type<Compile::TypeTraits<T>::IsArithmetic||Compile::TypeTraits<T>::IsPointer||Compile::TypeTraits<T>::IsEnum>());
	}

private:
	static intp GetHashCodeHelper(TParameterType key,Compile::Bool2Type<false> isStdArith)
	{
		return key.GetHashCode();
	}

	static intp GetHashCodeHelper(TParameterType key,Compile::Bool2Type<true> isStdArith)
	{
		return *(intp*)&key;
	}

};

template<typename T>
struct SafeEnumHashCoder
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static intp GetHashCode(T key)
	{
		return (int)key;
	}
};

template<typename T>
struct DefaultPointerHashCoder
{
	static intp GetHashCode(T key)
	{
		return key->GetHashCode();
	}
};

template<typename T>
struct DefaultDeleter
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static void Delete(TParameterType p)
	{
		Memory::Delete(p);
	}
};

template<typename T>
struct NoDeleter
{
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	static void Delete(TParameterType p)
	{
	}
};

template<typename TObject>
struct DefaultNewer
{
	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	static TObject New()
	{
		return new TObjectPointeeType();
	}

};

template<typename TId,typename TObject>
struct DefaultNewerById
{
	typedef typename Compile::TypeTraits<TId>::ParameterType TIdParameterType;
	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	static TObject New(TIdParameterType id)
	{
		return new TObjectPointeeType(id);
	}

};

MEDUSA_END;