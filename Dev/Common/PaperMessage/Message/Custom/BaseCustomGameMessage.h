#pragma once
#include "Core/Message/BaseCustomMessage.h"
#include "Core/Pattern/EnumPattern.h"
#include "Proto/Server/Common/LoginToken.pb.h"

USING_MEDUSA;

STRONG_ENUM_3(GameMessageLogicError,Success,AuthFaied,ServiceUnavailable);

class BaseCustomGameMessage:public BaseCustomMessage
{
public:
	BaseCustomGameMessage();
	~BaseCustomGameMessage(void);
	virtual void FillLoginToken(const ServerProto::LoginToken& token){}
	virtual int GetCustomError()const;

protected:
	virtual int GetFurtherCustomError()const;
};

