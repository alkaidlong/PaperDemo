#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"

#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class XXTEAEncryptor
{
public:
	XXTEAEncryptor(MemoryByteData key);
	~XXTEAEncryptor();

public:
	virtual MemoryByteData Encrypt(const MemoryByteData& data)const;
	virtual MemoryByteData Decrypt(const MemoryByteData& data)const;
private:
	static void EncryptHelper(MemoryUIntData v, MemoryUIntData k);
	static void DecryptHelper(MemoryUIntData v, MemoryUIntData k);
	static MemoryUIntData ToUIntArray(MemoryByteData data, bool includeLength);
	static  MemoryByteData ToByteArray(MemoryUIntData data, bool includeLength);
private:
	const static size_t mDelta = 0x9E3779B9;
	MemoryUIntData mKey;
};

MEDUSA_END;
