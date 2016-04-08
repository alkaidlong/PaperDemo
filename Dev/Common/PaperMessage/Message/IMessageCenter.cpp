
#include "Message/IMessageCenter.h"

#include "Config/PaperConfig.h"
#include "Config/ServerGameConfig.h"

#include "Core/Log/Log.h"
#include "Core/System/System.h"
#include "Message/GameMessageFactory.h"
#include "Core/Message/MessageDispatcher.h"
#include "Message/Custom/BaseCustomGameMessage.h"
#include "Core/Message/MessageEventArg.h"
#include "Core/Proto/Client/ServerList.pb.h"

#include "Message/Auth/AuthLoginRequest.h"
#include "Message/Logic/DumpPlayerDataRequest.h"
#include "Message/Logic/RefreshPlayerDataRequest.h"

#include "Message/Logic/HireHeroRequest.h"
#include "Message/Logic/CreatePlayerRequest.h"
#include "Message/Logic/ChangeForceIndexRequest.h"
#include "Message/Battle/ChallengeMissionRequest.h"
#include "Message/Logic/ExchangeSoulToHeroRequest.h"
#include "Message/Logic/BuyItemRequest.h"
#include "Message/Logic/BuyPowerRequest.h"
#include "Message/Battle/MissionCheckOutRequest.h"
#include "Message/Logic/ChangeAuraRequest.h"
#include "Message/Logic/ChangeEquipRequest.h"
#include "Message/Logic/UseItemRequest.h"
#include "Message/Logic/SellEquipRequest.h"
#include "Proto/Server/Common/MessageErrorCode.pb.h"
#include "Message/Logic/UpgradeEquipRequest.h"
#include "Message/Logic/HeroInheritRequest.h"
#include "Message/Logic/UpgradeSkillRequest.h"
#include "Message/Logic/TrainHeroRequest.h"
#include "Message/Logic/TrainHeroAcceptRequest.h"
#include "Message/Logic/DrawRuneRequest.h"
#include "Message/Logic/HeroBreakRequest.h"
#include "Message/Logic/UpgradeRuneRequest.h"
#include "Message/Logic/ChangeRuneRequest.h"
#include "Message/Logic/FragmentRobMatchRequest.h"
#include "Message/Logic/RankListRequest.h"
#include "Message/Logic/ExchangePVPScoreRequest.h"
#include "Message/Logic/PVPRequest.h"
#include "Message/Logic/GetPVPAwardRequest.h"
#include "Message/Logic/RefreshPVPScoreRequest.h"
#include "Message/Logic/PVPForcedHerosRequest.h"
#include "Message/Logic/ExchangeAuraRequest.h"
#include "Message/Logic/UpgradePetRequest.h"
#include "Message/Logic/CardActivityRequest.h"
#include "Message/Logic/UpgradeActivityRequest.h"
#include "Message/Logic/WineActivityRequest.h"
#include "Message/Logic/SignActivityRequest.h"
#include "Message/Logic/SevenDayGiftRequest.h"
#include "Message/Logic/GetBloodyChallengeGroupRequest.h"
#include "Message/Logic/AddBloodyBuffRequest.h"
#include "Message/Logic/BeginBloodyRequest.h"
#include "Message/Logic/BloodyRankListRequest.h"
#include "Message/Logic/BloodySettlementRequest.h"
#include "Message/Logic/GetChapterAwardRequest.h"
#include "Message/Battle/MissionSweepRequest.h"
#include "Message/Logic/OrderRequest.h"
#include "Message/Logic/AccumlateChargeAwardRequest.h"
#include "Message/Logic/OrderStatusRequest.h"
#include "Message/Logic/GuideFinishRequest.h"
#include "Message/Battle/PVPCheckAndPlayerDataRequest.h"
#include "Message/Battle/MissionResetRequest.h"
#include "Message/Logic/OtherPlayerDataRequest.h"
#include "Message/Logic/GetMailGiftRequest.h"
#include "Message/Logic/GetCDKPackageRequest.h"

void IMessageCenter::Update( float dt )
{	
	RETURN_IF_FALSE( mIsUpdate );
	RETURN_IF_NULL(mPlayer);
	RETURN_IF_FALSE( mPlayer->IsLogined() );

	mDuration+=dt;
	float messageDuration=ServerGameConfig::Instance().AutoMessageDuration();
	if (mDuration>messageDuration)
	{
		RefreshPlayerData();
		mDuration=0.f;
	}
}


void IMessageCenter::OnCallbackHelper( IMessage* message,MessageEventArg messageEventArg )
{
	if (!message->GetErrorReportSuppress().HasFlag(MessageErrorReportSuppress::HideActivityIndicator))
	{
		HideActivityIndicator();
	}
	
	switch(message->GetState())
	{
	case MessageState::Completed:
		{
			switch(message->GetType())
			{
			case MessageType::Request:
				if (message->GetServerError()==ServerProto::AuthFailed)	//auth failed
				{
					RETURN_IF_FALSE(ProcessAuthError(message,message->GetErrorReportSuppress()));
				}

				if (message->GetServerError()==ServerProto::Failed)	//auth failed
				{
					RETURN_IF_FALSE(ProcessFailedError(message,message->GetErrorReportSuppress()));
				}
				break;
			case MessageType::Custom:
				if (message->GetCustomError()==GameMessageLogicError::AuthFaied.ToInt())
				{
					RETURN_IF_FALSE(ProcessAuthError(message,message->GetErrorReportSuppress()));
				}
				break;
            default:
                break;
			}
			if (message->GetRootHandler().IsValid())
			{
				message->GetRootHandler().Invoke(message,messageEventArg);
			}

			if (!message->GetErrorReportSuppress().HasFlag(MessageErrorReportSuppress::UpdateLogic))
			{
				UpdateCurrentScene(message);
			}
		}
		break;
	case MessageState::ConnectFail:
		ProcessConnectError(message,message->GetErrorReportSuppress());
		break;
    default:
        break;
	}
}

void IMessageCenter::Login( StringRef user,StringRef sessionId/*=StringRef::Empty*/,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	ShowActivityIndicator();
	AuthLoginRequest* req=GameMessageFactory::SendMessage<AuthLoginRequest>(user,sessionId,CoreProto::LoginServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::DumpPlayerData( StringRef user,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	ShowActivityIndicator();
	
	DumpPlayerDataRequest* req=GameMessageFactory::SendMessage<DumpPlayerDataRequest>(user,
		mPlayer->GetSystemNoticeMaxId(),mPlayer->GetSystemNoticeVersion(),
		mPlayer->GetPlayerNoticeMaxId(),ServerGameConfig::Instance().PlayerNoticeMaxCount(),
		CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::RefreshPlayerData( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );

	RefreshPlayerDataRequest* req=GameMessageFactory::SendMessage<RefreshPlayerDataRequest>(
		(uint32)mPlayer->GetPromptMailMaxId(),(uint32)mPlayer->GetRewardMailMaxId(),
		ServerGameConfig::Instance().MailMaxCount(),
		mPlayer->GetSystemNoticeMaxId(),mPlayer->GetSystemNoticeVersion(),
		mPlayer->GetPlayerNoticeMaxId(),ServerGameConfig::Instance().PlayerNoticeMaxCount(),
		CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	req->SetErrorReportSuppress(MessageErrorReportSuppress::HideActivityIndicator);
	req->EnableProfile(false);
	SAFE_RELEASE(req);
}


void IMessageCenter::OtherPlayerData( uint64 TargetID,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	OtherPlayerDataRequest* req=GameMessageFactory::SendMessage<OtherPlayerDataRequest>(TargetID,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::MissionSweep( uint missionItemID,ServerProto::Logic::MissionSweepRequest_SweepType sweepType, IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	MissionSweepRequest* req=GameMessageFactory::SendMessage<MissionSweepRequest>(missionItemID,sweepType,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::AskOrder( uint chargeLevel, IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	OrderRequest* req=GameMessageFactory::SendMessage<OrderRequest>(chargeLevel,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::AskAccumlateChargeAward( uint chargeLevel, IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	AccumlateChargeAwardRequest* req=GameMessageFactory::SendMessage<AccumlateChargeAwardRequest>(chargeLevel,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::SyncOrder(StringRef orderNO,ServerProto::Logic::OrderStatus orderStatus, IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	//ShowActivityIndicator();
	OrderStatusRequest* req=GameMessageFactory::SendMessage<OrderStatusRequest>(orderNO,orderStatus,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::BuyPower( ServerProto::Logic::IdType idType,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	BuyPowerRequest* req=GameMessageFactory::SendMessage<BuyPowerRequest>(idType,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::MissionReset(uint missionItemID,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	MissionResetRequest* req=GameMessageFactory::SendMessage<MissionResetRequest>(missionItemID,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::HireHero( ServerProto::Logic::HireType model,bool isFree,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	HireHeroRequest* req=GameMessageFactory::SendMessage<HireHeroRequest>(model,isFree,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}
void IMessageCenter::CreatePlayer( StringRef user,StringRef playerName,uint heroID,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	
	ShowActivityIndicator();
	CreatePlayerRequest* req=GameMessageFactory::SendMessage<CreatePlayerRequest>(user,playerName,heroID,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChangeForceIndex(const List<uint64>& herosId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ChangeForceIndexRequest* req=GameMessageFactory::SendMessage<ChangeForceIndexRequest>(herosId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChallengeMission( uint missionId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ChallengeMissionRequest* req=GameMessageFactory::SendMessage<ChallengeMissionRequest>(missionId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChallengePvp( uint64 TargetID,ServerProto::Logic::PVPType type,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	PVPCheckAndPlayerDataRequest* req=GameMessageFactory::SendMessage<PVPCheckAndPlayerDataRequest>(TargetID,type,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ExchangeSoulToHero( uint heroItemId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ExchangeSoulToHeroRequest* req=GameMessageFactory::SendMessage<ExchangeSoulToHeroRequest>(heroItemId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}



void IMessageCenter::UseItem( uint itemId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UseItemRequest* req=GameMessageFactory::SendMessage<UseItemRequest>(itemId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::BuyItemById(uint itemId,uint Num,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	BuyItemRequest* req=GameMessageFactory::SendMessage<BuyItemRequest>(itemId,Num,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::MissionCheckOut(uint missionId,bool isPassed,const List<uint64>& survialHeroes,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	MissionCheckOutRequest* req=GameMessageFactory::SendMessage<MissionCheckOutRequest>(missionId,isPassed,survialHeroes,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::GetChapterAward(uint chapterId, const ServerProto::Logic::ChapterAwardBoxMask mask,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GetChapterAwardRequest* req=GameMessageFactory::SendMessage<GetChapterAwardRequest>(chapterId,mask,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChangeAura( uint64 sourceAuraId,uint64 targetAuraId,uint64 heroId,int armedPos,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ChangeAuraRequest* req=GameMessageFactory::SendMessage<ChangeAuraRequest>(sourceAuraId,targetAuraId,heroId,armedPos,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChangeEquip(uint64 sourceEquipId,uint64 targetEquipId,uint64 heroId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ChangeEquipRequest* req=GameMessageFactory::SendMessage<ChangeEquipRequest>(sourceEquipId,targetEquipId,heroId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ChangeRune(uint64 sourceRuneId,uint64 targetRuneId,uint64 heroId,int forcePos,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ChangeRuneRequest* req=GameMessageFactory::SendMessage<ChangeRuneRequest>(sourceRuneId,targetRuneId,heroId,forcePos,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::SellEquips(const List<uint64>& equips,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	SellEquipRequest* req=GameMessageFactory::SendMessage<SellEquipRequest>(equips,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::UpgradeEquip(uint64 equipId,bool isQuick,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UpgradeEquipRequest* req=GameMessageFactory::SendMessage<UpgradeEquipRequest>(equipId,isQuick,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);

}

void IMessageCenter::HeroInherit( uint64 inheritHerioId,uint64 acceptHeroId,uint32 itemId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	HeroInheritRequest* req=GameMessageFactory::SendMessage<HeroInheritRequest>(inheritHerioId,acceptHeroId,itemId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);

}

void IMessageCenter::UpgradeSkill(uint64 skillId,const List<uint64>& auraIDs,bool isSkill,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UpgradeSkillRequest* req=GameMessageFactory::SendMessage<UpgradeSkillRequest>(skillId,auraIDs,isSkill,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::UpgradePet(uint petItemId,const List<uint64>& heroIDs,List<ServerProto::Logic::Soul,NoCompare<ServerProto::Logic::Soul>>& heroSouls,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UpgradePetRequest* req=GameMessageFactory::SendMessage<UpgradePetRequest>(petItemId,heroIDs,heroSouls,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::TrainHero( ServerProto::Logic::HeroTrainType trainType,uint64 heroId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	TrainHeroRequest* req=GameMessageFactory::SendMessage<TrainHeroRequest>(trainType,heroId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::TrainHeroAccept( bool isOk,uint64 heroId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	TrainHeroAcceptRequest* req=GameMessageFactory::SendMessage<TrainHeroAcceptRequest>(isOk,heroId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::DrawRune(ServerProto::Logic::DrawRuneRequest_DrawType runeType,IMessage::MessageEventHandler handler)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	DrawRuneRequest* req=GameMessageFactory::SendMessage<DrawRuneRequest>(runeType,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::HeroBreak( uint64 heroId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	HeroBreakRequest* req=GameMessageFactory::SendMessage<HeroBreakRequest>(heroId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::UpgradeRune(uint64 targetRuneId,const List<uint64>& costRuneIds,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UpgradeRuneRequest* req=GameMessageFactory::SendMessage<UpgradeRuneRequest>(targetRuneId,costRuneIds,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::FragmentRobMatch(uint32 auraItemId,IMessage::MessageEventHandler handler)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	FragmentRobMatchRequest* req=GameMessageFactory::SendMessage<FragmentRobMatchRequest>(auraItemId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::ExchangeAura( uint32 auraItemId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ExchangeAuraRequest* req=GameMessageFactory::SendMessage<ExchangeAuraRequest>(auraItemId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::RankList( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	RankListRequest* req=GameMessageFactory::SendMessage<RankListRequest>(CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::ExchangePVPScore( uint pvpScore,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	ExchangePVPScoreRequest* req=GameMessageFactory::SendMessage<ExchangePVPScoreRequest>(pvpScore,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::RefreshPVPScore( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	RefreshPVPScoreRequest* req=GameMessageFactory::SendMessage<RefreshPVPScoreRequest>(CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::Pvp( ServerProto::Logic::PVPType pvpType,uint64 playerId,bool isWinner,List<uint64> durvivalHeros,uint auraId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	PVPRequest* req=GameMessageFactory::SendMessage<PVPRequest>(pvpType,playerId,isWinner,durvivalHeros,auraId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::GetPVPAward( ServerProto::Logic::PVPRewardTypeMask type,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GetPVPAwardRequest* req=GameMessageFactory::SendMessage<GetPVPAwardRequest>(type,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::PVPForcedHeros( uint64 heroId,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	PVPForcedHerosRequest* req=GameMessageFactory::SendMessage<PVPForcedHerosRequest>(heroId,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::CardActivity(uint32 position,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/)
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	CardActivityRequest* req = GameMessageFactory::SendMessage<CardActivityRequest>( position, CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	req->SetErrorReportSuppress(MessageErrorReportSuppress::UpdateLogic);
	SAFE_RELEASE(req);
}


void IMessageCenter::UpgradeActivity( uint32 index,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	UpgradeActivityRequest* req = GameMessageFactory::SendMessage<UpgradeActivityRequest>( index, CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::WineActivity( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	WineActivityRequest* req = GameMessageFactory::SendMessage<WineActivityRequest>( CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::SignActivity( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	SignActivityRequest* req = GameMessageFactory::SendMessage<SignActivityRequest>( CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}


void IMessageCenter::SevenDayGift(uint dayIndex, IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	SevenDayGiftRequest* req = GameMessageFactory::SendMessage<SevenDayGiftRequest>(dayIndex, CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	req->SetErrorReportSuppress(MessageErrorReportSuppress::UpdateLogic);
	SAFE_RELEASE(req);
}


void IMessageCenter::GetBloodyChallengeGroup( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GetBloodyChallengeGroupRequest* req = GameMessageFactory::SendMessage<GetBloodyChallengeGroupRequest>( CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::BeginBloody( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	BeginBloodyRequest* req = GameMessageFactory::SendMessage<BeginBloodyRequest>( CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::AddBloodyBuff(ServerProto::Logic::BloodyAddBuffType buffType, const ServerProto::Logic::RoleProperty& roleProperty,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	AddBloodyBuffRequest* req = GameMessageFactory::SendMessage<AddBloodyBuffRequest>( buffType,roleProperty,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::BloodyRankList( IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	BloodyRankListRequest* req = GameMessageFactory::SendMessage<BloodyRankListRequest>( CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::BloodySettlement( bool isWin,const List<uint64>& survivalheros,ServerProto::Logic::BloodyChallengeDifficultyType difficultyType,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	BloodySettlementRequest* req = GameMessageFactory::SendMessage<BloodySettlementRequest>( isWin,survivalheros,difficultyType,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::GuideFinish( ServerProto::Logic::GuideType type,uint guideId,bool isFinishAll,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GuideFinishRequest* req = GameMessageFactory::SendMessage<GuideFinishRequest>( type,guideId,isFinishAll,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::GetMailGift( uint mailID,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GetMailGiftRequest* req = GameMessageFactory::SendMessage<GetMailGiftRequest>( mailID,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}

void IMessageCenter::GetCDKPackage( StringRef key,IMessage::MessageEventHandler handler/*=IMessage::MessageEventHandler::Empty*/ )
{
	RETURN_IF_FALSE( mPlayer->IsLogined() );
	ShowActivityIndicator();
	GetCDKPackageRequest* req = GameMessageFactory::SendMessage<GetCDKPackageRequest>( key,CoreProto::GameServer,IMessage::MessageEventHandler(this,&IMessageCenter::OnCallbackHelper));
	req->SetRootHandler(handler);
	SAFE_RELEASE(req);
}
