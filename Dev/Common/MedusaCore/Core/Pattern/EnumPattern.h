#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"

#define ENUM_NAME_COMMON_OPERATOR(TEnum,TField)															   \
public:																						   \
	TEnum( const TEnum& rhs ) : mState( rhs.mState ) {}															\
	TEnum operator=( TEnum rhs ){mState = rhs.mState;return *this;}											   \
	template<int TValue,uint TIndex,StringRef TName()> TEnum(const TField<TValue,TIndex,TName>& rhs ) : mState( TValue ) {}													   \
	template<int TValue,uint TIndex,StringRef TName()> TEnum operator=(const TField<TValue,TIndex,TName>& rhs ){mState =TValue;return *this;}										   \
	bool operator==( TEnum rhs ) const{return mState == rhs.mState;}										   \
	bool operator!=( TEnum rhs ) const{return mState != rhs.mState;}										   \
	bool operator<( TEnum rhs ) const{return mState < rhs.mState;}											   \
	bool operator>( TEnum rhs ) const{return mState > rhs.mState;}											   \
	bool operator<=( TEnum rhs ) const{return mState <= rhs.mState;}										   \
	bool operator>=( TEnum rhs ) const{return mState >= rhs.mState;}										   \
	template<int TValue,int TIndex,StringRef TName()> bool operator==( TField<TValue,TIndex,TName> rhs ) const{return mState == TValue;}										   \
	template<int TValue,int TIndex,StringRef TName()> bool operator!=( TField<TValue,TIndex,TName> rhs ) const{return mState != TValue;}										   \
	template<int TValue,int TIndex,StringRef TName()> bool operator<( TField<TValue,TIndex,TName> rhs ) const{return mState < TValue;}											   \
	template<int TValue,int TIndex,StringRef TName()> bool operator>( TField<TValue,TIndex,TName> rhs ) const{return mState > TValue;}											   \
	template<int TValue,int TIndex,StringRef TName()> bool operator<=( TField<TValue,TIndex,TName> rhs ) const{return mState <= TValue;}										   \
	template<int TValue,int TIndex,StringRef TName()> bool operator>=( TField<TValue,TIndex,TName> rhs ) const{return mState >= TValue;}										   \
	int ToInt()const{return mState;}																													   \
	void ForceSet(int state){mState=state;}																													   \
	int* ForceGetPointer(){return &mState;}																													   \
	int& ForceGetReference(){return mState;}																													   \
	unsigned int ToUInt()const{return (unsigned int)mState;}											\
	intp GetHashCode()const{return mState;}

#define ENUM_FIELD_COMMON_OPERATOR(TEnum,TField)														   \
public:TField(){}																									   \
	bool operator==( TEnum rhs ) const{return TValue == rhs.mState;}										   \
	bool operator!=( TEnum rhs ) const{return TValue != rhs.mState;}										   \
	bool operator<( TEnum rhs ) const{return TValue < rhs.mState;}											   \
	bool operator>( TEnum rhs ) const{return TValue > rhs.mState;}											   \
	bool operator<=( TEnum rhs ) const{return TValue <= rhs.mState;}										   \
	bool operator>=( TEnum rhs ) const{return TValue >= rhs.mState;}										   \
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator==( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue == TValue2;}						\
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator!=( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue != TValue2;}										   \
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator<( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue < TValue2;}											   \
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator>( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue > TValue2;}											   \
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator<=( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue <= TValue2;}										   \
	template<int TValue2,int TIndex2,StringRef TName2()> bool operator>=( TField<TValue2,TIndex2,TName2> rhs ) const{return TValue >= TValue2;}										   \
	const static int IntValue=TValue;																											\
	const static unsigned int Index=TIndex;																											\
	int ToInt()const{return TValue;}																										\
	unsigned int ToUInt()const{return (unsigned int)TValue;}																										\
	unsigned int ToIndex()const{return TIndex;}																										\
	StringRef ToString()const{return TName();}																										\
	intp GetHashCode()const{return TValue;}

#define ENUM_CLASS_BEGIN(TEnum)																														\
class TEnum																																		   \
{																																				   \
	template<int TValue,unsigned int TIndex,StringRef TName()> \
class TEnum##Field{friend class TEnum;ENUM_FIELD_COMMON_OPERATOR(TEnum,TEnum##Field);};	   \
protected:int mState;																			\
	ENUM_NAME_COMMON_OPERATOR(TEnum,TEnum##Field);																								   \
public:																																		   

	//BEGIN_AUTO_GENERATE_ENUM_CLASS_END
#define ENUM_CLASS_END_1(TEnum,T1,P1)\
private:\
static StringRef OnName1(){return #T1;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=1;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;

#define ENUM_CLASS_END_2(TEnum,T1,P1,T2,P2)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=2;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;

#define ENUM_CLASS_END_3(TEnum,T1,P1,T2,P2,T3,P3)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=3;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;

#define ENUM_CLASS_END_4(TEnum,T1,P1,T2,P2,T3,P3,T4,P4)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=4;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;

#define ENUM_CLASS_END_5(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=5;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;

#define ENUM_CLASS_END_6(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=6;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;

#define ENUM_CLASS_END_7(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=7;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;

#define ENUM_CLASS_END_8(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=8;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;

#define ENUM_CLASS_END_9(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=9;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;

#define ENUM_CLASS_END_10(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=10;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;

#define ENUM_CLASS_END_11(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=11;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;

#define ENUM_CLASS_END_12(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=12;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;

#define ENUM_CLASS_END_13(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=13;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;

#define ENUM_CLASS_END_14(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=14;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;

#define ENUM_CLASS_END_15(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=15;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;

#define ENUM_CLASS_END_16(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=16;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;

#define ENUM_CLASS_END_17(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=17;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;

#define ENUM_CLASS_END_18(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=18;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;

#define ENUM_CLASS_END_19(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=19;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;

#define ENUM_CLASS_END_20(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=20;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;

#define ENUM_CLASS_END_21(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=21;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;

#define ENUM_CLASS_END_22(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=22;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;

#define ENUM_CLASS_END_23(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=23;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;

#define ENUM_CLASS_END_24(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=24;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;

#define ENUM_CLASS_END_25(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=25;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;

#define ENUM_CLASS_END_26(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=26;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;

#define ENUM_CLASS_END_27(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=27;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;

#define ENUM_CLASS_END_28(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
static StringRef OnName28(){return #T28;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;case P28:return #T28;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=28;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
static const TEnum##Field<P28,27,TEnum::OnName28> T28;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P28,27,TEnum::OnName28> TEnum::T28;

#define ENUM_CLASS_END_29(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
static StringRef OnName28(){return #T28;}\
static StringRef OnName29(){return #T29;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;case P28:return #T28;case P29:return #T29;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=29;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
static const TEnum##Field<P28,27,TEnum::OnName28> T28;\
static const TEnum##Field<P29,28,TEnum::OnName29> T29;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P28,27,TEnum::OnName28> TEnum::T28;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P29,28,TEnum::OnName29> TEnum::T29;

#define ENUM_CLASS_END_30(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
static StringRef OnName28(){return #T28;}\
static StringRef OnName29(){return #T29;}\
static StringRef OnName30(){return #T30;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;case P28:return #T28;case P29:return #T29;case P30:return #T30;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=30;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
static const TEnum##Field<P28,27,TEnum::OnName28> T28;\
static const TEnum##Field<P29,28,TEnum::OnName29> T29;\
static const TEnum##Field<P30,29,TEnum::OnName30> T30;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P28,27,TEnum::OnName28> TEnum::T28;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P29,28,TEnum::OnName29> TEnum::T29;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P30,29,TEnum::OnName30> TEnum::T30;

#define ENUM_CLASS_END_31(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
static StringRef OnName28(){return #T28;}\
static StringRef OnName29(){return #T29;}\
static StringRef OnName30(){return #T30;}\
static StringRef OnName31(){return #T31;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;case P28:return #T28;case P29:return #T29;case P30:return #T30;case P31:return #T31;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=31;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
static const TEnum##Field<P28,27,TEnum::OnName28> T28;\
static const TEnum##Field<P29,28,TEnum::OnName29> T29;\
static const TEnum##Field<P30,29,TEnum::OnName30> T30;\
static const TEnum##Field<P31,30,TEnum::OnName31> T31;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30,#T31};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P28,27,TEnum::OnName28> TEnum::T28;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P29,28,TEnum::OnName29> TEnum::T29;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P30,29,TEnum::OnName30> TEnum::T30;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P31,30,TEnum::OnName31> TEnum::T31;

#define ENUM_CLASS_END_32(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)\
private:\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
static StringRef OnName9(){return #T9;}\
static StringRef OnName10(){return #T10;}\
static StringRef OnName11(){return #T11;}\
static StringRef OnName12(){return #T12;}\
static StringRef OnName13(){return #T13;}\
static StringRef OnName14(){return #T14;}\
static StringRef OnName15(){return #T15;}\
static StringRef OnName16(){return #T16;}\
static StringRef OnName17(){return #T17;}\
static StringRef OnName18(){return #T18;}\
static StringRef OnName19(){return #T19;}\
static StringRef OnName20(){return #T20;}\
static StringRef OnName21(){return #T21;}\
static StringRef OnName22(){return #T22;}\
static StringRef OnName23(){return #T23;}\
static StringRef OnName24(){return #T24;}\
static StringRef OnName25(){return #T25;}\
static StringRef OnName26(){return #T26;}\
static StringRef OnName27(){return #T27;}\
static StringRef OnName28(){return #T28;}\
static StringRef OnName29(){return #T29;}\
static StringRef OnName30(){return #T30;}\
static StringRef OnName31(){return #T31;}\
static StringRef OnName32(){return #T32;}\
public:\
explicit TEnum(int val):mState(val){}\
StringRef ToString()const{switch(mState){\
case P1:return #T1;case P2:return #T2;case P3:return #T3;case P4:return #T4;case P5:return #T5;case P6:return #T6;case P7:return #T7;case P8:return #T8;case P9:return #T9;case P10:return #T10;case P11:return #T11;case P12:return #T12;case P13:return #T13;case P14:return #T14;case P15:return #T15;case P16:return #T16;case P17:return #T17;case P18:return #T18;case P19:return #T19;case P20:return #T20;case P21:return #T21;case P22:return #T22;case P23:return #T23;case P24:return #T24;case P25:return #T25;case P26:return #T26;case P27:return #T27;case P28:return #T28;case P29:return #T29;case P30:return #T30;case P31:return #T31;case P32:return #T32;\
default:return NULL;}}\
uint ToIndex()const{for(uint i=0;i<Size;++i){if(Values[i]==mState) return i;}return (uint)0xFFFFFFFF;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TEnum Parse(int val){if(IsDefined(val)){return TEnum(val);}MEDUSA_ASSERT_FAILED("Invalid enum val.");return TEnum::T1;}\
static bool TryParse(int val,TEnum& outEnum){if(IsDefined(val)){outEnum.ForceSet(val);return true;}return false;}\
static TEnum Parse(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){return TEnum(Values[i]);}}MEDUSA_ASSERT_FAILED("Invalid enum name.");return TEnum::T1;}\
static bool TryParse(TEnum& outEnum,StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0){outEnum.ForceSet(Values[i]);}}return false;}\
public:\
static const unsigned int Size=32;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TEnum##Field<P1,0,TEnum::OnName1> T1;\
static const TEnum##Field<P2,1,TEnum::OnName2> T2;\
static const TEnum##Field<P3,2,TEnum::OnName3> T3;\
static const TEnum##Field<P4,3,TEnum::OnName4> T4;\
static const TEnum##Field<P5,4,TEnum::OnName5> T5;\
static const TEnum##Field<P6,5,TEnum::OnName6> T6;\
static const TEnum##Field<P7,6,TEnum::OnName7> T7;\
static const TEnum##Field<P8,7,TEnum::OnName8> T8;\
static const TEnum##Field<P9,8,TEnum::OnName9> T9;\
static const TEnum##Field<P10,9,TEnum::OnName10> T10;\
static const TEnum##Field<P11,10,TEnum::OnName11> T11;\
static const TEnum##Field<P12,11,TEnum::OnName12> T12;\
static const TEnum##Field<P13,12,TEnum::OnName13> T13;\
static const TEnum##Field<P14,13,TEnum::OnName14> T14;\
static const TEnum##Field<P15,14,TEnum::OnName15> T15;\
static const TEnum##Field<P16,15,TEnum::OnName16> T16;\
static const TEnum##Field<P17,16,TEnum::OnName17> T17;\
static const TEnum##Field<P18,17,TEnum::OnName18> T18;\
static const TEnum##Field<P19,18,TEnum::OnName19> T19;\
static const TEnum##Field<P20,19,TEnum::OnName20> T20;\
static const TEnum##Field<P21,20,TEnum::OnName21> T21;\
static const TEnum##Field<P22,21,TEnum::OnName22> T22;\
static const TEnum##Field<P23,22,TEnum::OnName23> T23;\
static const TEnum##Field<P24,23,TEnum::OnName24> T24;\
static const TEnum##Field<P25,24,TEnum::OnName25> T25;\
static const TEnum##Field<P26,25,TEnum::OnName26> T26;\
static const TEnum##Field<P27,26,TEnum::OnName27> T27;\
static const TEnum##Field<P28,27,TEnum::OnName28> T28;\
static const TEnum##Field<P29,28,TEnum::OnName29> T29;\
static const TEnum##Field<P30,29,TEnum::OnName30> T30;\
static const TEnum##Field<P31,30,TEnum::OnName31> T31;\
static const TEnum##Field<P32,31,TEnum::OnName32> T32;\
TEnum():mState(P1){}\
};\
WEAK_MULTIPLE_DEFINE const StringRef TEnum::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30,#T31,#T32};\
WEAK_MULTIPLE_DEFINE const int TEnum::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31,P32};\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P1,0,TEnum::OnName1> TEnum::T1;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P2,1,TEnum::OnName2> TEnum::T2;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P3,2,TEnum::OnName3> TEnum::T3;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P4,3,TEnum::OnName4> TEnum::T4;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P5,4,TEnum::OnName5> TEnum::T5;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P6,5,TEnum::OnName6> TEnum::T6;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P7,6,TEnum::OnName7> TEnum::T7;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P8,7,TEnum::OnName8> TEnum::T8;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P9,8,TEnum::OnName9> TEnum::T9;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P10,9,TEnum::OnName10> TEnum::T10;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P11,10,TEnum::OnName11> TEnum::T11;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P12,11,TEnum::OnName12> TEnum::T12;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P13,12,TEnum::OnName13> TEnum::T13;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P14,13,TEnum::OnName14> TEnum::T14;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P15,14,TEnum::OnName15> TEnum::T15;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P16,15,TEnum::OnName16> TEnum::T16;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P17,16,TEnum::OnName17> TEnum::T17;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P18,17,TEnum::OnName18> TEnum::T18;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P19,18,TEnum::OnName19> TEnum::T19;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P20,19,TEnum::OnName20> TEnum::T20;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P21,20,TEnum::OnName21> TEnum::T21;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P22,21,TEnum::OnName22> TEnum::T22;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P23,22,TEnum::OnName23> TEnum::T23;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P24,23,TEnum::OnName24> TEnum::T24;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P25,24,TEnum::OnName25> TEnum::T25;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P26,25,TEnum::OnName26> TEnum::T26;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P27,26,TEnum::OnName27> TEnum::T27;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P28,27,TEnum::OnName28> TEnum::T28;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P29,28,TEnum::OnName29> TEnum::T29;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P30,29,TEnum::OnName30> TEnum::T30;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P31,30,TEnum::OnName31> TEnum::T31;\
	WEAK_MULTIPLE_DEFINE const TEnum::TEnum##Field<P32,31,TEnum::OnName32> TEnum::T32;

//END_AUTO_GENERATE_ENUM_CLASS_END


//BEGIN_AUTO_GENERATE_ENUM_DEFINE
#define STRONG_ENUM_CUSTOM_1(TEnum,T1,P1)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_1(TEnum,T1,P1)
#define STRONG_ENUM_CUSTOM_2(TEnum,T1,P1,T2,P2)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_2(TEnum,T1,P1,T2,P2)
#define STRONG_ENUM_CUSTOM_3(TEnum,T1,P1,T2,P2,T3,P3)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_3(TEnum,T1,P1,T2,P2,T3,P3)
#define STRONG_ENUM_CUSTOM_4(TEnum,T1,P1,T2,P2,T3,P3,T4,P4)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_4(TEnum,T1,P1,T2,P2,T3,P3,T4,P4)
#define STRONG_ENUM_CUSTOM_5(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_5(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)
#define STRONG_ENUM_CUSTOM_6(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_6(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)
#define STRONG_ENUM_CUSTOM_7(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_7(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)
#define STRONG_ENUM_CUSTOM_8(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_8(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)
#define STRONG_ENUM_CUSTOM_9(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_9(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)
#define STRONG_ENUM_CUSTOM_10(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_10(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)
#define STRONG_ENUM_CUSTOM_11(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_11(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)
#define STRONG_ENUM_CUSTOM_12(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_12(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)
#define STRONG_ENUM_CUSTOM_13(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_13(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)
#define STRONG_ENUM_CUSTOM_14(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_14(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)
#define STRONG_ENUM_CUSTOM_15(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_15(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)
#define STRONG_ENUM_CUSTOM_16(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_16(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)
#define STRONG_ENUM_CUSTOM_17(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_17(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)
#define STRONG_ENUM_CUSTOM_18(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_18(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)
#define STRONG_ENUM_CUSTOM_19(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_19(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)
#define STRONG_ENUM_CUSTOM_20(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_20(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)
#define STRONG_ENUM_CUSTOM_21(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_21(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)
#define STRONG_ENUM_CUSTOM_22(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_22(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)
#define STRONG_ENUM_CUSTOM_23(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_23(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)
#define STRONG_ENUM_CUSTOM_24(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_24(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)
#define STRONG_ENUM_CUSTOM_25(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_25(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)
#define STRONG_ENUM_CUSTOM_26(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_26(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)
#define STRONG_ENUM_CUSTOM_27(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_27(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)
#define STRONG_ENUM_CUSTOM_28(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_28(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)
#define STRONG_ENUM_CUSTOM_29(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_29(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)
#define STRONG_ENUM_CUSTOM_30(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_30(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)
#define STRONG_ENUM_CUSTOM_31(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_31(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)
#define STRONG_ENUM_CUSTOM_32(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)	ENUM_CLASS_BEGIN(TEnum)	ENUM_CLASS_END_32(TEnum,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)




#define STRONG_ENUM_1(TEnum,T1)	STRONG_ENUM_CUSTOM_1(TEnum,T1,0)
#define STRONG_ENUM_2(TEnum,T1,T2)	STRONG_ENUM_CUSTOM_2(TEnum,T1,0,T2,1)
#define STRONG_ENUM_3(TEnum,T1,T2,T3)	STRONG_ENUM_CUSTOM_3(TEnum,T1,0,T2,1,T3,2)
#define STRONG_ENUM_4(TEnum,T1,T2,T3,T4)	STRONG_ENUM_CUSTOM_4(TEnum,T1,0,T2,1,T3,2,T4,3)
#define STRONG_ENUM_5(TEnum,T1,T2,T3,T4,T5)	STRONG_ENUM_CUSTOM_5(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4)
#define STRONG_ENUM_6(TEnum,T1,T2,T3,T4,T5,T6)	STRONG_ENUM_CUSTOM_6(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5)
#define STRONG_ENUM_7(TEnum,T1,T2,T3,T4,T5,T6,T7)	STRONG_ENUM_CUSTOM_7(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6)
#define STRONG_ENUM_8(TEnum,T1,T2,T3,T4,T5,T6,T7,T8)	STRONG_ENUM_CUSTOM_8(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7)
#define STRONG_ENUM_9(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9)	STRONG_ENUM_CUSTOM_9(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8)
#define STRONG_ENUM_10(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)	STRONG_ENUM_CUSTOM_10(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9)
#define STRONG_ENUM_11(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)	STRONG_ENUM_CUSTOM_11(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10)
#define STRONG_ENUM_12(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12)	STRONG_ENUM_CUSTOM_12(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11)
#define STRONG_ENUM_13(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13)	STRONG_ENUM_CUSTOM_13(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12)
#define STRONG_ENUM_14(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14)	STRONG_ENUM_CUSTOM_14(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13)
#define STRONG_ENUM_15(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15)	STRONG_ENUM_CUSTOM_15(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14)
#define STRONG_ENUM_16(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16)	STRONG_ENUM_CUSTOM_16(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15)
#define STRONG_ENUM_17(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17)	STRONG_ENUM_CUSTOM_17(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16)
#define STRONG_ENUM_18(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18)	STRONG_ENUM_CUSTOM_18(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17)
#define STRONG_ENUM_19(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19)	STRONG_ENUM_CUSTOM_19(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18)
#define STRONG_ENUM_20(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20)	STRONG_ENUM_CUSTOM_20(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19)
#define STRONG_ENUM_21(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21)	STRONG_ENUM_CUSTOM_21(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20)
#define STRONG_ENUM_22(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22)	STRONG_ENUM_CUSTOM_22(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21)
#define STRONG_ENUM_23(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23)	STRONG_ENUM_CUSTOM_23(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22)
#define STRONG_ENUM_24(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24)	STRONG_ENUM_CUSTOM_24(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23)
#define STRONG_ENUM_25(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25)	STRONG_ENUM_CUSTOM_25(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24)
#define STRONG_ENUM_26(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26)	STRONG_ENUM_CUSTOM_26(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25)
#define STRONG_ENUM_27(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27)	STRONG_ENUM_CUSTOM_27(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26)
#define STRONG_ENUM_28(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28)	STRONG_ENUM_CUSTOM_28(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26,T28,27)
#define STRONG_ENUM_29(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29)	STRONG_ENUM_CUSTOM_29(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26,T28,27,T29,28)
#define STRONG_ENUM_30(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30)	STRONG_ENUM_CUSTOM_30(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26,T28,27,T29,28,T30,29)
#define STRONG_ENUM_31(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31)	STRONG_ENUM_CUSTOM_31(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26,T28,27,T29,28,T30,29,T31,30)
#define STRONG_ENUM_32(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32)	STRONG_ENUM_CUSTOM_32(TEnum,T1,0,T2,1,T3,2,T4,3,T5,4,T6,5,T7,6,T8,7,T9,8,T10,9,T11,10,T12,11,T13,12,T14,13,T15,14,T16,15,T17,16,T18,17,T19,18,T20,19,T21,20,T22,21,T23,22,T24,23,T25,24,T26,25,T27,26,T28,27,T29,28,T30,29,T31,30,T32,31)
//END_AUTO_GENERATE_ENUM_DEFINE
