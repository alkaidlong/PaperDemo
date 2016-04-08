#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename T>
	class SwapValue
	{
	public:
		typedef typename Compile::TypeTraits<T>::ParameterType TParameterType;
		typedef typename Compile::TypeTraits<T>::ReferenceType TReferenceType;
	public:
		SwapValue():mIsFront(true){}
		explicit SwapValue(TParameterType val):mFrontValue(val),mIsFront(true) {}
		SwapValue(const SwapValue& field){mFrontValue=field.mFrontValue;mBackValue=field.mBackValue;mIsFront=field.IsFront();}
		SwapValue& operator=(const SwapValue& field){mFrontValue=field.mFrontValue;mBackValue=field.mBackValue;mIsFront=field.IsFront();return *this;}
	public:
		bool IsFront() const { return mIsFront; }
		const T& FrontValue()const{return IsFront()?mFrontValue:mBackValue;}
		const T& BackValue()const{return IsFront()?mBackValue:mFrontValue;}

		T& FrontValue(){return IsFront()?mFrontValue:mBackValue;}
		T& BackValue(){return IsFront()?mBackValue:mFrontValue;}

		void Swap(){mIsFront=!mIsFront;}
	private:
		T mFrontValue;
		T mBackValue;
		bool mIsFront;
	};
}
MEDUSA_END;