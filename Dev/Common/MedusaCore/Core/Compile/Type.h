#pragma  once

#include "MedusaCorePreCompiled.h"


MEDUSA_BEGIN;
namespace Compile
{
	class NullType;
    
	class EmptyType
	{
		bool operator==(const EmptyType&)const
		{
			return true;
		}
        
		bool operator<(const EmptyType&)const
		{
			return false;
		}
        
		bool operator>(const EmptyType&)const
		{
			return false;
		}
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <int v>
	struct Int2Type
	{
		const static int Value = v;
	};
    
	template <bool v>
	struct Bool2Type
	{
		const static bool Value = v;
	};
    
	template <typename T>
	struct Type2Type
	{
		typedef T OriginalType;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template<typename T,T val>
	struct IntegralConstant
	{
		const static T Value=val;
		typedef T ValueType;
		typedef IntegralConstant<T,val> Type;
		operator T()const{return val;}
	};
    
	typedef IntegralConstant<bool,true> TrueType;
	typedef IntegralConstant<bool,false> FalseType;
    
	//////////////////////////////////////////////////////////////////////////
	template<bool cond,class T = void>
	struct EnableIf	//[IGNORE_PRE_DECLARE]
	{	// type is undefined for assumed !cond
	};

	template<class T>
	struct EnableIf<true, T>	//[IGNORE_PRE_DECLARE]
	{	// type is T for cond
		typedef T Type;
	};


	template<bool cond,class T = void>
	struct DisableIf	//[IGNORE_PRE_DECLARE]
	{	// type is undefined for assumed !cond
	};

	template<class T>
	struct DisableIf<false, T>	//[IGNORE_PRE_DECLARE]
	{	// type is T for cond
		typedef T Type;
	};

	//////////////////////////////////////////////////////////////////////////
	template<bool test,typename T>
	struct If
	{
        
	};
    
	template<typename T>
	struct If<true,T>
	{
		typedef T Result;
	};
	//////////////////////////////////////////////////////////////////////////
	template <bool flag, typename T1, typename T2>
	struct IfElse
	{
		typedef T1 Result;
	};
    
	template <typename T1, typename T2>
	struct IfElse<false, T1, T2>
	{
		typedef T2 Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
    
	template <typename T1, typename T2>
	struct IsSameType:public FalseType
	{
		
	};
    
	template <typename T>
	struct IsSameType<T,T>:public TrueType
	{
		
	};
	
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct RemoveConst
	{
		typedef T Result;
	};
    
	template <class T>
	struct RemoveConst<const T>
	{
		typedef T Result;
	};
    
	template <class T>
	struct RemoveConst<const T[]>
	{
		typedef T Result[];
	};
    
	template <class T,size_t N>
	struct RemoveConst<const T[N]>
	{
		typedef T Result[N];
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct AddConst
	{
		typedef const typename RemoveConst<T>::Result  Result;
	};
    
	template <class T>
	struct AddConst<T&>
	{
		typedef const T& Result;
	};
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct RemoveVolatile
	{
		typedef T Result;
	};
    
	template <class T>
	struct RemoveVolatile<volatile T>
	{
		typedef T Result;
	};
    
	template <class T>
	struct RemoveVolatile<volatile T[]>
	{
		typedef T Result[];
	};
    
	template <class T,size_t N>
	struct RemoveVolatile<volatile T[N]>
	{
		typedef T Result[N];
	};
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct AddVolatile
	{
		typedef volatile typename RemoveVolatile<T>::Result Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct RemoveConstVolatile
	{
		typedef typename RemoveConst<typename RemoveVolatile<T>::Result>::Result Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct AddConstVolatile
	{
		typedef typename AddConst<typename AddVolatile<T>::Result>::Result Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct RemoveReference
	{
		typedef T Result;
	};
    
	template <class T>
	struct RemoveReference<T &>
	{
		typedef T Result;
	};
    /*
	template <class T>
	struct RemoveReference<T&&>
	{
		typedef T Result;
	};
	*/
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	struct AddReference
	{
		typedef typename RemoveReference<T>::Result& Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct RemovePointer
	{
		typedef T Result;
	};
    
	template <typename T>
	struct RemovePointer<T*>
	{
		typedef T Result;
	};
    
	template <typename T>
	struct RemovePointer<T*const>
	{
		typedef T Result;
	};
    
	template <typename T>
	struct RemovePointer<T*volatile>
	{
		typedef T Result;
	};
    
	template <typename T>
	struct RemovePointer<T*const volatile>
	{
		typedef T Result;
	};
	//////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct AddPointer
	{
		typedef typename RemoveReference<T>::Result* Result;
	};
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct RemoveExtent
	{
		typedef T Result;
	};
    
	template<typename T,unsigned int N>
	struct RemoveExtent<T[N]>
	{
		typedef T Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct RemoveAllExtents
	{
		typedef T Result;
	};
    
	template<typename T,unsigned int N>
	struct RemoveAllExtents<T[N]>
	{
		typedef typename RemoveAllExtents<T>::Result Result;
	};
    
	template<typename T>
	struct RemoveAllExtents<T[]>
	{
		typedef typename RemoveAllExtents<T>::Result Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	template <class U>
	struct AddParameterType
	{
		typedef const U& Result;
	};
    
	template <class U>
	struct AddParameterType<U &>
	{
		typedef U& Result;
	};
    
	template <>
	struct AddParameterType<void>
	{
		typedef NullType Result;
	};
    
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<typename T> struct _IsIntegral:public FalseType{};
		template<> struct _IsIntegral<bool>:public TrueType{};
		template<> struct _IsIntegral<char>:public TrueType{};
		template<> struct _IsIntegral<unsigned char>:public TrueType{};
		template<> struct _IsIntegral<wchar_t>:public TrueType{};
		template<> struct _IsIntegral<short>:public TrueType{};
		template<> struct _IsIntegral<unsigned short>:public TrueType{};
		template<> struct _IsIntegral<int>:public TrueType{};
		template<> struct _IsIntegral<unsigned int>:public TrueType{};
		template<> struct _IsIntegral<long>:public TrueType{};
		template<> struct _IsIntegral<unsigned long>:public TrueType{};
		template<> struct _IsIntegral<long long>:public TrueType{};
		template<> struct _IsIntegral<unsigned long long>:public TrueType{};
	}
	
	template<typename T> struct IsIntegral:public Private::_IsIntegral<typename RemoveConstVolatile<T>::Result>{};
    
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<typename T> struct _IsVoid:public FalseType{};
		template<> struct _IsVoid<void>:public TrueType{};
	}
	template<typename T> struct IsVoid:public Private::_IsVoid<typename RemoveConstVolatile<T>::Result>{};
    
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<typename T> struct _IsFloatingPoint:public FalseType{};
		template<> struct _IsFloatingPoint<float>:public TrueType{};
		template<> struct _IsFloatingPoint<double>:public TrueType{};
	}
    
	template<typename T> struct IsFloatingPoint:public Private::_IsFloatingPoint<typename RemoveConstVolatile<T>::Result>{};
	//////////////////////////////////////////////////////////////////////////
	template<typename T> struct IsNumeric:public IfElse<IsIntegral<T>::Value||IsFloatingPoint<T>::Value,TrueType,FalseType>::Result{};
    
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<typename T> struct _IsArray:public FalseType{};
		template<typename T> struct _IsArray<T[]>:public TrueType{};
		template<typename T,unsigned int N> struct _IsArray<T[N]>:public TrueType{};
        
	}
	template<typename T> struct IsArray:public Private::_IsArray<typename RemoveConstVolatile<T>::Result>{};
	//////////////////////////////////////////////////////////////////////////
    
	namespace Private
	{
		template <class T> struct _IsMemberObject:public FalseType{};
		template <class T1,class T2> struct _IsMemberObject<T1 T2::*>:public TrueType{};
	}
	
	template <class T> struct IsMemberObject:public Private::_IsMemberObject<typename RemoveConstVolatile<T>::Result>{};
    
	//////////////////////////////////////////////////////////////////////////
    
#pragma region IsFunction
	template <typename T>
	struct IsFunction
	{
		const static bool Value =false;
	};
    
    
#define DEFINE_TEMPLATE_TYPENAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N))  typename T##N
#define DEFINE_TEMPLATE_TYPENAME(N, T)			MACRO_IF_ELSE(N,DEFINE_TEMPLATE_TYPENAME_1(N,T),MACRO_EMPTY)
    
#define DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL_HELPER(N,P) 							 \
template <typename T, MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T)>		 \
struct IsFunction<T(*)(MACRO_REPEAT_PARAM(N, T))>				 \
{																		 \
const static bool Value=true;										 \
};
    
#define DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL(N, P)			MACRO_IF_ELSE(N,DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL_HELPER(N,P),MACRO_EMPTY)
    
#ifdef WIN32
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL,MACRO_EMPTY);
#else
	//BEGIN_AUTO_GENERATE_FUNCTION_POINTER_RAW
template <typename T, typename T1> struct IsFunction<T(*)( T1)> { const static bool Value=true; };
template <typename T, typename T1, typename T2> struct IsFunction<T(*)( T1, T2)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3> struct IsFunction<T(*)( T1, T2, T3)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4> struct IsFunction<T(*)( T1, T2, T3, T4)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsFunction<T(*)( T1, T2, T3, T4, T5)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8, T9)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> { const static bool Value=true; };
//END_AUTO_GENERATE_FUNCTION_POINTER_RAW
#endif
    
    
    
#define DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS_HELPER(N,P) 							 \
template <typename T, MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T)>		 \
struct IsFunction<T(*)(MACRO_REPEAT_PARAM(N, T) MACRO_COMMA_IF(N) ...)>				 \
{																		 \
const static bool Value=true;										 \
};
#define DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS(N, P)			MACRO_IF_ELSE(N,DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS_HELPER(N,P),MACRO_EMPTY)

#ifdef WIN32
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS,MACRO_EMPTY);
#else
	//BEGIN_AUTO_GENERATE_FUNCTION_POINTER_RAW_VAR
template <typename T, typename T1> struct IsFunction<T(*)( T1 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2> struct IsFunction<T(*)( T1, T2 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3> struct IsFunction<T(*)( T1, T2, T3 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4> struct IsFunction<T(*)( T1, T2, T3, T4 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsFunction<T(*)( T1, T2, T3, T4, T5 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8, T9 , ...)> { const static bool Value=true; };
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsFunction<T(*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 , ...)> { const static bool Value=true; };
//END_AUTO_GENERATE_FUNCTION_POINTER_RAW_VAR
#endif
    
    
#pragma endregion IsFunction
    
#pragma region IsMemberFunction
    
	template <typename T>
	struct IsMemberFunction
	{
		const static bool Value=false;
	};
    
#define DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL_HELPER(N,P) 							 \
template <typename T,typename S, MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T)>		 \
struct IsMemberFunction<T (S::*)(MACRO_REPEAT_PARAM(N, T)) P>				 \
{																		 \
const static bool Value=true;										 \
};

#define DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL(N, P)			MACRO_IF_ELSE(N,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL_HELPER(N,P),MACRO_EMPTY)

    
#ifdef WIN32
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL,MACRO_EMPTY);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL,const);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL,volatile);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL,const volatile);
#else
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) > { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VOLATILE
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) volatile> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VOLATILE
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VOLATILE
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) const volatile> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VOLATILE
#endif
    
    
    
    
    
#define DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS_HELPER(N,P) 							 \
template <typename T,typename S, MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T)>		 \
struct IsMemberFunction<T (S::*)(MACRO_REPEAT_PARAM(N, T) MACRO_COMMA_IF(N) ...) P>				 \
{																		 \
const static bool Value=true;										 \
};
    
#define DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS(N, P)			MACRO_IF_ELSE(N,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS_HELPER(N,P),MACRO_EMPTY)

#ifdef WIN32
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS,MACRO_EMPTY);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS,const);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS,volatile);
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS,const volatile);
#else
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VAR
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9 , ...) > { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 , ...) > { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VAR
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VAR
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9 , ...) const> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 , ...) const> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VAR
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VOLATILE_VAR
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9 , ...) volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 , ...) volatile> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_VOLATILE_VAR
    
	//BEGIN_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VOLATILE_VAR
template <typename T,typename S, typename T1> struct IsMemberFunction<T (S::*)( T1 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2> struct IsMemberFunction<T (S::*)( T1, T2 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3> struct IsMemberFunction<T (S::*)( T1, T2, T3 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9 , ...) const volatile> { const static bool Value=true; };
template <typename T,typename S, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct IsMemberFunction<T (S::*)( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10 , ...) const volatile> { const static bool Value=true; };
//END_AUTO_GENERATE_MEMBER_FUNCTION_POINTER_CONST_VOLATILE_VAR
#endif
    
    
    
    
    
#pragma endregion IsMemberFunction
    
    
	//////////////////////////////////////////////////////////////////////////
	template<typename T> struct IsReference:public FalseType{};
	template<typename T> struct IsReference<T&>:public TrueType{};
    
    
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<typename T> struct _IsPointer:public FalseType{};
		template<typename T> struct _IsPointer<T*>:public IfElse<!IsMemberObject<T>::Value&&!IsMemberFunction<T>::Value,TrueType,FalseType>::Result{};
	}
    
	template <typename T> struct IsPointer:public Private::_IsPointer<typename RemoveConstVolatile<T>::Result>{};
	//////////////////////////////////////////////////////////////////////////
    
	template<typename T>
	struct IsArithmetic:public IfElse<IsIntegral<T>::Value||IsFloatingPoint<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T>
	struct IsFundamental:public IfElse<IsArithmetic<T>::Value||IsVoid<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T>
	struct IsCompound:public IfElse<!IsFundamental<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T>
	struct IsMemberPointer:public IfElse<IsMemberObject<T>::Value||IsMemberFunction<T>::Value,TrueType,FalseType>::Result{};
    
	//////////////////////////////////////////////////////////////////////////
    

	typedef char (& NoType )[1];
	typedef char (& YesType)[2];
	//struct AcceptIntType { AcceptIntType(int); };
	struct AcceptIntType64 { AcceptIntType64(int64); };

    
	NoType TestIntConversion(...);
	//YesType TestIntConversion(AcceptIntType);
	YesType TestIntConversion(int);
	NoType TestIntConversion(int64);
	NoType TestIntConversion(uint32);
	NoType TestIntConversion(uint64);
	NoType TestIntConversion(float);
	NoType TestIntConversion(double);
    NoType TestIntConversion(size_t);


    
	NoType TestIntPtrConversion(const volatile char *);
	NoType TestIntPtrConversion(const volatile short *);
	NoType TestIntPtrConversion(const volatile int *);
	NoType TestIntPtrConversion(const volatile long *);
	NoType TestIntPtrConversion(const volatile double *);
	NoType TestIntPtrConversion(const volatile float *);
	NoType TestIntPtrConversion(const volatile bool *);
	YesType TestIntPtrConversion(const volatile void *);
	template <typename T> T* AddPtr(T&);
    
	template <typename T>
	struct IsEnum
	{
    private:
		static T arg;
    public:
		const static bool Value=sizeof(TestIntConversion(arg))==sizeof(YesType)&&sizeof(TestIntPtrConversion(AddPtr(arg)))==sizeof(YesType);

	};

    
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct IsScalar:public IfElse<IsArithmetic<T>::Value||IsEnum<T>::Value||IsPointer<T>::Value||IsMemberPointer<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T>
	struct IsScalar<T&>:public FalseType{};
	//////////////////////////////////////////////////////////////////////////
	namespace Private
	{
		template<class T>
		struct PointerTraits
		{	// basic definition
		};
        
		template<class T>
		struct PointerTraits<T *>
		{	// pointer properties
			static const bool IsConst = false;
			static const bool IsVolatile = false;
		};
        
		template<class T>
		struct PointerTraits<const T *>
		{	// pointer to const properties
			static const bool IsConst = true;
			static const bool IsVolatile = false;
		};
        
		template<class T>
		struct PointerTraits<volatile T *>
		{	// pointer to volatile properties
			static const bool IsConst = false;
			static const bool IsVolatile = true;
		};
        
		template<class T>
		struct PointerTraits<const volatile T *>
		{	// pointer to const volatile properties
			static const bool IsConst = true;
			static const bool IsVolatile = true;
		};
	}
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct IsConst:public IfElse<Private::PointerTraits<T*>::IsConst&&!IsFunction<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T,size_t N>
	struct IsConst<T[N]>:public FalseType{};
    
	template<typename T,size_t N>
	struct IsConst<const T[N]>:public TrueType{};
    
	template<typename T>
	struct IsConst<T&>:public FalseType{};
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct IsVolatile:public IfElse<Private::PointerTraits<T*>::IsVolatile&&!IsFunction<T>::Value,TrueType,FalseType>::Result{};
    
	template<typename T,size_t N>
	struct IsVolatile<T[N]>:public FalseType{};
    
	template<typename T,size_t N>
	struct IsVolatile<const T[N]>:public TrueType{};
    
	template<typename T>
	struct IsVolatile<T&>:public FalseType{};
	//////////////////////////////////////////////////////////////////////////
	template <class TFrom, class TTo>
	struct ConversionFromTo
	{
	private:
		struct ConversionFromToHelper
		{
			typedef char Small;
			struct Big { char dummy[2]; };
			static Big   Test(...);
			static Small Test(TTo);
			static TFrom MakeTFrom();
		};
	public:
		const static bool IsExists = sizeof(typename ConversionFromToHelper::Small) == sizeof((ConversionFromToHelper::Test(ConversionFromToHelper::MakeTFrom())));
		const static bool IsExists2Way = IsExists && ConversionFromTo<TTo, TFrom>::IsExists;
		const static bool IsSameType = false;
	};
    
	template <class TFrom>
	struct ConversionFromTo<TFrom, TFrom>
	{
		const static bool IsExists =true;
		const static bool IsExists2Way = true;
		const static bool IsSameType = true;
	};
    
	template <class TFrom>
	struct ConversionFromTo<void, TFrom>
	{
		const static bool IsExists =false;
		const static bool IsExists2Way = false;
		const static bool IsSameType = false;
	};
    
	template <class TFrom>
	struct ConversionFromTo<TFrom,void>
	{
		const static bool IsExists =false;
		const static bool IsExists2Way = false;
		const static bool IsSameType = false;
	};
    
	template <>
	struct ConversionFromTo<void,void>
	{
		const static bool IsExists =false;
		const static bool IsExists2Way = false;
		const static bool IsSameType = false;
	};
    
	//////////////////////////////////////////////////////////////////////////
    
	template <class TSuper, class TSub>
	struct IsSuperSubclass
	{
	private:
		const static bool mDontUseWithIncompleteTypes=sizeof(TSuper)==sizeof(TSub);
	public:
		const static bool Value =!Compile::ConversionFromTo<const volatile TSuper*, const volatile void*>::IsSameType &&
        Compile::ConversionFromTo<const volatile TSub*, const volatile TSuper*>::IsExists;
	};
    
	template <>
	struct IsSuperSubclass<void, void>
	{
		const static bool Value=false;
	};
    
	template <class TSuper>
	struct IsSuperSubclass<TSuper, void>
	{
		const static bool Value=false;
	};
    
	template <class TSub>
	struct IsSuperSubclass<void, TSub>
	{
		const static bool Value=false;
	};
    
#define IS_SUPER_SUB_CLASS(TSuper, TSub) (Compile::IsSuperSubclass<TSuper,TSub>::Value)
    
	template <class TSuper, class TSub>
	struct IsSuperSubclassStrict
	{
	private:
		const static bool mDontUseWithIncompleteTypes=sizeof(TSuper)==sizeof(TSub);
	public:
		const static bool Value =!Compile::ConversionFromTo<const volatile TSuper*, const volatile void*>::IsSameType &&
        !Compile::ConversionFromTo<const volatile TSuper*, const volatile TSub*>::IsSameType&&
        Compile::ConversionFromTo<const volatile TSub*, const volatile TSuper*>::IsExists;
	};
    
	template <>
	struct IsSuperSubclassStrict<void, void> 
	{
		const static bool Value=false;
	};
    
	template <class TSuper>
	struct IsSuperSubclassStrict<TSuper, void> 
	{
		const static bool Value=false;
	};
    
	template <class TSub>
	struct IsSuperSubclassStrict<void, TSub> 
	{
		const static bool Value=false;
	};
    
#define IS_SUPER_SUB_CLASS_STRICT(TSuper, TSub) (Compile::IsSuperSubclassStrict<TSuper,TSub>::Value)
    
    
	// traits to construct default return value
	// and avoid "invalid value-initialization of reference types" error in GCC when return type is reference
	template <typename T>
	struct ConstructDefault
	{
		static T Construct()
		{
			return T();
		}
	};
    
	template <typename T> 
	struct ConstructDefault <T &>
	{
		static T & Construct() 
		{
			return *static_cast<T *>(0); 
		}
	};
}

#undef DEFINE_TEMPLATE_TYPENAME
#undef DEFINE_TEMPLATE_TYPENAME_1

//#undef DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL_HELPER
//#undef DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_NORMAL
//#undef DEFINE_IS_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS
//#undef DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_NORMAL
//#undef DEFINE_IS_MEMBER_FUNCTION_POINTER_RAW_CLASS_VAR_ARGS

MEDUSA_END;

