#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StackString.h"

MEDUSA_BEGIN;

class Guid
{
public:
	typedef StackString<64> StringType;

	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];

	static Guid NewGuid();
public:
	StringType ToString()const;
};
MEDUSA_END;