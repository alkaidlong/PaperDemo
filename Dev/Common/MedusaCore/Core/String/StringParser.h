#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/String/StdString.h"


MEDUSA_BEGIN;

class StringParser
{
	const static size_t mResultStringBufferSize=64;
public:
#pragma region A
	typedef StackString<mResultStringBufferSize> ResultStringType;

	template<class TValue>
	static TValue StringTo(const StringRef& inString);

	template<class TValue>
	static ResultStringType ToString(const TValue& inValue);


	static bool GBKToUTF8(const StringRef& fromString,HeapString& toString);
	static bool UTF8ToGBK(const StringRef& fromString,HeapString& toString);
	static bool UTF16ToGBK(const StringRef& fromString,HeapString& toString);
	static bool EncodeString(const StringRef& fromString,HeapString& toString, const char* fromCode, const char* toCode);
	
#pragma endregion A

#pragma region W
	typedef WStackString<mResultStringBufferSize> WResultStringType;

	template<class TValue>
	static TValue WStringTo(const WStringRef& inString);

	template<class TValue>
	static WResultStringType ToWString(const TValue& inValue);

#pragma endregion W

	
	template<typename T>
	static THeapString<T> Format(const T* format, ... )
	{
		va_list args;
		va_start(args, format);
		return FormatV(format,args);
	}

	template<typename T>
	static THeapString<T> FormatV(const T* format,va_list args)
	{
		static List<T> tempBuffer;
		FormatToBufferV(tempBuffer,format,args);
		return THeapString<T>(tempBuffer.GetItems());
	}

	template<typename T>
	static void FormatToBuffer(List<T>& buffer,const T*  format, ... )
	{
		va_list args;
		va_start(args, format);
		return FormatToBufferV(buffer,format,args);
	}

	template<typename T>
	static void FormatToBufferV(List<T>& buffer,const T*  format,va_list args)
	{
		int size=StdString::GetFormatLength(format,args)+1;
		buffer.ReserveSize(size);
		StdString::VSNPrintf(buffer.GetItems(), buffer.GetSize(),size,format, args);
		va_end(args);
	}

	template<typename T,size_t returnBufferSize>
	static TStackString<T,returnBufferSize> FormatStackString(const T*  format, ... )
	{
		va_list args;
		va_start(args, format);
		return FormatStackStringV<T,returnBufferSize>(format,args);
	}

	template<typename T,size_t returnBufferSize>
	static TStackString<T,returnBufferSize> FormatStackStringV(const T*  format,va_list args)
	{
		TStackString<T,returnBufferSize> result;

		int length=StdString::GetFormatLength(format,args)+1;
		if (length<=0)
		{
			return result;
		}
		size_t size= Math::Min((size_t)length,returnBufferSize);
		StdString::VSPrintf(result.Buffer(),size,format,args);
		va_end(args);
		return result;
	}
	
	static intp ConvertToBuffer(const List<char>& inBuffer,List<wchar_t>& outBuffer);
	static intp ConvertToBuffer(const char* str,size_t length,List<wchar_t>& outBuffer);

	static intp ConvertToBuffer(const List<wchar_t>& inBuffer,List<char>& outBuffer);
	static intp ConvertToBuffer(const wchar_t* str,size_t length,List<char>& outBuffer);

	static HeapString ToA(const WStringRef& str);
	static WHeapString ToW(const StringRef& str);


	template<typename T>
	static bool Split(const TStringRef<T>& str,const TStringRef<T>& delimter,List<THeapString<T> >& outResults )
	{
		RETURN_FALSE_IF(str.IsNull());
		THeapString<T> copy=str;
		T* copyBuffer=copy.Buffer();

		T* context;
		T* result=StdString::SplitString(copyBuffer,delimter.Buffer(),&context);
		while (result!=NULL)
		{
			outResults.Append(THeapString<T>::Empty);
			outResults.Last()=result;
			result=StdString::SplitString(NULL,delimter.Buffer(),&context);
		}

		return !outResults.IsEmpty();
	}

	template<typename T>
	static bool Join(const TStringRef<T>& delimter,ICollection<TStringRef<T> >& strings,THeapString<T>& outResult)
	{
		outResult.Clear();
		size_t count=strings.GetCount();
		FOR_EACH_COLLECTION(i,strings)
		{
			const TStringRef<T>& str=*i;
			outResult.Append(str);
			if (i!=count-1)
			{
				outResult.Append(delimter);
			}
		}

		return !outResult.IsEmpty();
	}

	template<typename T>
	static bool SplitToWords(const TStringRef<T>& str,List<THeapString<T> >& outResults )
	{
		return Split(str,StdString::ConstValues<T>::WordSeparators,outResults);
	}
private:
	static List<char> mBuffer;
	static List<wchar_t> mBufferW;

};

MEDUSA_END;
