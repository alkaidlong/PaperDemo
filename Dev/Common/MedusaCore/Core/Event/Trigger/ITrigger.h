#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

ENUM_BEGIN(TriggerState)
{
	None,
	Open,
	Closed,
}ENUM_END;


class ITrigger
{
public:
	ITrigger():mState(TriggerState::None){}
	virtual ~ITrigger(void){}
	virtual bool Initialize(){return true;}

	bool IsDead()const{return mState==TriggerState::Closed;}


	virtual void Open()=0;
	virtual void Close()=0;

	virtual void Update(float dt)=0;

protected:
    TriggerState::TriggerState_t mState;
};


MEDUSA_END;