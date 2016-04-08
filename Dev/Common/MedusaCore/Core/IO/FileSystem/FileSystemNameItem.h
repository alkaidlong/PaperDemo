#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/Proto/Client/FileSystem.pb.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.h"

MEDUSA_BEGIN;

class FileSystemNameItem
{
public:
	FileSystemNameItem();
	FileSystemNameItem(StringRef name);

	~FileSystemNameItem();
public:
	StringRef GetName() const { return mName; }

	FileSystemOrderItem* GetOrderItem(size_t order)const;
	bool ContainsOrderItem(size_t order)const;
	bool RemoveOrderItem(size_t order);

	bool AddOrderItem(FileSystemOrderItem* orderItem);


	bool Initialize(const CoreProto::FileSystemNameItem& item);

	Dictionary<size_t,FileSystemOrderItem*>* GetOrderItems() const { return mOrderItems; }
	size_t GetCount()const;

	bool IsEmpty()const{return GetCount()==0;}
private:
	HeapString mName;
	FileSystemOrderItem* mFirstOrderItem;
	Pattern::LazyStrongPtr<Dictionary<size_t,FileSystemOrderItem*> > mOrderItems;
};

MEDUSA_END;
