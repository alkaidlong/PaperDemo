#include "MedusaCorePreCompiled.h"
#include "Core/String/StringParser.h"

MEDUSA_BEGIN;
#pragma region A

#pragma region StringTo
template<class TValue>
TValue StringParser::StringTo( const StringRef& inString )
{
	TValue result;
	return result;
}

template<>
StringRef StringParser::StringTo(const StringRef& inString)
{
	return inString;
}



template<>
bool StringParser::StringTo(const StringRef& inString)
{
	if (inString.Length()!=4)
	{
		return false;
	}

	return inString.Compare("TRUE",true)==0;
}

template<>
int StringParser::StringTo(const StringRef& inString)
{
	return atoi(inString.Buffer());
}

template<>
int64 StringParser::StringTo(const StringRef& inString)
{
	return strtoll(inString.c_str(),NULL,10);
}

template<>
uint64 StringParser::StringTo(const StringRef& inString)
{
	return strtoull(inString.c_str(),NULL,10);
}

template<>
uint32 StringParser::StringTo(const StringRef& inString)
{
	return (uint32)strtoul(inString.c_str(),NULL,10);
}

template<>
char StringParser::StringTo(const StringRef& inString)
{
	return (char)strtol(inString.c_str(),NULL,10);
}


template<>
unsigned char StringParser::StringTo(const StringRef& inString)
{
	return (unsigned char)strtoul(inString.c_str(),NULL,10);
}

template<>
short StringParser::StringTo(const StringRef& inString)
{
	return (short)strtol(inString.c_str(),NULL,10);
}

template<>
float StringParser::StringTo(const StringRef& inString)
{
	return (float)strtod(inString.c_str(),NULL);
}

template<>
double StringParser::StringTo(const StringRef& inString)
{
	return atof(inString.Buffer());
}

#pragma endregion StringTo

#pragma region ToString

template<>
StringParser::ResultStringType StringParser::ToString(const bool& inValue)
{
	return inValue?ResultStringType("True"):ResultStringType("False");
}

template<>
StringParser::ResultStringType StringParser::ToString(const int& inValue)
{
	ResultStringType temp;
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%d",inValue);
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}

template<>
StringParser::ResultStringType StringParser::ToString(const int64& inValue)
{
	ResultStringType temp;
	
#ifdef MEDUSA_WINDOWS
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%I64x",inValue);
#else
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%lld",inValue);
#endif
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}

template<>
StringParser::ResultStringType StringParser::ToString(const uint32& inValue)
{
	ResultStringType temp;

	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%u",inValue);
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}
#ifndef MEDUSA_LINUX
template<>
StringParser::ResultStringType StringParser::ToString(const unsigned long& inValue)
{
	ResultStringType temp;
    
#ifdef MEDUSA_WINDOWS
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%I64x",inValue);
#else
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%llu",inValue);
#endif
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}
#endif

template<>
StringParser::ResultStringType StringParser::ToString(const uint64& inValue)
{
	ResultStringType temp;

#ifdef MEDUSA_WINDOWS
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%I64x",inValue);
#else
	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%llu",inValue);
#endif
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}

template<>
StringParser::ResultStringType StringParser::ToString(const short& inValue)
{
	ResultStringType temp;

	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%d",inValue);
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}


template<>
StringParser::ResultStringType StringParser::ToString(const float& inValue)
{
	ResultStringType temp;

	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%f",inValue);
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}

template<>
StringParser::ResultStringType StringParser::ToString(const double& inValue)
{
	ResultStringType temp;

	int r=StdString::SPrintf(temp.Buffer(),temp.Size(),"%f",inValue);
	if (r!=-1)
	{
		temp.ForceSetLength(r);
	}
	return temp;
}


template<class TValue>
StringParser::ResultStringType StringParser::ToString( const TValue& inValue )
{
	return ResultStringType("");
}


#pragma endregion ToString


bool StringParser::EncodeString( const StringRef& fromString,HeapString& toString, const char* fromCode, const char* toCode )
{
	RETURN_TRUE_IF_EMPTY(fromString);
	iconv_t iconvH;
	iconvH = iconv_open(fromCode, toCode);
	if (iconvH == 0)
	{
		return false;
	}

//#ifdef MEDUSA_WINDOWS

	char* strChar = (char*)fromString.c_str();
	char** pin = &strChar;
	size_t strLength = fromString.Length();
	char* outbuf = (char*) malloc(strLength*4);
	char* pBuff = outbuf;
	memset( outbuf, 0, strLength*4);
	size_t outLength = strLength*4;
#if defined(MEDUSA_IOS)||defined(MEDUSA_ANDROID)||defined(MEDUSA_LINUX)
    if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))
#else
    if (-1 == iconv(iconvH, (const char**)pin, &strLength, &outbuf, &outLength))
#endif
	
	{
		free(pBuff);
		iconv_close(iconvH);
		return false;
	}
	toString = pBuff;
	iconv_close(iconvH);

	free(pBuff);
//#endif
	return true;
}

bool StringParser::GBKToUTF8( const StringRef& fromString,HeapString& toString )
{
	return EncodeString(fromString,toString,"gb2312","utf-8");
}

bool StringParser::UTF8ToGBK( const StringRef& fromString,HeapString& toString )
{
	return EncodeString(fromString,toString,"utf-8","gb2312");
}

bool StringParser::UTF16ToGBK( const StringRef& fromString,HeapString& toString )
{
	return EncodeString(fromString,toString,"utf-16","gb2312");
}

#pragma endregion A

#pragma region W

#pragma region WStringTo

template<class TValue>
TValue StringParser::WStringTo( const WStringRef& inString )
{
	TValue result;
	return result;
}

template<>
WStringRef StringParser::WStringTo(const WStringRef& inString)
{
	return inString;
}

template<>
bool StringParser::WStringTo(const WStringRef& inString)
{
	if (inString.Length()!=4)
	{
		return false;
	}

	return inString.Compare(L"TRUE",true)==0;
}

template<>
int StringParser::WStringTo(const WStringRef& inString)
{
	return (int)wcstol(inString.Buffer(),NULL,10);
}

template<>
int64 StringParser::WStringTo(const WStringRef& inString)
{
#ifdef MEDUSA_WINDOWS
	return _wcstoi64(inString.c_str(),NULL,10);
#endif
#ifdef MEDUSA_IOS
	return wcstoll(inString.c_str(),NULL,10);
#endif

#ifdef MEDUSA_ANDROID
	std::wstringstream ss;
	ss<<inString.c_str();
	int64 r;
	ss>>r;
	return r;
#endif

	return 0;
}

template<>
uint64 StringParser::WStringTo(const WStringRef& inString)
{
#ifdef MEDUSA_WINDOWS
	return _wcstoui64(inString.c_str(),NULL,10);
#endif
#ifdef MEDUSA_IOS
	return wcstoull(inString.c_str(),NULL,10);
#endif

#ifdef MEDUSA_ANDROID
	std::wstringstream ss;
	ss<<inString.c_str();
	uint64 r;
	ss>>r;
	return r;
#endif

	return 0;
}

template<>
uint32 StringParser::WStringTo(const WStringRef& inString)
{
	return (uint32)wcstoul(inString.c_str(),NULL,10);
}

template<>
char StringParser::WStringTo(const WStringRef& inString)
{
	return (char)wcstol(inString.c_str(),NULL,10);
}


template<>
unsigned char StringParser::WStringTo(const WStringRef& inString)
{
	return (unsigned char)wcstol(inString.c_str(),NULL,10);
}

template<>
short StringParser::WStringTo(const WStringRef& inString)
{
	return (short)wcstol(inString.c_str(),NULL,10);
}

template<>
float StringParser::WStringTo(const WStringRef& inString)
{
	return (float)wcstod(inString.c_str(),NULL);
}

template<>
double StringParser::WStringTo(const WStringRef& inString)
{
	return (float)wcstod(inString.c_str(),NULL);
}


#pragma endregion WStringTo

#pragma region ToWString

template<>
StringParser::WResultStringType StringParser::ToWString(const bool& inValue)
{
	return inValue?WResultStringType(L"True"):WResultStringType(L"False");
}

template<>
StringParser::WResultStringType StringParser::ToWString(const int32& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%d",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}

template<>
StringParser::WResultStringType StringParser::ToWString(const uint32& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%u",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}


template<>
StringParser::WResultStringType StringParser::ToWString(const short& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%d",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}

template<>
StringParser::WResultStringType StringParser::ToWString(const int64& inValue)
{

	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%lld",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}

template<>
StringParser::WResultStringType StringParser::ToWString(const uint64& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%llu",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}


template<>
StringParser::WResultStringType StringParser::ToWString(const float& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%f",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);
}

template<>
StringParser::WResultStringType StringParser::ToWString(const double& inValue)
{
	wchar_t temp[mResultStringBufferSize];
	int r=StdString::SPrintf(temp,mResultStringBufferSize,L"%f",inValue);
	if (r!=-1)
	{
		temp[r]=L'\0';
	}
	return WResultStringType(temp);

}

template<class TValue>
StringParser::WResultStringType StringParser::ToWString( const TValue& inValue )
{
	return WResultStringType(L"");
}


#pragma endregion ToString


#pragma endregion W




intp StringParser::ConvertToBuffer( const List<char>& inBuffer,List<wchar_t>& outBuffer )
{
	return ConvertToBuffer(inBuffer.GetItems(),inBuffer.GetSize(),outBuffer);
}

intp StringParser::ConvertToBuffer( const char* str,size_t length,List<wchar_t>& outBuffer )
{
	outBuffer.Clear();
	if (length==0)
	{
		return 0;
	}

	outBuffer.ReserveSize(length+1);
	const UTF8* sourceStart = reinterpret_cast<const UTF8*>(str);
	const UTF8* sourceEnd = sourceStart + length;
#ifdef MEDUSA_WINDOWS
	//sizeof(wchar_t)==2
	
	UTF16* targetStart = reinterpret_cast<UTF16*>(outBuffer.GetItems());
	UTF16* targetEnd = targetStart + length;
	ConversionResult res = MedusaConvertUTF8toUTF16(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
	*targetStart = 0;
	if(res==conversionOK)
	{
		return targetStart-reinterpret_cast<UTF16*>(outBuffer.GetItems());
	}
#else
	//sizeof(wchar_t)==4
	UTF32* targetStart = reinterpret_cast<UTF32*>(outBuffer.GetItems());
	UTF32* targetEnd = targetStart + length;
	ConversionResult res = MedusaConvertUTF8toUTF32(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
	*targetStart = 0;
	if(res==conversionOK)
	{
		return targetStart-reinterpret_cast<UTF32*>(outBuffer.GetItems());
	}
#endif
	return 0;

}

intp StringParser::ConvertToBuffer(const List<wchar_t>& inBuffer,List<char>& outBuffer )
{
	return ConvertToBuffer(inBuffer.GetItems(),inBuffer.GetSize(),outBuffer);
}


intp StringParser::ConvertToBuffer( const wchar_t* str,size_t length,List<char>& outBuffer )
{
	outBuffer.Clear();
	if (length==0)
	{
		return 0;
	}


#ifdef MEDUSA_WINDOWS
	//sizeof(wchar_t)==2
	size_t utf8Size=length*3+1;
	outBuffer.ReserveSize(utf8Size);

	const UTF16* sourceStart = reinterpret_cast<const UTF16*>(str);
	const UTF16* sourceEnd = sourceStart + length;
	UTF8* targetStart = reinterpret_cast<UTF8*>(outBuffer.GetItems());
	UTF8* targetEnd = targetStart + utf8Size;
	ConversionResult res = MedusaConvertUTF16toUTF8(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
	*targetStart = 0;
	if(res==conversionOK)
	{
		return targetStart-reinterpret_cast<UTF8*>(outBuffer.GetItems());
	}
#else
	//sizeof(wchar_t)==4
	size_t utf8Size=length*4+1;
	outBuffer.ReserveSize(utf8Size);

	const UTF32* sourceStart = reinterpret_cast<const UTF32*>(str);
	const UTF32* sourceEnd = sourceStart + length;
	UTF8* targetStart = reinterpret_cast<UTF8*>(outBuffer.GetItems());
	UTF8* targetEnd = targetStart + utf8Size;
	ConversionResult res = MedusaConvertUTF32toUTF8(&sourceStart, sourceEnd, &targetStart, targetEnd, strictConversion);
	*targetStart = 0;
	if(res==conversionOK)
	{
		return targetStart-reinterpret_cast<UTF8*>(outBuffer.GetItems());
	}
#endif

	return 0;
}

Medusa::HeapString StringParser::ToA( const WStringRef& str )
{
	List<char> tempBuffer;
	intp count=ConvertToBuffer(str.c_str(),str.Length(),tempBuffer);
	if(count<=0)
	{
		return HeapString::Empty;
	}
	return HeapString(tempBuffer.GetItems(),count+1);
}

Medusa::WHeapString StringParser::ToW( const StringRef& str )
{
	List<wchar_t> tempBuffer;
	intp count=ConvertToBuffer(str.c_str(),str.Length(),tempBuffer);
	if(count<=0)
	{
		return WHeapString::Empty;
	}
	return WHeapString(tempBuffer.GetItems(),count+1);
}



List<char> StringParser::mBuffer;
List<wchar_t> StringParser::mBufferW;


MEDUSA_END;
