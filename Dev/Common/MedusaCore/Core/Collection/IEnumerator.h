#pragma once

#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

template<typename T>
struct IEnumerator
{

public:
	virtual ~IEnumerator(){}

	virtual T Current()=0;

	virtual bool MoveNext()=0;
	virtual void Reset()=0;
};


MEDUSA_END;