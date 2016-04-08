#pragma once

#include "Core/Compile/TypeList.h"
MEDUSA_BEGIN;
namespace Compile
{
	////////////////////////////////////////////////////////////////////////////////
	// class template TypeTraits
	//
	// Figures out at compile time various properties of any given type
	// Invocations (T is a type, TypeTraits<T>::Property):
	//
	// - isPointer       : returns true if T is a pointer type
	// - PointeeType     : returns the type to which T points if T is a pointer 
	//                     type, NullType otherwise
	// - isReference     : returns true if T is a reference type
	// - ReferredType    : returns the type to which T refers if T is a reference 
	//                     type, NullType otherwise
	// - isMemberPointer : returns true if T is a pointer to member type
	// - isStdUnsignedInt: returns true if T is a standard unsigned integral type
	// - isStdSignedInt  : returns true if T is a standard signed integral type
	// - isStdIntegral   : returns true if T is a standard integral type
	// - isStdFloat      : returns true if T is a standard floating-point type
	// - isStdArith      : returns true if T is a standard arithmetic type
	// - isStdFundamental: returns true if T is a standard fundamental type
	// - isUnsignedInt   : returns true if T is a unsigned integral type
	// - isSignedInt     : returns true if T is a signed integral type
	// - isIntegral      : returns true if T is a integral type
	// - isFloat         : returns true if T is a floating-point type
	// - isArith         : returns true if T is a arithmetic type
	// - isFundamental   : returns true if T is a fundamental type
	// - ParameterType   : returns the optimal type to be used as a parameter for 
	//                     functions that take Ts
	// - isConst         : returns true if T is a const-qualified type
	// - NonConstType    : Type with removed 'const' qualifier from T, if any
	// - isVolatile      : returns true if T is a volatile-qualified type
	// - NonVolatileType : Type with removed 'volatile' qualifier from T, if any
	// - NonConstVolatileType : Type with removed 'const' and 'volatile' qualifiers from 
	//                     T, if any
	// - ParameterType   : returns the optimal type to be used as a parameter 
	//                       for functions that take 'const T's
	//
	////////////////////////////////////////////////////////////////////////////////

	template <typename T>
	class TypeTraits
	{
	public:
		typedef typename AddConst<T>::Result ConstType;
		typedef typename AddVolatile<T>::Result VolatileType;
		typedef typename AddConst<VolatileType>::Result ConstVolatileType;

		typedef typename RemoveConst<T>::Result NonConstType;
		typedef typename RemoveVolatile<T>::Result NonVolatileType;
		typedef typename RemoveConstVolatile<T>::Result NonConstVolatileType;

		typedef typename AddPointer<T>::Result PointerType;
		typedef typename AddReference<T>::Result ReferenceType;

		typedef typename RemovePointer<T>::Result PointeeType;
		typedef typename RemoveReference<T>::Result ReferredType;
		typedef typename RemovePointer<ReferredType>::Result DirectType;
		typedef typename RemoveConstVolatile<DirectType>::Result UnderlyingType;



		typedef typename AddConst<PointerType>::Result ConstPointerType;
		typedef typename AddConst<ReferenceType>::Result ConstReferenceType;

		typedef typename AddVolatile<PointerType>::Result VolatilePointerType;
		typedef typename AddVolatile<ReferenceType>::Result VolatileReferenceType;


		const static bool IsConst =Compile::IsConst<T>::Value;
		const static bool IsVolatile =Compile::IsVolatile<T>::Value;

		const static bool IsReference =Compile::IsReference<T>::Value;
		const static bool IsFunction =Compile::IsFunction<T>::Value;
		const static bool IsMemberFunction=Compile::IsMemberFunction<T>::Value;
		const static bool IsMemberPointer= Compile::IsMemberPointer<T>::Value;
		const static bool IsPointer=Compile::IsPointer<T>::Value;


		const static bool IsIntegral=Compile::IsIntegral<T>::Value;
		const static bool IsFloatingPoint=Compile::IsFloatingPoint<T>::Value;
		const static bool IsNumeric=Compile::IsNumeric<T>::Value;
		const static bool IsArithmetic=Compile::IsArithmetic<T>::Value;
		const static bool IsFundamental=Compile::IsFundamental<T>::Value;

#ifdef MEDUSA_CPP11
#ifdef MEDUSA_IOS
        const static bool IsPOD= std::is_pod<T>::value;
		const static bool IsEnum= Compile::IsEnum<T>::Value;
#else
        const static bool IsPOD= std::is_pod<T>::value;
		const static bool IsEnum= Compile::IsEnum<T>::Value&&std::is_enum<T>::value;
#endif

#else
		const static bool IsPOD= IsArithmetic||IsPointer;
		const static bool IsEnum= Compile::IsEnum<T>::Value;
#endif
		
		typedef typename IfElse<IsArithmetic || IsPointer || IsMemberPointer, T, typename AddParameterType<T>::Result>::Result ParameterType;
		typedef typename IfElse<IsArithmetic || IsPointer || IsMemberPointer,ConstType ,ConstReferenceType>::Result ConstReturnType;
		typedef typename IfElse<IsArithmetic || IsPointer || IsMemberPointer,T ,ReferenceType>::Result ReturnType;
	};
}

MEDUSA_END;