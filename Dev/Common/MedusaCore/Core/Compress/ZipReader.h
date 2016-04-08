#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/Dictionary.h"

#ifdef MEDUSA_ZIP
MEDUSA_BEGIN;


class ZipReader
{
	struct ZipFileInfo
	{
		unz_file_pos Pos;
		uLong UncompressedSize;
		bool operator==(const ZipFileInfo& info)const{return Pos.num_of_file==info.Pos.num_of_file&&Pos.pos_in_zip_directory==info.Pos.pos_in_zip_directory&&UncompressedSize==info.UncompressedSize;}
	};
public:
	ZipReader();
	~ZipReader();

	bool Open(StringRef path);
	void Close();

	bool IsValid()const{return mZipFile!=NULL;}
	bool Exists(StringRef fileName) const;
	MemoryByteData ReadAllData(StringRef fileName)const;
	
private:
	unzFile mZipFile;
	Dictionary<HeapString,ZipFileInfo>  mFileDict;
};


MEDUSA_END;
#endif