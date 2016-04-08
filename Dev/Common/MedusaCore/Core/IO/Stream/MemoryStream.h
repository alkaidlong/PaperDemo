#pragma once
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

class MemoryStream:public IStream
{
public:
	MemoryStream(size_t capacity=0);
	MemoryStream(const MemoryByteData& data,bool writable=true);
	virtual ~MemoryStream(void);
public:
	const MemoryByteData& GetBuffer() const { return mData; }
	void SetBuffer(const MemoryByteData& val) { mData = val; }
	MemoryByteData GetCurrentBuffer() const { return MemoryByteData::FromStatic(mData.GetData()+mPos,(size_t)GetLeftLength()); }

public:
	virtual bool Flush();
	virtual bool Close();
	virtual bool IsOpen()const{return mData.IsValid();}
	virtual bool IsEnd()const{return mPos>=mData.GetSize();}

	virtual bool Seek(int64 offset,SeekOrigin direction);

	virtual void SetLength(uint64 val);
	virtual uint64 GetLength()const{return mData.GetSize();}
	virtual uint64 GetPosition()const{return mPos;}

	virtual size_t ReadDataTo(MemoryByteData& outData,DataReadingMode mode=DataReadingMode::AlwaysCopy);
	virtual size_t WriteData(const MemoryByteData& data);

	virtual int PeekChar();
	virtual int PeekWChar();
	virtual int ReadChar();
	virtual int ReadWChar();
	virtual bool WriteChar(char val);
	virtual bool WriteChar(wchar val);

	virtual StringRef ReadString(size_t maxCount=1024);
	virtual WStringRef ReadStringW(size_t maxCount=1024);
	virtual bool ReadToString(HeapString& outString);
	virtual bool ReadToString(WHeapString& outString);
	virtual bool ReadLineToString(HeapString& outString,bool includeNewLine=true);
	virtual bool ReadLineToString(WHeapString& outString,bool includeNewLine=true);
	virtual size_t WriteString(const StringRef& str);
	virtual size_t WriteString(const WStringRef& str);

	virtual bool CanRead()const{return mIsOpen&&mPos<mData.GetSize();}
	virtual bool CanWrite()const;
	virtual bool CanSeek()const{return mIsOpen;}
private:
	bool Resize(size_t size);
private:
	MemoryByteData mData; 
	size_t mPos;
	bool mIsExpandable;
	bool mIsWritable;
	bool mIsOpen;
};


MEDUSA_END;