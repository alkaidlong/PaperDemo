#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/MathHeader.h"

MEDUSA_BEGIN;

MemoryStream::MemoryStream( size_t capacity/*=0*/ ):mIsWritable(true),mIsExpandable(true),mPos(0),mIsOpen(true)
{
	mData=MemoryByteData::Alloc(capacity);
}

MemoryStream::MemoryStream( const MemoryByteData& data,bool writable/*=true*/ ):mData(data),mPos(0),mIsWritable(writable),mIsExpandable(false),mIsOpen(true)
{

}

MemoryStream::~MemoryStream(void)
{
	Close();
}

bool MemoryStream::Flush()
{
	return true;
}

bool MemoryStream::Close()
{
	mPos=0;
	mIsWritable=false;
	mIsOpen=false;
	mIsExpandable=false;
	mData=MemoryByteData::Empty;

	return true;
}

bool MemoryStream::Seek( int64 offset,SeekOrigin direction )
{
	RETURN_FALSE_IF_FALSE(CanSeek());

	size_t newPos=mPos;
	switch(direction.ToInt())
	{
	case SeekOrigin::Head.IntValue:
		newPos=(size_t)offset;
		break;
	case SeekOrigin::Current.IntValue:
		newPos+=(size_t)offset;
		break;
	case SeekOrigin::End.IntValue:
		newPos=mData.GetSize()+(size_t)offset;
		break;
	}

	if (newPos<=(int)mData.GetSize())
	{
		mPos=newPos;
		return true;
	}
	return false;
}

void MemoryStream::SetLength( uint64 val )
{
	RETURN_IF_FALSE(CanWrite());

	if (mIsExpandable)
	{
		if (mData.GetSize()<val)
		{
			Resize((size_t)val);
		}
	}
	else
	{
		mData.ForceSetSize((size_t)val);
	}
	
}

bool MemoryStream::Resize( size_t size )
{
	//always to extend to bigger size
	RETURN_FALSE_IF(mData.GetSize()>=size);
	byte* buffer=mData.GetData();
	Memory::Realloc(buffer,size);
	mData.ForceSetData(buffer);
	mData.ForceSetSize(size);
	mData.ForceEnsureRefCount();	//maybe mData is empty before
	return true;
}

size_t MemoryStream::ReadDataTo( MemoryByteData& outData ,DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanRead());
	size_t readSize=Math::Min(mData.GetSize()-(size_t)mPos,outData.GetSize());

	switch (mode)
	{
	case DataReadingMode::AlwaysCopy:
		Memory::SafeCopy(outData.GetData(),outData.GetSize(),mData.GetData()+mPos,readSize);
		outData.ForceSetSize(readSize);
		break;
	case DataReadingMode::DirectMove:
		outData=MemoryByteData::FromStatic(mData.GetData()+mPos,readSize);
		break;
	default:
		break;
	}

	mPos+=readSize;
	return readSize;
}

size_t MemoryStream::WriteData( const MemoryByteData& data )
{
	RETURN_ZERO_IF_FALSE(CanWrite());

	size_t writeSize=data.GetSize();
	size_t newSize=(size_t)mPos+data.GetSize();

	if(newSize>mData.GetSize())
	{
		if(mIsExpandable)
		{
			newSize=Math::GetNewSizeSquare(mData.GetSize(),newSize);
			Resize(newSize);
		}
		else
		{
			writeSize=mData.GetSize()-(size_t)mPos;
		}
	}

	Memory::SafeCopy(mData.GetData()+mPos,mData.GetSize()-(size_t)mPos,data.GetData(),writeSize);
	mPos+=writeSize;
	return writeSize;

}

int MemoryStream::PeekChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	return *(mData.GetData()+mPos);
}

int MemoryStream::PeekWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	if (mPos+sizeof(wchar)-1>=mData.GetSize())
	{
		return -1;
	}
	return *(wchar*)(mData.GetData()+mPos);
}


int MemoryStream::ReadChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	return *(mData.GetData()+mPos++);
}

int MemoryStream::ReadWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	if (mPos+sizeof(wchar)-1>=mData.GetSize())
	{
		return -1;
	}
	int c= *(wchar*)(mData.GetData()+mPos);
	mPos+=sizeof(wchar);
	return c;
}




bool MemoryStream::WriteChar( char val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mPos>=mData.GetSize())
	{
		RETURN_FALSE_IF_FALSE(mIsExpandable);
		size_t newSize=(size_t)mPos+1;
		newSize=Math::GetNewSizeSquare(mData.GetSize(),newSize);
		Resize(newSize);
	}

	*(mData.GetData()+mPos++)=val;
	return true;
}

bool MemoryStream::WriteChar( wchar val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (mPos+sizeof(wchar)-1>=mData.GetSize())
	{
		RETURN_FALSE_IF_FALSE(mIsExpandable);
		size_t newSize=(size_t)mPos+sizeof(wchar);
		newSize=Math::GetNewSizeSquare(mData.GetSize(),newSize);
		Resize(newSize);
	}

	*(wchar*)(mData.GetData()+mPos)=val;
	mPos+=sizeof(wchar);
	return true;
}

StringRef MemoryStream::ReadString(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return StringRef::Empty;
	}

	StringRef result((char*)mData.GetData()+mPos);
	mPos+=result.Length()+1;	//read '\0' also
	return result;
}

WStringRef MemoryStream::ReadStringW(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return WStringRef::Empty;
	}
	WStringRef result((wchar*)mData.GetData()+mPos);
	mPos+=(result.Length()+1)*sizeof(wchar);	//read '\0' also
	return result;
}

bool MemoryStream::ReadToString( HeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());
	
	char* buffer=(char*)mData.GetData();
	size_t size=mData.GetSize();
	size_t oldPos=mPos;

	while (true)
	{
		if (mPos>=size)
		{
			mPos=oldPos;
			return false;
		}

		if (buffer[mPos]=='\0')
		{
			outString.Append(buffer+oldPos,mPos-oldPos);
			++mPos;
			return true;
		}

		++mPos;
	}
	return false;
}

bool MemoryStream::ReadToString( WHeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());
	RETURN_FALSE_IF_FALSE(CanRead());

	wchar* buffer=(wchar*)mData.GetData();
	size_t size=mData.GetSize()/sizeof(wchar);
	mPos/=sizeof(wchar);
	size_t oldPos=mPos;

	while (true)
	{
		if (mPos>=size)
		{
			mPos=oldPos;
			return false;
		}

		if (buffer[mPos]==L'\0')
		{
			outString.Append(buffer+oldPos,mPos-oldPos);
			++mPos;
			mPos*=sizeof(wchar);
			return true;
		}

		++mPos;
	}
	return false;

}

bool MemoryStream::ReadLineToString( HeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());

	char* buffer=(char*)mData.GetData();
	size_t size=mData.GetSize();
	size_t oldPos=mPos;

	while (true)
	{
		if (mPos>=size)
		{
			outString.Append(buffer+oldPos,mPos-oldPos);
			return true;
		}

		switch (buffer[mPos])
		{
		case '\0':
			outString.Append(buffer+oldPos,mPos-oldPos);
			return true;
		case StdString::ConstValues<char>::LineSeparator:
		case StdString::ConstValues<char>::Return:
			if (includeNewLine)
			{
				++mPos;
				if (mPos+1<size&&StdString::ConstValues<char>::IsNewLine(buffer[mPos+1]))
				{
					++mPos;
				}
				outString.Append(buffer+oldPos,mPos-oldPos);	//include '\n'
			}
			else
			{
				outString.Append(buffer+oldPos,mPos-oldPos);	//include '\n'
				++mPos;
				if (mPos+1<size&&StdString::ConstValues<char>::IsNewLine(buffer[mPos+1]))
				{
					++mPos;
				}
			}
			
			return true;
		default:
			break;
		}
		++mPos;
	}
	return true;
}

bool MemoryStream::ReadLineToString( WHeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());
	wchar* buffer=(wchar*)mData.GetData();
	size_t size=mData.GetSize()/sizeof(wchar);
	mPos/=sizeof(wchar);
	size_t oldPos=mPos;

	while (true)
	{
		if (mPos>=size)
		{
			outString.Append(buffer+oldPos,mPos-oldPos);
			mPos*=sizeof(wchar);

			return true;
		}

		switch (buffer[mPos])
		{
		case L'\0':
			outString.Append(buffer+oldPos,mPos-oldPos);
			mPos*=sizeof(wchar);

			return true;
		case StdString::ConstValues<wchar>::LineSeparator:
		case StdString::ConstValues<wchar>::Return:
			if (includeNewLine)
			{
				++mPos;
				if (mPos+1<size&&StdString::ConstValues<wchar>::IsNewLine(buffer[mPos+1]))
				{
					++mPos;
				}
				outString.Append(buffer+oldPos,mPos-oldPos);	//include '\n'
			}
			else
			{
				outString.Append(buffer+oldPos,mPos-oldPos);	//include '\n'
				++mPos;
				if (mPos+1<size&&StdString::ConstValues<wchar>::IsNewLine(buffer[mPos+1]))
				{
					++mPos;
				}
			}
			mPos*=sizeof(wchar);

			return true;
		default:
			break;
		}
		++mPos;
	}
	return true;
}

size_t MemoryStream::WriteString( const StringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	RETURN_ZERO_IF_EMPTY(str);
	byte* buffer=(byte*)str.c_str();
	size_t length=str.Length()+1;	//copy '\0'
	size_t offset=0;
	do
	{
		MemoryByteData data=MemoryByteData::FromStatic(buffer+offset,length-offset);
		size_t num=WriteData(data);
		offset+=num;
	}while (offset<length);

	return offset;
}

size_t MemoryStream::WriteString( const WStringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	byte* buffer=(byte*)str.c_str();
	size_t length=(str.Length()+1)*sizeof(wchar_t);//copy '\0'
	size_t offset=0;
	do
	{
		MemoryByteData data=MemoryByteData::FromStatic(buffer+offset,length-offset);
		size_t num=WriteData(data);
		offset+=num;
	}while (offset<length);

	return offset;
}

bool MemoryStream::CanWrite() const
{
	if (mIsExpandable)
	{
		return mIsOpen&&mIsWritable;
	}
	else
	{
		return mIsOpen&&mIsWritable&&mPos<mData.GetSize();
	}
	
}



MEDUSA_END;
