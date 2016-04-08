#pragma once
#include "Core/IO/FileSystem/Accessor/IFileSystemAccessor.h"
#include "Core/Compress/ZipReader.h"

#ifdef MEDUSA_ANDROID

MEDUSA_BEGIN;

class AndroidFileSystemAccessor:public IFileSystemAccessor
{
public:
	AndroidFileSystemAccessor(StringRef applicationPath);
	virtual ~AndroidFileSystemAccessor(void);

	virtual bool Exists(StringRef filePath,int permission=0)const;
	virtual bool GetFileMode(StringRef filePath,FileMode& outFileMode)const;

	virtual bool Delete(StringRef filePath)const;
	virtual bool Copy(StringRef srcFilePath,StringRef destFilePath)const;
	virtual bool Move(StringRef srcFilePath,StringRef destFilePath)const;

	virtual MemoryByteData ReadAllData(StringRef filePath,const FileCoderList& coderList)const;
	virtual MemoryByteData ReadAllDataPriority(StringRef firstPath,StringRef secondPath,const FileCoderList& coderList)const;
	virtual bool WriteAllDataTo(MemoryByteData data,StringRef filePath,const FileCoderList& coderList)const;
private:
	ZipReader mZipReader;
};


MEDUSA_END;

#endif