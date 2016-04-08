#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XOR/XOREncoder.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Coder/CoderFactory.h"
MEDUSA_BEGIN;

XOREncoder::XOREncoder(const IEventArg& e):ICoder(e)
{
	const UserDataEventArg<MemoryByteData>& e2=(const UserDataEventArg<MemoryByteData>&)e;
	mKey=e2.GetData();
}

XOREncoder::XOREncoder( const MemoryByteData& e ):ICoder(e)
{
	mKey=e;
}


XOREncoder::~XOREncoder()
{

}

bool XOREncoder::CodeInPlace(MemoryByteData& data) const 
{
	size_t keyIndex=0;
	size_t srcSize=data.GetSize();
	size_t keySize=mKey.GetSize();

	if (srcSize!=keySize)
	{
		for (size_t i=0;i<srcSize;++i)
		{
			data[i]^=mKey[keyIndex];
			if (keyIndex<keySize-1)
			{
				++keyIndex;
			}
			else
			{
				keyIndex=0;
			}
		}
	}
	else
	{
		for (size_t i=0;i<srcSize;++i)
		{
			data[i]^=mKey[i];
		}
	}

	return true;
}

MemoryByteData XOREncoder::Code(const MemoryByteData& data) const 
{
	MemoryByteData temp=MemoryByteData::Alloc(data.GetSize());

	if (CodeInPlace(temp))
	{
		return temp;
	}
	return MemoryByteData::Empty;
}

bool XOREncoder::TryGetResultSize(const MemoryByteData& data,size_t& outSize) const 
{
	outSize=data.GetSize();
	return true;
}

bool XOREncoder::CodeTo(const MemoryByteData& data,MemoryByteData& outData) const 
{
	size_t keyIndex=0;
	size_t srcSize=data.GetSize();
	size_t keySize=mKey.GetSize();

	if (keySize!=srcSize)
	{
		for (size_t i=0;i<srcSize;++i)
		{
			outData[i]=data[i]^mKey[keyIndex];
			if (keyIndex<keySize-1)
			{
				++keyIndex;
			}
			else
			{
				keyIndex=0;
			}
		}
	}
	else
	{
		for (size_t i=0;i<srcSize;++i)
		{
			outData[i]=data[i]^mKey[i];
		}
	}

	return true;
}

MemoryByteData XOREncoder::CodeSmart(MemoryByteData& data) const 
{
	CodeInPlace(data);
	return data;
}


MEDUSA_END;