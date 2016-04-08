#include "MedusaCorePreCompiled.h"
#include "Core/Coder/LZMA/LZMADecoder.h"
#include "Core/Coder/CoderFactory.h"

MEDUSA_BEGIN;

LZMADecoder::LZMADecoder(const IEventArg& e):ICoder(e)
{
}

LZMADecoder::~LZMADecoder()
{

}

static void* LZMAAlloc(void *p, size_t size)
{
	return malloc(size);
}

static void LZMAFree(void *p, void *address)
{
	SAFE_FREE(address);
}

bool LZMADecoder::CodeInPlace(MemoryByteData& data) const 
{
	return false;
}

MemoryByteData Medusa::LZMADecoder::Code( const MemoryByteData& data ) const
{
	const byte* inBuffer=data.GetData();
	size_t inSize=data.GetSize();
	const size_t propSize=5;
	ELzmaStatus outStatus;

	ISzAlloc myAlloc;
	myAlloc.Alloc=LZMAAlloc;
	myAlloc.Free=LZMAFree;

	CLzmaDec p;
	SRes res;
	if (inSize < propSize)
		return MemoryByteData::Empty;

	LzmaDec_Construct(&p);
	
	res = LzmaDec_AllocateProbs(&p, inBuffer, propSize, &myAlloc);

	uint64 fileSize = 0;
	for (int i = 0; i < 8; i++)
		fileSize |= ((uint64)inBuffer[propSize + i]) << (8 * i);

	MemoryByteData result=MemoryByteData::Alloc((size_t)fileSize);

	LzmaDec_Init(&p);
	p.dic = result.GetData();
	p.dicBufSize = (size_t)fileSize;

	size_t outSize=inSize-13;
	res = LzmaDec_DecodeToDic(&p, (size_t)fileSize, inBuffer+13, &outSize, LZMA_FINISH_ANY, &outStatus);

	if (res == SZ_OK && outStatus == LZMA_STATUS_NEEDS_MORE_INPUT)
		res = SZ_ERROR_INPUT_EOF;

	LzmaDec_FreeProbs(&p, &myAlloc);
	return result;
}

bool LZMADecoder::TryGetResultSize(const MemoryByteData& data,size_t& outSize) const 
{
	const byte* inBuffer=data.GetData();
	size_t inSize=data.GetSize();
	const size_t propSize=5;

	ISzAlloc myAlloc;
	myAlloc.Alloc=LZMAAlloc;
	myAlloc.Free=LZMAFree;

	CLzmaDec p;
	SRes res;
	if (inSize < propSize)
		return false;

	LzmaDec_Construct(&p);

	res = LzmaDec_AllocateProbs(&p, inBuffer, propSize, &myAlloc);

	uint64 fileSize = 0;
	for (int i = 0; i < 8; i++)
		fileSize |= ((uint64)inBuffer[propSize + i]) << (8 * i);

	outSize=(size_t)fileSize;

	LzmaDec_FreeProbs(&p, &myAlloc);

	return true;
}

bool LZMADecoder::CodeTo(const MemoryByteData& data,MemoryByteData& outData) const 
{
	const byte* inBuffer=data.GetData();
	size_t inSize=data.GetSize();
	const size_t propSize=5;
	ELzmaStatus outStatus;

	ISzAlloc myAlloc;
	myAlloc.Alloc=LZMAAlloc;
	myAlloc.Free=LZMAFree;

	CLzmaDec p;
	SRes res;
	if (inSize < propSize)
		return false;

	LzmaDec_Construct(&p);

	res = LzmaDec_AllocateProbs(&p, inBuffer, propSize, &myAlloc);

	uint64 fileSize = 0;
	for (int i = 0; i < 8; i++)
		fileSize |= ((uint64)inBuffer[propSize + i]) << (8 * i);

	if (outData.GetSize()!=(size_t)fileSize)
	{
		LzmaDec_FreeProbs(&p, &myAlloc);
		return false;
	}
	else
	{
		LzmaDec_Init(&p);
		p.dic = outData.GetData();
		p.dicBufSize = (size_t)fileSize;

		size_t outSize=inSize-13;
		res = LzmaDec_DecodeToDic(&p, (size_t)fileSize, inBuffer+13, &outSize, LZMA_FINISH_ANY, &outStatus);

		if (res == SZ_OK && outStatus == LZMA_STATUS_NEEDS_MORE_INPUT)
			res = SZ_ERROR_INPUT_EOF;

		LzmaDec_FreeProbs(&p, &myAlloc);
		return true;
	}
	
}


MemoryByteData LZMADecoder::CodeSmart(MemoryByteData& data) const 
{
	return Code(data);
}




MEDUSA_END;