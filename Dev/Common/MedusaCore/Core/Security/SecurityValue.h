#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Math/Random.h"

MEDUSA_BEGIN;
template<typename T,bool TIsResetKey>
class SecurityValueAutoUnlock;

template<typename T,bool TIsResetKey>
class SecurityValue
{
	friend class SecurityValueAutoUnlock<T,TIsResetKey>;
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
public:
	SecurityValue()
	{
		ResetKey();
		Lock();
	}
	~SecurityValue()
	{
		Unlock();
	}
	SecurityValue(TParameterType val){ResetKey();mValue=val;Lock();}
	SecurityValue(const SecurityValue& field){ResetKey();mValue=field.GetValue();Lock();}
	SecurityValue& operator=(const SecurityValue& field){SetValue(field.GetValue());return *this;}
	SecurityValue& operator=(TParameterType val){SetValue(val.GetValue());return *this;}
public:
	inline operator T()
	{
		Unlock();
		T temp=mValue;
		Lock();
		return temp;
	}

	T GetValue()const
	{
		Unlock();
		T temp=mValue;
		Lock();
		return temp;
	}

	void SetValue(TParameterType val) {Unlock();mValue = val; Lock();}
private:
	void ResetKey()
	{
		Random rand;
		MemoryByteData key=MemoryByteData::Alloc(sizeof(T));
		rand.NextBytes(key);
		mEncoder.SetKey(key);
		mDecoder.SetKey(key);
	}
	void Lock()
	{
		if (TIsResetKey)
		{
			ResetKey();
		}
		mEncoder.CodeInPlace(MemoryByteData::FromStatic(&mValue,sizeof(T)));
	}
	void Unlock(){mDecoder.CodeInPlace(MemoryByteData::FromStatic(&mValue,sizeof(T)));}

	const T& ForceGetValue()const{return mValue;}
	T& ForceGetValue(){return mValue;}
	void ForceSetValue(TParameterType val) { mValue = val;}

private:
	T mValue;
	XOREncoder mEncoder;
	XORDecoder mDecoder;
};

template<typename T,bool TIsResetKey=false>
class SecurityValueAutoUnlock
{
public:
	typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;

	SecurityValueAutoUnlock(SecurityValue<T,TIsResetKey>& val ):mValue(val)
	{
		mValue.Unlock();
	}
	~SecurityValueAutoUnlock()
	{
		mValue.Lock();
	}

	const T& GetValue()const{return mValue.ForceGetValue();}
	T& GetValue(){return mValue.ForceGetValue();}
	void SetValue(TParameterType val) { mValue.ForceSetValue(val);}
private:
	SecurityValue<T,TIsResetKey>& mValue;

};


MEDUSA_END;