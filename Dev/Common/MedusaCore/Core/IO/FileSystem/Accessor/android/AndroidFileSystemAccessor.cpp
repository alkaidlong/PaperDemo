#include "MedusaCorePreCompiled.h"
#include "AndroidFileSystemAccessor.h"
#include "Core/Log/Log.h"
#include "Core/IO/File.h"
#include "Core/IO/FileList/FileCoderList.h"

#ifdef MEDUSA_ANDROID
MEDUSA_BEGIN;


AndroidFileSystemAccessor::AndroidFileSystemAccessor(StringRef applicationPath)
{
	mZipReader.Open(applicationPath);
}


AndroidFileSystemAccessor::~AndroidFileSystemAccessor(void)
{
}

bool AndroidFileSystemAccessor::Exists( StringRef filePath,int permission/*=0*/ ) const
{
	//first check in writable path
	if (File::Exists(filePath,permission))
	{
		return true;
	}
	return mZipReader.Exists(filePath);
}


bool AndroidFileSystemAccessor::GetFileMode( StringRef filePath,FileMode& outFileMode ) const
{
	return File::GetFileMode(filePath,outFileMode);
}

bool AndroidFileSystemAccessor::Delete( StringRef filePath ) const
{
	return File::Delete(filePath);
}

bool AndroidFileSystemAccessor::Copy( StringRef srcFilePath,StringRef destFilePath ) const
{
	return File::Copy(srcFilePath,destFilePath);
}

bool AndroidFileSystemAccessor::Move( StringRef srcFilePath,StringRef destFilePath ) const
{
	return File::Move(srcFilePath,destFilePath);
}

Medusa::MemoryByteData AndroidFileSystemAccessor::ReadAllData( StringRef filePath,const FileCoderList& coderList ) const
{
	if (File::Exists(filePath))
	{
		MemoryByteData data= File::ReadAllData(filePath);
		return Code(data,coderList);
	}
	MemoryByteData data=mZipReader.ReadAllData(filePath);
	return Code(data,coderList);
}

Medusa::MemoryByteData AndroidFileSystemAccessor::ReadAllDataPriority( StringRef firstPath,StringRef secondPath,const FileCoderList& coderList ) const
{
	//try to read data from first path
	if(Exists(firstPath))
	{
		return ReadAllData(firstPath,coderList);
	}
	else
	{
		//try to read data from second path
		if (Exists(secondPath))
		{
			return ReadAllData(secondPath,coderList);
		}
		else
		{
			return MemoryByteData::Empty;
		}
	}
}

bool AndroidFileSystemAccessor::WriteAllDataTo( MemoryByteData data,StringRef filePath ,const FileCoderList& coderList) const
{
	//zip reader is readonly
	if (!coderList.IsEmpty())
	{
		MemoryByteData result=coderList.Code(data);
		return File::WriteAllDataTo(result,filePath);;
	}

	return File::WriteAllDataTo(data,filePath);
}


MEDUSA_END;

#endif