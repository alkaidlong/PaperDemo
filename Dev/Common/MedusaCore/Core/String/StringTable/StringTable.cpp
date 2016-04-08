#include "MedusaCorePreCompiled.h"
#include "Core/String/StringTable/StringTable.h"
#include "Core/Log/Log.h"
#include "Core/Proto/Proto.h"
#include "Core/String/StringTable/StringNameItem.h"
#include "Core/String/StringTable/StringOrderItem.h"
#include "Core/String/StringParser.h"
#include "Core/Utility/HashUtility.h"
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;

StringTable::~StringTable()
{
	Unload();
}

bool StringTable::Initialize()
{
	MemoryByteData data=FileSystem::Instance().ReadAllData("StringTable.bin");
	return LoadFromData(data);
}



bool StringTable::LoadFromData( MemoryByteData data )
{
	Unload();
	CoreProto::StringTable config;
	Proto::ParseFrom(config,data);

	FOR_EACH_COLLECTION_STL(j,config.nameitems())
	{
		const CoreProto::StringNameItem& item=*j;
		StringNameItem* nameItem=new StringNameItem();
		nameItem->Load(item);
#ifdef MEDUSA_DEBUG
		int hashCode=HashUtility::HashString(item.name().c_str());
		if (mNameItemMap.ContainsOtherKey(StringRef(item.name().c_str()),hashCode))
		{
			Log::AssertFailedFormat("Duplicate string table item name:%s",item.name().c_str());
		}
#endif
		mNameItemMap.Add(HeapString(item.name().c_str()),nameItem);
	}
	return true;
}

void StringTable::Unload()
{
	SAFE_DELETE_DICTIONARY_VALUE(mNameItemMap);
}


StringRef StringTable::GetString(const FileId& fileId )const
{
	StringNameItem* nameItem=mNameItemMap.TryGetValueWithFailed(fileId.Name,NULL);
	Log::AssertNotNullFormat(nameItem,"Cannot find string:%s",fileId.Name.c_str());
	const StringOrderItem* orderItem=nameItem->GetOrderItem(fileId.Order);
	Log::AssertNotNullFormat(nameItem,"Cannot find string:%s order:%d",fileId.Name.c_str(),fileId.Order);
	return orderItem->GetValue();
}


bool StringTable::Contains( const FileId& fileId ) const
{
	StringNameItem* nameItem=mNameItemMap.TryGetValueWithFailed(fileId.Name,NULL);
	RETURN_FALSE_IF_NULL(nameItem);
	return nameItem->ContainsOrderItem(fileId.Order);
}


HeapString StringTable::GetStringFormat( FileId fileId, ... )const
{
#ifdef MEDUSA_DEBUG
	Log::Assert(fileId.Name.EndWith("Format"),"key should ends with Format");
#endif // MEDUSA_DEBUG

	va_list args;
	va_start(args, fileId);

	StringRef format=GetString(fileId);
	return StringParser::FormatV(format.c_str(),args);
}

HeapString StringTable::GetStringFormatV( FileId fileId, va_list args ) const
{
#ifdef MEDUSA_DEBUG
	Log::Assert(fileId.Name.EndWith("Format"),"key should ends with Format");
#endif // MEDUSA_DEBUG

	StringRef format=GetString(fileId);
	return StringParser::FormatV(format.c_str(),args);
}

const List<StringRef>* StringTable::GetAllStrings( StringRef name ) const
{
	StringNameItem* nameItem=mNameItemMap.TryGetValueWithFailed(name,NULL);
	RETURN_NULL_IF_NULL(nameItem);
	return &(nameItem->GetItems());
}


MEDUSA_END;
