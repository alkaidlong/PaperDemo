#include "MedusaCorePreCompiled.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/String/StackString.h"
#include "Core/IO/Directory.h"

MEDUSA_BEGIN;

FileStream::FileStream(void):mFile(NULL),mFileSize(0)
{
}

FileStream::FileStream( StringRef inFileName,FileOpenMode openMode/*=FileOpenMode::ReadOnly*/,FileDataType dataType/*=FileDataType::Binary*/ ):mFile(NULL),mFileSize(0)
{
	Open(inFileName,openMode,dataType);
}

FileStream::~FileStream(void)
{
	if (mFile!=NULL)
	{
		Close();
	}
}

bool FileStream::OpenReadBinary( StringRef fileName )
{
	return Open(fileName,FileOpenMode::ReadOnly,FileDataType::Binary);
}

bool FileStream::OpenReadText( StringRef fileName )
{
	return Open(fileName,FileOpenMode::ReadOnly,FileDataType::Text);
}

bool FileStream::OpenNewWriteBinary( StringRef fileName )
{
	Directory::CreateDirectoryForFile(fileName);
	return Open(fileName,FileOpenMode::DestoryWriteOrCreate,FileDataType::Binary);
}

bool FileStream::OpenNewWriteText( StringRef fileName )
{
	Directory::CreateDirectoryForFile(fileName);
	return Open(fileName,FileOpenMode::DestoryWriteOrCreate,FileDataType::Text);
}

bool FileStream::Open( StringRef inFileName,FileOpenMode openMode,FileDataType dataType )
{
	RETURN_FALSE_IF_NULL_OR_EMPTY_STRING(inFileName);

	StackString<4> openModeString;

	switch (openMode.ToInt())
	{
	case FileOpenMode::ReadOnly.IntValue:
		openModeString="r";
		break;
	case FileOpenMode::DestoryWriteOrCreate.IntValue:
		openModeString="w";
		break;
	case FileOpenMode::AppendKeepEOFOrCreate.IntValue:
		openModeString="a";
		break;
	case FileOpenMode::ReadWrite.IntValue:	
		openModeString="r+";
		break;
	case FileOpenMode::DestoryReadWriteOrCreate.IntValue:
		openModeString="w+";
		break;
	case FileOpenMode::AppendClearEOFOrCreate.IntValue:	
		openModeString="a+";
		break;
	default:
		break;
	}



	if (dataType==FileDataType::Binary)	
	{
		openModeString+='b';
	}
	else if(dataType==FileDataType::Text)						
	{
		openModeString+='t';
	}

#ifdef MEDUSA_WINDOWS
	errno_t err= fopen_s(&mFile,inFileName.Buffer(),openModeString.Buffer());
#else 
	mFile=fopen(inFileName.Buffer(),openModeString.Buffer());
#endif

	if (mFile!=NULL)
	{
		if(Seek(0,SeekOrigin::End))
		{
 			mFileSize=GetPosition();
			Rewind();
		}

		mOpenMode=openMode;
		mFileName=inFileName;


		return true;
	}
	return false;
}

bool FileStream::Close()
{
	RETURN_TRUE_IF_NULL(mFile);
	bool result= fclose(mFile)==0;
	mFile=NULL;
	mFileSize=0;

	return result;
}

bool FileStream::Flush()
{
	return fflush(mFile)==0?true:false;
}

bool FileStream::IsEnd() const
{
	return feof(mFile)!=0;
}

size_t FileStream::WriteData(const MemoryByteData& data)
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	return fwrite(data.GetData(),1,data.GetSize(),mFile);
}

size_t FileStream::ReadDataTo( MemoryByteData& outData,DataReadingMode mode/*=DataReadingMode::AlwaysCopy*/)
{
	RETURN_ZERO_IF_FALSE(CanRead());
	//ignore mode
	size_t count= fread(outData.GetData(),1,outData.GetSize(),mFile);
	outData.ForceSetSize(count);
	return count;
}

int FileStream::PeekChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	int c=ReadChar();
	if (c!=-1)
	{
		ungetc(c,mFile);
	}
	return c;
}

int FileStream::PeekWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	int c=ReadWChar();
	if (c!=-1)
	{
		ungetwc(c,mFile);
	}
	return c;
}

int FileStream::ReadChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	return fgetc(mFile);
}

int FileStream::ReadWChar()
{
	RETURN_OBJECT_IF_FALSE(CanRead(),-1);
	ushort c= fgetwc(mFile);
	if (c==(ushort)WEOF)
	{
		return -1;
	}
	return (int)c;
}

bool FileStream::WriteChar( char val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	return fputc(val,mFile)!=EOF;
}
bool FileStream::WriteChar( wchar val )
{
	RETURN_FALSE_IF_FALSE(CanWrite());
	return fputwc(val,mFile)!=WEOF;
}

StringRef FileStream::ReadString(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return StringRef::Empty;
	}
	mTempString.Clear();
	mTempString.ReserveSize(maxCount);
	ReadToString(mTempString);
	mTempString.ReleaseExtraSize();
	return mTempString;

}

WStringRef FileStream::ReadStringW(size_t maxCount/*=1024*/)
{
	if(!CanRead())
	{
		return WStringRef::Empty;
	}

	mTempString.Clear();
	mTempString.ReserveSize(maxCount);
	ReadToString(mTempStringW);
	mTempString.ReleaseExtraSize();
	return mTempStringW;

}

bool FileStream::ReadToString( HeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());
	bool isSuccess=false;
	while (true)
	{
		int result=ReadChar();
		if (result!=-1)
		{
			isSuccess=true;
			outString.Append((char)result);
			BREAK_IF_ZERO(result);
		}
		else
		{
			break;
		}
	}

	return isSuccess;
}

bool FileStream::ReadToString( WHeapString& outString )
{
	RETURN_FALSE_IF_FALSE(CanRead());
	bool isSuccess=false;
	while (true)
	{
		int result=ReadWChar();
		if (result!=-1)
		{
			isSuccess=true;
			outString.Append((wchar)result);
			BREAK_IF_ZERO(result);
		}
		else
		{
			break;
		}
	}

	return isSuccess;
}

bool FileStream::ReadLineToString( HeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());
	char* str=fgets(outString.c_str(),static_cast<int>(outString.Size()),mFile);
	if (str!=outString.c_str())
	{
		outString.Clear();
		return false;
	}
	else if(!includeNewLine)
	{
		outString.RemoveEndAny(StdString::ConstValues<char>::NewLineChars);
	}

	outString.ForceUpdateLength();
	return true;
}

bool FileStream::ReadLineToString( WHeapString& outString ,bool includeNewLine/*=true*/)
{
	RETURN_FALSE_IF_FALSE(CanRead());
	wchar* str=fgetws(outString.c_str(),static_cast<int>(outString.Size()),mFile);
	if (str!=outString.c_str())
	{
		outString.Clear();
		return false;
	}
	else if(!includeNewLine)
	{
		outString.RemoveEndAny(StdString::ConstValues<wchar>::NewLineChars);
	}
	outString.ForceUpdateLength();
	return true;
}

size_t FileStream::WriteString( const StringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	if(fputs(str.c_str(),mFile)==EOF)
	{
		return 0;
	}

	//fputc('\0',mFile);	//fputs won't copy '\0'
	return str.Length();
}

size_t FileStream::WriteString( const WStringRef& str )
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	RETURN_ZERO_IF_FALSE(CanWrite());
	if(fputws(str.c_str(),mFile)==EOF)
	{
		return 0;
	}

	//fputwc(L'\0',mFile);	//fputws won't copy '\0'
	return str.Length();
}

bool FileStream::Seek( int64 offset,SeekOrigin direction )
{
	RETURN_FALSE_IF_FALSE(CanSeek());
	return fseek(mFile,(long)offset,direction.ToInt())==0;
}

int FileStream::Printf( const char* inStringFormat,... )const
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	va_list args;
	va_start(args,inStringFormat);
	int tWriteSize=fprintf(mFile,inStringFormat,args);
	va_end(args);
	return tWriteSize;
}

int FileStream::Scanf( const char* inStringFormat,... )const
{
	RETURN_ZERO_IF_FALSE(CanRead());
	va_list args;
	va_start(args,inStringFormat);
#ifdef MEDUSA_WINDOWS
	int tReadSize=fscanf_s(mFile,inStringFormat,args);
#else 
	int tReadSize=fscanf(mFile,inStringFormat,args);
#endif

	va_end(args);
	return tReadSize;
}

int FileStream::GetLastErrorID()const
{
	return ferror(mFile);
}

void FileStream::ClearError()const
{
	return clearerr(mFile);
}

void FileStream::Rewind()
{
	return rewind(mFile);
}

FILE* FileStream::CreateTempFile()
{
#ifdef MEDUSA_WINDOWS
	FILE* file;
	tmpfile_s(&file);
	return file;

#else
	return tmpfile();
#endif

}

int FileStream::GetFileHandle()const
{
#ifdef MEDUSA_WINDOWS
	return _fileno(mFile);
#else
	return fileno(mFile);
#endif
}

bool FileStream::IsErrorInFile()const
{
	return ferror(mFile)==0?false:true;
}


bool FileStream::GetCurrentPos( fpos_t* outPosition )const
{
	return fgetpos(mFile,outPosition)==0?true:false;
}

bool FileStream::SetCurrentPos( const fpos_t* inNewPosition )
{
	RETURN_ZERO_IF_FALSE(CanSeek());
	return fsetpos(mFile,inNewPosition)==0?true:false;
}

bool FileStream::SetBuffer( FileBufferMode mode,byte* buffer,size_t size ) const
{
	return setvbuf(mFile,(char*)buffer,mode.ToInt(),size)==0?true:false;
}

bool FileStream::WriteBack( int inBackChar )const
{
	RETURN_ZERO_IF_FALSE(CanWrite());
	return ungetc(inBackChar,mFile)!=EOF;
}

uint64 FileStream::GetPosition() const
{
	return ftell(mFile);
}

void FileStream::SetLength( uint64 val )
{
	RETURN_IF_FALSE(CanWrite());

#ifdef MEDUSA_WINDOWS
	_chsize_s(mFile->_file,val);
#elif defined( MEDUSA_LINUX )
	ftruncate(mFile->_fileno,val);
#else
	ftruncate(mFile->_file,val);
	//_chsize(mFile->_file,val);
#endif

}





MEDUSA_END;
