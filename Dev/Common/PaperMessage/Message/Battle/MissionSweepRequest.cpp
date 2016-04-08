
#include "Message/Battle/MissionSweepRequest.h"
#include "Message/Player.h"
#include "Config/PVEConfig.h"
#include "Config/MissionConfig.h"
#include "Config/ServerGameConfig.h"
#include "Config/PaperConfig.h"

MissionSweepRequest::~MissionSweepRequest(void)
{
}

void MissionSweepRequest::Initialize(uint missionItemID,ServerProto::Logic::MissionSweepRequest_SweepType sweepType)
{
	mRequest.set_missionitemid(missionItemID);
	mRequest.set_type(sweepType);
}

void MissionSweepRequest::BeforeEnd()
{
	if (IsResultOk())
	{
		if (GetCustomError()==ServerProto::Logic::MissionSweepResponse_ErrorDetailCode_Ok)
		{
			int costDiamond=0;
			if (mRequest.type()==ServerProto::Logic::MissionSweepRequest_SweepType::MissionSweepRequest_SweepType_OneTime)
			{
				costDiamond=((int)mRequest.type())*ServerGameConfig::Instance().ExtraOneSweepCostDiamonds();

			}
			else
			{
				costDiamond=((int)ServerGameConfig::Instance().MaxMissionSweep())*ServerGameConfig::Instance().ExtraOneSweepCostDiamonds();
			}
			mPlayer->CostDiamond(costDiamond);

			if (mResponse.has_curplayerdata())
			{
				mPlayer->UpdateServerPlayer(mResponse.curplayerdata());
			}

			FOR_EACH_COLLECTION_STL(i,mResponse.missionawards())
			{
				mPlayer->AddAward(*i,PaperAnalyticsAwardReason::PVEMissionSweep);
			}

			if (mResponse.has_curmissionstatus())
			{
				mPlayer->UpdateMission(mResponse.curmissionstatus());
			}
			if (mResponse.has_unlockmissionitemid())
			{
				mPlayer->AddServerMission(mResponse.unlockmissionitemid());
			}
			if (mResponse.has_unlockchapteritemid())
			{
				mPlayer->AddServerChapter(mResponse.unlockchapteritemid());
			}
		}
	}
     
	IMessage::BeforeEnd();
}

void MissionSweepRequest::Mock()
{
	
}



IMPLEMENT_REGISTER_REQUEST(MissionSweepRequest,IMessage,MissionSweepResponse);
