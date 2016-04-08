#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/FileDefines.h"

MEDUSA_BEGIN;

class IFileSystemAccessor
{
public:
	virtual ~IFileSystemAccessor(){}
	virtual bool Exists(StringRef filePath,int permission=0)const=0;
	virtual bool GetFileMode(StringRef filePath,FileMode& outFileMode)const=0;

	virtual bool Delete(StringRef filePath)const=0;
	virtual bool Copy(StringRef srcFilePath,StringRef destFilePath)const=0;
	virtual bool Move(StringRef srcFilePath,StringRef destFilePath)const=0;

	virtual MemoryByteData ReadAllData(StringRef filePath,const FileCoderList& coderList)const=0;
	virtual MemoryByteData ReadAllDataPriority(StringRef firstPath,StringRef secondPath,const FileCoderList& coderList)const=0;
	virtual bool WriteAllDataTo(MemoryByteData data,StringRef filePath,const FileCoderList& coderList)const=0;
protected:
	MemoryByteData Code( MemoryByteData& data,const FileCoderList& coderList ) const;

};


MEDUSA_END;
