#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class ISerializable
	{
	public:
		virtual MemoryByteData Serialize(const MemoryByteData& data)const=0;
		virtual MemoryByteData Unserialize(const MemoryByteData& data)const=0;
	};
}

MEDUSA_END;