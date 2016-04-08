#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;


Medusa::MemoryByteData IStream::ReadBeginToCurrent( DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/ )
{
	uint64 pos=GetPosition();
	Rewind();
	return ReadData((size_t)pos,mode);
}

Medusa::MemoryByteData IStream::ReadToEnd(DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)
{
	return ReadData((size_t)GetLeftLength(),mode);
}

Medusa::MemoryByteData IStream::ReadData( size_t size,DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/ )
{
	if (GetLeftLength()>=size)
	{
		switch (mode)
		{
		case DataReadingMode::AlwaysCopy:
			{
				MemoryByteData data=MemoryByteData::Alloc(size);
				ReadDataTo(data,mode);
				return data;
			}
			break;
		case DataReadingMode::DirectMove:
			{
				MemoryByteData data;
				data.ForceSetSize(size);
				ReadDataTo(data,mode);
				return data;
			}
			break;
		default:
			break;
		}
		
	}
	return MemoryByteData::Empty;
}

bool IStream::CopyTo( IStream& dest,size_t bufferSize/*=1024*/ ) 
{
	RETURN_FALSE_IF_FALSE(CanRead()&&dest.CanWrite());

	MemoryByteData buffer;
	buffer.ForceSetSize(bufferSize);
	do 
	{
		size_t count=ReadDataTo(buffer,DataReadingMode::DirectMove);
		BREAK_IF_ZERO(count);
		dest.WriteData(buffer.Sub(count));
	} while (true);
	
	return true;
}

void IStream::ReadAllLinesTo( List<HeapString>& outLines,size_t maxCount/*=1024*/,bool isTrim/*=true*/,bool ignoreEmptyLine/*=true*/ )
{
	HeapString temp;
	temp.ReserveSize(maxCount);
	while(true)
	{
		ReadLineToString(temp);
		BREAK_IF_EMPTY(temp);
		if (ignoreEmptyLine)
		{
			CONTINUE_IF_EMPTY(temp);
		}

		if (isTrim)
		{
			temp.TrimAll();
		}
		outLines.Add(temp);
		temp.ForceSetLength(0);
	}
}

size_t IStream::WriteLine()
{
	return Write(StdString::ConstValues<char>::LineSeparator);
}
size_t IStream::WriteLineW()
{
	return Write(StdString::ConstValues<wchar>::LineSeparator);
}

size_t IStream::WriteLine( const StringRef& str )
{
	return WriteString(str)+WriteLine();
}

size_t IStream::WriteLine( const WStringRef& str )
{
	return WriteString(str)+WriteLineW();
}
MEDUSA_END;
