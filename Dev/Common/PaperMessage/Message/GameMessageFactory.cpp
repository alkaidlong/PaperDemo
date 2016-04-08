#include "Message/GameMessageFactory.h"
#include "Config/PaperConfig.h"
#include "Message/Player.h"

void GameMessageFactory::SetTimeout( IMessage* message )
{
	message->SetTimeout(PaperConfig::Instance().MessageTimeout());
}

const ServerProto::LoginToken& GameMessageFactory::GetLoginToken()
{
	return mPlayer->GetLoginToken();
}


Player* GameMessageFactory::mPlayer=NULL;
