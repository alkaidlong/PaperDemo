#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class ILoadable
	{
	public:
		bool LoadFromFilesPriority(StringRef firstPath,StringRef secondPath,const FileCoderList& coderList);
		bool LoadFromFile(StringRef path,const FileCoderList& coderList);
		virtual bool LoadFromData(const MemoryByteData& data);
		virtual void Unload();
	};
}

MEDUSA_END;