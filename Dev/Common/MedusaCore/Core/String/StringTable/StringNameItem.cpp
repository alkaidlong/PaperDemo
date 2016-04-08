#include "MedusaCorePreCompiled.h"
#include "Core/String/StringTable/StringNameItem.h"
#include "Core/String/StringTable/StringOrderItem.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

StringNameItem::StringNameItem( size_t order,const StringRef& filePath )
{
	mFirstOrderItem=new StringOrderItem(order,filePath);
	mOrderItems=NULL;

}

StringNameItem::StringNameItem():mFirstOrderItem(NULL),mOrderItems(NULL)
{

}

StringNameItem::~StringNameItem(void)
{
	if (mOrderItems!=NULL)
	{
		SAFE_DELETE_DICTIONARY_VALUE(*mOrderItems);
		SAFE_DELETE(mOrderItems);
	}
	else
	{
		SAFE_DELETE(mFirstOrderItem);
	}
}

const StringOrderItem* StringNameItem::GetOrderItem( size_t order ) const
{
	if (mFirstOrderItem!=NULL)
	{
		if (mFirstOrderItem->GetOrder()==order)
		{
			return mFirstOrderItem;
		}
	}

	return mOrderItems->TryGetValueWithFailed(order,NULL);
}

bool StringNameItem::ContainsOrderItem( size_t order ) const
{
	return GetOrderItem(order)!=NULL;
}

bool StringNameItem::Load( const CoreProto::StringNameItem& item )
{
	mName=item.name();

	if (item.orderitems().size()==1)
	{
		mFirstOrderItem=new StringOrderItem();
		mFirstOrderItem->Load(*item.orderitems().begin());
		mItems.Add(mFirstOrderItem->GetValue());
	}
	else
	{
		mOrderItems=new Dictionary<size_t,StringOrderItem*>();
		FOR_EACH_COLLECTION_STL(i,item.orderitems())
		{
			const CoreProto::StringOrderItem& orderItem=*i;
			size_t order=orderItem.order();
			StringOrderItem* nameOrderItem=mOrderItems->TryGetValueWithFailed(order,NULL);
			if (nameOrderItem==NULL)
			{
				nameOrderItem=new StringOrderItem();
				nameOrderItem->Load(orderItem);
				mOrderItems->Add(order,nameOrderItem);
				mItems.Add(nameOrderItem->GetValue());
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

bool StringNameItem::Save( CoreProto::StringNameItem* item ) const
{
	item->set_name(mName.c_str());
	if (mOrderItems==NULL)
	{
		if (mFirstOrderItem!=NULL)
		{
			CoreProto::StringOrderItem* newOrderItem= item->add_orderitems();
			mFirstOrderItem->Save(newOrderItem);
		}
		
	}
	else
	{
		FOR_EACH_COLLECTION(i,*mOrderItems)
		{
			StringOrderItem* orderItem=(*i).Value;
			CoreProto::StringOrderItem* newOrderItem= item->add_orderitems();
			orderItem->Save(newOrderItem);
		}
	}

	return true;
}
MEDUSA_END;
