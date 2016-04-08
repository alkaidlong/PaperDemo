
#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"


#define FLAGS_NAME_COMMON_OPERATOR(TFlags,TField)															   \
public:																									   \
	TFlags( const TFlags& rhs ) : mState( rhs.mState ) {}															\
	TFlags operator=( TFlags rhs ){mState = rhs.mState;return *this;}											   \
	template<int TValue,StringRef TName()> TFlags(TField<TValue,TName> rhs ) : mState( TValue ) {}													   \
	template<int TValue,StringRef TName()> TFlags operator=( TField<TValue,TName> rhs ){mState = TValue;return *this;}										   \
	bool operator==( TFlags rhs ) const{return mState == rhs.mState;}										   \
	bool operator!=( TFlags rhs ) const{return mState != rhs.mState;}										   \
	bool operator<( TFlags rhs ) const{return mState < rhs.mState;}											   \
	bool operator>( TFlags rhs ) const{return mState > rhs.mState;}											   \
	bool operator<=( TFlags rhs ) const{return mState <= rhs.mState;}										   \
	bool operator>=( TFlags rhs ) const{return mState >= rhs.mState;}										   \
	template<int TValue,StringRef TName()> bool operator==( TField<TValue,TName> rhs ) const{return mState == TValue;}										   \
	template<int TValue,StringRef TName()> bool operator!=( TField<TValue,TName> rhs ) const{return mState != TValue;}										   \
	template<int TValue,StringRef TName()> bool operator<( TField<TValue,TName> rhs ) const{return mState < TValue;}											   \
	template<int TValue,StringRef TName()> bool operator>( TField<TValue,TName> rhs ) const{return mState > TValue;}											   \
	template<int TValue,StringRef TName()> bool operator<=( TField<TValue,TName> rhs ) const{return mState <= TValue;}										   \
	template<int TValue,StringRef TName()> bool operator>=( TField<TValue,TName> rhs ) const{return mState >= TValue;}										   \
	TFlags operator|( TFlags rhs ) const{return TFlags( mState | rhs.mState );}								   \
	TFlags operator&( TFlags rhs ) const{return TFlags( mState & rhs.mState );}								   \
	TFlags operator^( TFlags rhs ) const{return TFlags( mState ^ rhs.mState );}								   \
	TFlags operator~() const{return TFlags( ~mState );}														   \
	template<int TValue,StringRef TName()> TFlags operator|( TField<TValue,TName> rhs ) const{return TFlags( mState | TValue );}								   \
	template<int TValue,StringRef TName()> TFlags operator&( TField<TValue,TName> rhs ) const{return TFlags( mState & TValue );}								   \
	template<int TValue,StringRef TName()> TFlags operator^( TField<TValue,TName> rhs ) const{return TFlags( mState ^ TValue );}								   \
	TFlags& operator|=( TFlags rhs ){mState |= rhs.mState;return *this;}								   \
	TFlags& operator&=( TFlags rhs ){mState &= rhs.mState;return *this;}								   \
	TFlags& operator^=( TFlags rhs ){mState ^= rhs.mState;return *this;}								   \
	template<int TValue,StringRef TName()> TFlags operator|=( TField<TValue,TName> rhs ){mState |= TValue;return TFlags( *this );}								   \
	template<int TValue,StringRef TName()> TFlags operator&=( TField<TValue,TName> rhs ){mState &= TValue;return TFlags( *this );}								   \
	template<int TValue,StringRef TName()> TFlags operator^=( TField<TValue,TName> rhs ){mState ^= TValue;return TFlags( *this );}								   \
	TFlags operator<<( unsigned int s ){return TFlags( mState << s );}										   \
	TFlags operator>>( unsigned int s ){return TFlags( mState >> s );}										   \
	TFlags& operator<<=( unsigned int s ){mState <<= s;return *this;}											   \
	TFlags& operator>>=( unsigned int s ){mState >>= s;return *this;}											   \
	int ToInt()const{return mState;}																		\
	bool HasFlag(TFlags rhs)const{return (mState&rhs.ToInt())==rhs.ToInt();}									\
	void SetFlag(TFlags rhs){mState|=rhs.ToInt();}									\
	void RemoveFlag(TFlags rhs){mState&=~rhs.ToInt();}									\
	void SetOrRemoveFlagIf(TFlags rhs,bool isSet){if(isSet){mState|=rhs.ToInt();}else{mState&=~rhs.ToInt();}}\
	template<int TValue,StringRef TName()> bool HasFlag(TField<TValue,TName> field)const{return (mState&TValue)==TValue;}									\
	template<int TValue,StringRef TName()> void SetFlag(TField<TValue,TName> field){mState|=TValue;}															\
	template<int TValue,StringRef TName()> void RemoveFlag(TField<TValue,TName> field){mState&=~TValue;}\
	template<int TValue,StringRef TName()> void SetOrRemoveFlagIf(TField<TValue,TName> field,bool isSet){if(isSet){mState|=TValue;}else{mState&=~TValue;}}\
	bool ForceHasFlag(int flag)const{return (mState&flag)==flag;}									\
	void ForceSetOrRemoveFlagIf(int flag,bool isSet){if(isSet){mState|=flag;}else{mState&=~flag;}}\
	void ForceSetFlag(int flag){mState|=flag;}\
	void ForceRemoveFlag(int flag){mState&=~flag;}\
	void ForceSet(int state){mState=state;}																													   \
	int* ForceGetPointer(){return &mState;}																													   \
	int& ForceGetReference(){return mState;}																													   \
	unsigned int ToUInt()const{return (unsigned int)mState;}											\
	intp GetHashCode()const{return mState;}


#define FLAGS_FIELD_COMMON_OPERATOR(TFlags,TField)														   \
public:	TField(){}																								   \
	bool operator==( TFlags rhs ) const{return TValue == rhs.mState;}										   \
	bool operator!=( TFlags rhs ) const{return TValue != rhs.mState;}										   \
	bool operator<( TFlags rhs ) const{return TValue < rhs.mState;}											   \
	bool operator>( TFlags rhs ) const{return TValue > rhs.mState;}											   \
	bool operator<=( TFlags rhs ) const{return TValue <= rhs.mState;}										   \
	bool operator>=( TFlags rhs ) const{return TValue >= rhs.mState;}										   \
	template<int TValue2,StringRef TName2()> bool operator==( TField<TValue2,TName2> rhs ) const{return TValue == TValue2;}										   \
	template<int TValue2,StringRef TName2()> bool operator!=( TField<TValue2,TName2> rhs ) const{return TValue != TValue2;}										   \
	template<int TValue2,StringRef TName2()> bool operator<( TField<TValue2,TName2> rhs ) const{return TValue < TValue2;}											   \
	template<int TValue2,StringRef TName2()> bool operator>( TField<TValue2,TName2> rhs ) const{return TValue > TValue2;}											   \
	template<int TValue2,StringRef TName2()> bool operator<=( TField<TValue2,TName2> rhs ) const{return TValue <= TValue2;}										   \
	template<int TValue2,StringRef TName2()> bool operator>=( TField<TValue2,TName2> rhs ) const{return TValue >= TValue2;}										   \
	TFlags operator|( TFlags rhs ) const{return TFlags( TValue | rhs.mState );}								   \
	TFlags operator&( TFlags rhs ) const{return TFlags( TValue & rhs.mState );}								   \
	TFlags operator^( TFlags rhs ) const{return TFlags( TValue ^ rhs.mState );}								   \
	TFlags operator~() const{return TFlags(~TValue);}														   \
	template<int TValue2,StringRef TName2()> TFlags operator|( TField<TValue2,TName2> rhs ) const{return TFlags(TValue | TValue2);}								   \
	template<int TValue2,StringRef TName2()> TFlags operator&( TField<TValue2,TName2> rhs ) const{return TFlags(TValue & TValue2);}								   \
	template<int TValue2,StringRef TName2()> TFlags operator^( TField<TValue2,TName2> rhs ) const{return TFlags(TValue ^ TValue2);}								   \
	static const int IntValue=TValue;																															   \
	int ToInt()const{return TValue;}																														   \
	StringRef ToString()const{return TName();}



#define FLAGS_CLASS_BEGIN(TFlags)																														\
class TFlags																																		   \
{																																					   \
	template<int TValue,StringRef TName()> \
class TFlags##Field{friend class TFlags;FLAGS_FIELD_COMMON_OPERATOR(TFlags,TFlags##Field);};	   \
protected:int mState;																																   \
	FLAGS_NAME_COMMON_OPERATOR(TFlags,TFlags##Field);																								   \
public:explicit TFlags(int state=0):mState(state){}

//BEGIN_AUTO_GENERATE_FLAGS_CLASS_END
#define FLAGS_CLASS_END_1(TFlags,T1,P1)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=1;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;

#define FLAGS_CLASS_END_2(TFlags,T1,P1,T2,P2)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=2;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;

#define FLAGS_CLASS_END_3(TFlags,T1,P1,T2,P2,T3,P3)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=3;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;

#define FLAGS_CLASS_END_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=4;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;

#define FLAGS_CLASS_END_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=5;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;

#define FLAGS_CLASS_END_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=6;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;

#define FLAGS_CLASS_END_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=7;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;

#define FLAGS_CLASS_END_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
static StringRef OnName1(){return #T1;}\
static StringRef OnName2(){return #T2;}\
static StringRef OnName3(){return #T3;}\
static StringRef OnName4(){return #T4;}\
static StringRef OnName5(){return #T5;}\
static StringRef OnName6(){return #T6;}\
static StringRef OnName7(){return #T7;}\
static StringRef OnName8(){return #T8;}\
public:\
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=8;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;

#define FLAGS_CLASS_END_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=9;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;

#define FLAGS_CLASS_END_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=10;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;

#define FLAGS_CLASS_END_11(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=11;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;

#define FLAGS_CLASS_END_12(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=12;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;

#define FLAGS_CLASS_END_13(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=13;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;

#define FLAGS_CLASS_END_14(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=14;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;

#define FLAGS_CLASS_END_15(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=15;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;

#define FLAGS_CLASS_END_16(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=16;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;

#define FLAGS_CLASS_END_17(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=17;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;

#define FLAGS_CLASS_END_18(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=18;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;

#define FLAGS_CLASS_END_19(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=19;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;

#define FLAGS_CLASS_END_20(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=20;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;

#define FLAGS_CLASS_END_21(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=21;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;

#define FLAGS_CLASS_END_22(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=22;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;

#define FLAGS_CLASS_END_23(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=23;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;

#define FLAGS_CLASS_END_24(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=24;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;

#define FLAGS_CLASS_END_25(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=25;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;

#define FLAGS_CLASS_END_26(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=26;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;

#define FLAGS_CLASS_END_27(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=27;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;

#define FLAGS_CLASS_END_28(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
if ((mState&P28)==P28){if(!result.IsNullOrEmpty()){result+='|';}result+=#T28;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=28;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
static const TFlags##Field<P28,TFlags::OnName28> T28;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P28,TFlags::OnName28> TFlags::T28;

#define FLAGS_CLASS_END_29(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
if ((mState&P28)==P28){if(!result.IsNullOrEmpty()){result+='|';}result+=#T28;}\
if ((mState&P29)==P29){if(!result.IsNullOrEmpty()){result+='|';}result+=#T29;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=29;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
static const TFlags##Field<P28,TFlags::OnName28> T28;\
static const TFlags##Field<P29,TFlags::OnName29> T29;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P28,TFlags::OnName28> TFlags::T28;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P29,TFlags::OnName29> TFlags::T29;

#define FLAGS_CLASS_END_30(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
if ((mState&P28)==P28){if(!result.IsNullOrEmpty()){result+='|';}result+=#T28;}\
if ((mState&P29)==P29){if(!result.IsNullOrEmpty()){result+='|';}result+=#T29;}\
if ((mState&P30)==P30){if(!result.IsNullOrEmpty()){result+='|';}result+=#T30;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=30;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
static const TFlags##Field<P28,TFlags::OnName28> T28;\
static const TFlags##Field<P29,TFlags::OnName29> T29;\
static const TFlags##Field<P30,TFlags::OnName30> T30;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P28,TFlags::OnName28> TFlags::T28;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P29,TFlags::OnName29> TFlags::T29;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P30,TFlags::OnName30> TFlags::T30;

#define FLAGS_CLASS_END_31(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
if ((mState&P28)==P28){if(!result.IsNullOrEmpty()){result+='|';}result+=#T28;}\
if ((mState&P29)==P29){if(!result.IsNullOrEmpty()){result+='|';}result+=#T29;}\
if ((mState&P30)==P30){if(!result.IsNullOrEmpty()){result+='|';}result+=#T30;}\
if ((mState&P31)==P31){if(!result.IsNullOrEmpty()){result+='|';}result+=#T31;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=31;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
static const TFlags##Field<P28,TFlags::OnName28> T28;\
static const TFlags##Field<P29,TFlags::OnName29> T29;\
static const TFlags##Field<P30,TFlags::OnName30> T30;\
static const TFlags##Field<P31,TFlags::OnName31> T31;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30,#T31};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P28,TFlags::OnName28> TFlags::T28;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P29,TFlags::OnName29> TFlags::T29;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P30,TFlags::OnName30> TFlags::T30;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P31,TFlags::OnName31> TFlags::T31;

#define FLAGS_CLASS_END_32(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)\
private:\
static StringRef OnName0(){return "none";}\
static StringRef OnNameAll(){return "all";}\
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
HeapString ToString()const{if (mState==0){return HeapString("none");}\
if (mState==(P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31|P32)){return HeapString("all");}\
HeapString result;\
if ((mState&P1)==P1){if(!result.IsNullOrEmpty()){result+='|';}result+=#T1;}\
if ((mState&P2)==P2){if(!result.IsNullOrEmpty()){result+='|';}result+=#T2;}\
if ((mState&P3)==P3){if(!result.IsNullOrEmpty()){result+='|';}result+=#T3;}\
if ((mState&P4)==P4){if(!result.IsNullOrEmpty()){result+='|';}result+=#T4;}\
if ((mState&P5)==P5){if(!result.IsNullOrEmpty()){result+='|';}result+=#T5;}\
if ((mState&P6)==P6){if(!result.IsNullOrEmpty()){result+='|';}result+=#T6;}\
if ((mState&P7)==P7){if(!result.IsNullOrEmpty()){result+='|';}result+=#T7;}\
if ((mState&P8)==P8){if(!result.IsNullOrEmpty()){result+='|';}result+=#T8;}\
if ((mState&P9)==P9){if(!result.IsNullOrEmpty()){result+='|';}result+=#T9;}\
if ((mState&P10)==P10){if(!result.IsNullOrEmpty()){result+='|';}result+=#T10;}\
if ((mState&P11)==P11){if(!result.IsNullOrEmpty()){result+='|';}result+=#T11;}\
if ((mState&P12)==P12){if(!result.IsNullOrEmpty()){result+='|';}result+=#T12;}\
if ((mState&P13)==P13){if(!result.IsNullOrEmpty()){result+='|';}result+=#T13;}\
if ((mState&P14)==P14){if(!result.IsNullOrEmpty()){result+='|';}result+=#T14;}\
if ((mState&P15)==P15){if(!result.IsNullOrEmpty()){result+='|';}result+=#T15;}\
if ((mState&P16)==P16){if(!result.IsNullOrEmpty()){result+='|';}result+=#T16;}\
if ((mState&P17)==P17){if(!result.IsNullOrEmpty()){result+='|';}result+=#T17;}\
if ((mState&P18)==P18){if(!result.IsNullOrEmpty()){result+='|';}result+=#T18;}\
if ((mState&P19)==P19){if(!result.IsNullOrEmpty()){result+='|';}result+=#T19;}\
if ((mState&P20)==P20){if(!result.IsNullOrEmpty()){result+='|';}result+=#T20;}\
if ((mState&P21)==P21){if(!result.IsNullOrEmpty()){result+='|';}result+=#T21;}\
if ((mState&P22)==P22){if(!result.IsNullOrEmpty()){result+='|';}result+=#T22;}\
if ((mState&P23)==P23){if(!result.IsNullOrEmpty()){result+='|';}result+=#T23;}\
if ((mState&P24)==P24){if(!result.IsNullOrEmpty()){result+='|';}result+=#T24;}\
if ((mState&P25)==P25){if(!result.IsNullOrEmpty()){result+='|';}result+=#T25;}\
if ((mState&P26)==P26){if(!result.IsNullOrEmpty()){result+='|';}result+=#T26;}\
if ((mState&P27)==P27){if(!result.IsNullOrEmpty()){result+='|';}result+=#T27;}\
if ((mState&P28)==P28){if(!result.IsNullOrEmpty()){result+='|';}result+=#T28;}\
if ((mState&P29)==P29){if(!result.IsNullOrEmpty()){result+='|';}result+=#T29;}\
if ((mState&P30)==P30){if(!result.IsNullOrEmpty()){result+='|';}result+=#T30;}\
if ((mState&P31)==P31){if(!result.IsNullOrEmpty()){result+='|';}result+=#T31;}\
if ((mState&P32)==P32){if(!result.IsNullOrEmpty()){result+='|';}result+=#T32;}\
return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(StringRef name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(StringRef name,bool ignoreCase=false){TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);MEDUSA_ASSERT(splitResult,"Invalid flags names");UN_USED(splitResult);FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}MEDUSA_ASSERT_TRUE(isSucceed,"Invalid flags names");return result;}\
static bool TryParse(TFlags& outFlags,StringRef name,bool ignoreCase=false){bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));FOR_EACH_COLLECTION(i,names){const HeapString& str=*i;if (isSucceed){for (j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static const unsigned int Size=32;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnName0> None;\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31|P32,TFlags::OnNameAll> All;\
static const TFlags##Field<P1,TFlags::OnName1> T1;\
static const TFlags##Field<P2,TFlags::OnName2> T2;\
static const TFlags##Field<P3,TFlags::OnName3> T3;\
static const TFlags##Field<P4,TFlags::OnName4> T4;\
static const TFlags##Field<P5,TFlags::OnName5> T5;\
static const TFlags##Field<P6,TFlags::OnName6> T6;\
static const TFlags##Field<P7,TFlags::OnName7> T7;\
static const TFlags##Field<P8,TFlags::OnName8> T8;\
static const TFlags##Field<P9,TFlags::OnName9> T9;\
static const TFlags##Field<P10,TFlags::OnName10> T10;\
static const TFlags##Field<P11,TFlags::OnName11> T11;\
static const TFlags##Field<P12,TFlags::OnName12> T12;\
static const TFlags##Field<P13,TFlags::OnName13> T13;\
static const TFlags##Field<P14,TFlags::OnName14> T14;\
static const TFlags##Field<P15,TFlags::OnName15> T15;\
static const TFlags##Field<P16,TFlags::OnName16> T16;\
static const TFlags##Field<P17,TFlags::OnName17> T17;\
static const TFlags##Field<P18,TFlags::OnName18> T18;\
static const TFlags##Field<P19,TFlags::OnName19> T19;\
static const TFlags##Field<P20,TFlags::OnName20> T20;\
static const TFlags##Field<P21,TFlags::OnName21> T21;\
static const TFlags##Field<P22,TFlags::OnName22> T22;\
static const TFlags##Field<P23,TFlags::OnName23> T23;\
static const TFlags##Field<P24,TFlags::OnName24> T24;\
static const TFlags##Field<P25,TFlags::OnName25> T25;\
static const TFlags##Field<P26,TFlags::OnName26> T26;\
static const TFlags##Field<P27,TFlags::OnName27> T27;\
static const TFlags##Field<P28,TFlags::OnName28> T28;\
static const TFlags##Field<P29,TFlags::OnName29> T29;\
static const TFlags##Field<P30,TFlags::OnName30> T30;\
static const TFlags##Field<P31,TFlags::OnName31> T31;\
static const TFlags##Field<P32,TFlags::OnName32> T32;\
};\
WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10,#T11,#T12,#T13,#T14,#T15,#T16,#T17,#T18,#T19,#T20,#T21,#T22,#T23,#T24,#T25,#T26,#T27,#T28,#T29,#T30,#T31,#T32};\
WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31,P32};\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnName0> TFlags::None;\
WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10|P11|P12|P13|P14|P15|P16|P17|P18|P19|P20|P21|P22|P23|P24|P25|P26|P27|P28|P29|P30|P31|P32,TFlags::OnNameAll> TFlags::All;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName1> TFlags::T1;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName2> TFlags::T2;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName3> TFlags::T3;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName4> TFlags::T4;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName5> TFlags::T5;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName6> TFlags::T6;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName7> TFlags::T7;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName8> TFlags::T8;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName9> TFlags::T9;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName10> TFlags::T10;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P11,TFlags::OnName11> TFlags::T11;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P12,TFlags::OnName12> TFlags::T12;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P13,TFlags::OnName13> TFlags::T13;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P14,TFlags::OnName14> TFlags::T14;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P15,TFlags::OnName15> TFlags::T15;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P16,TFlags::OnName16> TFlags::T16;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P17,TFlags::OnName17> TFlags::T17;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P18,TFlags::OnName18> TFlags::T18;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P19,TFlags::OnName19> TFlags::T19;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P20,TFlags::OnName20> TFlags::T20;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P21,TFlags::OnName21> TFlags::T21;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P22,TFlags::OnName22> TFlags::T22;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P23,TFlags::OnName23> TFlags::T23;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P24,TFlags::OnName24> TFlags::T24;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P25,TFlags::OnName25> TFlags::T25;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P26,TFlags::OnName26> TFlags::T26;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P27,TFlags::OnName27> TFlags::T27;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P28,TFlags::OnName28> TFlags::T28;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P29,TFlags::OnName29> TFlags::T29;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P30,TFlags::OnName30> TFlags::T30;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P31,TFlags::OnName31> TFlags::T31;\
	WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P32,TFlags::OnName32> TFlags::T32;

//END_AUTO_GENERATE_FLAGS_CLASS_END

//BEGIN_AUTO_GENERATE_FLAGS_DEFINE
#define STRONG_FLAGS_CUSTOM_1(TFlags,T1,P1)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_1(TFlags,T1,P1)
#define STRONG_FLAGS_CUSTOM_2(TFlags,T1,P1,T2,P2)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_2(TFlags,T1,P1,T2,P2)
#define STRONG_FLAGS_CUSTOM_3(TFlags,T1,P1,T2,P2,T3,P3)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_3(TFlags,T1,P1,T2,P2,T3,P3)
#define STRONG_FLAGS_CUSTOM_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)
#define STRONG_FLAGS_CUSTOM_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)
#define STRONG_FLAGS_CUSTOM_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)
#define STRONG_FLAGS_CUSTOM_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)
#define STRONG_FLAGS_CUSTOM_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)
#define STRONG_FLAGS_CUSTOM_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)
#define STRONG_FLAGS_CUSTOM_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)
#define STRONG_FLAGS_CUSTOM_11(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_11(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11)
#define STRONG_FLAGS_CUSTOM_12(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_12(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12)
#define STRONG_FLAGS_CUSTOM_13(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_13(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13)
#define STRONG_FLAGS_CUSTOM_14(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_14(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14)
#define STRONG_FLAGS_CUSTOM_15(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_15(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15)
#define STRONG_FLAGS_CUSTOM_16(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_16(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16)
#define STRONG_FLAGS_CUSTOM_17(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_17(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17)
#define STRONG_FLAGS_CUSTOM_18(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_18(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18)
#define STRONG_FLAGS_CUSTOM_19(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_19(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19)
#define STRONG_FLAGS_CUSTOM_20(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_20(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20)
#define STRONG_FLAGS_CUSTOM_21(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_21(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21)
#define STRONG_FLAGS_CUSTOM_22(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_22(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22)
#define STRONG_FLAGS_CUSTOM_23(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_23(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23)
#define STRONG_FLAGS_CUSTOM_24(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_24(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24)
#define STRONG_FLAGS_CUSTOM_25(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_25(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25)
#define STRONG_FLAGS_CUSTOM_26(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_26(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26)
#define STRONG_FLAGS_CUSTOM_27(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_27(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27)
#define STRONG_FLAGS_CUSTOM_28(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_28(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28)
#define STRONG_FLAGS_CUSTOM_29(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_29(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29)
#define STRONG_FLAGS_CUSTOM_30(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_30(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30)
#define STRONG_FLAGS_CUSTOM_31(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_31(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31)
#define STRONG_FLAGS_CUSTOM_32(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_32(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10,T11,P11,T12,P12,T13,P13,T14,P14,T15,P15,T16,P16,T17,P17,T18,P18,T19,P19,T20,P20,T21,P21,T22,P22,T23,P23,T24,P24,T25,P25,T26,P26,T27,P27,T28,P28,T29,P29,T30,P30,T31,P31,T32,P32)




#define STRONG_FLAGS_1(TEnum,T1)	STRONG_FLAGS_CUSTOM_1(TEnum,T1,1)
#define STRONG_FLAGS_2(TEnum,T1,T2)	STRONG_FLAGS_CUSTOM_2(TEnum,T1,1,T2,2)
#define STRONG_FLAGS_3(TEnum,T1,T2,T3)	STRONG_FLAGS_CUSTOM_3(TEnum,T1,1,T2,2,T3,4)
#define STRONG_FLAGS_4(TEnum,T1,T2,T3,T4)	STRONG_FLAGS_CUSTOM_4(TEnum,T1,1,T2,2,T3,4,T4,8)
#define STRONG_FLAGS_5(TEnum,T1,T2,T3,T4,T5)	STRONG_FLAGS_CUSTOM_5(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16)
#define STRONG_FLAGS_6(TEnum,T1,T2,T3,T4,T5,T6)	STRONG_FLAGS_CUSTOM_6(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32)
#define STRONG_FLAGS_7(TEnum,T1,T2,T3,T4,T5,T6,T7)	STRONG_FLAGS_CUSTOM_7(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64)
#define STRONG_FLAGS_8(TEnum,T1,T2,T3,T4,T5,T6,T7,T8)	STRONG_FLAGS_CUSTOM_8(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128)
#define STRONG_FLAGS_9(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9)	STRONG_FLAGS_CUSTOM_9(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256)
#define STRONG_FLAGS_10(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)	STRONG_FLAGS_CUSTOM_10(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512)
#define STRONG_FLAGS_11(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)	STRONG_FLAGS_CUSTOM_11(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024)
#define STRONG_FLAGS_12(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12)	STRONG_FLAGS_CUSTOM_12(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048)
#define STRONG_FLAGS_13(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13)	STRONG_FLAGS_CUSTOM_13(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096)
#define STRONG_FLAGS_14(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14)	STRONG_FLAGS_CUSTOM_14(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192)
#define STRONG_FLAGS_15(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15)	STRONG_FLAGS_CUSTOM_15(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384)
#define STRONG_FLAGS_16(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16)	STRONG_FLAGS_CUSTOM_16(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768)
#define STRONG_FLAGS_17(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17)	STRONG_FLAGS_CUSTOM_17(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536)
#define STRONG_FLAGS_18(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18)	STRONG_FLAGS_CUSTOM_18(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072)
#define STRONG_FLAGS_19(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19)	STRONG_FLAGS_CUSTOM_19(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144)
#define STRONG_FLAGS_20(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20)	STRONG_FLAGS_CUSTOM_20(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288)
#define STRONG_FLAGS_21(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21)	STRONG_FLAGS_CUSTOM_21(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576)
#define STRONG_FLAGS_22(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22)	STRONG_FLAGS_CUSTOM_22(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152)
#define STRONG_FLAGS_23(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23)	STRONG_FLAGS_CUSTOM_23(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304)
#define STRONG_FLAGS_24(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24)	STRONG_FLAGS_CUSTOM_24(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608)
#define STRONG_FLAGS_25(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25)	STRONG_FLAGS_CUSTOM_25(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216)
#define STRONG_FLAGS_26(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26)	STRONG_FLAGS_CUSTOM_26(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432)
#define STRONG_FLAGS_27(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27)	STRONG_FLAGS_CUSTOM_27(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864)
#define STRONG_FLAGS_28(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28)	STRONG_FLAGS_CUSTOM_28(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864,T28,134217728)
#define STRONG_FLAGS_29(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29)	STRONG_FLAGS_CUSTOM_29(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864,T28,134217728,T29,268435456)
#define STRONG_FLAGS_30(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30)	STRONG_FLAGS_CUSTOM_30(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864,T28,134217728,T29,268435456,T30,536870912)
#define STRONG_FLAGS_31(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31)	STRONG_FLAGS_CUSTOM_31(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864,T28,134217728,T29,268435456,T30,536870912,T31,1073741824)
#define STRONG_FLAGS_32(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32)	STRONG_FLAGS_CUSTOM_32(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512,T11,1024,T12,2048,T13,4096,T14,8192,T15,16384,T16,32768,T17,65536,T18,131072,T19,262144,T20,524288,T21,1048576,T22,2097152,T23,4194304,T24,8388608,T25,16777216,T26,33554432,T27,67108864,T28,134217728,T29,268435456,T30,536870912,T31,1073741824,T32,-2147483648)
//END_AUTO_GENERATE_FLAGS_DEFINE

