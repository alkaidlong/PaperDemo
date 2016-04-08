#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/Accessor/IFileSystemAccessor.h"
#include "Core/IO/FileList/FileCoderList.h"

MEDUSA_BEGIN;


Medusa::MemoryByteData IFileSystemAccessor::Code( MemoryByteData& data,const FileCoderList& coderList ) const
{
	if (!coderList.IsEmpty())
	{
		data=coderList.Code(data);
	}

	return data;
}

MEDUSA_END;
