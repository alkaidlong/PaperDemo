#pragma once

#include "Core/IO/FileDefines.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class FileStream:public IStream
{
public:
	FileStream(void);
	FileStream(StringRef inFileName,FileOpenMode openMode=FileOpenMode::ReadOnly,FileDataType dataType=FileDataType::Binary);

	~FileStream(void);
public:
	bool OpenReadBinary(StringRef fileName);
	bool OpenReadText(StringRef fileName);
	bool OpenNewWriteBinary(StringRef fileName);
	bool OpenNewWriteText(StringRef fileName);
	bool Open(StringRef inFileName,FileOpenMode openMode=FileOpenMode::ReadOnly,FileDataType dataType=FileDataType::Binary);

	int Printf(const char* inStringFormat,...)const;
	int Scanf(const char* inStringFormat,...)const;
	int GetLastErrorID()const;
	void ClearError()const;
	static FILE* CreateTempFile();
	int GetFileHandle()const;
	bool IsErrorInFile()const;
	bool GetCurrentPos(fpos_t* outPosition)const;
	bool SetCurrentPos(const fpos_t* inNewPosition);
	
	bool SetBuffer(FileBufferMode mode,byte* buffer,size_t size)const;
	bool WriteBack(int inBackChar)const;
	FILE* GetFile() const { return mFile; }
	virtual bool IsOpen()const{return mFile!=NULL;}
	virtual bool IsEnd()const;

public:
	virtual void Rewind();

	virtual bool Flush();
	virtual bool Close();
	virtual bool Seek(int64 offset,SeekOrigin direction);
	virtual void SetLength(uint64 val);
	virtual uint64 GetLength()const{return mFileSize;}
	virtual uint64 GetPosition()const;

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



	virtual bool CanRead()const{return !IsEnd();}
	virtual bool CanWrite()const{return mOpenMode!=FileOpenMode::ReadOnly;}
	virtual bool CanSeek()const{return true;}

private:
	FILE* mFile;
	uint64 mFileSize;
	HeapString mFileName;
	FileOpenMode mOpenMode;

	HeapString mTempString;
	WHeapString mTempStringW;
};


MEDUSA_END;