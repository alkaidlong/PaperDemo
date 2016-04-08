#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Message/MessageEventArg.h"
#include "Proto/Server/Logic/HireType.pb.h"
#include "Core/Collection/Dictionary.h"
#include "Message/Player.h"
#include "Message/GameMessageFactory.h"
#include "Proto/Server/Logic/HeroTrainType.pb.h"
#include "Proto/Server/Logic/DrawRuneRequest.pb.h"
#include "Proto/Server/Logic/PVPRequest.pb.h"
#include "Proto/Server/Logic/PVPRewardTypeMask.pb.h"
#include "Proto/Server/Logic/ChapterAwardBoxMask.pb.h"
#include "Message/Battle/MissionCheckOutRequest.h"
#include "Proto/Server/Logic/MissionSweepRequest.pb.h"
#include "Proto/Server/Logic/OrderRequest.pb.h"
#include "Proto/Server/Logic/AccumlateChargeAwardRequest.pb.h"
#include "Proto/Server/Logic/OrderStatusRequest.pb.h"
#include "Proto/Server/Logic/GuideType.pb.h"
#include "Proto/Server/Logic/IdType.pb.h"
#include "Proto/Server/Logic/MissionResetRequest.pb.h"
#include "Proto/Server/Logic/OrderStatus.pb.h"

USING_MEDUSA;


class IMessageCenter
{
protected:
	IMessageCenter(void):mIsUpdate(false),mPlayer(NULL),mDuration(0.f){}
	virtual ~IMessageCenter(void){}
public:
	bool IsUpdate() const { return mIsUpdate; }
	void SetIsUpdate(bool val) { mIsUpdate = val; }

	Player* GetPlayer() const { return mPlayer; }
	void SetPlayer(Player* val) { mPlayer = val; GameMessageFactory::SetPlayer(mPlayer);}

	virtual void Update(float dt);
public:
	virtual bool ProcessConnectError(IMessage* message,MessageErrorReportSuppress errorReportSuppress)=0;
	virtual bool ProcessAuthError(IMessage* message,MessageErrorReportSuppress errorReportSuppress)=0;
	virtual bool ProcessFailedError(IMessage* message,MessageErrorReportSuppress errorReportSuppress)=0;

#pragma region Messages
public:
	virtual void Login(StringRef user,StringRef sessionId=StringRef::Empty,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void DumpPlayerData(StringRef user,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void RefreshPlayerData(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void OtherPlayerData(uint64 TargetID,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

	virtual void HireHero(ServerProto::Logic::HireType model,bool isFree,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void CreatePlayer(StringRef user,StringRef playerName,uint heroID,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChangeForceIndex(const List<uint64>& herosId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChallengeMission(uint missionId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChallengePvp(uint64 TargetID,ServerProto::Logic::PVPType type,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ExchangeSoulToHero(uint heroItemId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void BuyItemById(uint itemId,uint Num,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UseItem(uint itemId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void MissionCheckOut(uint missionId,bool isPassed,const List<uint64>& survialHeroes,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void GetChapterAward(uint chapterId,const ServerProto::Logic::ChapterAwardBoxMask mask,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChangeAura(uint64 sourceAuraId,uint64 targetAuraId,uint64 heroId,int armedPos,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChangeEquip(uint64 sourceEquipId,uint64 targetEquipId,uint64 heroId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ChangeRune(uint64 sourceRuneId,uint64 targetRuneId,uint64 heroId,int forcePos,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void SellEquips(const List<uint64>& equips,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UpgradeEquip(uint64 equipId,bool isQuick,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void HeroInherit(uint64 inheritHerioId,uint64 acceptHeroId,uint32 itemId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UpgradeSkill(uint64 skillId,const List<uint64>& auraIDs,bool isSkill,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UpgradePet(uint petItemId,const List<uint64>& heroIDs,List<ServerProto::Logic::Soul,NoCompare<ServerProto::Logic::Soul>>& heroSouls,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void TrainHero(ServerProto::Logic::HeroTrainType trainType,uint64 heroId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void TrainHeroAccept(bool isOk,uint64 heroId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void DrawRune(ServerProto::Logic::DrawRuneRequest_DrawType runeType ,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void HeroBreak(uint64 heroId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UpgradeRune(uint64 targetRuneId,const List<uint64>& costRuneIds,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void FragmentRobMatch(uint32 auraItemId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ExchangeAura(uint32 auraItemId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void RankList(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void ExchangePVPScore(uint pvpScore,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void RefreshPVPScore(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void Pvp(ServerProto::Logic::PVPType pvpType,uint64 playerId,bool isWinner,List<uint64> durvivalHeros,uint auraId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void GetPVPAward(ServerProto::Logic::PVPRewardTypeMask type,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void PVPForcedHeros(uint64 heroId,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void CardActivity(uint32 position,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void UpgradeActivity(uint32 index,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void WineActivity(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void SignActivity(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void SevenDayGift(uint dayIndex, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void MissionSweep(uint missionItemID,ServerProto::Logic::MissionSweepRequest_SweepType sweepType, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void AskOrder(uint chargeLevel, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void AskAccumlateChargeAward(uint awardIndex, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

	virtual void SyncOrder(StringRef orderNO,ServerProto::Logic::OrderStatus orderStatus,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);


	virtual void BuyPower(ServerProto::Logic::IdType idType, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void MissionReset(uint missionItemID, IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

	virtual void BeginBloody(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void AddBloodyBuff(ServerProto::Logic::BloodyAddBuffType buffType,const ServerProto::Logic::RoleProperty& roleProperty,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void GetBloodyChallengeGroup(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void BloodyRankList(IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void BloodySettlement(bool isWin,const List<uint64>& survivalheros,ServerProto::Logic::BloodyChallengeDifficultyType difficultyType,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);
	virtual void GetMailGift(uint mailID,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

	virtual void GuideFinish(ServerProto::Logic::GuideType type,uint guideId,bool isFinishAll,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

	virtual void GetCDKPackage(StringRef key,IMessage::MessageEventHandler handler=IMessage::MessageEventHandler::Empty);

#pragma endregion Messages
protected:
	virtual void ShowActivityIndicator(){}
	virtual void HideActivityIndicator(){}
	virtual void UpdateCurrentScene(IMessage* message){}

	
private:
	void OnCallbackHelper(IMessage* message,MessageEventArg messageEventArg);
protected:
	bool mIsUpdate;
	Player* mPlayer;
	float mDuration;
};

