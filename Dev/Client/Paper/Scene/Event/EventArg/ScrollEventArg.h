#pragma once
#include "Core/Event/EventArg/IEventArg.h"

USING_MEDUSA;



class ScrollEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI(ScrollEventArg);

public:
	ScrollEventArg(int pos,uint status):mScrollPos(pos),mStatus(status){}
	virtual ~ScrollEventArg(void){}

	int GetScrollPos() const { return mScrollPos; }
	void SetScrollPos(int val) { mScrollPos = val; }

	uint GetStatus() const { return mStatus; }
	void SetStatus(uint val) { mStatus = val; }
protected:
	int mScrollPos;
	
	uint mStatus;
};


