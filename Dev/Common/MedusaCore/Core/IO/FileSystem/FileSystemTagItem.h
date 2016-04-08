#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileId.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Proto/Client/FileSystem.pb.h"
#include "Core/System/EnvironmentTag.h"

MEDUSA_BEGIN;

class FileSystemTagItem
{
public:
	FileSystemTagItem(void);
	FileSystemTagItem(const EnvironmentTag& tag):mTag(tag){}

	~FileSystemTagItem(void);
	bool operator<(const FileSystemTagItem& tagItem)const{return mScore<tagItem.mScore;}
	bool Initialize(const CoreProto::FileSystemTagItem& item);
	const Dictionary<HeapString,FileSystemNameItem*>& GetNameItems() const { return mNameItems; }

	FileSystemNameItem* GetNameItem(StringRef name)const;
	bool AddNameItem(FileSystemNameItem* nameItem);
	bool ContainsNameItem(StringRef name)const;

	FileSystemOrderItem* GetOrderItem(const FileId& fileId)const;
	bool ContainsOrderItem(const FileId& fileId)const;

	int UpdateDiffScore(const EnvironmentTag& tag);

	bool IsEmpty()const{return mNameItems.IsEmpty();}
	const Medusa::EnvironmentTag& GetTag() const { return mTag; }

private:

private:
	Dictionary<HeapString,FileSystemNameItem*> mNameItems;
	EnvironmentTag mTag;

	/*
	Int.MinValue: not match
	-1:	super match in anyway
	0:	perfect match
	>0:	diff
	*/
	int mScore;	
};

MEDUSA_END;
