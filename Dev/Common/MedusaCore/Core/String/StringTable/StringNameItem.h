#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Core/Proto/Client/StringTable.pb.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class StringNameItem
{
public:
	StringNameItem();
	StringNameItem(size_t order,const StringRef& filePath);

	~StringNameItem();
public:

	const StringOrderItem* GetOrderItem(size_t order)const;
	bool ContainsOrderItem(size_t order)const;

	bool Load(const CoreProto::StringNameItem& item);
	bool Save(CoreProto::StringNameItem* item)const;
	const List<StringRef>& GetItems()const{return mItems;}
private:
	HeapString mName;
	StringOrderItem* mFirstOrderItem;
	Dictionary<size_t,StringOrderItem*>* mOrderItems;
	List<StringRef> mItems;
};

MEDUSA_END;
