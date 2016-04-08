#pragma once

#include "Core/String/BaseString.h"
#include "Core/Collection/List.h"



MEDUSA_BEGIN;

template<typename T>
class THeapString:public BaseString<T>
{
public:
	using BaseString<T>::operator==;
public:
	explicit THeapString(T inChar):BaseString<T>(Memory::Alloc<T>(2),2)
	{
		this->Push(inChar);
	}

	THeapString(const TStringRef<T>& inBuffer):BaseString<T>(Memory::Alloc<T>(inBuffer.Length()+1),inBuffer.Length()+1)
	{
		this->Push(inBuffer);
	}

	THeapString(const THeapString& inString):BaseString<T>(Memory::Alloc<T>(inString.Length()+1),inString.Length()+1)
	{
		this->Push(inString);
	}

	THeapString(const BaseString<T>& inString):BaseString<T>(Memory::Alloc<T>(inString.Length()+1),inString.Length()+1)
	{
		this->Push(inString);
	}

	THeapString(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str):BaseString<T>(Memory::Alloc<T>(str.length()+1),str.length()+1)
	{
		this->Push(str.c_str());
	}

	explicit THeapString(size_t size,bool isInitNull=false):BaseString<T>(Memory::Alloc<T>(size),size,isInitNull)
	{

	}
	
	
	THeapString():BaseString<T>(NULL,(size_t)0)
	{
		
	}

	THeapString(const T* inBuffer,size_t bufferSize):BaseString<T>(Memory::Alloc<T>(bufferSize),bufferSize)
	{
		this->Push(inBuffer);
	}

	explicit THeapString(const T* inBuffer):BaseString<T>(Memory::Alloc<T>(32),32)
	{
		this->Push(inBuffer);
	}


	template<size_t size>
	explicit THeapString(const T (&str)[size]):BaseString<T>(Memory::Alloc<T>(size),size)
	{
		this->Push(str);
	}

	virtual ~THeapString()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		SAFE_FREE(this->mBuffer);
		this->mBufferSize=0;
		this->mLength=0;
	}

	THeapString& operator=(const BaseString<T>& str)
	{
		return this->operator=(str.ToString());
	}

	THeapString& operator=(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& str)
	{
		return this->operator=(TStringRef<T>(str));
	}

	THeapString& operator=(const T* str)
	{
		return this->operator=(TStringRef<T>(str));
	}

	THeapString& operator=(const TStringRef<T>& inString)
	{
		size_t length=inString.Length();
		if (inString.IsNull())
		{
			Clear();
		}
		else
		{
			if (length==0)
			{
				size_t size= Math::GetNewSizeSquare(this->mBufferSize,length+1);
				bool isSuccess=this->ResizeHelper(size);
				MEDUSA_ASSERT_TRUE(isSuccess,"");
                UN_USED(isSuccess);
				*this->mBuffer='\0';
			}
			else
			{
				if (length>=this->mBufferSize)
				{
					size_t size=Math::GetNewSizeSquare(this->mBufferSize,length+1);
					bool isSuccess=this->ResizeHelper(size);
					MEDUSA_ASSERT_TRUE(isSuccess,"");
                    UN_USED(isSuccess);
				}
				this->mLength=length;
				StdString::CopyStringN(this->mBuffer,this->mBufferSize, inString.Buffer(), this->mLength );
				this->mBuffer[this->mLength] = 0;
			}
		}
		
		return *this;
	}

	THeapString operator+(const BaseString<T>& str)const
	{
		THeapString result(*this);
		result+=str;
		return result;
	}

	THeapString operator+(const TStringRef<T>& str)const
	{
		THeapString result(*this);
		result+=str;
		return result;
	}

	THeapString operator+(T c)const
	{
		THeapString result(*this);
		result+=c;
		return result;
	}
	
	friend THeapString operator+(T inFirstChar,const THeapString& inSecondString)
	{
		THeapString result(inFirstChar);
		result+=inSecondString;
		return result;
	}

	//to be more fast
	bool operator==(const THeapString& inString)const
	{
		return this->ToString()==inString.ToString();
	}
	bool operator!=(const THeapString& inString)const
	{
		return this->ToString()!=inString.ToString();
	}
	bool operator>(const THeapString& inString)const
	{
		return this->ToString()>inString.ToString();
	}
	bool operator<(const THeapString& inString)const
	{
		return this->ToString()<inString.ToString();
	}
	bool operator>=(const THeapString& inString)const
	{
		return this->ToString()>=inString.ToString();
	}
	bool operator<=(const THeapString& inString)const
	{
		return this->ToString()<=inString.ToString();
	}
public:

	THeapString SubString(size_t index)const
	{
		return SubString(index,this->mLength-index);
	}
	
	THeapString SubString(size_t index,size_t length)const
	{
		MEDUSA_ASSERT_FALSE(this->IsNull(),"Null string");
		return THeapString(TStringRef<T>(this->mBuffer+index,length));
	}

	bool ReserveSize(size_t size)
	{
		RETURN_TRUE_IF(this->mBufferSize>=size);

		return this->ResizeHelper(size);
	}

	void ReleaseExtraSize()
	{
		RETURN_IF_ZERO(this->mBufferSize);

		if (this->mLength==0)
		{
			SAFE_FREE(this->mBuffer);
			this->mBufferSize=0;
		}
		else
		{
			RETURN_IF_EQUAL(this->mBufferSize,this->mLength);
			this->mBufferSize=this->mLength;
			Memory::Realloc(this->mBuffer,this->mBufferSize);
		}
	}

protected:
	virtual bool ResizeHelper(size_t size)
	{
		if (this->mBufferSize>=size&&this->mBuffer!=NULL)
		{
			return true;
		}
		
		Memory::Realloc(this->mBuffer,size);

		if (this->mBuffer!=NULL)
		{
			this->mBufferSize=size;
			return true;
		}
		return false;
	}
public:
	const static THeapString Empty;
};

template<typename T>
WEAK_MULTIPLE_DEFINE const THeapString<T> THeapString<T>::Empty;
//[PRE_DECLARE_BEGIN]
typedef THeapString<char> HeapString;
typedef THeapString<wchar_t> WHeapString;
//[PRE_DECLARE_END]

MEDUSA_END;
