#pragma once
#include "Core/IO/FileDefines.h"
#include "Core/Memory/Memory.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

STRONG_ENUM_CUSTOM_3(SeekOrigin,Head,SEEK_SET,Current,SEEK_CUR,End,SEEK_END);

enum class DataReadingMode
{
	AlwaysCopy=0,
	DirectMove=1
};


class IStream
{
public:
	IStream(void){}
	virtual ~IStream(void){}
public:
	template<class T>
	bool ReadTo(T& outVal)
	{
		MemoryByteData data=MemoryByteData::FromStatic((byte*)&outVal,sizeof(T));
		return ReadDataTo(data)==sizeof(T);
	};

	//So confident that this have to be succeed!
	template<class T>
	T Read()
	{
		T outVal;
		MemoryByteData data=MemoryByteData::FromStatic((byte*)&outVal,sizeof(T));
		ReadDataTo(data);
		return outVal;
	};

	template<class T,typename TCompare>
	bool ReadToList(size_t size,List<T,TCompare>& outItems)
	{
		outItems.Clear();
		size_t count=size/sizeof(T);
		outItems.ReserveSize(count);
		byte* buffer=(byte*)outItems.GetItems();

		MemoryByteData data=MemoryByteData::FromStatic(buffer,count);
		size_t readSize=ReadDataTo(data);
		outItems.ForceSetCount(readSize/sizeof(T));
		return readSize==size;
	}
	MemoryByteData ReadBeginToCurrent(DataReadingMode mode=DataReadingMode::AlwaysCopy);
	MemoryByteData ReadToEnd(DataReadingMode mode=DataReadingMode::AlwaysCopy);
	MemoryByteData ReadData(size_t size,DataReadingMode mode=DataReadingMode::AlwaysCopy);

public:
	template<class T>
	bool Write(T val)
	{
		return WriteData(MemoryByteData::FromStatic((byte*)&val,sizeof(T)))==sizeof(T);
	}

public:
	void SetPosition(uint64 val){Seek((int64)val,SeekOrigin::Head);}
	uint64 GetLeftLength()const{return GetLength()-GetPosition();}
	bool Skip(size_t size){return Seek((int)size,SeekOrigin::Current);}
	template<typename T> IStream& operator<<(T val){Write(val);return *this;}
	template<typename T> IStream& operator>>(T val){ReadTo(val);return *this;}
	bool CopyTo(IStream& dest,size_t bufferSize=1024);
	void ReadAllLinesTo(List<HeapString>& outLines,size_t maxCount=1024,bool isTrim=true,bool ignoreEmptyLine=true);
	size_t WriteLine();
	size_t WriteLineW();

	size_t WriteLine(const StringRef& str);
	size_t WriteLine(const WStringRef& str);
public:
	virtual void Rewind(){Seek(0,SeekOrigin::Head);}

	virtual bool Flush()=0;
	virtual bool Close()=0;
	virtual bool IsOpen()const=0;
	virtual bool IsEnd()const=0;


	virtual bool Seek(int64 offset,SeekOrigin direction)=0;
	virtual void SetLength(uint64 val)=0;
	virtual uint64 GetLength()const=0;
	virtual uint64 GetPosition()const=0;

	virtual size_t ReadDataTo(MemoryByteData& outData,DataReadingMode mode=DataReadingMode::AlwaysCopy)=0;
	virtual int PeekChar()=0;
	virtual int PeekWChar()=0;
	virtual int ReadChar()=0;
	virtual int ReadWChar()=0;


	virtual StringRef ReadString(size_t maxCount=1024)=0;
	virtual WStringRef ReadStringW(size_t maxCount=1024)=0;
	virtual bool ReadToString(HeapString& outString)=0;
	virtual bool ReadToString(WHeapString& outString)=0;
	virtual bool ReadLineToString(HeapString& outString,bool includeNewLine=true)=0;
	virtual bool ReadLineToString(WHeapString& outString,bool includeNewLine=true)=0;

	virtual bool WriteChar(char val)=0;
	virtual bool WriteChar(wchar val)=0;
	virtual size_t WriteData(const MemoryByteData& data)=0;

	virtual size_t WriteString(const StringRef& str)=0;
	virtual size_t WriteString(const WStringRef& str)=0;
	

	virtual bool CanRead()const=0;
	virtual bool CanWrite()const=0;
	virtual bool CanSeek()const=0;

};


MEDUSA_END;