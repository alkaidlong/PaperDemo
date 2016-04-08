#include "MedusaCorePreCompiled.h"
#include "Package.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/ProxyStream.h"

MEDUSA_BEGIN;


Package::Package():mStream(NULL)
{

}

Package::~Package()
{
	SAFE_DELETE(mStream);
}

bool Package::OpenFromFile(const StringRef& file,FileOpenMode openMode/*=FileOpenMode::ReadOnly*/)
{
	return true;
}

bool Package::OpenFromStream(IStream& stream)
{
	return true;
}

bool Package::Close()
{
	return true;
}

bool Package::Flush()
{
	return true;
}


bool Package::IsDirty() const
{
	return true;
}


bool Package::IsOpen() const
{
	return mStream!=NULL&&mStream->IsOpen();
}

bool Package::CanRead() const
{
	return mStream->CanRead();
}

bool Package::CanWrite() const
{
	return mStream->CanWrite();
}

Medusa::StringRef Package::GetPackageName() const
{
	return StringRef::Empty;
}

bool Package::Contains(const StringRef& file) const
{
	return true;
}

uint Package::GetFileCount() const
{
	return 0;
}

IStream* Package::OpenFile(const StringRef& file,FileOpenMode openMode/*=FileOpenMode::ReadOnly*/)
{
	return NULL;
}

PackageFile* Package::GetFileInfo(const StringRef& file)
{
	return NULL;
}

bool Package::Add(PackageFile* newFile)
{
	return true;
}

bool Package::Remove(const StringRef& file)
{
	return true;
}

bool Package::Defrag()
{
	return true;
}

bool Package::Merge(const Package& otherPack)
{
	return true;
}

MEDUSA_END;