#pragma once
#include "Message/BaseRequestGameMessage.h"
#include "Proto/Server/Auth/AuthLoginRequest.pb.h"
#include "Proto/Server/Auth/AuthLoginResponse.pb.h"

class AuthLoginRequest: public BaseRequestGameMessage<ServerProto::Auth::AuthLoginRequest,ServerProto::Auth::AuthLoginResponse>
{
	DECLARE_REGISTER_REQUEST(AuthLoginRequest);
public:
	AuthLoginRequest():BaseRequestGameMessage<ServerProto::Auth::AuthLoginRequest,ServerProto::Auth::AuthLoginResponse>(){}
	~AuthLoginRequest(void);

	void Initialize(StringRef user,const StringRef& sessionId=StringRef::Empty);

	virtual void Mock();

	virtual void BeforeEnd();

};

