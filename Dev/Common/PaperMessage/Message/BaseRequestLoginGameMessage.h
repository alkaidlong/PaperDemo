#pragma once
#include "Message/BaseRequestGameMessage.h"
USING_MEDUSA;

template<typename TRequest,typename TResponse>
class BaseRequestLoginGameMessage:public BaseRequestGameMessage<TRequest,TResponse>
{
public:
	BaseRequestLoginGameMessage(){}
	virtual ~BaseRequestLoginGameMessage(void){}
	virtual void FillLoginToken(const ServerProto::LoginToken& token)
	{
		ServerProto::LoginToken* loginTokenData= this->mRequest.mutable_token();
		loginTokenData->CopyFrom(token);
	}
};
