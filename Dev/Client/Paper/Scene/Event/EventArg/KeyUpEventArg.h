#pragma once
#include "Core/Event/EventArg/IEventArg.h"




USING_MEDUSA;
class KeyUpEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI(KeyUpEventArg);
public:
	KeyUpEventArg(uint key,uint status):mKey(key),mStatus(status){}
	virtual ~KeyUpEventArg(void){}
	uint GetKey() const { return mKey; }
	void SetKey(uint val) { mKey = val; }

	uint GetStatus() const { return mStatus; }
	void SetStatus(uint val) { mStatus = val; }
protected:
	uint mKey;
	uint mStatus;
};


