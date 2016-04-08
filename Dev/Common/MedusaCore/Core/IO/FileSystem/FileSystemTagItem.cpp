#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystemTagItem.h"
#include "Core/IO/FileSystem/FileSystemNameItem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

FileSystemTagItem::FileSystemTagItem( void )
{
	mScore=0;
}


FileSystemTagItem::~FileSystemTagItem(void)
{
	SAFE_DELETE_DICTIONARY_VALUE(mNameItems);

}

FileSystemNameItem* FileSystemTagItem::GetNameItem( StringRef name ) const
{
	return mNameItems.TryGetValueWithFailed(name,NULL);
}


FileSystemOrderItem* FileSystemTagItem::GetOrderItem( const FileId& fileId ) const
{
	FileSystemNameItem* nameItem=mNameItems.TryGetValueWithFailed(fileId.Name,NULL);
	RETURN_NULL_IF_NULL(nameItem);
	return nameItem->GetOrderItem(fileId.Order);
}


bool FileSystemTagItem::ContainsOrderItem( const FileId& fileId ) const
{
	FileSystemNameItem* nameItem=mNameItems.TryGetValueWithFailed(fileId.Name,NULL);
	RETURN_FALSE_IF_NULL(nameItem);
	return nameItem->ContainsOrderItem(fileId.Order);
}


bool FileSystemTagItem::ContainsNameItem( StringRef name ) const
{
	return mNameItems.ContainsKey(name);
}

bool FileSystemTagItem::Initialize( const  CoreProto::FileSystemTagItem& item )
{
	mTag.SetTag(item.tag());

	FOR_EACH_COLLECTION_STL(i,item.nameitems())
	{
		const CoreProto::FileSystemNameItem& nameItem=*i;

		StringRef name=nameItem.name();
		FileSystemNameItem* fsNameItem=mNameItems.TryGetValueWithFailed(name,NULL);
		if (fsNameItem==NULL)
		{
			fsNameItem=new FileSystemNameItem();
			fsNameItem->Initialize(nameItem);
			mNameItems.Add(name,fsNameItem);
		}
		else
		{
			Log::AssertFailed("duplicate register");
		}
	}

	return true;
}

bool FileSystemTagItem::AddNameItem( FileSystemNameItem* nameItem )
{
	return mNameItems.TryAdd(nameItem->GetName(),nameItem);
}


int FileSystemTagItem::UpdateDiffScore( const EnvironmentTag& tag )
{
	mScore=mTag.GetDiffScore(tag);
	return mScore;
}



MEDUSA_END;
