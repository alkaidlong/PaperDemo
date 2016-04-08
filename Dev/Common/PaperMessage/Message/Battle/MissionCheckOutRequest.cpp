
#include "Message/Battle/MissionCheckOutRequest.h"
#include "Message/Player.h"
#include "Config/PVEConfig.h"
#include "Config/MissionConfig.h"


MissionCheckOutRequest::~MissionCheckOutRequest(void)
{
}


void MissionCheckOutRequest::Initialize(uint missionId,bool isPassed,const List<uint64>& survialHeroes)
{
	mRequest.set_missionitemid(missionId);
	mRequest.set_ispassed(isPassed);
	FOR_EACH_COLLECTION(i,survialHeroes)
	{
		mRequest.add_survivalheros(*i);
	}
}

void MissionCheckOutRequest::BeforeEnd()
{
	if (IsResultOk())
	{
		if (GetCustomError()==ServerProto::Logic::MissionCheckOutResponse_ErrorDetailCode_Ok)
		{
			if (mResponse.has_curplayerdata())
			{
				mPlayer->UpdateServerPlayer(mResponse.curplayerdata());
			}

			FOR_EACH_COLLECTION_STL(i,mResponse.missionawards())
			{
				mPlayer->AddAward(*i,PaperAnalyticsAwardReason::PVEMission);
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

			const ServerProto::Config::PVEConfigItem* pveConfig = PVEConfig::Instance().GetChapterItemByMissionId(mRequest.missionitemid());

			//const ServerProto::Logic::Chapter* chapterServer = mPlayer->GetServerChapter(pveConfig->id());
			ServerProto::Logic::Chapter chapterIn;
			chapterIn.set_chapteritemid(pveConfig->id());
			chapterIn.set_curmission(mRequest.missionitemid());
			mPlayer->UpdateChapter(chapterIn);

			StringParser::ResultStringType idStr=StringParser::ToString(mRequest.missionitemid());

			if (mRequest.ispassed())
			{
				Analytics::CompeleteMission(idStr);
			}
			else
			{
				Analytics::FailedMission(idStr,"Default");
			}

		}
	}

	IMessage::BeforeEnd();
}

void MissionCheckOutRequest::Mock()
{
	mResponse.set_errorcode(ServerProto::Ok);
	mResponse.set_errordetail(ServerProto::Logic::MissionCheckOutResponse_ErrorDetailCode_Ok);


	//award->mutable_awardequip()->
	//if (mRequest.passroadnum()!=0)
	{
		// 		uint64 heroId = mRequest.survivalheros(0);
		// 		ServerProto::Logic::Hero* hero = mResponse.mutable_deltaplayerdata()->add_heroes();
		// 		hero->set_id(heroId);
		// 		hero->set_heroitemid(heroId);
		// 		hero->set_level(1);
	}
}



IMPLEMENT_REGISTER_REQUEST(MissionCheckOutRequest,IMessage,MissionCheckOutResponse);
