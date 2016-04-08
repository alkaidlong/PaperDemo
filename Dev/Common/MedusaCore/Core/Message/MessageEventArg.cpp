#include "MedusaCorePreCompiled.h"
#include "Core/Message/MessageEventArg.h"
MEDUSA_BEGIN;

MessageEventArg::MessageEventArg( IMessage* message ) :mMessage(message)
{
	SAFE_RETAIN(mMessage);
}

MessageEventArg::MessageEventArg( const MessageEventArg& e )
{
	mMessage=e.mMessage;
	SAFE_RETAIN(mMessage);
}

MessageEventArg::~MessageEventArg(void)
{
	SAFE_RELEASE(mMessage);
}

MEDUSA_END;
