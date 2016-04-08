#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XOR/XORDecoder.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Coder/CoderFactory.h"

MEDUSA_BEGIN;

XORDecoder::XORDecoder(const IEventArg& e):ICoder(e)
{
	const UserDataEventArg<MemoryByteData>& e2=(const UserDataEventArg<MemoryByteData>&)e;
	mKey=e2.GetData();
}

XORDecoder::XORDecoder( const MemoryByteData& e ):ICoder(e)
{
	mKey=e;
}

XORDecoder::~XORDecoder()
{

}


bool XORDecoder::CodeInPlace(MemoryByteData& data) const 
{
	size_t keyIndex=0;
	size_t srcSize=data.GetSize();
	size_t keySize=mKey.GetSize();

	if (keySize!=srcSize)
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

MemoryByteData XORDecoder::Code(const MemoryByteData& data) const 
{
	MemoryByteData temp=MemoryByteData::Alloc(data.GetSize());

	if (CodeInPlace(temp))
	{
		return temp;
	}
	return MemoryByteData::Empty;
}

bool XORDecoder::TryGetResultSize(const MemoryByteData& data,size_t& outSize) const 
{
	outSize=data.GetSize();
	return true;
}

bool XORDecoder::CodeTo(const MemoryByteData& data,MemoryByteData& outData) const 
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

MemoryByteData XORDecoder::CodeSmart(MemoryByteData& data) const 
{
	CodeInPlace(data);
	return data;
}



MEDUSA_END;