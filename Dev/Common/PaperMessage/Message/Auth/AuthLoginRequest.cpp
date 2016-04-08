
#include "Message/Auth/AuthLoginRequest.h"
#include "Message/Player.h"
#include "Proto/Server/Common/MessageErrorCode.pb.h"
#include "Config/ServerGameConfig.h"



AuthLoginRequest::~AuthLoginRequest(void)
{
}


void AuthLoginRequest::Initialize(StringRef user,const StringRef& sessionId/*=StringRef::Empty*/)
{
	uint platformId=ServerGameConfig::Instance().PlatformID();
#ifdef MEDUSA_WINDOWS
	platformId=ServerProto::Auth::PlatformDev;
#endif
	mRequest.set_selectedplatform((ServerProto::Auth::ThirdPlatform)platformId);
	mRequest.set_user(user.c_str());
	mRequest.set_sessionid(sessionId.c_str());
}

void AuthLoginRequest::Mock()
{
	mResponse.set_errorcode(ServerProto::Ok);
	mResponse.set_errordetail(ServerProto::Auth::AuthLoginResponse_ErrorDetailCode_Ok);

	mResponse.mutable_token()->set_token("nimaaaaaaaaaa");
	mResponse.mutable_token()->set_playerid(12345);
}


void AuthLoginRequest::BeforeEnd()
{
	if(IsResultOk())
	{
		const ServerProto::LoginToken& loginToken = mResponse.token();
		mPlayer->SetLoginToken(loginToken);
	}

	IMessage::BeforeEnd();
}

IMPLEMENT_REGISTER_REQUEST(AuthLoginRequest,IMessage,AuthLoginResponse);
