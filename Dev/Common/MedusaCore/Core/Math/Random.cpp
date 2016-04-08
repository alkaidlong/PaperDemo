#include "MedusaCorePreCompiled.h"
#include "Core/Math/Random.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;



Random::~Random(void)
{
}

void Random::NextBytes( MemoryByteData& outData ) const
{
	byte* buffer=outData.GetData();
	size_t size=outData.GetSize();
	FOR_EACH_SIZE(i,size)
	{
		buffer[i]=StaticNextByteWithoutSeed();
	}
}

void Random::StaticNextBytes( MemoryByteData& outData )
{
	StaticSrand();
	byte* buffer=outData.GetData();
	size_t size=outData.GetSize();
	FOR_EACH_SIZE(i,size)
	{
		buffer[i]=StaticNextByteWithoutSeed();
	}
}

void Random::StaticNextBytesWithoutSeed(MemoryByteData& outData)
{
	byte* buffer=outData.GetData();
	size_t size=outData.GetSize();
	FOR_EACH_SIZE(i,size)
	{
		buffer[i]=StaticNextByteWithoutSeed();
	}
}

MEDUSA_END;
