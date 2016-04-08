#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;


enum class BusinessPlatformLoginState
{
    None=0,/**< 未登录		*/
    Guest,/**< 游客账号登陆	*/
	Normal,/**< 普通账号登陆	*/

};

typedef Pattern::Delegate<void ( IBusinessPlatform*,BusinessPlatformLoginEventArg&)> BusinessPlatformLoginDelegate;
typedef Pattern::Delegate<void ( IBusinessPlatform*,BusinessPlatformPayEventArg&)> BusinessPlatformPayDelegate;



MEDUSA_END;