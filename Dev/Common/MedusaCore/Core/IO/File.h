#pragma once

#include "Core/IO/FileDefines.h"

#include "Core/IO/FileInfo.h"
#include "Core/Memory/Memory.h"
#include "Core/IO/Stream/FileStream.h"

MEDUSA_BEGIN;

class File
{
public:
	File(void);
	~File(void);

	static bool Exists(StringRef filePath,int permission=0);
	static bool Delete(StringRef filePath);
	static bool GetFileMode(StringRef filePath,FileMode& outFileMode);

	static bool Copy(StringRef srcFilePath,StringRef destFilePath);
	static bool Move(StringRef srcFilePath,StringRef destFilePath);
	static bool Rename(StringRef oldName,StringRef newName);



	static bool ReadAllTextTo(StringRef filePath,HeapString& outString);
	static bool WriteAllTextTo(StringRef filePath,StringRef str);

	static bool ReadAllLines(StringRef filePath,List<HeapString>& outLines,size_t maxCount=1024,bool isTrim=true,bool ignoreEmptyLine=true);

	static MemoryByteData ReadAllData(StringRef filePath);
	static bool WriteAllDataTo(MemoryByteData data,StringRef filePath);

	static MemoryByteData ReadAllDataPriority(StringRef firstPath,StringRef secondPath);

	static void OpenTextReader(StringRef filePath);
};

MEDUSA_END;