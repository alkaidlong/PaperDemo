#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/ProxyStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


ProxyStream::ProxyStream( IStream* stream,uint64 limitSize/*=0*/,bool autoCloseSourceStream/*=false*/ )
	:mSourceStream(stream),mLimitSize(limitSize),mAutoCloseSourceStream(autoCloseSourceStream)
{
	LOG_ASSERT_NOT_NULL(stream);
	mBeginPosition=stream->GetPosition();
	if (mLimitSize!=0)
	{
		MEDUSA_ASSERT_LESS_EQUAL(limitSize,mSourceStream->GetLeftLength(),"Invalid limitSize");
	}
}

ProxyStream::~ProxyStream(void)
{
	Close();
}

bool ProxyStream::IsSourcePosValid() const
{
	RETURN_FALSE_IF_NULL(mSourceStream);
	uint64 pos=mSourceStream->GetPosition();
	RETURN_FALSE_IF_FALSE(pos>=mBeginPosition);
	return mLimitSize==0?true:pos-mBeginPosition<=mLimitSize;
}

bool ProxyStream::IsEnd() const
{
	return mSourceStream->IsEnd()||(mLimitSize!=0&&mSourceStream->GetLeftLength()>=mLimitSize);
}

uint64 ProxyStream::GetLength() const
{
	return mLimitSize!=0?mLimitSize:mSourceStream->GetLength();
}


bool ProxyStream::CanRead() const
{
	RETURN_FALSE_IF_FALSE(mSourceStream->CanRead());
	return IsSourcePosValid();
}

bool ProxyStream::CanWrite() const
{
	RETURN_FALSE_IF_FALSE(mSourceStream->CanWrite());
	return IsSourcePosValid();
}

bool ProxyStream::Flush()
{
	return mSourceStream->Flush();
}

bool ProxyStream::Close()
{
	if (mSourceStream!=NULL)
	{
		mSourceStream->SetPosition(mBeginPosition);
	}

	if (mAutoCloseSourceStream)
	{
		SAFE_DELETE(mSourceStream);
	}

	mSourceStream=NULL;
	mAutoCloseSourceStream=false;
	mBeginPosition=0;
	mLimitSize=0;

	return true;
}

bool ProxyStream::Seek( int64 offset,SeekOrigin direction )
{
	RETURN_FALSE_IF_FALSE(CanSeek());
	uint64 originalPos=GetPosition();
	RETURN_FALSE_IF_FALSE(mSourceStream->Seek(offset,direction));
	if (!IsSourcePosValid())
	{
		//roll back
		mSourceStream->SetPosition(originalPos);
		return false;
	}
	return true;
}

void ProxyStream::SetLength( uint64 val )
{
	RETURN_IF_FALSE(CanWrite());
	mSourceStream->SetLength(val);
	if (mLimitSize!=0&&mLimitSize>val)
	{
		mLimitSize=val;	//auto update limit size
	}

	mBeginPosition=Math::Min(mBeginPosition,val);
	
}


size_t ProxyStream::ReadDataTo( MemoryByteData& outData ,DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanRead());
	size_t readSize=Math::Min((size_t)GetLeftLength(),outData.GetSize());
	size_t oldSize=outData.GetSize();
	outData.ForceSetSize(readSize);
	size_t result=mSourceStream->ReadDataTo(outData,mode);
	outData.ForceSetSize(oldSize);
	return result;
	
}

size_t ProxyStream::WriteData( const MemoryByteData& data )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	if (mLimitSize==0)
	{
		return mSourceStream->WriteData(data);
	}

	size_t newSize=Math::Min(data.GetSize(),(size_t)GetLeftLength());
	MemoryByteData tempData=data;
	tempData.ForceSetSize(newSize);

	return mSourceStream->WriteData(tempData);
}

int ProxyStream::PeekChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	return mSourceStream->PeekChar();
}

int ProxyStream::PeekWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	if (GetPosition()+sizeof(wchar)-1>=GetLength())
	{
		return -1;
	}
	return mSourceStream->PeekWChar();
}


int ProxyStream::ReadChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	return mSourceStream->ReadChar();
}

int ProxyStream::ReadWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	if (GetPosition()+sizeof(wchar)-1>=GetLength())
	{
		return -1;
	}
	return mSourceStream->ReadWChar();
}

bool ProxyStream::WriteChar( char val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	return mSourceStream->WriteChar(val);
}

bool ProxyStream::WriteChar( wchar val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());

	if (GetPosition()+sizeof(wchar)-1>=GetLength())
	{
		return false;
	}
	return mSourceStream->WriteChar(val);
}

StringRef ProxyStream::ReadString(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return StringRef::Empty;
	}
	uint64 oldPos=GetPosition();
	StringRef result=mSourceStream->ReadString(maxCount);
	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		return StringRef::Empty;
	}
	return result;
}

WStringRef ProxyStream::ReadStringW(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return WStringRef::Empty;
	}
	uint64 oldPos=GetPosition();
	WStringRef result=mSourceStream->ReadStringW(maxCount);
	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		return WStringRef::Empty;
	}
	return result;
}

bool ProxyStream::ReadToString( HeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());
	
	uint64 oldPos=GetPosition();
	bool isSuccess=mSourceStream->ReadToString(outString);
	RETURN_FALSE_IF_FALSE(isSuccess);

	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		outString.Clear();
		return false;
	}
	return true;
}

bool ProxyStream::ReadToString( WHeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());

	uint64 oldPos=GetPosition();
	bool isSuccess=mSourceStream->ReadToString(outString);
	RETURN_FALSE_IF_FALSE(isSuccess);

	if (!IsSourcePosValid())
	{
		SetPosition(oldPos);
		outString.Clear();
		return false;
	}
	return true;

}

bool ProxyStream::ReadLineToString( HeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());

	bool isSuccess=mSourceStream->ReadLineToString(outString,includeNewLine);
	RETURN_FALSE_IF_FALSE(isSuccess);

	if (!IsSourcePosValid())
	{
		uint64 newPos=GetPosition();
		uint64 adjustPos=mBeginPosition+mLimitSize;
		SetPosition(adjustPos);

		size_t extraSize=size_t(newPos-adjustPos);
		outString.RemoveAt(outString.Length()-extraSize,extraSize);
	}
	return true;
}

bool ProxyStream::ReadLineToString( WHeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());
	bool isSuccess=mSourceStream->ReadLineToString(outString,includeNewLine);
	RETURN_FALSE_IF_FALSE(isSuccess);

	if (!IsSourcePosValid())
	{
		uint64 newPos=GetPosition();
		uint64 adjustPos=mBeginPosition+mLimitSize;
		SetPosition(adjustPos);

		size_t extraSize=size_t(newPos-adjustPos);
		extraSize*=sizeof(wchar);
		outString.RemoveAt(outString.Length()-extraSize,extraSize);
	}
	return true;
}

size_t ProxyStream::WriteString( const StringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryByteData data=str.ToData().Cast<byte>();
	return mSourceStream->WriteData(data);
}

size_t ProxyStream::WriteString( const WStringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	MemoryByteData data=str.ToData().Cast<byte>();
	return mSourceStream->WriteData(data);
}

MEDUSA_END;
