#pragma once
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class XORDecoder:public ICoder
{
public:
	XORDecoder(const IEventArg& e);
	XORDecoder(const MemoryByteData& e);

	~XORDecoder();

	void SetKey(const MemoryByteData& e){mKey=e;}


	virtual bool CodeInPlace(MemoryByteData& data)const override;
	virtual MemoryByteData Code(const MemoryByteData& data)const override;
	virtual bool TryGetResultSize(const MemoryByteData& data,size_t& outSize)const override;
	virtual bool CodeTo(const MemoryByteData& data,MemoryByteData& outData)const override;
	virtual MemoryByteData CodeSmart(MemoryByteData& data)const override;
private:
	MemoryByteData mKey;
};

MEDUSA_END;