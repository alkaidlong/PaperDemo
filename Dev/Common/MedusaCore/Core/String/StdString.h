#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Collection/BitArray.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

namespace StdString
{
	static bool IsDigit(int c){return isdigit(c)!=0;}
	static bool IsXDigit(int c){return isxdigit(c)!=0;}

	static bool IsAlpha(int c){return isalpha(c)!=0;}
	static bool IsSpaceOrTab(int c){return c=='\t'||c==' ';}	//tab or space
	static bool IsSpace(int c){return isspace(c)!=0;}

	static bool IsControl(int c){return iscntrl(c)!=0;}
	static bool IsLower(int c){return islower(c)!=0;}
	static bool IsUpper(int c){return isupper(c)!=0;}


	static bool IsGraph(int c){return isgraph(c)!=0;}
	static bool IsPrint(int c){return isprint(c)!=0;}
	static bool IsPunct(int c){return ispunct(c)!=0;}	//Checks whether c is a punctuation character.






	static size_t GetLength(const char* src){return ::strlen(src);}
	static size_t GetLength(const wchar_t* src){return ::wcslen(src);}

	static int Compare(const char* src,const char* dst){return ::strcmp(src,dst);}
	static int Compare(const wchar_t* src,const wchar_t* dst){return ::wcscmp(src,dst);}

	static int CompareN(const char* src,const char* dst,size_t count){return ::strncmp(src,dst,count);}
	static int CompareN(const wchar_t* src,const wchar_t* dst,size_t count){return ::wcsncmp(src,dst,count);}

	static int CompareIgnoreCase(const char* dst,const char* src)
	{
		int f, l;

		do
		{
			if ( ((f = (unsigned char)(*(dst++))) >= 'A') && (f <= 'Z') )
				f -= 'A' - 'a';
			if ( ((l = (unsigned char)(*(src++))) >= 'A') && (l <= 'Z') )
				l -= 'A' - 'a';
		}
		while ( f && (f == l) );

		return(f - l);
	}
	static int CompareIgnoreCase(const wchar_t* dst,const wchar_t* src)
	{
		wchar_t f,l;
		do  {
			f = tolower(*dst);
			l = tolower(*src);
			dst++;
			src++;
		} while ( (f) && (f == l) );
		return (int)(f - l);
	}

	static int CompareNIgnoreCase(const char* first,const char* last,size_t count)
	{
		if(count)
		{
			int f=0;
			int l=0;

			do
			{

				if ( ((f = (unsigned char)(*(first++))) >= 'A') &&
					(f <= 'Z') )
					f -= 'A' - 'a';

				if ( ((l = (unsigned char)(*(last++))) >= 'A') &&
					(l <= 'Z') )
					l -= 'A' - 'a';

			}
			while ( --count && f && (f == l) );

			return ( f - l );
		}
		else
		{
			return 0;
		}
		//return ::_strnicmp(src,dst,count);
	}
	static int CompareNIgnoreCase(const wchar_t* first,const wchar_t* last,size_t count)
	{
		wchar_t f,l;
		int result = 0;

		if(count)
		{
			do {
				f = tolower(*first);
				l = tolower(*last);
				first++;
				last++;
			} while ( (--count) && f && (f == l) );

			result = (int)(f-l);
		}
		return result;
		//return ::_wcsnicmp(src,dst,count);
	}

	static const char* FindFirstChar(const char* src,char c){return ::strchr(src,c);}
	static const wchar_t* FindFirstChar(const wchar_t* src,wchar_t c){return ::wcschr(src,c);}

	static const char* FindLastChar(const char* src,char c){return ::strrchr(src,c);}
	static const wchar_t* FindLastChar(const wchar_t* src,wchar_t c){return ::wcsrchr(src,c);}

	static const char* FindString(const char* src,const char* dst){return ::strstr(src,dst);}
	static const wchar_t* FindString(const wchar_t* src,const wchar_t* dst){return ::wcsstr(src,dst);}

	static const char* FindCharAny(const char* src,const char* dst){return ::strpbrk(src,dst);}
	static const wchar_t* FindCharAny(const wchar_t* src,const wchar_t* dst){return ::wcspbrk(src,dst);}
	//Get span of character set in string.	strspn("129th","1234567890")==3
	static size_t StringSpan(const char* str,const char* set){return strspn(str,set);}
	static size_t StringSpan(const wchar_t* str,const wchar_t* set){return wcsspn(str,set);}


	//Get span until character in string.	strcspn("fcba73","1234567890")==4
	static size_t StringReverseSpan(const char* str,const char* set){return strcspn(str,set);}
	static size_t StringReverseSpan(const wchar_t* str,const wchar_t* set){return wcscspn(str,set);}

	
	static long ToInteger(const char* src,char** endPtr,int base){return ::strtol(src,endPtr,base);}
	static long ToInteger(const wchar_t* src,wchar_t** endPtr,int base){return ::wcstol(src,endPtr,base);}

	static double ToDouble(const char* src,char** endPtr){return ::strtod(src,endPtr);}
	static double ToDouble(const wchar_t* src,wchar_t** endPtr){return ::wcstod(src,endPtr);}

#ifdef MEDUSA_WINDOWS
	static char* SplitString(char* dest,const char* delim,char** context){return ::strtok_s(dest,delim,context);}
	static wchar_t* SplitString(wchar_t* dest,const wchar_t* delim,wchar_t** context){return ::wcstok_s(dest,delim,context);}

	static errno_t SplitString(wchar_t* dest,size_t destSize,const wchar_t* src){return ::wcscpy_s(dest,destSize,src);}

	static errno_t CopyString(char* dest,size_t destSize,const char* src){return ::strcpy_s(dest,destSize,src);}
	static errno_t CopyString(wchar_t* dest,size_t destSize,const wchar_t* src){return ::wcscpy_s(dest,destSize,src);}

	static errno_t CopyStringN(char* dest,size_t destSize,const char* src,size_t count){return ::strncpy_s(dest,destSize,src,count);}
	static errno_t CopyStringN(wchar_t* dest,size_t destSize,const wchar_t* src,size_t count){return ::wcsncpy_s(dest,destSize,src,count);}

	static errno_t ToUpper(char* dest,size_t destSize){return ::_strupr_s(dest,destSize);}
	static errno_t ToUpper(wchar_t* dest,size_t destSize){return ::_wcsupr_s(dest,destSize);}

	static errno_t ToLower(char* dest,size_t destSize){return ::_strlwr_s(dest,destSize);}
	static errno_t ToLower(wchar_t* dest,size_t destSize){return ::_wcslwr_s(dest,destSize);}

	static errno_t ReplaceAllTo(char* dest,size_t destSize,char c){return ::_strset_s(dest,destSize,c);}
	static errno_t ReplaceAllTo(wchar_t* dest,size_t destSize,wchar_t c){return ::_wcsset_s(dest,destSize,c);}


	static errno_t ReplaceAllToN(char* dest,size_t destSize,char c,size_t count){return ::_strnset_s(dest,destSize,c,count);}
	static errno_t ReplaceAllToN(wchar_t* dest,size_t destSize,wchar_t c,size_t count){return ::_wcsnset_s(dest,destSize,c,count);}
#else
	static char* SplitString(char* dest,const char* delim,char** context){return ::strtok(dest,delim);}
	static wchar_t* SplitString(wchar_t* dest,const wchar_t* delim,wchar_t** context){return ::wcstok(dest,delim,context);}

	static wchar_t* SplitString(wchar_t* dest,size_t destSize,const wchar_t* src){return ::wcscpy(dest,src);}

	static char* CopyString(char* dest,size_t destSize,const char* src){return ::strcpy(dest,src);}
	static wchar_t* CopyString(wchar_t* dest,size_t destSize,const wchar_t* src){return ::wcscpy(dest,src);}

	static char* CopyStringN(char* dest,size_t destSize,const char* src,size_t count){return ::strncpy(dest,src,count);}
	static wchar_t* CopyStringN(wchar_t* dest,size_t destSize,const wchar_t* src,size_t count){return ::wcsncpy(dest,src,count);}

	static void ToUpper(char* dest,size_t destSize)
	{
		for (; dest; ++dest) {
			if (('a'<=*dest)&&(*dest<='z')) {
				*dest-='a'-'A';
			}
		}

	}
	static void ToUpper(wchar_t* dest,size_t destSize)
	{
		for (; dest; ++dest) {
			if ((L'a'<=*dest)&&(*dest<=L'z')) {
				*dest-=L'a'-L'A';
			}
		}
	}

	static void ToLower(char* dest,size_t destSize)
	{
		for (; dest; ++dest) {
			if (('A'<=*dest)&&(*dest<='Z')) {
				*dest-='A'-'a';
			}
		}
	}
	static void ToLower(wchar_t* dest,size_t destSize)
	{
		for (; dest; ++dest) {
			if ((L'A'<=*dest)&&(*dest<=L'Z')) {
				*dest-=L'A'-L'a';
			}
		}
	}

	static void ReplaceAllTo(char* dest,size_t destSize,char c)
	{
		Memory::Set(dest, c, destSize);
	}
	static void ReplaceAllTo(wchar_t* dest,size_t destSize,wchar_t c){return Memory::Set(dest, c, destSize);}


	static void ReplaceAllToN(char* dest,size_t destSize,char c,size_t count){return Memory::Set(dest, c, count);}
	static void ReplaceAllToN(wchar_t* dest,size_t destSize,wchar_t c,size_t count){return Memory::Set(dest, c, count);}
#endif


	static char* Reverse(char* dest)
	{
		char *start = dest;
		char *left = dest;
		char ch;

		while (*dest++);                 /* find end of string */

		dest -= 2;

		while (left < dest)
		{
			ch = *left;
			*left++ = *dest;
			*dest-- = ch;
		}

		return(start);
	}
	static wchar_t* Reverse(wchar_t* dest)
	{
		wchar_t *start = dest;
		wchar_t *left = dest;
		wchar_t ch;

		while (*dest++);                 /* find end of string */

		dest -= 2;

		while (left < dest)
		{
			ch = *left;
			*left++ = *dest;
			*dest-- = ch;
		}

		return(start);

	}

#ifdef MEDUSA_WINDOWS
	static int VSPrintf(char* dest,size_t destSize,const char* format,va_list p){return ::vsprintf_s(dest,destSize,format,p);}
	static int VSPrintf(wchar_t* dest,size_t destSize,const wchar_t* format,va_list p){return ::vswprintf_s(dest,destSize,format,p);}
#else
	static int VSPrintf(char* dest,size_t destSize,const char* format,va_list p){return ::vsprintf(dest,format,p);}
	static int VSPrintf(wchar_t* dest,size_t destSize,const wchar_t* format,va_list p){return ::vswprintf(dest,destSize,format,p);}
#endif

#ifdef MEDUSA_WINDOWS
	static int VSNPrintf(char* dest,size_t destSize,size_t count,const char* format,va_list p){return ::_vsnprintf_s(dest,destSize,count,format,p);}
	static int VSNPrintf(wchar_t* dest,size_t destSize,size_t count,const wchar_t* format,va_list p){return ::_vsnwprintf_s(dest,destSize,count,format,p);}
#else
	static int VSNPrintf(char* dest,size_t destSize,size_t count,const char* format,va_list p){return ::vsnprintf(dest,count,format,p);}
	static int VSNPrintf(wchar_t* dest,size_t destSize,size_t count,const wchar_t* format,va_list p){return ::vswprintf(dest,count,format,p);}
#endif

#ifdef MEDUSA_WINDOWS
	static int GetFormatLength(const char* format,va_list p){return ::_vscprintf(format,p);}
	static int GetFormatLength(const wchar_t* format,va_list p){return ::_vscwprintf(format,p);}
#else
	static int GetFormatLength(const char* format,va_list p){va_list args;va_copy(args, p);return ::vsnprintf(NULL,0,format,args);}
	static int GetFormatLength(const wchar_t* format,va_list p)
	{
		// Unlike vsnprintf(), vswprintf() does not tell you how many
		// characters would have been written if there was space enough in
		// the buffer - it just reports an error when there is not enough
		// space.  Assume a moderately large machine so kilobytes of wchar_t
		// on the stack is not a problem.
		int bufferSize = 128;
		const static int maxBufferSize = 1024*1024;

		do 
		{
			va_list args;
			va_copy(args, p);
			wchar_t buffer[bufferSize];	//supported in C99
			int result = vswprintf(buffer, sizeof(buffer)/sizeof(buffer[0]), format, args);
			if (result >= 0)
				return result;
			bufferSize *= 2;
		} while (bufferSize < maxBufferSize);
		return -1;

	}
#endif


#ifdef MEDUSA_WINDOWS
	static int SPrintf(char* dest,size_t destSize,const char* format,...)
	{
		va_list args;
		va_start(args, format);
		int result= ::vsprintf_s(dest,destSize,format,args);
		va_end(args);
		return result;
	}
	static int SPrintf(wchar_t* dest,size_t destSize,const wchar_t* format,...)
	{
		va_list args;
		va_start(args, format);
		int result= ::vswprintf_s(dest,destSize,format,args);
		va_end(args);
		return result;
	}
	
#else
	static int SPrintf(char* dest,size_t destSize,const char* format,...)
	{
		va_list args;
		va_start(args, format);
		int result= ::vsprintf(dest,format,args);
		va_end(args);
		return result;
	}
	static int SPrintf(wchar_t* dest,size_t destSize,const wchar_t* format,...)
	{
		va_list args;
		va_start(args, format);
		int result= ::vswprintf(dest,destSize,format,args);
		va_end(args);
		return result;
	}

#endif


	template<typename T>
	struct ConstValues;


	template<typename T>
	static bool IsWordSeparator(T c)
	{
		static bool isInitialized=false;
		static BitArray<128> bitArray;
		if (!isInitialized)
		{
			bitArray.ClearZero();
			FOR_EACH_ARRAY(i,ConstValues<T>::WordSeparators)
			{
				bitArray.Set(ConstValues<T>::WordSeparators[i],true);
			}

			isInitialized=true;
		}

		return bitArray.Get(c);
	}

};

template<>
struct StdString::ConstValues<char>
{
	static bool IsNewLine(char c){return c==Return||c==LineSeparator;}
	static bool IsEmptyChar(char c){return c==Space||IsControlChar(c);}
	static bool IsControlChar(char c){return c==Return||c==LineSeparator||c==Tab||c=='\f'||c=='\v';}

	const static char Return='\r';
	const static char LineSeparator='\n';
	const static char Tab='\t';
	const static char Space=' ';
	const static char Hyphen='-';
	const static char Slash='/';
	const static char Backslash='\\';


	const static char TrimChars[];
	const static char Empty[];
	const static char WordSeparators[];
	const static char NewLineChars[];


};

template<>
struct StdString::ConstValues<wchar_t>
{
	static bool IsNewLine(wchar_t c){return c==Return||c==LineSeparator;}
	static bool IsEmptyChar(wchar_t c){return c==Space||IsControlChar(c);}
	static bool IsControlChar(wchar_t c){return c==Return||c==LineSeparator||c==Tab||c==L'\f'||c==L'\v';}

	const static wchar_t Return=L'\r';
	const static wchar_t LineSeparator=L'\n';
	const static wchar_t Tab=L'\t';
	const static wchar_t Space=L' ';
	const static wchar_t Hyphen=L'-';
	const static wchar_t Slash=L'/';
	const static char Backslash=L'\\';

	const static wchar_t TrimChars[];
	const static wchar_t Empty[];
	const static wchar_t WordSeparators[];
	const static wchar_t NewLineChars[];



};

WEAK_MULTIPLE_DEFINE const char StdString::ConstValues<char>::TrimChars[]=" \t\r\n\v\f\r";
WEAK_MULTIPLE_DEFINE const char StdString::ConstValues<char>::Empty[]="";
WEAK_MULTIPLE_DEFINE const char StdString::ConstValues<char>::WordSeparators[]=" \t\r\n\v\f";
WEAK_MULTIPLE_DEFINE const char StdString::ConstValues<char>::NewLineChars[]="\r\n";



WEAK_MULTIPLE_DEFINE const wchar_t StdString::ConstValues<wchar_t>::TrimChars[]=L" \t\r\n\v\f\r\x0085\x00a0";
WEAK_MULTIPLE_DEFINE const wchar_t StdString::ConstValues<wchar_t>::Empty[]=L"";
WEAK_MULTIPLE_DEFINE const wchar_t StdString::ConstValues<wchar_t>::WordSeparators[]=L" \t\r\n\v\f";
WEAK_MULTIPLE_DEFINE const wchar_t StdString::ConstValues<wchar_t>::NewLineChars[]=L"\r\n";

MEDUSA_END;
