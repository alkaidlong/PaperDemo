#pragma once
#include "MedusaCorePreDeclares.h"
#include "PackageHeader.h"
#include "PackageFile.h"
#include "Core/IO/FileDefines.h"

MEDUSA_BEGIN;


class Package
{
public:
	Package();
	~Package();
public:
	bool OpenFromFile(const StringRef& file,FileOpenMode openMode=FileOpenMode::ReadOnly);
	bool OpenFromStream(IStream& stream);

	bool Close();
	bool Flush();
	bool IsOpen()const;
	bool IsDirty()const;

	bool CanRead()const;
	bool CanWrite()const;
public:
	StringRef GetPackageName()const;
	bool Contains(const StringRef& file)const;
	uint GetFileCount()const;

public:
	IStream* OpenFile(const StringRef& file,FileOpenMode openMode=FileOpenMode::ReadOnly);
	PackageFile* GetFileInfo(const StringRef& file);
	bool Add(PackageFile* newFile);
	bool Remove(const StringRef& file);
	bool Defrag();

public:
	bool Merge(const Package& otherPack);
private:
	PackageHeader mHeader;
	IStream* mStream;

};


MEDUSA_END;