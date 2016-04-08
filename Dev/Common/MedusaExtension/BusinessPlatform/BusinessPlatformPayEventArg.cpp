#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatformPayEventArg.h"

MEDUSA_BEGIN;


BusinessPlatformPayEventArg::BusinessPlatformPayEventArg( ):ErrorCode(PayErrorCode::Success),Price(0),OriginalPrice(0),Count(0)
{

}

BusinessPlatformPayEventArg::~BusinessPlatformPayEventArg( void )
{

}

MEDUSA_END;
