#pragma once
#include "Core/Event/EventArg/IEventArg.h"
#include "PaperHeader.h"

USING_MEDUSA;


class TextureLoadEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI(TextureLoadEventArg);
public:
	TextureLoadEventArg(const StringRef path,const MemoryByteData& data):mPath(path),mData(data),mTexture(NULL){}
	virtual ~TextureLoadEventArg(void){}

	StringRef GetPath() const { return mPath; }
	const MemoryByteData& GetData() const { return mData; }

	CCTexture2D* GetTexture() const { return mTexture; }
	void SetTexture(CCTexture2D* val) { mTexture = val; }
protected:
	HeapString mPath;
	MemoryByteData mData;
	CCTexture2D* mTexture;
	
};


