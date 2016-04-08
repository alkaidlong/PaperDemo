#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/FuckyString.pb.h"
#include "Core/Collection/Dictionary.h"
MEDUSA_BEGIN;

class FuckyStringNode
{
	

public:
	FuckyStringNode();
	~FuckyStringNode();
public:
	bool Load(const CoreProto::FuckyStringNode& item);
	bool IsFucky() const { return mIsFucky; }
	const Dictionary<wchar_t,FuckyStringNode*>* GetChildsPtr()const { return mChilds; }

private:
	wchar_t mChar;
	bool mIsFucky;
	Dictionary<wchar_t,FuckyStringNode*>* mChilds;
};

MEDUSA_END;
