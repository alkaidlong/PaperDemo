#pragma once
#include "Core/IO/FileDefines.h"
#include "Core/String/StackString.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class FileInfo
{
	MEDUSA_DECLARE_STATIC_CONSTRUCTOR();
public:
	FileInfo(StringRef filePath);
	~FileInfo(void);
public:
	FileType GetType() const { return mFileType; }
	StringRef GetExtension() const { return mFileExtension; }
	StringRef GetFullPath() const { return mFullPath; }
	StringRef GetFullName() const { return mFullName; }
	StringRef GetName() const { return mName; }

	StringRef GetDirectory() const { return mDirectoryPath; }

	bool IsFile() const { return mDirectoryPath.IsEmpty(); }
	bool IsImageFile()const;
	bool IsShaderFile()const;

	static StringRef GetExtension(StringRef file);
	static FileType GetType(StringRef filePath);
	bool operator<(const FileInfo& info)const{return mFullPath<info.mFullPath;}
	static bool IsImageFile(FileType fileType);

private:
	static FileType CheckFileType(StringRef fileExt);
	static void OnInitFileExtDict();

private:
	static Dictionary<StringRef,FileType> mFileExtDict;
	StackString<16> mFileExtension;
	HeapString mFullPath;
	HeapString mFullName;
	HeapString mName;


	HeapString mDirectoryPath;

	FileType mFileType;
};


MEDUSA_END;