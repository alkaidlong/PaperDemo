#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;

class MD5 
{
public:
	MD5();
	MD5(const void* input, size_t length);
	MD5(const StringRef& str);
	HeapString ToString();
public:
	const byte* Digest();

	void Update(const void* input, size_t length);
	void Update(const StringRef& str);
	void Reset();

private:
	void Update(const byte* input, size_t length);
	void Final();
	void Transform(const byte block[64]);
	void Encode(const uint32* input, byte* output, size_t length);
	void Decode(const byte* input, uint32* output, size_t length);
	static HeapString BytesToHexString(const byte* input, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);

private:
	uint32 _state[4];	/* state (ABCD) */
	uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message Digest */
	bool _finished;		/* calculate finished ? */

	static const byte PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const int mBufferSize=1024;
};


MEDUSA_END;