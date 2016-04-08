#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystemNameItem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.inl"

MEDUSA_BEGIN;


FileSystemNameItem::FileSystemNameItem():mFirstOrderItem(NULL),mOrderItems(NULL)
{

}

FileSystemNameItem::FileSystemNameItem( StringRef name ):mName(name),mFirstOrderItem(NULL),mOrderItems(NULL)
{

}

FileSystemNameItem::~FileSystemNameItem(void)
{
	if (mOrderItems /*!=NULL*/)
	{
		SAFE_DELETE_DICTIONARY_VALUE(*mOrderItems);
	}
	else
	{
		SAFE_DELETE(mFirstOrderItem);
	}
}

bool FileSystemNameItem::Initialize( const CoreProto::FileSystemNameItem& item )
{
	mName=item.name();

	if (item.orderitems().size()==1)
	{
		mFirstOrderItem=new FileSystemOrderItem();
		mFirstOrderItem->Initialize(*item.orderitems().begin());
	}
	else
	{
		mOrderItems.Alloc();
		FOR_EACH_COLLECTION_STL(i,item.orderitems())
		{
			const CoreProto::FileSystemOrderItem& orderItem=*i;
			size_t order=orderItem.order();
			FileSystemOrderItem* nameOrderItem=mOrderItems->TryGetValueWithFailed(order,NULL);
			if (nameOrderItem==NULL)
			{
				nameOrderItem=new FileSystemOrderItem();
				nameOrderItem->Initialize(orderItem);
				mOrderItems->Add(order,nameOrderItem);

				if (order==0)
				{
					mFirstOrderItem=nameOrderItem;	//quick access
				}
			}
			else
			{
				Log::AssertFailed("duplicate register");
			}
		}

	}

	return true;
}

FileSystemOrderItem* FileSystemNameItem::GetOrderItem( size_t order ) const
{
	if (mFirstOrderItem!=NULL)
	{
		if (mFirstOrderItem->GetOrder()==order)
		{
			return mFirstOrderItem;
		}
	}

	if (mOrderItems /* !=NULL */ )
	{
		return mOrderItems->TryGetValueWithFailed(order,NULL);
	}

	return NULL;
}


bool FileSystemNameItem::RemoveOrderItem( size_t order )
{
	RETURN_FALSE_IF_NULL(mFirstOrderItem);
	FileSystemOrderItem* orderItem= mOrderItems->TryGetValueWithFailed(order,NULL);
	RETURN_FALSE_IF_NULL(orderItem);
	mOrderItems->RemoveKey(order);
	if (mFirstOrderItem==orderItem)
	{
		mFirstOrderItem=NULL;
	}

	SAFE_DELETE(orderItem);
	return true;
}

bool FileSystemNameItem::ContainsOrderItem( size_t order ) const
{
	return GetOrderItem(order)!=NULL;
}


size_t FileSystemNameItem::GetCount() const
{
	if (mOrderItems /*!=NULL*/)
	{
		return mOrderItems->GetCount();
	}

	if (mFirstOrderItem!=NULL)
	{
		return 1;
	}

	return 0;

}

bool FileSystemNameItem::AddOrderItem( FileSystemOrderItem* orderItem )
{
	size_t order=orderItem->GetOrder();
	if (ContainsOrderItem(order))
	{
		Log::LogErrorFormat("Duplicate add order item");
		return false;
	}

	if (mFirstOrderItem==NULL)
	{
		mFirstOrderItem=orderItem;
	}
	else
	{
		mOrderItems->Add(order,orderItem);
		if (order==0)
		{
			mFirstOrderItem=orderItem;	//quick access
		}
	}

	return true;
}

MEDUSA_END;
