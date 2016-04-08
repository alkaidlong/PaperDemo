#pragma once
#include "Core/Collection/IEnumerator.h"

MEDUSA_BEGIN;

template<typename T>
class Enumerator
{
public:
	Enumerator(IEnumerator<T>* enumator):mEnumeartor(enumator){MEDUSA_ASSERT_NOT_NULL(mEnumeartor,"enumator should not be null!");}
	~Enumerator(){SAFE_DELETE(mEnumeartor);}
	T operator*(){return mEnumeartor->Current();}

	bool MoveNext(){return mEnumeartor->MoveNext();}
	void Reset(){return mEnumeartor->Reset();}

private:
	IEnumerator<T>* mEnumeartor;
};

MEDUSA_END;