#include "MedusaCorePreCompiled.h"
#include "Core/String/StringTable/StringOrderItem.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;

StringOrderItem::~StringOrderItem(void)
{
}

bool StringOrderItem::Load( const CoreProto::StringOrderItem& item )
{
	mOrder=item.order();
	mValue=item.value();

	return true;
}

bool StringOrderItem::Save( CoreProto::StringOrderItem* item ) const
{
	item->set_order(static_cast<uint32>(mOrder));
	item->set_value(mValue.c_str());
	
	return true;
}
MEDUSA_END;
