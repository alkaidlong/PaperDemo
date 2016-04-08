
#include "MockMessageCenter.h"

#include "Config/PaperConfig.h"
#include "Core/Log/Log.h"
#include "Core/System/System.h"
#include "Message/GameMessageFactory.h"
#include "Core/Message/MessageDispatcher.h"
#include "Message/Custom/BaseCustomGameMessage.h"
#include "Core/Message/MessageEventArg.h"

#include "Message/Auth/AuthLoginRequest.h"
#include "Message/Logic/DumpPlayerDataRequest.h"
#include "Message/Logic/HireHeroRequest.h"
#include "Message/Logic/CreatePlayerRequest.h"
#include "Message/Logic/ChangeForceIndexRequest.h"
#include "Message/Battle/ChallengeMissionRequest.h"
#include "Message/Logic/ExchangeSoulToHeroRequest.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#include "Message/Logic/BuyItemRequest.h"
#include "Message/Battle/MissionCheckOutRequest.h"
#include "Message/Logic/ChangeAuraRequest.h"
#include "Message/Logic/ChangeEquipRequest.h"
#include "Message/Logic/UseItemRequest.h"
#include "Message/Logic/SellEquipRequest.h"
#include "Proto/Server/Common/MessageErrorCode.pb.h"
#include "Message/Logic/UpgradeEquipRequest.h"
#include "Message/Logic/HeroInheritRequest.h"

MockMessageCenter::MockMessageCenter(void)
{
	mIsUpdate = true;
}


MockMessageCenter::~MockMessageCenter(void)
{
}

void MockMessageCenter::Update( float dt )
{	
	
}


bool MockMessageCenter::ProcessConnectError(IMessage* message,MessageErrorReportSuppress errorReportSuppress)
{
	Log::LogInfo("Connect failed");

	if (!errorReportSuppress.HasFlag(MessageErrorReportSuppress::ConnectFail))
	{
		Log::LogError("Connect failed");
		return false;
	}
	return true;
}


bool MockMessageCenter::ProcessAuthError(IMessage* message,MessageErrorReportSuppress errorReportSuppress)
{
	Log::LogInfo("Auth failed");

	if (!errorReportSuppress.HasFlag(MessageErrorReportSuppress::AuthFailed))
	{
		if (!errorReportSuppress.HasFlag(MessageErrorReportSuppress::SwitchUI))
		{
			
		}
		Log::LogError("Auth failed");
		return false;
	}
	return true;
}


bool MockMessageCenter::ProcessFailedError(IMessage* message, MessageErrorReportSuppress errorReportSuppress )
{
	Log::LogInfo("Unknown failed");

	if (!errorReportSuppress.HasFlag(MessageErrorReportSuppress::ServerFailed))
	{
		Log::LogError("Server failed!");
		return false;
	}
	return true;
}

void MockMessageCenter::ShowActivityIndicator()
{
	Log::LogInfo("Message Sending...");

}

void MockMessageCenter::HideActivityIndicator()
{
	Log::LogInfo("Message Completed!");
}

void MockMessageCenter::UpdateCurrentScene()
{

}
