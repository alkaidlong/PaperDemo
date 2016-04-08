
#include "Message/Battle/MissionResetRequest.h"
#include "Message/Player.h"
#include "Config/PVEConfig.h"
#include "Config/MissionConfig.h"
#include "Config/ServerGameConfig.h"
#include "Config/PaperConfig.h"

MissionResetRequest::~MissionResetRequest(void)
{
}

void MissionResetRequest::Initialize(uint missionItemID)
{
	mRequest.set_missionitemid(missionItemID);
}

void MissionResetRequest::BeforeEnd()
{
	if (IsResultOk())
	{
		if (GetCustomError()==ServerProto::Logic::MissionResetResponse_ErrorDetailCode_Ok)
		{
			//ServerProto::Logic::ServerPlayer* serverPlayer=mPlayer->GetServerPlayerMutable();
			int missionId=mPlayer->GetCurSelectMissionID();
			const ServerProto::Logic::Mission* missionServer =  mPlayer->GetServerMission(missionId);
			mPlayer->CostDiamond(ServerGameConfig::Instance().GetMissonResetCostDiamond(missionServer->resettimestoday()),PaperCostDiamondReason::BuyPvePower); 
			if (mResponse.has_curmissionstatus())
			{
				mPlayer->UpdateMission(mResponse.curmissionstatus());
			}
		}
	}
     
	IMessage::BeforeEnd();
}

void MissionResetRequest::Mock()
{
	
}



IMPLEMENT_REGISTER_REQUEST(MissionResetRequest,IMessage,MissionResetResponse);
