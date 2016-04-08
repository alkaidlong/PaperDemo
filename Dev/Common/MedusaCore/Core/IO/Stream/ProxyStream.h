#pragma once
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

class ProxyStream:public IStream
{
public:
	ProxyStream(IStream* stream,uint64 litmitSize=0,bool autoCloseSourceStream=false);
	virtual ~ProxyStream(void);
public:
	virtual bool Flush();
	virtual bool Close();
	virtual bool IsOpen()const{return mSourceStream->IsOpen();}
	virtual bool IsEnd()const;

	virtual bool Seek(int64 offset,SeekOrigin direction);

	virtual void SetLength(uint64 val);
	virtual uint64 GetLength()const;
	virtual uint64 GetPosition()const{return mSourceStream->GetPosition()-mBeginPosition;}

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

	virtual bool CanRead()const;
	virtual bool CanWrite()const;
	virtual bool CanSeek()const{return mSourceStream->CanSeek();}
private:
	bool IsSourcePosValid()const;
private:
	IStream* mSourceStream;
	uint64 mBeginPosition;
	uint64 mLimitSize;
	bool mAutoCloseSourceStream;
};


MEDUSA_END;