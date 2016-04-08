#include "MedusaCorePreCompiled.h"
#include "PosixFileSystemAccessor.h"
#include "Core/IO/File.h"
#include "Core/IO/FileList/FileCoderList.h"

MEDUSA_BEGIN;

#if defined(MEDUSA_WINDOWS)||defined(MEDUSA_IOS)||defined(MEDUSA_LINUX)

PosixFileSystemAccessor::PosixFileSystemAccessor(void)
{
}


PosixFileSystemAccessor::~PosixFileSystemAccessor(void)
{
}

bool PosixFileSystemAccessor::Exists( StringRef filePath,int permission/*=0*/ ) const
{
	return File::Exists(filePath,permission);
}


bool PosixFileSystemAccessor::GetFileMode( StringRef filePath,FileMode& outFileMode ) const
{
	return File::GetFileMode(filePath,outFileMode);		 
}

bool PosixFileSystemAccessor::Delete( StringRef filePath ) const
{
	return File::Delete(filePath);
}

bool PosixFileSystemAccessor::Copy( StringRef srcFilePath,StringRef destFilePath ) const
{
	return File::Copy(srcFilePath,destFilePath);
}

bool PosixFileSystemAccessor::Move( StringRef srcFilePath,StringRef destFilePath ) const
{
	return File::Move(srcFilePath,destFilePath);
}

Medusa::MemoryByteData PosixFileSystemAccessor::ReadAllData( StringRef filePath,const FileCoderList& coderList ) const
{
	MemoryByteData data=File::ReadAllData(filePath);
	return Code(data,coderList);
}

Medusa::MemoryByteData PosixFileSystemAccessor::ReadAllDataPriority( StringRef firstPath,StringRef secondPath,const FileCoderList& coderList ) const
{
	MemoryByteData data=File::ReadAllDataPriority(firstPath,secondPath);
	return Code(data,coderList);
}

bool PosixFileSystemAccessor::WriteAllDataTo( MemoryByteData data,StringRef filePath,const FileCoderList& coderList ) const
{
	if (!coderList.IsEmpty())
	{
		MemoryByteData result=coderList.Code(data);
		return  File::WriteAllDataTo(result,filePath);
	}

	return File::WriteAllDataTo(data,filePath);
}



#endif

MEDUSA_END;
