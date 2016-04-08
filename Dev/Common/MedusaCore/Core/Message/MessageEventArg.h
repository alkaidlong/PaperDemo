#pragma once
#include "MedusaCorePreCompiled.h"

#include "Core/Message/IMessage.h"

MEDUSA_BEGIN;

class MessageEventArg:public IEventArg
{
public:
	MessageEventArg(IMessage* message);
	virtual ~MessageEventArg(void);
	MessageEventArg(const MessageEventArg& e);
public:
	IMessage* GetMessage() const { return mMessage; }
	void SetMessage(IMessage* val) { mMessage = val; }

	bool IsResultOk()const{return mMessage->IsResultOk();}

	template<typename T>
	T GetCustomError()const{return (T)mMessage->GetCustomError();}

	int GetServerError()const{return mMessage->GetServerError();}

	template<typename T>
	T* GetMessage() const { return (T*)mMessage; }

private:
	IMessage* mMessage;
};


MEDUSA_END;
