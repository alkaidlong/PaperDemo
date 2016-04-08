#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Utility/HashUtility.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/MathHeader.h"
#include "Core/String/StdString.h"


MEDUSA_BEGIN;

template<typename T>
class TStringRef
{
public:
	template<size_t size>
	TStringRef(const T (&str)[size])
	{
		mBuffer=str;
		mLength=Math::UIntMaxValue;
	}

	TStringRef(const T* inBuffer=StdString::ConstValues<T>::Empty)
	{
		mBuffer=inBuffer;
		mLength=Math::UIntMaxValue;
	}
	TStringRef(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str)
	{
		mBuffer=str.c_str();
		mLength=str.length();
	}

	TStringRef(const T* inBuffer,size_t length)
	{
		mBuffer=inBuffer;
		mLength=length;
	}

	TStringRef(const MemoryData<T>& data)
	{
		mBuffer=(const T*)data.GetData();
		mLength=data.IsNull()?0:data.GetSize()-1;
	}

	~TStringRef(void)
	{
		mBuffer=NULL;
		mLength=0;
	}

	/*operator const T*()const
	{
	return mBuffer;
	}*/

	TStringRef(const TStringRef& inString)
	{
		mBuffer=inString.mBuffer;
		mLength=(inString.IsLengthAvailable())?inString.Length():Math::UIntMaxValue;
	}

	TStringRef& operator=(const TStringRef& inString)
	{
		mBuffer=inString.mBuffer;
		mLength=(inString.IsLengthAvailable())?inString.Length():Math::UIntMaxValue;
		return *this;
	}

	TStringRef SubString(size_t index)const
	{
		if (IsNull())
		{
			return TStringRef::Empty;
		}
		return IsLengthAvailable()?TStringRef(mBuffer+index,mLength-index):TStringRef(mBuffer+index);
	}
public:
	bool operator==(const TStringRef& inString)const
	{
		if (inString.IsNull())
		{
			return IsNull();
		}
		return Length()==inString.Length()&&StdString::Compare(mBuffer, inString.Buffer())==0;
	}
	bool operator!=(const TStringRef& inString)const
	{
		return !operator==(inString);
	}
	bool operator>(const TStringRef& inString)const
	{
		if (inString.IsNull())
		{
			return !IsNull();
		}

		if (IsNull())
		{
			return false;
		}

		return StdString::Compare (mBuffer, inString.Buffer())>0;
	}
	bool operator<(const TStringRef& inString)const
	{
		if (inString.IsNull())
		{
			return false;
		}

		if (IsNull())
		{
			return true;
		}

		return StdString::Compare (mBuffer, inString.Buffer())<0;
	}
	bool operator>=(const TStringRef& inString)const
	{
		return !operator<(inString);
	}
	bool operator<=(const TStringRef& inString)const
	{
		return !operator>(inString);
	}

	THeapString<T> operator+(const TStringRef<T>& inString)const;
	THeapString<T> operator+(const char c)const;

	THeapString<T> SubString(size_t index,size_t length)const;
public:
	int Compare(const TStringRef& inString,bool isIgnoreCase=false)const
	{
		if (isIgnoreCase)
		{
			if (inString.IsLengthAvailable())
			{
				return StdString::CompareNIgnoreCase(mBuffer,inString.Buffer(),inString.Length());
			}
			return StdString::CompareIgnoreCase(mBuffer,inString.Buffer());
		}

		if (inString.IsLengthAvailable())
		{
			return StdString::CompareN(mBuffer,inString.Buffer(),inString.Length());
		}
		return StdString::Compare(mBuffer,inString.Buffer());
	}
	intp IndexOf(T inFindChar,intp index=0)const
	{
		const T* p=StdString::FindFirstChar(mBuffer+index,inFindChar);
		if (p==NULL)
		{
			return -1;
		}

		return p-mBuffer;
	}
	intp IndexOf(const TStringRef& inString,intp index=0)const
	{
		const T* p=StdString::FindString(mBuffer+index,inString.Buffer());
		if (p==NULL)
		{
			return -1;
		}

		return p-mBuffer;
	}
	intp IndexOfAny(const TStringRef& inString,intp index=0)const
	{
		const T* p=StdString::FindCharAny(mBuffer+index,inString.Buffer());
		if (p==NULL)
		{
			return -1;
		}

		return p-mBuffer;
	}
	intp LastIndexOf(T inFindChar,intp index=0)const
	{
		const T* p=StdString::FindLastChar(mBuffer+index,inFindChar);
		if (p==NULL)
		{
			return -1;
		}

		return p-mBuffer;
	}
	intp LastIndexOf(const TStringRef& inString,intp index=0)const
	{
		size_t length=inString.Length();
		if (length>Length()-index)
		{
			return -1;
		}

		intp endIndex=length-1;
		const T* inBuffer=inString.Buffer();

		intp j,ti;
		for (intp i=mLength-1;i>=index;i--)
		{
			if (inBuffer[endIndex]==mBuffer[i])	
			{
				for (j=endIndex,ti=i;j>=i;--j,--ti)
				{
					if (inBuffer[j]!=mBuffer[ti])	
					{
						break;
					}
				}
				++j;
				if (j==0&&i-ti==endIndex+1)
				{
					return (i-endIndex);
				}
			}
		}
		return -1;
	}
	intp LastIndexOfAny(const TStringRef& inString,intp index=0)const
	{
		intp length=Length();
		if (length==0||index<0||index>=length)
		{
			return -1;
		}

		for (intp i=length-1;i>=index;--i)
		{
			if (inString.Contains(mBuffer[i]))
			{
				return i;
			}
		}

		return -1;
	}
	bool Contains(T inFindChar)const
	{
		return IndexOf(inFindChar)>=0;
	}
	bool Contains(const TStringRef& inString)const
	{
		return IndexOf(inString)>=0;
	}
	bool ContainsAny(const TStringRef& inString)const
	{
		return IndexOfAny(inString)>=0;
	}
	bool BeginWith(const TStringRef& inString)const
	{
		size_t length=inString.Length();
		if (length>Length())
		{
			return false;
		}

		if (Length()==0)
		{
			return length==0;
		}
		else
		{
			if (length==0)
			{
				return true;
			}
		}

		const T* buffer=inString.Buffer();
		size_t i=0;
		while(*buffer!=0)
		{
			if (i>Length()||mBuffer[i++]!=*buffer++)
			{
				return false;
			}
		}

		return true;
	}
	bool EndWith(const TStringRef& inString)const
	{
		size_t length=inString.Length();
		if (length>Length())
		{
			return false;
		}

		if (Length()==0)
		{
			return length==0;
		}
		else
		{
			if (length==0)
			{
				return true;
			}
		}

		const T* buffer=inString.Buffer();

		size_t i=Length()-1;
		const T* pEnd=buffer+length-1;
		--buffer;

		while(pEnd!=buffer)
		{
			if (*pEnd--!=mBuffer[i--])
			{
				return false;
			}
		}

		return true;
	}
	long ToInteger(int radix=10)const
	{
		return StdString::ToInteger(mBuffer,NULL,radix);
	}
	bool TryParseInteger(long& outResult,int radix=10)const
	{
		T* endPtr;
		outResult=StdString::ToInteger(mBuffer,&endPtr,radix);
		return endPtr!=mBuffer;
	}
	double ToDouble()const
	{
		return StdString::ToDouble(mBuffer,NULL);
	}
	bool TryParseDouble(double& outResult)const
	{
		T* endPtr;
		outResult= StdString::ToDouble(mBuffer,&endPtr);
		return endPtr!=mBuffer;
	}
	size_t Count(T inChar)const
	{
		size_t count=0;
		const T* p=mBuffer;

		while((*p)!=0)
		{
			if (*p==inChar)
			{
				++count;
			}
			++p;
		}
		return count;
	}
	size_t Count(const TStringRef& inString)const
	{
		size_t length=inString.Length();

		if (length>Length())
		{
			return 0;
		}

		size_t count=0;
		const T* p=mBuffer;

		while((*p)!=0)
		{
			p= StdString::FindString(p,inString.Buffer());
			if (p!=NULL)
			{
				count++;
				p+=length;
			}
			else
			{
				break;
			}

		}
		return count;
	}
	void CopyTo(T* outBuffer,size_t outBufferSize)const
	{
		size_t length=Length();
		RETURN_IF(length>outBufferSize);

		Memory::SafeCopy(outBuffer,outBufferSize,mBuffer,length);
	}
	void CopyTo(T* outBuffer,size_t outBufferSize,size_t length)const
	{
		Memory::SafeCopy(outBuffer,outBufferSize,0,length);

	}
	void CopyTo(T* outBuffer,size_t outBufferSize,size_t beginIndex,size_t length)const
	{
		RETURN_IF(length>outBufferSize);

		size_t myLength=Length();
		RETURN_IF(beginIndex+length>myLength+1);

		Memory::SafeCopy(outBuffer,outBufferSize,mBuffer+beginIndex,length);
	}
/*
	void Split(const TStringRef& delimter,List<THeapString<T> >& outResults )const
	{
		RETURN_IF(IsNull());
		size_t size=Length()+1;
		T* copyBuffer=Memory::Alloc<T>(size);
		Memory::SafeCopy(copyBuffer,size,mBuffer,size);

		T* context;
		T* result=StdString::SplitString(copyBuffer,delimter.Buffer(),&context);
		while (result!=NULL)
		{
			outResults.Append(THeapString<T>(result));
			result=StdString::SplitString(NULL,delimter.Buffer(),&context);
		}

		free(copyBuffer);
	}
 */
public:
	T operator[](size_t index)const
	{
		return mBuffer[index];
	}

	bool IsNull()const
	{
		return mBuffer==NULL;
	}
	bool IsEmpty()const
	{
		return mBuffer==NULL||*mBuffer==0;
	}

	bool IsNullOrEmpty()const
	{
		return mBuffer==NULL||*mBuffer==0;
	}

	bool IsRefEqualsTo(const TStringRef& other)const
	{
		return mBuffer==other.Buffer();
	}

	bool IsEqualsTo(const TStringRef& other)const
	{
		return *this==other;
	}

	size_t Length()const
	{
		if (mLength==Math::UIntMaxValue)
		{
			mLength=mBuffer==NULL?0:StdString::GetLength(mBuffer);
		}

		return mLength;
	}

	intp GetHashCode()const{return (intp)HashUtility::HashString(mBuffer);}
	const T* Buffer()const{return mBuffer;}
	const T* c_str()const{return mBuffer;}
	void ForceSetBuffer(const T* buffer){mBuffer=buffer;}
	void ForceSetLength(size_t length){mLength=length;}
	void ForceUpdateLength(){mLength=Math::UIntMaxValue;}
	MemoryData<T> ToData()const{return MemoryData<T>::FromStatic(mBuffer,Length());}
private:
	bool IsLengthAvailable()const{return mLength!=Math::UIntMaxValue;}
protected:
	const T* mBuffer;
	mutable size_t mLength;
public:
	const static TStringRef Empty;

};

template<typename T>
WEAK_MULTIPLE_DEFINE const TStringRef<T> TStringRef<T>::Empty;

//[PRE_DECLARE_BEGIN]
typedef TStringRef<char> StringRef;
typedef TStringRef<wchar_t> WStringRef;
//[PRE_DECLARE_END]

MEDUSA_END;