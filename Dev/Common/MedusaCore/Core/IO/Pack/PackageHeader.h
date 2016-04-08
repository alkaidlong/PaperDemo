#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

/*
WithoutNameFile: remove dirs and file names in file list, only use name hash to locate file content.
We cannot enumerate file names or add new file in this mode.
*/
STRONG_FLAGS_3(PackageFlags,IsEncrypted,IsCompressed,WithoutNameFile);

enum class PackageCoderType
{
	None=0,
	LZMAEncoder=1,
	XOREncoder=2,

	LZMADecoder=101,
	XORDecoder=102,
};

struct PackageCoderInfo
{
	PackageCoderInfo():Type(PackageCoderType::None){}
public:
	bool ParseFrom(IStream& stream);
public:
	PackageCoderType Type;
	MemoryByteData Key;
};

struct PackageHeader
{
	PackageHeader();
	~PackageHeader();

	bool ParseFrom(IStream& stream);
public:
	uint Version;
	PackageFlags Flag;	//flags to control read
	uint FileListOffset;

	//Coder
	List<PackageCoderInfo*> Coders;

	MemoryByteData UserData;
public:
	const static uint32 Signature='KAPM';	//Little endian, I mean 'MPAK'
	const static uint32 CurrentVersion=1;
};


MEDUSA_END;