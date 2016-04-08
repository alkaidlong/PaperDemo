#include "MedusaCorePreCompiled.h"
#include "Core/Coder/XXTEA/XXTEAEncryptor.h"

MEDUSA_BEGIN;


XXTEAEncryptor::XXTEAEncryptor(MemoryByteData key)
{
	mKey=ToUIntArray(key, false);
}

XXTEAEncryptor::~XXTEAEncryptor()
{
}

Medusa::MemoryByteData XXTEAEncryptor::Encrypt( const MemoryByteData& data ) const
{
	if (data.IsNull())
	{
		return data;
	}
	MemoryUIntData dataBuffer=ToUIntArray(data, true);
	EncryptHelper(dataBuffer,mKey);

	return ToByteArray(dataBuffer,false);;
}

Medusa::MemoryByteData XXTEAEncryptor::Decrypt( const MemoryByteData& data ) const
{
	if (data.IsNull())
	{
		return data;
	}
	MemoryUIntData dataBuffer=ToUIntArray(data, false);
	DecryptHelper(dataBuffer,mKey);
	return ToByteArray(dataBuffer,true);;
}


void XXTEAEncryptor::EncryptHelper( MemoryUIntData v, MemoryUIntData k )
{
	RETURN_IF_FALSE(v.IsValid());
	uint32 n =static_cast<uint32>(v.GetSize()) - 1;
	if (n < 1||k.GetSize() < 4)
	{
		return;
	}
	uint32 z = v[n];

	uint32 sum = 0;
	uint32 q = 6 + 52 / (n + 1);
	while (q-- > 0)
	{
		sum+=mDelta;
		uint32 e = sum >> 2 & 3;
		uint32 y;
		uint32 p;
		for (p = 0; p < n; p++)
		{
			y = v[p + 1];
			z = v[p] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z);
		}
		y = v[0];
		z = v[n] += (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z);
	}
	return ;
}


void XXTEAEncryptor::DecryptHelper( MemoryUIntData v, MemoryUIntData k )
{
	RETURN_IF_FALSE(v.IsValid());

	uint32 n =static_cast<uint32>( v.GetSize()) - 1;
	if (n < 1||k.GetSize() < 4)
	{
		return;
	}
	uint32 y = v[0];

	uint32 q = 6 + 52 / (n + 1);
	uint32 sum = (uint32)(q * mDelta);
	while (sum != 0)
	{
		uint32 e = sum >> 2 & 3;
		uint32 z;
		uint32 p;
		for (p = n; p > 0; p--)
		{
			z = v[p - 1];
			y = v[p] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z);
		}
		z = v[n];
		y = v[0] -= (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z);
		sum -= mDelta;
	}
	return;
}

Medusa::MemoryUIntData XXTEAEncryptor::ToUIntArray( MemoryByteData data, bool includeLength )
{
	size_t n = (((data.GetSize() & 3) == 0) ? (data.GetSize() >> 2) : ((data.GetSize() >> 2) + 1));
	MemoryUIntData result;

	if (includeLength)
	{
		result=MemoryUIntData::Alloc(n+1);
		result.ClearZero();
		result[n] = static_cast<uint32>(data.GetSize());
	}
	else
	{
		result=MemoryUIntData::Alloc(n);
		result.ClearZero();
	}

	n=data.GetSize();
	for (size_t i = 0; i < n; i++)
	{
		result[i >> 2] |= (size_t)data[i] << ((i & 3) << 3);
	}
	return result;
}

Medusa::MemoryByteData XXTEAEncryptor::ToByteArray( MemoryUIntData data, bool includeLength )
{
	size_t n;
	if (includeLength)
	{
		n = (size_t)data[data.GetSize() - 1];
	}
	else
	{
		n = data.GetSize() << 2;
	}
	MemoryByteData result=MemoryByteData::Alloc(n);
	result.ClearZero();

	for (size_t i = 0; i < n; i++)
	{
		result[i] = (byte)(data[i >> 2] >> ((i & 3) << 3));
	}
	return result;
}


MEDUSA_END;
