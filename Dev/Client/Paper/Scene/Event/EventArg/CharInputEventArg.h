#pragma once
#include "Core/Event/EventArg/IEventArg.h"

USING_MEDUSA;



class CharInputEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI(CharInputEventArg);

public:
	CharInputEventArg(uint key,uint status):mKey(key),mStatus(status){}
	virtual ~CharInputEventArg(void){}
	uint GetKey() const { return mKey; }
	void SetKey(uint val) { mKey = val; }

	uint GetStatus() const { return mStatus; }
	void SetStatus(uint val) { mStatus = val; }
protected:
	uint mKey;
	uint mStatus;
};


