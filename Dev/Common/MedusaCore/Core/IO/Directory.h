#pragma once

#include "Core/IO/FileDefines.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/List.h"



MEDUSA_BEGIN;

class Directory
{
public:
	Directory(void);
	~Directory(void);

	static bool CreateDir(const StringRef& dir);
	static bool CreateDirRecursively(const StringRef& dir);

	static bool RemoveDir(const StringRef& dir);
	static bool RemoveDirRecursively(const StringRef& dir);


	static bool CreateDirectoryForFile(const StringRef& filePath);
	static bool Exists(const StringRef& dir);

	static void Copy(const StringRef& fromDir,const StringRef& toDir,bool isRecursively=true);
	static void Move(const StringRef& fromDir,const StringRef& toDir,bool isRecursively=true);

	static void GetFiles(const StringRef& dir,List<HeapString>& outFiles,bool isRecursively=false,const StringRef& serarchPattern=StringRef::Empty);
	static void GetDirectories(const StringRef& dir,List<HeapString>& outDirectories,bool isRecursively=true,const StringRef& serarchPattern=StringRef::Empty);
private:
	static bool IsFitSearchPattern(const StringRef& fileName,const StringRef& serarchPattern);
};

MEDUSA_END;