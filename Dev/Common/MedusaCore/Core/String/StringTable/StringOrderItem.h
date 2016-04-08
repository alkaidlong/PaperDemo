#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/StringTable.pb.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class StringOrderItem
{
public:
	StringOrderItem():mOrder(0){}
	StringOrderItem(size_t order,const StringRef& val):mOrder(order),mValue(val){}
	~StringOrderItem();
public:
	size_t GetOrder() const { return mOrder; }
	StringRef GetValue() const { return mValue; }

	bool Load(const CoreProto::StringOrderItem& item);
	bool Save(CoreProto::StringOrderItem* item)const;

private:
	size_t mOrder;
	HeapString mValue;
};
MEDUSA_END;
