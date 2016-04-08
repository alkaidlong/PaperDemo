#include "MedusaCorePreCompiled.h"
#include "Core/Coder/LZMA/LZMAEncoder.h"
#include "Core/Coder/CoderFactory.h"

MEDUSA_BEGIN;

LZMAEncoder::LZMAEncoder(const IEventArg& e):ICoder(e)
{
}

LZMAEncoder::~LZMAEncoder()
{

}

bool LZMAEncoder::CodeInPlace(MemoryByteData& data) const 
{
	return false;
}

MemoryByteData LZMAEncoder::Code(const MemoryByteData& data) const 
{
	return MemoryByteData::Empty;
}

bool LZMAEncoder::TryGetResultSize(const MemoryByteData& data,size_t& outSize) const 
{
	outSize=0;
	return false;
}

bool LZMAEncoder::CodeTo(const MemoryByteData& data,MemoryByteData& outData) const 
{
	return false;
}


MemoryByteData LZMAEncoder::CodeSmart(MemoryByteData& data) const 
{
	return Code(data);
}





MEDUSA_END;