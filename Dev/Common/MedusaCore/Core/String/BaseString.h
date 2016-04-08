#pragma once

#include "Core/String/TStringRef.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Utility/HashUtility.h"
#include "Core/Memory/Memory.h"
#include "Core/String/StdString.h"
MEDUSA_BEGIN;


template<typename T>
class BaseString
{
public:
	const static T LineSeparator=StdString::ConstValues<T>::LineSeparator;
public:
	BaseString(T* inBuffer,size_t bufferSize,bool isInitNull=false)
	{
		mLength=0;
		mBuffer=inBuffer;
		mBufferSize=bufferSize;

		if (mBuffer!=NULL)
		{
			if (isInitNull)
			{
				Memory::Set(mBuffer,(char)0,mBufferSize);
			}
			else
			{
				mBuffer[0]=0;
			}
		}
	}

	virtual ~BaseString(void)
	{
	}

	/*operator const T*()const
	{
	return mBuffer;
	}*/

	operator TStringRef<T>()const
	{
		return TStringRef<T>(mBuffer,mLength);
	}

protected:
	/*BaseString()
	{

	}*/
public:
	virtual void Clear()=0;
	BaseString& operator=(const BaseString& inString)
	{
		size_t length=inString.Length();

		if (length>=mBufferSize)
		{
			size_t size= Math::GetNewSizeSquare(mBufferSize,length+1);
			bool isSuccess=ResizeHelper(size);
			MEDUSA_ASSERT_TRUE(isSuccess,"");
            UN_USED(isSuccess);
		}
		mLength=length;
		StdString::CopyStringN( mBuffer,mBufferSize, inString.Buffer(), mLength );

		mBuffer[mLength] = 0;
		return *this;
	}

	BaseString& operator=(const TStringRef<T>& inString)
	{
		size_t length=inString.Length();

		if (length>=mBufferSize)
		{
			size_t size= Math::GetNewSizeSquare(mBufferSize,length+1);
			bool isSuccess=ResizeHelper(size);
			MEDUSA_ASSERT_TRUE(isSuccess,"");
            UN_USED(isSuccess);
		}

		mLength=length;
		StdString::CopyStringN(mBuffer,mBufferSize, inString.Buffer(), mLength );

		mBuffer[mLength] = 0;
		return *this;
	}

	BaseString& operator+=(const BaseString& inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(const T* inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(TStringRef<T> inString)
	{
		Append(inString);
		return *this;
	}

	BaseString& operator+=(T inChar)
	{
		Append(inChar);

		return *this;
	}

	//to be more fast
	bool operator==(const TStringRef<T>& inString)const
	{
		return ToString()==inString;
	}
	bool operator!=(const TStringRef<T>& inString)const
	{
		return ToString()!=inString;
	}
	bool operator>(const TStringRef<T>& inString)const
	{
		return ToString()>inString;
	}
	bool operator<(const TStringRef<T>& inString)const
	{
		return ToString()<inString;
	}
	bool operator>=(const TStringRef<T>& inString)const
	{
		return ToString()>=inString;
	}
	bool operator<=(const TStringRef<T>& inString)const
	{
		return ToString()<=inString;
	}

	bool operator==(const BaseString& inString)const
	{
		return ToString()==inString.ToString();
	}
	bool operator!=(const BaseString& inString)const
	{
		return ToString()!=inString.ToString();
	}
	bool operator>(const BaseString& inString)const
	{
		return ToString()>inString.ToString();
	}
	bool operator<(const BaseString& inString)const
	{
		return ToString()<inString.ToString();
	}
	bool operator>=(const BaseString& inString)const
	{
		return ToString()>=inString.ToString();
	}
	bool operator<=(const BaseString& inString)const
	{
		return ToString()<=inString.ToString();
	}

	T& operator[](size_t index)
	{
		return mBuffer[index];
	}

	T operator[](size_t index)const
	{
		return mBuffer[index];
	}


	bool IsNull()const
	{
		return mBufferSize==0||mBuffer==NULL;
	}

	bool IsEmpty()const
	{
		return mLength==0;
	}

	bool IsNullOrEmpty()const
	{
		return mLength==0||mBufferSize==0||mBuffer==NULL;
	}

	size_t Size()const
	{
		return mBufferSize;
	}

	T* c_str(){return mBuffer;}
	T* Buffer(){return mBuffer;}

	const T* c_str()const{return mBuffer;}
	const T* Buffer()const{return mBuffer;}
	TStringRef<T> ToString()const{return TStringRef<T>(mBuffer,mLength);}
	size_t Length() const { return mLength; }
	void ForceSetLength(size_t length) {mLength=length;mBuffer[mLength]=0;}
	void ForceUpdateLength()
	{
		mLength=mBuffer!=NULL?StdString::GetLength(mBuffer):0;
	}

	intp GetHashCode()const
	{
		return HashUtility::HashString(mBuffer);
	}
public:
	int Compare(const TStringRef<T>& inString,bool isIgnoreCase=false)const
	{
		return ToString().Compare(inString,isIgnoreCase);
	}

	intp IndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().IndexOf(inFindChar);
	}

	intp IndexOf(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().IndexOf(inString);
	}

	intp IndexOfAny(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().IndexOfAny(inString);
	}

	intp LastIndexOf(T inFindChar)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().LastIndexOf(inFindChar);
	}

	intp LastIndexOfAny(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().LastIndexOfAny(inString);
	}

	intp LastIndexOf(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().LastIndexOf(inString);
	}

	bool Contains(T inFindChar)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().Contains(inFindChar);
	}

	bool Contains(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().Contains(inString);
	}

	bool ContainsAny(const TStringRef<T>&  inString)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().ContainsAny(inString);
	}


	bool BeginWith(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().BeginWith(inString);
	}

	bool EndWith(const TStringRef<T>& inString)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().EndWith(inString);
	}


	long ToInteger(int radix=10)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().ToInteger(radix);
	}

	bool TryParseInteger(long& outResult,int radix=10)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().TryParseInteger(outResult,radix);
	}

	double ToDouble()const
	{
		return ToString().ToDouble();
	}

	bool TryParseDouble(double& outResult)const
	{
		RETURN_FALSE_IF(IsNull());
		return ToString().TryParseDouble(outResult);
	}



	size_t Count(T inChar)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().Count(inChar);
	}

	size_t Count(const TStringRef<T>& inString)const
	{
		RETURN_OBJECT_IF(IsNull(),-1);
		return ToString().Count(inString);
	}


	void CopyTo(const BaseString& outString)
	{
		RETURN_IF(IsNull());
		CopyTo(outString.Buffer(),outString.Size(),0,mLength);
	}

	void CopyTo(const BaseString& outString,size_t length)
	{
		RETURN_IF(IsNull());
		CopyTo(outString.Buffer(),outString.Size(),0,length);
	}

	void CopyTo(const BaseString& outString,size_t beginIndex,size_t length)
	{
		RETURN_IF(IsNull());
		CopyTo(outString.Buffer(),outString.Size());
	}

	void CopyTo(T* outBuffer,size_t outBufferSize)
	{
		RETURN_IF(IsNull());
		CopyTo(outBuffer,outBufferSize,0,mLength);
	}

	void CopyTo(T* outBuffer,size_t outBufferSize,size_t length)
	{
		RETURN_IF(IsNull());
		CopyTo(outBuffer,outBufferSize,0,length);
	}

	void CopyTo(T* outBuffer,size_t outBufferSize,size_t beginIndex,size_t length)
	{
		RETURN_IF(IsNull());
		RETURN_IF(beginIndex+length>mLength);
		RETURN_IF(length>outBufferSize);
		Memory::SafeCopy(outBuffer,outBufferSize,mBuffer+beginIndex,length);
	}

	TStringRef<T> SubString(size_t index)const
	{
		if (IsNull())
		{
			return TStringRef<T>::Empty;
		}
		return TStringRef<T>(mBuffer+index,mLength-index);
	}
public:
	void ToCase(bool isLowCase)
	{
		RETURN_IF(IsNull());
		if (isLowCase)
		{
			ToLower();
		}
		else
		{
			ToUpper();
		}
	}

	void ToUpper()
	{
		RETURN_IF(IsNull());
		StdString::ToUpper(mBuffer,mLength);
	}

	void ToLower()
	{
		RETURN_IF(IsNull());
		StdString::ToLower(mBuffer,mLength);
	}

	void Reverse()
	{
		RETURN_IF(IsNull());
		StdString::Reverse(mBuffer);
	}

	void ReplaceAllTo(T inChar)
	{
		RETURN_IF(IsNull());
		StdString::ReplaceAllTo(mBuffer,mBufferSize,inChar);
	}

	void ReplacelTo(T inChar,size_t count)
	{
		RETURN_IF(IsNull());
		StdString::ReplaceAllToN(mBuffer,mBufferSize,inChar,count);
	}

	void ReplaceAll(T oldChar,T newChar)
	{
		RETURN_IF(IsNull());
		RETURN_IF(oldChar==newChar);
		RETURN_IF(mLength==0);

		for (size_t i=0;i<mLength;++i)
		{
			if (mBuffer[i]==oldChar)
			{
				mBuffer[i]=newChar;
			}
		}
	}

	void ReplaceFirst(T oldChar,T newChar)
	{
		RETURN_IF(IsNull());
		RETURN_IF(oldChar==newChar);
		RETURN_IF(mLength==0);

		for (size_t i=0;i<mLength;++i)
		{
			if (mBuffer[i]==oldChar)
			{
				mBuffer[i]=newChar;
				return;
			}
		}
	}

	void ReplaceLast(T oldChar,T newChar)
	{
		RETURN_IF(IsNull());
		RETURN_IF(oldChar==newChar);
		RETURN_IF(mLength==0);

		for (intp i=(intp)mLength-1;i>=0;--i)
		{
			if (mBuffer[i]==oldChar)
			{
				mBuffer[i]=newChar;
				return;
			}
		}
	}

	bool ReplaceAll(const TStringRef<T>& oldString,const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsNull());
		size_t oldLength=oldString.Length();
		size_t newLength=newString.Length();
		if (oldLength==newLength)
		{
			T* index=(T*)StdString::FindString(mBuffer,oldString.Buffer());
			while(index!=NULL)
			{
				Memory::SafeCopy(index,mBuffer+mBufferSize-index,newString.Buffer(),newLength);
				index+=oldLength;
				index=(T*)StdString::FindString(index,oldString.Buffer());
			}
		}
		else if (oldLength>newLength)
		{
			T* index= (T*)StdString::FindString(mBuffer,oldString.Buffer());
			while(index!=NULL)
			{
				Memory::SafeCopy(index,mBuffer+mBufferSize-index,newString.Buffer(),newLength);
				index+=newLength;

				Memory::SetZero(index,oldLength-newLength);
				index+=oldLength-newLength;

				index= (T*)StdString::FindString(index,oldString.Buffer());
			}

			//do a compress 
			T* w=mBuffer;
			T* r=mBuffer;
			T* oldEnd=mBuffer+mLength;
			while(r!=oldEnd)
			{
				if (*r==0)
				{
					++r;
				}
				else
				{
					*w++=*r++;
				}
			}

			*w=0;

			mLength=w-mBuffer;
		} 
		else
		{
			T* index= (T*)StdString::FindString(mBuffer,oldString.Buffer());
			if (index==NULL)
			{
				return true;
			}

			size_t dis=newLength-oldLength;

			while(index!=NULL)
			{
				if (mLength+dis>=mBufferSize)
				{
					size_t newSize=Math::GetNewSizeSquare(mBufferSize,mLength+dis+1);
					RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
				}

				//copy last string
				Memory::SafeCopy(index+newLength,mBufferSize+mBuffer-index-newLength,index+oldLength,mLength+mBuffer-index+oldLength);
				//copy new string
				Memory::SafeCopy(index,mBufferSize+mBuffer-index,newString.Buffer(),newLength);
				mLength+=dis;

				index= (T*)StdString::FindString(index,oldString.Buffer());
			}

		}
		return true;
	}

	bool ReplaceFirst(const TStringRef<T>& oldString,const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsNull());
		
		intp index= IndexOf(oldString);
		if (index<0)
		{
			return false;
		}

		size_t oldLength=oldString.Length();
		size_t newLength=newString.Length();

		if (oldLength==newLength)
		{
			Memory::SafeCopy(mBuffer+index,mBufferSize-index,newString.Buffer(),oldLength);
		}
		else if(oldLength>newLength)
		{
			Memory::SafeCopy(mBuffer+index,mBufferSize-index,newString.Buffer(),newLength);
			RemoveAt(index+newLength,oldLength-newLength);
		}
		else 
		{
			size_t dis=newLength-oldLength;
			if (mLength+dis>=mBufferSize)
			{
				size_t newSize=Math::GetNewSizeSquare(mBufferSize,mLength+dis+1);
				RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
			}

			//copy last string
			Memory::SafeCopy(mBuffer+index+newLength,mBufferSize+index-newLength,mBuffer+index+oldLength,mLength+index+oldLength);
			//copy new string
			Memory::SafeCopy(mBuffer+index,mBufferSize+index,newString.Buffer(),newLength);
			mLength+=dis;
		}
		return true;
	}



	bool ReplaceLast(const TStringRef<T>& oldString,const TStringRef<T>& newString)
	{
		RETURN_FALSE_IF(IsNull());
		T* w=mBuffer;
		T* r=mBuffer;
		const T* p=oldString.Buffer();

		intp index= LastIndexOf(oldString);
		if (index<0)
		{
			return false;
		}

		size_t oldLength=oldString.Length();
		size_t newLength=newString.Length();

		if (oldLength==newLength)
		{
			Memory::SafeCopy(mBuffer+index,mBufferSize-index,newString.Buffer(),oldLength);
		}
		else if(oldLength>newLength)
		{
			Memory::SafeCopy(mBuffer+index,mBufferSize-index,newString.Buffer(),newLength);
			RemoveAt(index+newLength,oldLength-newLength);
		}
		else 
		{
			size_t dis=newLength-oldLength;
			if (mLength+dis>=mBufferSize)
			{
				size_t newSize=Math::GetNewSizeSquare(mBufferSize,mLength+dis+1);
				RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
			}

			//copy last string
			Memory::SafeCopy(mBuffer+index+newLength,mBufferSize+index-newLength,mBuffer+index+oldLength,mLength+index+oldLength);
			//copy new string
			Memory::SafeCopy(mBuffer+index,mBufferSize+index,newString.Buffer(),newLength);
			mLength+=dis;
		}

		return true;
	}


	bool RemoveBeginAny(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer;

		for (size_t i=0;i<mLength;++i)
		{
			if(chars.Contains(mBuffer[i]))
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0,p-mBuffer);
	}

	bool RemoveBeginAnyExclude(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer;

		for (size_t i=0;i<mLength;++i)
		{
			if(!chars.Contains(mBuffer[i]))
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0,p-mBuffer);
	}

	bool RemoveBegin(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer;

		for (size_t i=0;i<mLength;++i)
		{
			if (mBuffer[i]==inChar)
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0,p-mBuffer);
	}

	bool RemoveBeginExclude(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer;

		for (size_t i=0;i<mLength;++i)
		{
			if (mBuffer[i]!=inChar)
			{
				++p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(0,p-mBuffer);
	}

	bool RemoveEnd(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer+mLength-1;

		for (intp i=mLength-1;i>=0;--i)
		{
			if (mBuffer[i]==inChar)
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p-mBuffer+1);
	}

	bool RemoveEndExclude(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer+mLength-1;

		for (intp i=mLength-1;i>=0;--i)
		{
			if (mBuffer[i]!=inChar)
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p-mBuffer+1);
	}

	bool RemoveEndAny(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer+mLength-1;

		for (intp i=mLength-1;i>=0;--i)
		{
			if(chars.Contains(mBuffer[i]))
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p-mBuffer+1);
	}

	bool RemoveEndAnyExclude(const TStringRef<T>& chars)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer+mLength-1;

		for (intp i=mLength-1;i>=0;--i)
		{
			if(!chars.Contains(mBuffer[i]))
			{
				--p;
			}
			else
			{
				break;
			}
		}
		return RemoveAt(p-mBuffer+1);
	}

	bool Append(T inChar,size_t count=1)
	{
		return Insert(mLength,inChar,count);
	}

	bool Append(const TStringRef<T>& inString)
	{
		return Insert(mLength,inString);
	}

	bool Append(const T* buffer,size_t length)
	{
		return Insert(mLength,buffer,length);
	}

	bool AppendLine()
	{
		return Append(LineSeparator);
	}

	bool AppendLine(T inChar,size_t count=1)
	{
		if(Insert(mLength,inChar,count))
		{
			return Append(LineSeparator);
		}

		return false;
	}

	bool AppendLine(const TStringRef<T>& inString)
	{
		if(Insert(mLength,inString))
		{
			return Append(LineSeparator);
		}
		return false;
	}

	bool AppendLine(const T* buffer,size_t length)
	{
		if(Insert(mLength,buffer,length))
		{
			return Append(LineSeparator);
		}
		return false;
	}

	bool AppendFormat(const T* format,...)
	{
		RETURN_FALSE_IF_NULL(format);

		va_list args;
		va_start(args,format);

		int length=StdString::GetFormatLength(format,args);
		RETURN_FALSE_IF(length<=0);

		if ((size_t)length>=mBufferSize)
		{
			size_t newSize=Math::GetNewSizeSquare(mBufferSize,length+1);

			RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
		}

		T* temp=new T[length+1];
		StdString::VSPrintf(temp,length+1,format,args);

		va_end(args);

		Append(TStringRef<T>(temp,length));

		SAFE_DELETE_ARRAY(temp);

		return true;
	}

	bool Push(T inChar,size_t count=1)
	{
		return Insert(0,inChar,count);
	}
	bool Push(const TStringRef<T>& inString)
	{
		return Insert(0,inString);
	}

	bool Insert(size_t index,T inChar,size_t count=1)
	{
		RETURN_FALSE_IF_ZERO(inChar);
		RETURN_FALSE_IF_ZERO(count);
		RETURN_FALSE_IF(index>mLength);

		if (mLength+count>=mBufferSize)
		{
			size_t size= Math::GetNewSizeSquare(mBufferSize,mLength+count+1);
			RETURN_FALSE_IF_FALSE(ResizeHelper(size));
		}

		Memory::SafeCopy(mBuffer+index+count,mBufferSize-index-count,mBuffer+index,mLength-index);
		if (count==1)
		{
			mBuffer[index]=inChar;
		}
		else
		{
			Memory::Set(mBuffer+index,inChar,count);
		}
		mLength+=count;
		mBuffer[mLength]=0;

		return true;
	}


	bool Insert(size_t index,const TStringRef<T>& inString)
	{
		return Insert(index,inString.Buffer(),inString.Length());
	}

	bool Insert(size_t index,const T* buffer,size_t length)
	{
		RETURN_FALSE_IF_NULL(buffer);
		RETURN_FALSE_IF_ZERO(length);
		RETURN_FALSE_IF(index>mLength);

		if (mLength+length>=mBufferSize)
		{
			size_t size= Math::GetNewSizeSquare(mBufferSize,mLength+length+1);
			RETURN_FALSE_IF_FALSE(ResizeHelper(size));
		}

		RETURN_FALSE_IF(mLength+length>mBufferSize);
		Memory::SafeCopy(mBuffer+index+length,mBufferSize-index-length,mBuffer+index,mLength-index+1);	//+1 to copy '\0'
		Memory::SafeCopy(mBuffer+index,mBufferSize-index,buffer,length);
		mLength+=length;
		mBuffer[mLength]=0;

		return true;
	}

	bool RemoveAll(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		T* p=mBuffer;

		for (size_t i=0;i<mLength;++i)
		{
			if (mBuffer[i]!=inChar)
			{
				*p=mBuffer[i];
				++p;
			}
		}

		++p;
		*p=0;
		mLength=p-mBuffer;

		return true;
	}

	bool RemoveFirst()
	{
		return RemoveAt(0);
	}

	bool RemoveFirst(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		intp index= IndexOf(inChar);
		if (index>=0)
		{
			return RemoveAt(index);
		}
		return false;
	}

	bool RemoveLast(T inChar)
	{
		RETURN_FALSE_IF(IsNull());
		intp index= LastIndexOf(inChar);
		if (index>=0)
		{
			return RemoveAt(index);
		}
		return false;
	}

	bool RemoveLast()
	{
		return RemoveAt(mLength-1);
	}
	bool RemoveAt(size_t index)
	{
		return RemoveAt(index,1);
	}

	bool RemoveAt(size_t index,size_t length)
	{
		RETURN_FALSE_IF(IsNull());
		RETURN_FALSE_IF(index+length>mLength);
		Memory::SafeCopy(mBuffer+index,mBufferSize-index,mBuffer+index+length,mLength-index-length+1);	//+1 to copy '\0'
		mLength-=length;
		return true;
	}

	bool RemoveFrom(size_t index)
	{
		return RemoveAt(index,mLength-index);
	}

	bool RemoveAll(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsNull());
		T *w=mBuffer;	
		T* r=mBuffer;
		const T *p=inString.Buffer();

		while(*r!=0)
		{
			if(*p==0)
			{
				p=inString.Buffer();
			}

			if (*r!=*p)
			{
				*w++=*r++;
				p=inString.Buffer();
			}
			else
			{
				++r;
				++p;
			}
		}

		if (*p!=0)
		{
			r-=p-inString.Buffer();
			StdString::CopyString(w,mBufferSize+mBuffer-w,r);
			mLength+=p-inString.Buffer();
		}
		else
		{
			*w=0;
			mLength=w-mBuffer;
		}
	}

	bool RemoveFirst(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsNull());
		intp index= IndexOf(inString);
		if (index>=0)
		{
			return RemoveAt(index,inString.Length());
		}
		return false;
	}
	bool RemoveLast(const TStringRef<T>& inString)
	{
		RETURN_FALSE_IF(IsNull());
		intp index= LastIndexOf(inString);
		if (index>=0)
		{
			return RemoveAt(index,inString.Length());
		}
		return false;
	}

	void TrimAll()
	{
		TrimBegin();
		TrimEnd();
	}

	void TrimBegin()
	{
		RemoveBeginAny(StdString::ConstValues<T>::TrimChars);
	}

	void TrimEnd()
	{
		RemoveEndAny(StdString::ConstValues<T>::TrimChars);
	}

	bool Format(const T* format,...)
	{
		RETURN_FALSE_IF_NULL(format);

		va_list args;
		va_start(args,format);
		int length=StdString::GetFormatLength(format,args);
		size_t size=length+1;	//for 0
		RETURN_FALSE_IF(size<=0);

		if (size>=mBufferSize)
		{
			size_t newSize= Math::GetNewSizeSquare(mBufferSize,size);

			RETURN_FALSE_IF_FALSE(ResizeHelper(newSize));
		}
		StdString::VSPrintf(mBuffer,size,format,args);
		va_end(args);
		mLength=length;

		return true;
	}


	MemoryData<T> ToMemoryData()const{return MemoryData<T>(mBuffer,mLength);}
protected:
	virtual bool ResizeHelper(size_t size)=0;
protected:
	size_t mLength;
	size_t mBufferSize;
	T* mBuffer;
};




MEDUSA_END;