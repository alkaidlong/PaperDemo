#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/IO/File.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;


namespace Pattern
{
	bool ILoadable::LoadFromFilesPriority(StringRef firstPath, StringRef secondPath ,const FileCoderList& coderList)
	{
		bool isSuccess=LoadFromFile(firstPath,coderList);
		RETURN_TRUE_IF_TRUE(isSuccess);

		//failed to load it from write path, may be it's incompatible
		FileSystem::Instance().GetAccessor().Delete(firstPath);
		isSuccess=LoadFromFile(secondPath,coderList);
		if (!isSuccess)
		{
			//Still failed?
			Log::LogErrorFormat("Cannot load %s anyhow! Try to reinstall!",secondPath.c_str());
			return false;
		}

		return true;
	}

	bool ILoadable::LoadFromFile( StringRef path ,const FileCoderList& coderList)
	{
		RETURN_FALSE_IF_EMPTY(path);
		MemoryByteData data=FileSystem::Instance().GetAccessor().ReadAllData(path,coderList);
		return LoadFromData(data);
	}

	bool ILoadable::LoadFromData( const MemoryByteData& data )
	{
		Unload();
		if(data.IsNull())
		{
			return false;
		}

		return true;
	}

	void ILoadable::Unload()
	{
		
	}

}

MEDUSA_END;