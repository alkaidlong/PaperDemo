#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
namespace Pattern
{
	struct IOverrideValue
	{
		virtual uint GetIndex()const=0;
		virtual void Apply()=0;
		virtual bool IsOverride()const=0;
	};

	template<typename T,uint TIndex>
	class OverrideValue:public IOverrideValue
	{
	public:
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
		const static uint Index=TIndex;
		virtual uint GetIndex()const{return TIndex;}
	public:
		OverrideValue():mIsOverride(false){}
		explicit OverrideValue(TParameterType val):mValue(val),mIsOverride(false) {}
		OverrideValue(const OverrideValue& field){mValue=field.mValue;mOverrideValue=field.mOverrideValue;mIsOverride=field.IsOverride();}
		OverrideValue& operator=(const OverrideValue& field){mValue=field.mValue;mOverrideValue=field.mOverrideValue;mIsOverride=field.IsOverride();return *this;}
		OverrideValue& operator=(TParameterType val){mOverrideValue=val;mIsOverride=mOverrideValue!=mValue;return *this;}

		operator T()const{return IsOverride()?mOverrideValue:mValue;}

		operator T&(){return IsOverride()?mOverrideValue:mValue;}

		bool operator==(const OverrideValue& val)const{return Value()==val.Value();}
		bool operator!=(const OverrideValue& val)const{return Value()!=val.Value();}
		bool operator>(const OverrideValue& val)const{return Value()>val.Value();}
		bool operator>=(const OverrideValue& val)const{return Value()>=val.Value();}
		bool operator<(const OverrideValue& val)const{return Value()<val.Value();}
		bool operator<=(const OverrideValue& val)const{return Value()<=val.Value();}

		/*bool operator==(TParameterType val)const{return Value()==val;}
		bool operator!=(TParameterType val)const{return Value()!=val;}
		bool operator>(TParameterType val)const{return Value()>val;}
		bool operator>=(TParameterType val)const{return Value()>=val;}
		bool operator<(TParameterType val)const{return Value()<val;}
		bool operator<=(TParameterType val)const{return Value()<=val;}*/
	public:
		virtual bool IsOverride() const { return mIsOverride; }
		const T& Value()const{return IsOverride()?mOverrideValue:mValue;}
		void SetOverriedValue(TParameterType val) { mOverrideValue = val;mIsOverride=mOverrideValue!=mValue;}

		void ForceSetValue(TParameterType val) { mValue = val; mOverrideValue=mValue;mIsOverride=false;}

		const T& ForceGetValueReference()const{return mValue;}
		T& ForceGetValueReference(){return mValue;}

		const T* ForceGetValuePointer()const{return &mValue;}
		T* ForceGetValuePointer(){return &mValue;}

		virtual void Apply(){if(mIsOverride){mValue=mOverrideValue;mIsOverride=false;}}

	private:
		T mValue;
		T mOverrideValue;
		bool mIsOverride;
	};
}
MEDUSA_END;