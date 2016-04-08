#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LINUX

#include "Core/System/Environment.h"
MEDUSA_BEGIN;



HeapString Environment::GetSystemInfoByName ( const StringRef& inName )const
{
	return HeapString::Empty;
}

int Environment::GetUIScreenWidth() const
{
	return 0;
}


bool Environment::IsJailBreakHelper() const
{
	return false;
}

HeapString Environment::GetMacAddress()
{
	return HeapString::Empty;
}

bool Environment::IsNetworkAvailable()
{
	return true;
}



MEDUSA_END;

#endif
