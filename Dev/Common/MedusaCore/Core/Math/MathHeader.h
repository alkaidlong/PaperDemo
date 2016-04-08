#pragma once
#include "MedusaCorePreCompiled.h"
MEDUSA_BEGIN;

namespace Math
{
	static float Floor(float x);
	/*

	value   round   floor   ceil    trunc
		-----   -----   -----   ----    -----
		2.3     2.0     2.0     3.0     2.0
		3.8     4.0     3.0     4.0     3.0
		5.5     6.0     5.0     6.0     5.0
		-2.3    -2.0    -3.0    -2.0    -2.0
		-3.8    -4.0    -4.0    -3.0    -3.0
		-5.5    -6.0    -6.0    -5.0    -5.0

	*/

#pragma region Values

	template<typename T>
	struct Values	//[IGNORE_PRE_DECLARE]
	{
		const static T Min;
		const static T Max;
	};

	template<> WEAK_MULTIPLE_DEFINE const byte Values<byte>::Min=(byte)0x00;
	template<> WEAK_MULTIPLE_DEFINE const char Values<char>::Min=(char)0x80;
	template<> WEAK_MULTIPLE_DEFINE const short Values<short>::Min=(short)0x8000;
	template<> WEAK_MULTIPLE_DEFINE const ushort Values<ushort>::Min=(ushort)0x0000;
	template<> WEAK_MULTIPLE_DEFINE const int Values<int>::Min=(int)0x80000000;
	template<> WEAK_MULTIPLE_DEFINE const uint Values<uint>::Min=(uint)0x00000000;
	template<> WEAK_MULTIPLE_DEFINE const float Values<float>::Min=FLT_MIN;
	template<> WEAK_MULTIPLE_DEFINE const double Values<double>::Min=DBL_MIN;

	template<> WEAK_MULTIPLE_DEFINE const byte Values<byte>::Max=(byte)0xFF;
	template<> WEAK_MULTIPLE_DEFINE const char Values<char>::Max=(char)0x7F;
	template<> WEAK_MULTIPLE_DEFINE const short Values<short>::Max=(short)0x7FFF;
	template<> WEAK_MULTIPLE_DEFINE const ushort Values<ushort>::Max=(ushort)0xFFFF;
	template<> WEAK_MULTIPLE_DEFINE const int Values<int>::Max=(int)0x7FFFFFFF;
	template<> WEAK_MULTIPLE_DEFINE const uint Values<uint>::Max=(uint)0xFFFFFFFF;
	template<> WEAK_MULTIPLE_DEFINE const float Values<float>::Max=FLT_MAX;
	template<> WEAK_MULTIPLE_DEFINE const double Values<double>::Max=DBL_MAX;


	const static  float Pi=3.14159265358979323846f;
	const static  float PiHalf=1.570796326794897f;
	const static  float Pi2=6.28318530717958647692f;
	const static  float PiInverse=0.3183098861837907f;
	const static  float Pi2Inverse=0.1591549430918953f;
	const static  float E=2.7182818284590451f;
	const static  float Sqrt2=1.414213562373095f;
	const static  float FloatCompareEpsilon=0.0001f;
	const static  double DoubleCompareEpsilon=0.0001f;
	const static  float FloatMaxValue=FLT_MAX;
	const static  float FloatMinValue=FLT_MIN;
	const static  double DoubleMaxValue=DBL_MAX;
	const static  double DoubleMinValue=DBL_MIN;



	const static byte ByteMaxValue=(byte)0xFF;
	const static byte ByteMinValue=(byte)0x00;
	const static char CharMaxValue=(char)0x7F;
	const static char CharMinValue=(char)0x80;
	const static short ShortMaxValue=(short)0x7FFF;
	const static short ShortMinValue=(short)0x8000;
	const static ushort UShortMaxValue=(ushort)0xFFFF;
	const static ushort UShortMinValue=(ushort)0x0000;
	const static int IntMaxValue=(int)0x7FFFFFFF;
	const static int IntMinValue=(int)0x80000000;
	const static uint UIntMaxValue=(uint)0xFFFFFFFF;
	const static uint UIntMinValue=(uint)0x00000000;

#pragma endregion Values

	template <typename T>
	FORCE_INLINE static T Sign(T val)
	{
		if (val>(T)0)
		{
			return (T)1;
		}
		else if(val<(T)0)
		{
			return (T)(-1);
		}
		return (T)0;
	}

	template <typename T>
	FORCE_INLINE static T InverseSign(T val)
	{
		return -Sign(val);
	}

	

	template <typename T>
	FORCE_INLINE static bool IsPowerOfTwo(T val)
	{
		return (val&(val-1))==0;
	}

	template <typename T1,typename T2>
	FORCE_INLINE static bool IsEqual(T1 left,T2 right)
	{
		return left==right;
	}

    template <typename T1,typename T2>
	FORCE_INLINE static bool IsEqualSign(T1 left,T2 right)
	{
		return IsEqual<T1,T2>(Sign<T1>(left),Sign<T2>(right));
	}
    
	template <typename T>
	FORCE_INLINE static T Compare(T left,T right)
	{
		return left-right;
	}


	template <typename T1,typename T2,typename T3>
	FORCE_INLINE static bool IsEqualEpsilon(T1 left,T2 right,T3 epsilon)
	{
		T3 delta=left-right;
		if (delta<0)
		{
			delta=-delta;
		}
		return delta<epsilon;
	}



	template <typename T>
	FORCE_INLINE static bool IsZero(T val)
	{
		return val==(T)0;
	}



	template <typename T> FORCE_INLINE static T Max(T left,T right){return left>right?left:right;}
	template <typename T> FORCE_INLINE static T Max3(T p1,T p2,T p3){return Max(Max(p1,p2),p3);}
	template <typename T> FORCE_INLINE static T Max4(T p1,T p2,T p3,T p4){return Max(Max3(p1,p2,p3),p4);}
	template <typename T> FORCE_INLINE static T Max5(T p1,T p2,T p3,T p4,T p5){return Max(Max4(p1,p2,p3,p4),p5);}
	template <typename T> FORCE_INLINE static T Max6(T p1,T p2,T p3,T p4,T p5,T p6){return Max(Max5(p1,p2,p3,p4,p5),p6);}
	template <typename T> FORCE_INLINE static T Max7(T p1,T p2,T p3,T p4,T p5,T p6,T p7){return Max(Max6(p1,p2,p3,p4,p5,p6),p7);}
	template <typename T> FORCE_INLINE static T Max8(T p1,T p2,T p3,T p4,T p5,T p6,T p7,T p8){return Max(Max7(p1,p2,p3,p4,p5,p6,p7),p8);}


	template <typename T> FORCE_INLINE static T Min(T left,T right){return left<right?left:right;}
	template <typename T> FORCE_INLINE static T Min3(T p1,T p2,T p3){return Min(Min(p1,p2),p3);}
	template <typename T> FORCE_INLINE static T Min4(T p1,T p2,T p3,T p4){return Min(Min3(p1,p2,p3),p4);}
	template <typename T> FORCE_INLINE static T Min5(T p1,T p2,T p3,T p4,T p5){return Min(Min4(p1,p2,p3,p4),p5);}
	template <typename T> FORCE_INLINE static T Min6(T p1,T p2,T p3,T p4,T p5,T p6){return Min(Min5(p1,p2,p3,p4,p5),p6);}
	template <typename T> FORCE_INLINE static T Min7(T p1,T p2,T p3,T p4,T p5,T p6,T p7){return Min(Min6(p1,p2,p3,p4,p5,p6),p7);}
	template <typename T> FORCE_INLINE static T Min8(T p1,T p2,T p3,T p4,T p5,T p6,T p7,T p8){return Min(Min7(p1,p2,p3,p4,p5,p6,p7),p8);}


	template <typename T>
	FORCE_INLINE static void Swap(T& a,T& b)
	{
		T temp=a;
		a=b;
		b=temp;
	}
#pragma region Trigonometric
	/*
	cosx=1-(x^2)/(2!)+(x^4)/(4!)-(x^6)/(6!)+...    x属于（负无穷，正无穷）
	sinx=x-(x^3)/(3!)+(x^5)/(5!)-(x^7)/(7!)+...    x属于（负无穷，正无穷）

	递归：sin(x)=x*term(n)
	term(n)=1-x^2/(2n+2)/(2n+3)*term(n+1)

	cos(x)=term(n)
	term(n)=1-x^2/(2n+1)/(2n+2)*term(n+1)

	TODO: it has the same performce as system sin() even in VS release mode. it's strange that we have to profile it in IOS system again.
	*/

	template<const double& R>
	struct CompileSinHelper
	{
		FORCE_INLINE static double sin()
		{
			const double Rsqr=R*R;
			return R*(1.0-Rsqr/2.0/3.0
				*(1.0-Rsqr/4.0/5.0
				*(1.0-Rsqr/6.0/7.0
				*(1.0-Rsqr/8.0/9.0
				*(1.0-Rsqr/10.0/11.0
				*(1.0-Rsqr/12.0/13.0
				*(1.0-Rsqr/14.0/15.0
				*(1.0-Rsqr/16.0/17.0
				*(1.0-Rsqr/18.0/19.0
				*(1.0-Rsqr/20.0/21.0
				))))))))));
		}
	};

	template<const double& R>
	struct CompileCosHelper
	{
		FORCE_INLINE static double cos()
		{
			const double Rsqr=R*R;
			return (1.0-Rsqr/1.0/2.0
				*(1.0-Rsqr/3.0/4.0
				*(1.0-Rsqr/5.0/6.0
				*(1.0-Rsqr/7.0/8.0
				*(1.0-Rsqr/9.0/10.0
				*(1.0-Rsqr/11.0/12.0
				*(1.0-Rsqr/13.0/14.0
				*(1.0-Rsqr/15.0/16.0
				*(1.0-Rsqr/17.0/18.0
				*(1.0-Rsqr/19.0/20.0
				))))))))));
		}
	};

	

	FORCE_INLINE static float ToDegree(float radian)
	{
		return radian*57.29577951f;
	}

	FORCE_INLINE static float ToRadian(float degree)
	{
		return degree*0.01745329252f;
	}
	template<const double& R>
	FORCE_INLINE static void CompileSin()
	{
		return CompileSinHelper<R>::sin();
	}

	template<const double& R>
	FORCE_INLINE static void CompileCos()
	{
		return CompileCosHelper<R>::cos();
	}

	FORCE_INLINE static float Sin(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sinf_neon(radian);
#else
		return sinf(radian);
#endif
	}

	FORCE_INLINE static float Sinh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sinhf_neon(radian);
#else
		return sinhf(radian);
#endif
	}

	FORCE_INLINE static float Asin(float x)
	{
		if (x<=-1.f)
		{
			return -PiHalf;
		}
		else if (x>=1.f)
		{
			return PiHalf;
		}
		else
		{
#ifdef MEDUSA_MATH_NEON_ENABLED
			return asinf_neon(x);
#else
			return asinf(x);
#endif
		}
	}

	FORCE_INLINE static float Cos(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return cosf_neon(radian);
#else
		return cosf(radian);
#endif
	}
	FORCE_INLINE static float Cosh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return coshf_neon(radian);
#else
		return coshf(radian);
#endif
	}

#ifdef MEDUSA_MATH_CPP11
	FORCE_INLINE static double Acosh(double radian)
	{
		return acosh(radian);
	}
	FORCE_INLINE static float Acosh(float radian)
	{
		return acoshf(radian);
	}

	FORCE_INLINE static double Asinh(double radian)
	{
		return asinh(radian);
	}
	FORCE_INLINE static float Asinh(float radian)
	{
		return asinhf(radian);
	}

	FORCE_INLINE static double Atanh(double radian)
	{
		return atanh(radian);
	}
	FORCE_INLINE static float Atanh(float radian)
	{
		return atanhf(radian);
	}
#endif

	FORCE_INLINE static float Acos(float x)
	{
		if (x<=-1.f)
		{
			return Pi;
		}
		else if (x>=1.f)
		{
			return 0.f;
		}
		else
		{
#ifdef MEDUSA_MATH_NEON_ENABLED
			return acosf_neon(x);
#else
			return acosf(x);
#endif
		}
	}

	FORCE_INLINE static float Tan(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return tanf_neon(radian);
#else
		return tanf(radian);
#endif
	}

	FORCE_INLINE static float Cot(float radian)
	{
		return Tan(PiHalf-radian);
	}


	FORCE_INLINE static float Tanh(float radian)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return tanhf_neon(radian);
#else
		return tanhf(radian);
#endif
	}

	FORCE_INLINE static float Atan(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return atanf_neon(x);
#else
		return atanf(x);
#endif
	}

	FORCE_INLINE static float Atan2(float y,float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return atan2f_neon(y,x);
#else
		return atan2f(y,x);
#endif
	}

	FORCE_INLINE static float WrapPi(float a)
	{
		//limit a to -π and π
		a+=Pi;
		a-=Floor(a*PiHalf)*Pi2;
		a-=Pi;
		return a;
	}
#pragma endregion Trigonometric
#pragma region Rounding and remainder functions
	//求e的x次幂
	FORCE_INLINE static float Exp(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return expf_neon(x);
#else
		return expf(x);
#endif
	}

#ifdef MEDUSA_MATH_CPP11
	//求2的x次幂
	FORCE_INLINE static float Exp2(float x)
	{
		return exp2(x);
	}
	FORCE_INLINE static double Exp2(double x)
	{
		return exp2(x);
	}

	//求e的x次幂-1
	FORCE_INLINE static float ExpM1(float x)
	{
		return expm1(x);
	}

	FORCE_INLINE static double ExpM1(double x)
	{
		return expm1(x);
	}

	//返回|x|对数的整数部分,ilogb(10.000000) = 3
	FORCE_INLINE static int Ilogb(float x)
	{
		return ilogb(x);
	}
	FORCE_INLINE static int Ilogb(double x)
	{
		return ilogb(x);
	}

	//返回|x|对数,logb (1024.000000) = 10.000000
	FORCE_INLINE static float Logb(float x)
	{
		return logb(x);
	}
	FORCE_INLINE static double Logb(double x)
	{
		return logb(x);
	}

	//返回|1+x|的自然对数，log1p (1.000000) = 0.693147
	FORCE_INLINE static float Log1p(float x)
	{
		return log1pf(x);
	}
	FORCE_INLINE static double Log1p(double x)
	{
		return log1p(x);
	}

	//log2x.
	FORCE_INLINE static float Log2(float x)
	{
		return log2f(x);
	}
	FORCE_INLINE static double Log2(double x)
	{
		return log2(x);
	}

	//Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
	FORCE_INLINE static float Truncate(float x)
	{
		return trunc(x);
	}
	FORCE_INLINE static double Truncate(double x)
	{
		return truncf(x);
	}

	//Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
	FORCE_INLINE static float Round(float x)
	{
		return round(x);
	}
	FORCE_INLINE static double Round(double x)
	{
		return roundf(x);
	}

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	//lround (2.3) = 2
	//	lround (3.8) = 4
	//	lround (-2.3) = -2
	//	lround (-3.8) = -4
	FORCE_INLINE static long int LRound(float x)
	{
		return lround(x);
	}
	FORCE_INLINE static long int LRound(double x)
	{
		return lroundf(x);
	}

	//Returns the integer value that is nearest in value to x, with halfway cases rounded away from zero.
	/*llround (2.3) = 2
	llround (3.8) = 4
	llround (-2.3) = -2
	llround (-3.8) = -4*/
	FORCE_INLINE static long long int LLRound(float x)
	{
		return llround(x);
	}
	FORCE_INLINE static long long int LLRound(double x)
	{
		return llroundf(x);
	}
#endif


	FORCE_INLINE static float Log(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return logf_neon(x);
#else
		return logf(x);
#endif
	}

	FORCE_INLINE static float Log10(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return log10f_neon(x);
#else
		return log10f(x);
#endif
	}

	FORCE_INLINE static float Pow(float x,float y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return powf_neon(x,y);
#else
		return powf(x,y);
#endif
	}

	

	FORCE_INLINE static float Fract(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return x-floorf_neon(x);
#else
		return x-floorf(x);
#endif
	}

	//求不大于x的最大整数
	FORCE_INLINE static float Floor(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return floorf_neon(x);
#else
		return floorf(x);
#endif
	}

	//求不小于x的最小整数
	FORCE_INLINE static float Ceil(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return ceilf_neon(x);
#else
		return ceilf(x);
#endif
	}
	FORCE_INLINE static int Abs(int x)
	{
		return x<0?-x:x;
	}

	FORCE_INLINE static short Abs(short x)
	{
		return x<0?-x:x;
	}

	FORCE_INLINE static float Abs(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return fabsf_neon(x);
#else
		return fabsf(x);
#endif
	}

#ifdef MEDUSA_WINDOWS
	FORCE_INLINE static div_t Div(int number,int denom)
	{
		return div(number,denom);
	}

	FORCE_INLINE static ldiv_t Div(long int number,long int denom)
	{
		return div(number,denom);
	}

	FORCE_INLINE static lldiv_t Div(long long int number,long long int denom)
	{
		return div(number,denom);
	}
#else
	FORCE_INLINE static div_t Div(int number,int denom)
	{
		return div(number,denom);
	}

	
#endif
	//把浮点数x分解成尾数和指数
	//x=m*2^y，m为规格化小数。返回尾数m，并将指数存入y中。
	FORCE_INLINE static float Frexp(float x,int* y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return medusa_frexpf(x,y);
#else
		return frexpf(x,y);
#endif
	}

	//装载浮点数
	//返回x*2^y的值。
	FORCE_INLINE static float Ldexp(float x,int y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return ldexpf_neon(x,y);
#else
		return ldexpf(x,y);
#endif
	}

	//将浮点数x分解成整数部分和小数部分
	//返回小数部分，将整数部分存入*y所指内存中
	FORCE_INLINE static double Mod(double x,double* y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return modf_neon(x,y);
#else
		return modf(x,y);
#endif
	}

	//计算x/y的余数
	FORCE_INLINE static float Fmod(float x,float y)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return fmodf_neon(x,y);
#else
		return fmodf(x,y);
#endif
	}


	FORCE_INLINE static float Sqrt(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return sqrtf_neon(x);
#else
		return sqrtf(x);
#endif
	}

	FORCE_INLINE static float InverseSqrt(float x)
	{
#ifdef MEDUSA_MATH_NEON_ENABLED
		return invsqrtf_neon(x);
#else
		return 1.f/sqrtf(x);
#endif
	}

	//计算直角三角行的斜边长
	FORCE_INLINE static float Hypot(float x,float y)
	{
		return hypotf(x,y);
	}

#pragma endregion Rounding and remainder functions

	template<typename T>
	FORCE_INLINE static T Clamp(T x,T min,T max)
	{
		return x<min?min:(x>max?max:x);
	}

	template<typename T>
	FORCE_INLINE static T ClampAboveZero(T x)
	{
		return x<0?0:x;
	}

	template<typename T>
	FORCE_INLINE static T Mix(float f,T min,T max)
	{
		return (T)(min*(1.f-f)+max*f);
	}

	//blend [0-1]
	template<typename T>
	FORCE_INLINE static T LinearInterpolate(T begin,T end,float blend)
	{
		return begin+(T)((end-begin)*blend);
	}


	template<typename T>
	FORCE_INLINE static T LinearInterpolate(T val,T srcMin,T srcMax,T destMin,T destMax)
	{
		return destMin+(destMax-destMin)*(val-srcMin)/(srcMax-srcMin);
	}

	template<typename T>
	FORCE_INLINE static float LinearBlend(T val,T begin,T end)
	{
		return Clamp((val-begin)/(end-begin),0.f,1.f);
	}

	template<typename T>
	FORCE_INLINE static float SmoothBlend(T val,T begin,T end)
	{
		float f=Clamp((val-begin)/(end-begin),0.f,1.f);
		return f*f*(3.f-2.f*f);
	}

	template<typename T>
	FORCE_INLINE static T Barycentric(T value1, T value2, T value3, T amount1, T amount2)
	{
		return ((value1 + (amount1 * (value2 - value1))) + (amount2 * (value3 - value1)));
	}

	FORCE_INLINE static float CatmullRom(float value1, float value2, float value3, float value4, float amount)
	{
		float num = amount * amount;
		float num2 = amount * num;
		return (0.5f * ((((2.f * value2) + ((-value1 + value3) * amount)) + (((((2.f * value1) - (5.f * value2)) + (4.f * value3)) - value4) * num)) + ((((-value1 + (3.f * value2)) - (3.f * value3)) + value4) * num2)));
	}


	FORCE_INLINE static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount)
	{
		float num3 = amount;
		float num = num3 * num3;
		float num2 = num3 * num;
		float num7 = ((2.f * num2) - (3.f * num)) + 1.f;
		float num6 = (-2.f * num2) + (3.f * num);
		float num5 = (num2 - (2.f * num)) + num3;
		float num4 = num2 - num;
		return ((((value1 * num7) + (value2 * num6)) + (tangent1 * num5)) + (tangent2 * num4));
	}

	//explicit template specialization cannot have a storage class on GCC,so cannot replace inline with static
	template <>
	inline bool IsZero(float val)
	{
		return fabs(val)<FloatCompareEpsilon;
	}

	template <>
	inline bool IsZero(double val)
	{
		return fabs(val)<DoubleCompareEpsilon;
	}

	template <>
	inline bool IsEqualEpsilon(float left,float right,float epsilon)
	{
		return fabs(left-right)<epsilon;
	}

	template <>
	inline bool IsEqualEpsilon(double left,double right,float epsilon)
	{
		return fabs(left-right)<epsilon;
	}

	template <>
	inline bool IsEqual(float left,float right)
	{
		return fabs(left-right)<FloatCompareEpsilon;
	}

	template <>
	inline bool IsEqual(double left,double right)
	{
		return fabs(left-right)<DoubleCompareEpsilon;
	}

	template <>
	inline float Compare(float left,float right)
	{
		float delta=left-right;
		return fabs(delta)<FloatCompareEpsilon?0.f:delta;
	}

	template <>
	inline double Compare(double left,double right)
	{
		double delta=left-right;
		return fabs(delta)<DoubleCompareEpsilon?0.0:delta;
	}


	FORCE_INLINE static size_t GetNewSizeSquare(size_t originalSize,size_t newSize)
	{
		if (originalSize==0)
		{
			originalSize=1;
		}

		while(originalSize<newSize)
		{
			originalSize<<=1;
		}

		return originalSize;
	}

	FORCE_INLINE static size_t NextPOT(size_t x)
	{
		--x;
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >>16);
		return ++x;
	}

	namespace Tween
	{
		enum class TweenType
		{
			None = -1,
			//Linear：无缓动效果
			Linear,

			//Quadratic：二次方的缓动（t^2）
			QuadraticEaseIn,
			QuadraticEaseOut,
			QuadraticEaseInOut,

			//Cubic：三次方的缓动（t^3）
			CubicEaseIn,
			CubicEaseOut,
			CubicEaseInOut,

			//Quartic：四次方的缓动（t^4）
			QuarticEaseIn,
			QuarticEaseOut,
			QuarticEaseInOut,

			//Quintic：五次方的缓动（t^5）
			QuinticEaseIn,
			QuinticEaseOut,
			QuinticEaseInOut,

			//Sinusoidal：正弦曲线的缓动（sin(t)）
			SinusoidalEaseIn,
			SinusoidalEaseOut,
			SinusoidalEaseInOut,

			//Exponential：指数曲线的缓动（2^t）
			ExponentialEaseIn,
			ExponentialEaseOut,
			ExponentialEaseInOut,

			//Circular：圆形曲线的缓动（sqrt(1-t^2)）
			CircularEaseIn,
			CircularEaseOut,
			CircularEaseInOut,

			//Elastic：指数衰减的正弦曲线缓动
			ElasticEaseIn,
			ElasticEaseOut,
			ElasticEaseInOut,

			//Back：超过范围的三次方缓动（(s+1)*t^3 - s*t^2）
			BackEaseIn,
			BackEaseOut,
			BackEaseInOut,

			//Bounce：指数衰减的反弹缓动。
			BounceEaseIn,
			BounceEaseOut,
			BounceEaseInOut,

			//Rate:自定义的比率
			RateEaseIn,
			RateEaseOut,
			RateEaseInOut,

			//贝塞尔
			Bezier,

			Count,
		};



		//Linear：无缓动效果
		FORCE_INLINE static float Linear(float time){return time;}

		//Quadratic：二次方的缓动（t^2）
		FORCE_INLINE static float QuadraticEaseIn(float time);
		FORCE_INLINE static float QuadraticEaseOut(float time);
		FORCE_INLINE static float QuadraticEaseInOut(float time);

		//Cubic：三次方的缓动（t^3）
		FORCE_INLINE static float CubicEaseIn(float time);
		FORCE_INLINE static float CubicEaseOut(float time);
		FORCE_INLINE static float CubicEaseInOut(float time);

		//Quartic：四次方的缓动（t^4）
		FORCE_INLINE static float QuarticEaseIn(float time);
		FORCE_INLINE static float QuarticEaseOut(float time);
		FORCE_INLINE static float QuarticEaseInOut(float time);

		//Quintic：五次方的缓动（t^5）
		FORCE_INLINE static float QuinticEaseIn(float time);
		FORCE_INLINE static float QuinticEaseOut(float time);
		FORCE_INLINE static float QuinticEaseInOut(float time);


		//Sinusoidal：正弦曲线的缓动（sin(t)）
		FORCE_INLINE static float SinusoidalEaseIn(float time);
		FORCE_INLINE static float SinusoidalEaseOut(float time);
		FORCE_INLINE static float SinusoidalEaseInOut(float time);

		//Exponential：指数曲线的缓动（2^t）
		FORCE_INLINE static float ExponentialEaseIn(float time);
		FORCE_INLINE static float ExponentialEaseOut(float time);
		FORCE_INLINE static float ExponentialEaseInOut(float time);

		//Circular：圆形曲线的缓动（sqrt(1-t^2)）
		FORCE_INLINE static float CircularEaseIn(float time);
		FORCE_INLINE static float CircularEaseOut(float time);
		FORCE_INLINE static float CircularEaseInOut(float time);

		//Elastic：指数衰减的正弦曲线缓动
		FORCE_INLINE static float ElasticEaseIn(float time, float period);
		FORCE_INLINE static float ElasticEaseOut(float time, float period);
		FORCE_INLINE static float ElasticEaseInOut(float time, float period);

		//Back：超过范围的三次方缓动（(s+1)*t^3 - s*t^2）
		FORCE_INLINE static float BackEaseIn(float time);
		FORCE_INLINE static float BackEaseOut(float time);
		FORCE_INLINE static float BackEaseInOut(float time);

		//Bounce：指数衰减的反弹缓动。
		FORCE_INLINE static float BounceTime(float time);
		FORCE_INLINE static float BounceEaseIn(float time);
		FORCE_INLINE static float BounceEaseOut(float time);
		FORCE_INLINE static float BounceEaseInOut(float time);

		//Rate:自定义的比率
		FORCE_INLINE static float RateEaseIn(float time, float rate);
		FORCE_INLINE static float RateEaseOut(float time, float rate);
		FORCE_INLINE static float RateEaseInOut(float time, float rate);

		//贝塞尔
		FORCE_INLINE static float Bezier(float time, float a, float b, float c, float d);
		//自定义
		FORCE_INLINE static float TweenTo(float time, TweenType type, const float* args);

	}

};



//template<> byte MinValue(){return ByteMinValue;}
//template<> char MinValue(){return CharMinValue;}
//template<> short MinValue(){return ShortMinValue;}
//template<> ushort MinValue(){return UShortMinValue;}
//template<> int MinValue(){return IntMinValue;}
//template<> uint MinValue(){return UIntMinValue;}
//template<> float MinValue(){return FloatMinValue;}
//template<> double MinValue(){return DoubleMinValue;}
//
//template<> byte MaxValue(){return ByteMaxValue;}
//template<> char MaxValue(){return CharMaxValue;}
//template<> short MaxValue(){return ShortMaxValue;}
//template<> ushort MaxValue(){return UShortMaxValue;}
//template<> int MaxValue(){return IntMaxValue;}
//template<> uint MaxValue(){return UIntMaxValue;}
//template<> float MaxValue(){return FloatMaxValue;}
//template<> double MaxValue(){return DoubleMaxValue;}


MEDUSA_END;
