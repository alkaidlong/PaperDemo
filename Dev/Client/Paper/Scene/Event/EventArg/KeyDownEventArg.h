#pragma once
#include "Core/Event/EventArg/IEventArg.h"


USING_MEDUSA;


class KeyDownEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI(KeyDownEventArg);
public:
	KeyDownEventArg(uint key,uint status):mKey(key),mStatus(status){}
	virtual ~KeyDownEventArg(void){}
	uint GetKey() const { return mKey; }
	void SetKey(uint val) { mKey = val; }

	uint GetStatus() const { return mStatus; }
	void SetStatus(uint val) { mStatus = val; }
protected:
	uint mKey;
	uint mStatus;
};


