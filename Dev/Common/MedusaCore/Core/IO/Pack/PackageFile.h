#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

struct PackageFile
{
	PackageFile();
	~PackageFile();

	bool ParseFrom(IStream& stream);

};


MEDUSA_END;