#pragma once
#include "Core/Message/BaseRequestMessage.h"
#include "Proto/Server/Common/LoginToken.pb.h"
class Player;

USING_MEDUSA;

template<typename TRequest,typename TResponse>
class BaseRequestGameMessage:public BaseRequestMessage<TRequest,TResponse>
{
public:
	BaseRequestGameMessage():mPlayer(NULL){}
	virtual ~BaseRequestGameMessage(void){}
	virtual void FillLoginToken(const ServerProto::LoginToken& token){}

	void SetPlayer(Player* val) { mPlayer = val; }
	Player* GetPlayer() const { return mPlayer; }

protected:
	Player* mPlayer;
};
