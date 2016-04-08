#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Compile/Type.h"
#include "Core/Compile/TypeTraits.h"

MEDUSA_BEGIN;



namespace Utility
{
	bool IsLittleEndian();
	void EnableFloatPointException(bool isEnable);
	bool HasBit(size_t val,byte index);
	uint32 SwapUInt32(uint32 val);
	uint64 SwapUInt64(uint64 val);

	void SwapBytes(unsigned char* data,size_t size);

	inline uint64 GetHighPart(uint64 val){return val&0xffffffff00000000ull;}


}

MEDUSA_END;