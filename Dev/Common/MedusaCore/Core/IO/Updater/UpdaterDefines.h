#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

//clientV < updatingV <= serverV
enum class ResourceCheckingResult
{
	NetworkError,	//network is unavailable now
	ServerConfigError,	//failed to get Server.bin
	ServerUnavailable,	//server status is not ok
	ClientUncompatiable,	//server min version > client version
	CientAlreadyNewest,		//server max version <= client version
	ClientNeedNewUpdating,	//updating verion < server max version
	ClientNeedContinueUpdating,	//updating version < server max version
};


MEDUSA_END;
