#pragma once
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;

class MemoryFileAutoRegister
{
public:
	template<typename T>
	MemoryFileAutoRegister(const FileId& fileId,MemoryData<T> data)
	{
		EnvironmentTag matchAllTag(PublishVersions::All,PublishDevices::All,PublishLanguages::All);
		FileSystem::Instance().AddMemoryFile(fileId,data.template Cast<char>(),matchAllTag);

	}
	template<typename T>
	MemoryFileAutoRegister(const FileId& fileId,T* buffer,size_t byteSize)
	{
		MemoryByteData data=MemoryByteData::FromStatic((byte*)buffer,byteSize);
		EnvironmentTag matchAllTag(PublishVersions::All,PublishDevices::All,PublishLanguages::All);
		FileSystem::Instance().AddMemoryFile(fileId,data,matchAllTag);
	}
	template<typename T,size_t size>
	MemoryFileAutoRegister(const FileId& fileId,T (&buffer)[size])
	{
		MemoryByteData data=MemoryByteData::FromStatic((byte*)buffer,size*sizeof(T));
		EnvironmentTag matchAllTag(PublishVersions::All,PublishDevices::All,PublishLanguages::All);
		FileSystem::Instance().AddMemoryFile(fileId,data,matchAllTag);
	}

}; 

MEDUSA_END;