#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Collection/Dictionary.h"
#include "Core/IO/FileId.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/ILoadable.h"

MEDUSA_BEGIN;

class StringTable:public Pattern::Singleton<StringTable>,public Pattern::ILoadable
{
	friend class Pattern::Singleton<StringTable>;
private:
	StringTable(){}
	~StringTable();
public:
	bool Initialize();
	virtual bool LoadFromData(MemoryByteData data);
	virtual void Unload();

public:
	bool Contains(const FileId& fileId)const;
	StringRef GetString(const FileId& fileId)const;
	const List<StringRef>* GetAllStrings(StringRef name)const;

	HeapString GetStringFormat(FileId fileId, ... )const;
	HeapString GetStringFormatV(FileId fileId, va_list args )const;

private:
	Dictionary<HeapString,StringNameItem*> mNameItemMap;
};
MEDUSA_END;
