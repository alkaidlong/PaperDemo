
#include "Config/PaperConfig.h"
#include "Message/Player.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/System/System.h"
#include "Core/Message/MessageDispatcher.h"
#include "Config/PVEConfig.h"
#include "Core/Config/ServerConfig.h"
#include "Core/Config/ServerList.h"
#include "Config/ServerGameConfig.h"
#include "Config/MissionConfig.h"
#include "Config/EquipConfig.h"
#include "Config/AuraConfig.h"
#include "Config/RuneConfig.h"
#include "Config/PetConfig.h"
#include "Proto/Server/Config/RuneConfig.pb.h"
#include "Core/Utility/DateTime.h"
#include "Config/PlayerLevelConfig.h"
#include "PaperAnalytics.h"
#include "Core/Math/Random.h"
#include "Core/String/StringTable/StringTable.h"
#include "Config/HeroLevelConfig.h"
#include "Config/ItemConfig.h"

Player::Player(void)
{
	mIsChanged=false;
	mIsLogined=false;

	mIsLoopHeroHireCD = false;
	mIsLoopRunePerfusionCD = false;
	mCurServerSystemTime = 0;
	mAccumulateServerSystemTime = 0.0f;
	mIsLoopSystemTime = false;
	mLastHireHero = NULL;
	mMailPromptMaxId=0;
	mMailRewardMaxId=0;
	mSystemNoticeMaxId=0;
	mCurBloodyChallengeDifficultyType = ServerProto::Logic::BloodyChallengeInvalidDifficulty;
	mNewUnlockChapterId=0;
	mUnlockedChapterId=0;
	mGameAssistantIndex=0;
	mIsAnnoucementShowed=false;
}

Player::~Player(void)
{
}

bool Player::Load()
{
#if ENABLE_PROTO_STRING==1
	FileId fileId("Player.bin",0);
#else
	FileId fileId("Player.cfg",0);
#endif

	HeapString writablePath= System::Instance().GetWritablePath(mPlayerFileName);
	MemoryByteData data= FileSystem::Instance().GetAccessor().ReadAllData(writablePath,FileCoderList::Empty);
	bool isSuccess=Proto::ParseFrom(mPlayerData,data);

	if (!isSuccess)
	{
		FileSystem::Instance().GetAccessor().Delete(writablePath);
		ResetToDefault();
	}

	UpdateMessageServer();
	UpdateMailMaxId();
	UpdateSystemNoticeMaxId();

	//define cur chapter id
	if(mPlayerData.serverplayer().has_curchapter())
	{
		mCurSelectChapterID = mPlayerData.serverplayer().curchapter();
		FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().chapters())
		{
			const ServerProto::Logic::Chapter& chapter=*i;
			if (chapter.chapteritemid()==mCurSelectChapterID)
			{
				mCurSelectMissionID=chapter.curmission();
			}
		}
	}
	else
	{
		mCurSelectChapterID = PVEConfig::Instance().GetChapterIDByIndex(0);
		mCurSelectMissionID=PVEConfig::Instance().GetMissionIDByIndex(1,0);
	}


	mCurSelectForceIndex = -1;

	//TODO:
	mPlayerData.mutable_logintoken()->set_token("d30f081a-6988-491c-9dcb-7f2472cac922");
	mPlayerData.mutable_logintoken()->set_playerid(1);

	return true;
}


bool Player::Save(bool isForceToSave/*=false*/)
{
	//return true;
	//return false;	//disable save right now
	if (!isForceToSave)
	{
		RETURN_TRUE_IF_FALSE(mIsLogined);
		RETURN_TRUE_IF_FALSE(mIsChanged);
	}

	HeapString writablePath= System::Instance().GetWritablePath(mPlayerFileName);
	MemoryByteData data=Proto::Serialize(mPlayerData);

	if(data.IsNull())
	{
		return false;
	}

	FileSystem::Instance().GetAccessor().WriteAllDataTo(data,writablePath,FileCoderList::Empty);
	mIsChanged=false;
	return true;
}

void Player::ResetToDefault()
{
	mPlayerData.Clear();
	mPlayerData.set_isenablemusic(true);
	mPlayerData.set_isenableeffect(true);
	mPlayerData.set_unreadmailcount(0);
	mPlayerData.mutable_serverplayer()->set_id(0);
	mIsLogined=false;
	MarkChanged();
}

void Player::ResetPlayerData( void )
{
	uint lastTimeServerId=GetLastTimeChooseServerId();
	HeapString lastTimeUserName = GetLastTimeUserName();

	bool isEnableMusic=mPlayerData.isenablemusic();
	bool isEnableEffect=mPlayerData.isenableeffect();
	ServerProto::LoginToken copyToken;
	copyToken.CopyFrom(mPlayerData.logintoken());

	ResetToDefault();
	mPlayerData.set_isenablemusic(isEnableMusic);
	mPlayerData.set_isenableeffect(isEnableEffect);
	mPlayerData.set_lasttimechooseserverid(lastTimeServerId);	//Don't change server id
	mPlayerData.set_lasttimeusername(lastTimeUserName.c_str());

	mPlayerData.mutable_logintoken()->CopyFrom(copyToken);
	MarkChanged();
	Save(true);
}


void Player::Update( float dt )
{
	if (mIsLoopHeroHireCD)
	{
		FOR_EACH_SIZE(i,(unsigned int)mPlayerData.serverplayer().herohireinfos_size())
		{
			ServerProto::Logic::HireInfo* hereInfo = mPlayerData.mutable_serverplayer()->mutable_herohireinfos(i);

			float cdTime = hereInfo->cd();
			if ( (int)cdTime>0 )
			{
				cdTime -= dt;
				hereInfo->set_cd(cdTime);
			}
		}
	}

	if(mIsLoopRunePerfusionCD)
	{
		if ( mPlayerData.serverplayer().drawrunerefreshlefttimesec()>0 )
		{
			mDrawRuneRefreshLeftTimeSec -= dt;
			mPlayerData.mutable_serverplayer()->set_drawrunerefreshlefttimesec((uint)mDrawRuneRefreshLeftTimeSec);
		}
	}

	if (mIsLoopSystemTime)
	{
		mAccumulateServerSystemTime += dt;
	}
}


#pragma region Get data



#pragma endregion Get data

#pragma region Update Data
void Player::ClearLoginToken()
{
	mPlayerData.clear_logintoken();
	Logout();
}


void Player::SetLoginToken(const ServerProto::LoginToken& loginToken)
{
	ServerProto::LoginToken* token= mPlayerData.mutable_logintoken();
	token->set_token(loginToken.token());	//do not copy player id
	if(!token->has_playerid())
	{
		token->set_playerid(loginToken.playerid());
	}

	MarkChanged();
}


void Player::UpdateForceHeroes()
{
	mForceHeroes.Clear();
	mNotForceHeroes.Clear();
	mIDHeroDict.Clear();
	mItemIDHeroDict.Clear();
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		const ServerProto::Logic::Hero& hero=*i;
		if (hero.forceindex()>=0)
		{
			mForceHeroes.Add(&hero);
		}
		else if (hero.forceindex()==-1)
		{
			mNotForceHeroes.Add(&hero);
		}
		mIDHeroDict.Add(hero.id(),&hero);
		mItemIDHeroDict.Add(hero.heroitemid(),&hero);
	}

	if (mForceHeroes.GetCount()>ServerGameConfig::Instance().ForceNumMax())
	{
		Log::LogErrorFormat("Force hero count:%zu out of %d.",mForceHeroes.GetCount(),ServerGameConfig::Instance().ForceNumMax());
		mForceHeroes.Clear();
	}
}

void Player::UpdatePet()
{
	mOpenPetsId.Clear();

	uint talentCount = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().pets())
	{
		const ServerProto::Logic::Pet* pet=&(*i);
		talentCount+=pet->level();
		mOpenPetsId.Add(pet->petitemid());
	}

	const Dictionary<uint,const ServerProto::Config::PetConfigItem*>& petDict = PetConfig::Instance().GetPetDict();
	FOR_EACH_COLLECTION(i,petDict)
	{
		const ServerProto::Config::PetConfigItem* petConfig = (*i).Value;
		const ServerProto::Logic::Pet* petServer = GetServerPet(petConfig->id());
		if (petServer==NULL)
		{
			const ServerProto::Logic::Pet* prevPetServer = GetServerPet(petConfig->unlockprevpetid());

			bool isReach = true;

			if (GetLevel()<petConfig->unlockplayerlevel())
			{
				isReach = false;
			}
			if (talentCount<petConfig->unlockpetpointsused())
			{
				isReach = false;
			}

			if (petConfig->unlockprevpetid()!=0)
			{
				if (prevPetServer==NULL)
				{
					isReach = false;
				}
				else
				{
					if (prevPetServer->level()<petConfig->unlockprevpetlevel())
					{
						isReach = false;
					}
				}
			}

			if (isReach)
			{
				mOpenPetsId.Add(petConfig->id());
			}
		}
	}

}

void Player::UpdateAura(const ServerProto::Logic::Aura& changeAura)
{
	ServerProto::Logic::Aura* findAura = (ServerProto::Logic::Aura*)GetServerAura(changeAura.id());
	if (findAura!=NULL)
	{
		findAura->MergeFrom(changeAura);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateAuras: not find aura %llu",changeAura.id());
	}
}

void Player::UpdateAura()
{
	//字典
	mAuraHeroDict.Clear();
	mIDAurasDict.Clear();
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		const ServerProto::Logic::Hero& hero=*i;
		FOR_EACH_COLLECTION_STL(j,hero.auras())
		{
			const ServerProto::Logic::Aura& aura = *j;

			mAuraHeroDict.Add(&aura,&hero);
			mIDAurasDict.Add(aura.id(),&aura);
		}
	}

	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().auras())
	{
		const ServerProto::Logic::Aura& aura = *i;
		mAuraHeroDict.Add(&aura,NULL);
		mIDAurasDict.Add(aura.id(),&aura);
	}
}

void Player::UpdateRune()
{
	mRuneHeroDict.Clear();
	mIDRunesDict.Clear();
	mNotWhiteRunes.Clear();
	mAllRunes.Clear();
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		const ServerProto::Logic::Hero& hero=*i;
		FOR_EACH_COLLECTION_STL(j,hero.runes())
		{
			const ServerProto::Logic::Rune& rune = *j;
			mRuneHeroDict.Add(&rune,&hero);
			mIDRunesDict.Add(rune.id(),&rune);
			const ServerProto::Config::RuneConfigItem* runeConfigItem = RuneConfig::Instance().GetRuneConfigItem(rune.runeitemid());
			if (runeConfigItem->quality()!=ServerProto::Logic::QualityValues::White)
			{
				mNotWhiteRunes.Add(&rune);
			}
			mAllRunes.Add(&rune);
		}
	}
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().runes())
	{
		const ServerProto::Logic::Rune& rune =*i;
		mRuneHeroDict.Add(&rune,NULL);
		mIDRunesDict.Add(rune.id(),&rune);		
		const ServerProto::Config::RuneConfigItem* runeConfigItem = RuneConfig::Instance().GetRuneConfigItem(rune.runeitemid());
		if (runeConfigItem->quality()!=ServerProto::Logic::QualityValues::White)
		{
			mNotWhiteRunes.Add(&rune);
		}
		mAllRunes.Add(&rune);
	}
}

void Player::UpdateEquip()
{
	mAllEquips.Clear();
	mEquipHeroDict.Clear();
	mIDEquipDict.Clear();
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		const ServerProto::Logic::Hero& hero=*i;
		FOR_EACH_COLLECTION_STL(j,hero.equips())
		{
			const ServerProto::Logic::Equip& equip = *j;
			mAllEquips.Add(&equip);
			mEquipHeroDict.Add(&equip,&hero);
			mIDEquipDict.Add(equip.id(),&equip);
		}
	}
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().equips())
	{
		const ServerProto::Logic::Equip& equip = *i;
		mAllEquips.Add(&equip);
		mEquipHeroDict.Add(&equip,NULL);
		mIDEquipDict.Add(equip.id(),&equip);
	}
}


void Player::SetLastTimeChooseServerId( uint serverId )
{
	mPlayerData.set_lasttimechooseserverid(serverId);
	UpdateMessageServer();
	MarkChanged();
}

void Player::SetLastTimeUserName( const StringRef& userName )
{
	mPlayerData.set_lasttimeusername(userName.c_str());
	MarkChanged();
}


void Player::UpdateMessageServer()
{
	if (HasLastTimeChooseServerId())
	{
		uint gameServerId=GetLastTimeChooseServerId();
		MemoryByteData encryptKey=ServerGameConfig::Instance().MessageEncryptKey().ToData().Cast<byte>();
		CoreProto::FileList::FileCoder::FileCoderType sendCoderType=ServerGameConfig::Instance().MessageEncoderType();
		CoreProto::FileList::FileCoder::FileCoderType receiveCoderType=ServerGameConfig::Instance().MessageDecoderType();
		ServerList::Instance().UpdateMessageServer(gameServerId,PaperConfig::Instance().MessageRetryTimes(),PaperConfig::Instance().MessageRetryInterval(),PaperConfig::MessageVersion,sendCoderType,receiveCoderType,encryptKey);
	}
}

void Player::SetServerPlayer( const ServerProto::Logic::ServerPlayer& serverPlayer )
{
	const List<StringRef>* strGameTip = StringTable::Instance().GetAllStrings("GameAssistant");
	Random random;
	mGameAssistantIndex = (uint)random.Next(strGameTip->GetCount()-1);

	mPlayerData.mutable_serverplayer()->CopyFrom(serverPlayer);
	UpdateForceHeroes();
	UpdatePet();
	UpdateAura();
	UpdateEquip();
	UpdateRune();
	UpdateSystemNoticeMaxId();
	UpdateGuideIds();

	mCurSelectChapterID = mPlayerData.serverplayer().curchapter();

	mDrawRuneRefreshLeftTimeSec = (float)mPlayerData.serverplayer().drawrunerefreshlefttimesec();
	mIsLoopHeroHireCD = true;
	mIsLoopRunePerfusionCD = true;

	SynchronizeServerSystemTime(mPlayerData.serverplayer().thislogintime());

	mIsLogined = true;

	//init analytics account
	uint serverListId=GetLastTimeChooseServerId();
	int gameServerId=ServerList::Instance().GetServerIdWithUsage(serverListId,CoreProto::GameServer);
	if (gameServerId!=-1)
	{
		StringParser::ResultStringType gameServerName=StringParser::ToString(gameServerId);
		StringParser::ResultStringType accountId=StringParser::ToString(mPlayerData.serverplayer().id());
		StringRef accountName=mPlayerData.lasttimeusername();
		Analytics::InitAccount(gameServerName,accountId,accountName,mPlayerData.serverplayer().level());
	}
}

void Player::UpdateServerPlayer( const ServerProto::Logic::ServerPlayer& serverPlayer )
{
	mPlayerData.mutable_serverplayer()->set_id(serverPlayer.id());
	if (serverPlayer.has_name())
		mPlayerData.mutable_serverplayer()->set_name(serverPlayer.name());
	if (serverPlayer.has_missionsweeptimes())
		mPlayerData.mutable_serverplayer()->set_missionsweeptimes(serverPlayer.missionsweeptimes());
	if (serverPlayer.has_level())
		mPlayerData.mutable_serverplayer()->set_level(serverPlayer.level());
	if (serverPlayer.has_money())
		mPlayerData.mutable_serverplayer()->set_money(serverPlayer.money());
	if (serverPlayer.has_diamond())
		mPlayerData.mutable_serverplayer()->set_diamond(serverPlayer.diamond());
	if (serverPlayer.has_pvepower())
		mPlayerData.mutable_serverplayer()->set_pvepower(serverPlayer.pvepower());
	if (serverPlayer.has_pvppower())
		mPlayerData.mutable_serverplayer()->set_pvppower(serverPlayer.pvppower());
	if (serverPlayer.has_rmb())
		mPlayerData.mutable_serverplayer()->set_rmb(serverPlayer.rmb());
	if (serverPlayer.has_loginaccumulatedays())
		mPlayerData.mutable_serverplayer()->set_loginaccumulatedays(serverPlayer.loginaccumulatedays());
	if (serverPlayer.has_logincontinuallydays())
		mPlayerData.mutable_serverplayer()->set_logincontinuallydays(serverPlayer.logincontinuallydays());
	if (serverPlayer.has_lastlogintime())
		mPlayerData.mutable_serverplayer()->set_lastlogintime(serverPlayer.lastlogintime());
	if (serverPlayer.has_curchapter())
		mPlayerData.mutable_serverplayer()->set_curchapter(serverPlayer.curchapter());
	if (serverPlayer.has_exp())
	{
		mPlayerData.mutable_serverplayer()->set_exp(serverPlayer.exp());
		mPlayerData.mutable_serverplayer()->set_level(PlayerLevelConfig::Instance().CalculateLevel(serverPlayer.exp()));
	}
	if (serverPlayer.has_thislogintime())
		mPlayerData.mutable_serverplayer()->set_thislogintime(serverPlayer.thislogintime());
	if (serverPlayer.has_viplevel())
		mPlayerData.mutable_serverplayer()->set_viplevel(serverPlayer.viplevel());

	if (serverPlayer.has_herohiresadness())
		mPlayerData.mutable_serverplayer()->set_herohiresadness(serverPlayer.herohiresadness());
	if (serverPlayer.has_availablepvepowerbuycount())
		mPlayerData.mutable_serverplayer()->set_availablepvepowerbuycount(serverPlayer.availablepvepowerbuycount());
	if (serverPlayer.has_availablepvppowerbuycount())
		mPlayerData.mutable_serverplayer()->set_availablepvppowerbuycount(serverPlayer.availablepvppowerbuycount());
	if (serverPlayer.has_curdrawlevel())
		mPlayerData.mutable_serverplayer()->set_curdrawlevel(serverPlayer.curdrawlevel());
	if (serverPlayer.has_drawrunerefreshlefttimesec())
	{
		mPlayerData.mutable_serverplayer()->set_drawrunerefreshlefttimesec(serverPlayer.drawrunerefreshlefttimesec());
		mDrawRuneRefreshLeftTimeSec = (float)serverPlayer.drawrunerefreshlefttimesec();
	}
	if (serverPlayer.has_pvprewardmask())
		mPlayerData.mutable_serverplayer()->set_pvprewardmask(serverPlayer.pvprewardmask());
	if (serverPlayer.has_pvprank())
		mPlayerData.mutable_serverplayer()->set_pvprank(serverPlayer.pvprank());
	if (serverPlayer.has_pvpscore())
		mPlayerData.mutable_serverplayer()->set_pvpscore(serverPlayer.pvpscore());
	if (serverPlayer.has_pvptodayleftcount())
		mPlayerData.mutable_serverplayer()->set_pvptodayleftcount(serverPlayer.pvptodayleftcount());



	FOR_EACH_COLLECTION_STL(i,serverPlayer.herohireinfos())
	{
		const ServerProto::Logic::HireInfo& hireInfo = *i;
		UpdateHeroHireInfo(hireInfo);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.chapters())
	{
		const ServerProto::Logic::Chapter& chapter = *i;
		UpdateChapter(chapter);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.missions())
	{
		const ServerProto::Logic::Mission& mission = *i;
		UpdateMission(mission);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.heroes())
	{
		const ServerProto::Logic::Hero& hero = *i;
		UpdateHero(hero);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.herosouls())
	{
		const ServerProto::Logic::Soul& soul = *i;
		UpdateHeroSoul(soul);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.equips())
	{
		const ServerProto::Logic::Equip& equip = *i;
		UpdateEquip(equip);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.auras())
	{
		const ServerProto::Logic::Aura& aura = *i;
		UpdateAura(aura);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.items())
	{
		const ServerProto::Logic::Item& item = *i;
		UpdateItem(item);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.runes())
	{
		const ServerProto::Logic::Rune& rune = *i;
		UpdateRune(rune);
	}
	FOR_EACH_COLLECTION_STL(i,serverPlayer.fragments())
	{
		const ServerProto::Logic::AuraFragment& auraFragment = *i;
		UpdateAuraFragment(auraFragment);
	}

	UpdateForceHeroes();
	UpdatePet();
	UpdateAura();
	UpdateEquip();
	UpdateRune();

	Analytics::UpdateAccountLevel(mPlayerData.serverplayer().level());

}

//chapter
const ServerProto::Logic::Chapter* Player::GetServerChapter( uint id )const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().chapters())
	{
		const ServerProto::Logic::Chapter* chapterData = &(*i);
		if (chapterData->chapteritemid()==id)
		{
			return chapterData;
		}
	}

	return NULL;
}

void Player::SetChapterCurMission( uint chaptId,uint missionId )
{
	ServerProto::Logic::Chapter* serverChapter = (ServerProto::Logic::Chapter*)GetServerChapter(chaptId);
	if (serverChapter!=NULL)
	{
		serverChapter->set_curmission(missionId);
	}
	else
	{
		Log::LogErrorFormat("Can not find chapter by id %d",chaptId);
	}
}


void Player::AddServerChapter(uint chapterId)
{
	const ServerProto::Logic::Chapter* serverChapter = GetServerChapter(chapterId);
	if (serverChapter==NULL)
	{
		ServerProto::Logic::Chapter* chapter = NULL;
		chapter = mPlayerData.mutable_serverplayer()->add_chapters();
		chapter->set_chapteritemid(chapterId);
		chapter->set_chapterawardmask(0);
		chapter->set_curmission(PVEConfig::Instance().GetMissionIDByIndex(chapterId,0));
		mNewUnlockChapterId=chapterId;	//增加解锁位置
		mUnlockedChapterId=chapterId;
		mPlayerData.mutable_serverplayer()->set_curchapter(chapterId);
	}
	else
	{
		Log::LogErrorFormat("Player:AddServerChapter:haved chapter id %d",chapterId);
	}
}

void Player::UpdateChapter(const ServerProto::Logic::Chapter& chatper)
{
	ServerProto::Logic::Chapter* findChapter = (ServerProto::Logic::Chapter*)GetServerChapter(chatper.chapteritemid());
	if (findChapter!=NULL)
	{
		findChapter->MergeFrom(chatper);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateChapter:not find chapter id %d",chatper.chapteritemid());
	}
}

//mission
const ServerProto::Logic::Mission* Player::GetServerMission( uint id )const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().missions())
	{
		const ServerProto::Logic::Mission* missionData = &(*i);
		if (missionData->missionitemid()==id)
		{
			return missionData;
		}
	}

	return NULL;
}

void Player::AddServerMission(uint missionId)
{
	const ServerProto::Logic::Mission* serverMission = GetServerMission(missionId);
	if (serverMission==NULL)
	{
		const ServerProto::Config::MissionConfigItem* missionConfig = MissionConfig::Instance().GetMissionConfigItem(missionId);

		ServerProto::Logic::Mission* mission = NULL;
		mission = mPlayerData.mutable_serverplayer()->add_missions();
		mission->set_missionitemid(missionId);
		mission->set_gotstar(0);
		mission->set_timestodayleft(missionConfig->maxcompletedperday());
		mission->set_resettimestoday(0);
	}
	else
	{
		Log::LogErrorFormat("Player:AddServerMission: haved mission id %d",missionId);
	}
}

void Player::UpdateMission( const ServerProto::Logic::Mission& mission )
{
	ServerProto::Logic::Mission* findMission = (ServerProto::Logic::Mission*)GetServerMission(mission.missionitemid());
	if (findMission!=NULL)
	{
		findMission->MergeFrom(mission);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateMission: not find mission id %d",mission.missionitemid());
	}
}

//hero
const ServerProto::Logic::HireInfo* Player::GetServerHeroHireInfo( ServerProto::Logic::HireType type )const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().herohireinfos())
	{
		const ServerProto::Logic::HireInfo* hereInfo = &(*i);
		if (hereInfo->type() == type)
		{
			return hereInfo;
		}
	}

	return NULL;
}

void Player::UpdateHeroHireInfo(const ServerProto::Logic::HireInfo& hireInfo)
{
	ServerProto::Logic::HireInfo* findHireInfo = (ServerProto::Logic::HireInfo*)GetServerHeroHireInfo(hireInfo.type());
	if (findHireInfo!=NULL)
	{
		findHireInfo->MergeFrom(hireInfo);
	}
	else
	{
		Log::LogError("Player:UpdateHeroHireInfo: not find hero hire type data");
	}
}

const ServerProto::Logic::Hero* Player::GetServerHero( uint64 heroId )const
{
	const ServerProto::Logic::Hero* hero = mIDHeroDict.TryGetValueWithFailed(heroId,NULL);
	if (hero==NULL)
	{
		Log::LogErrorFormat("Player:GetServerHero:not find hero from id %llu",heroId);
	}

	return hero;
}

const ServerProto::Logic::Hero* Player::GetServerHero( uint itemId )const
{
	const ServerProto::Logic::Hero* hero = mItemIDHeroDict.TryGetValueWithFailed(itemId,NULL);
	if (hero==NULL)
	{
		Log::LogErrorFormat("Player:GetServerHero:not find hero from itemid %d",itemId);
	}

	return hero;
}

uint Player::GetHeroWeightMax(uint64 heroId)const
{
	const ServerProto::Logic::Hero* heroServer = GetServerHero(heroId);
	const ServerProto::Config::HeroConfigItem* heroConfig = HeroConfig::Instance().GetHeroConfigItem(heroServer->heroitemid());
	return heroConfig->weightbegin()+(heroConfig->weightgrow()*(heroServer->level()-1));
}

uint Player::GetHeroCurWeight(uint64 heroId)const
{
	uint weight = 0;
	ServerProto::Logic::Hero* heroFindTar = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	if (heroFindTar!=NULL)
	{
		FOR_EACH_COLLECTION_STL(i,heroFindTar->equips())
		{
			const ServerProto::Logic::Equip& equip = (*i);
			const ServerProto::Config::EquipConfigItem* equipConfig = EquipConfig::Instance().GetEquipConfigItem(equip.equipitemid());
			weight+=equipConfig->weight();
		}
	}

	return weight;
}

void Player::SetHeroForceIndex( uint64 heroId,uint forceIndex )
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		ServerProto::Logic::Hero* hero=(ServerProto::Logic::Hero*)(&(*i));
		if (hero->forceindex()==forceIndex)
		{
			hero->set_forceindex(-1);
			break;
		}
	}
	ServerProto::Logic::Hero* hero = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	if (hero!=NULL)
	{
		hero->set_forceindex(forceIndex);
	}
	else
	{
		Log::AssertFailedFormat("Cannot find hero:%llu",heroId);
	}

	UpdateForceHeroes();
}

void Player::AddHero( const ServerProto::Logic::Hero& hireHero )
{
	bool isHave = false;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		ServerProto::Logic::Hero* hero=(ServerProto::Logic::Hero*)(&(*i));
		if (hero->id()==hireHero.id())
		{
			isHave = true;
			UpdateHero(hireHero);
			break;
		}
	}

	if (!isHave)
	{
		mLastHireHero = mPlayerData.mutable_serverplayer()->add_heroes();
		mLastHireHero->CopyFrom(hireHero);
	}

	UpdateForceHeroes();
	UpdateAura();
	UpdateEquip();
	UpdateRune();
}

void Player::HeroCleanUp( ServerProto::Logic::Hero* heroServer )
{
	//清空装备
	FOR_EACH_COLLECTION_STL(i,heroServer->equips())
	{
		const ServerProto::Logic::Equip& equipServer = *i;
		mPlayerData.mutable_serverplayer()->add_equips()->CopyFrom(equipServer);
	}
	heroServer->mutable_equips()->Clear();

	//清空符文
	FOR_EACH_COLLECTION_STL(i,heroServer->runes())
	{
		const ServerProto::Logic::Rune& runeServer = *i;
		mPlayerData.mutable_serverplayer()->add_runes()->CopyFrom(runeServer);
	}
	heroServer->mutable_runes()->Clear();

	//清空光环
	FOR_EACH_COLLECTION_STL(i,heroServer->auras())
	{
		const ServerProto::Logic::Aura& auraServer = *i;
		mPlayerData.mutable_serverplayer()->add_auras()->CopyFrom(auraServer);
	}
	heroServer->mutable_auras()->Clear();
}

void Player::RemoveHero( const uint64 heroId,bool isUpdate/*=true*/ )
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		ServerProto::Logic::Hero* hero=(ServerProto::Logic::Hero*)(&(*i));
		if (hero->id()==heroId)
		{
			HeroCleanUp(hero);
			Proto::RemoveItem<ServerProto::Logic::Hero>(mPlayerData.mutable_serverplayer()->mutable_heroes(),index);

			if (isUpdate)
			{
				UpdateForceHeroes();
				UpdateAura();
				UpdateEquip();
				UpdateRune();
			}
			return;
		}
		index++;
	}

	Log::LogErrorFormat("Not find hero %llu in player list",heroId);
}

void Player::RemoveHeros( const List<uint64>& heroIds )
{
	FOR_EACH_COLLECTION(i,heroIds)
	{
		RemoveHero(*i,false);
	}

	UpdateForceHeroes();
	UpdateAura();
	UpdateEquip();
	UpdateRune();
}

void Player::UpdateHero(const ServerProto::Logic::Hero& hireHero)
{
	ServerProto::Logic::Hero* findHero= (ServerProto::Logic::Hero*)GetServerHero(hireHero.id());

	if (findHero!=NULL)
	{
		findHero->set_id(hireHero.id());
		if (hireHero.has_heroitemid())
			findHero->set_heroitemid(hireHero.heroitemid());
		if (hireHero.has_level())
			findHero->set_level(hireHero.level());
		if (hireHero.has_property())
			findHero->mutable_property()->MergeFrom(hireHero.property());

		if (hireHero.has_potential())
			findHero->set_potential(hireHero.potential());
		if (hireHero.has_traintimes())
			findHero->set_traintimes(hireHero.traintimes());
		if (hireHero.has_forceindex())
			findHero->set_forceindex(hireHero.forceindex());
		if (hireHero.has_skilllevel())
			findHero->set_skilllevel(hireHero.skilllevel());
		if (hireHero.has_exp())
			findHero->set_exp(hireHero.exp());
		if (hireHero.has_breakcount())
			findHero->set_breakcount(hireHero.breakcount());
		if (hireHero.has_trainitemcost())
			findHero->set_trainitemcost(hireHero.trainitemcost());

		FOR_EACH_COLLECTION_STL(i,hireHero.equips())
		{
			const ServerProto::Logic::Equip& equip = *i;
			UpdateEquip(equip);
		}
		FOR_EACH_COLLECTION_STL(i,hireHero.auras())
		{
			const ServerProto::Logic::Aura& aura = *i;
			UpdateAura(aura);
		}
		FOR_EACH_COLLECTION_STL(i,hireHero.runes())
		{
			const ServerProto::Logic::Rune& rune = *i;
			UpdateRune(rune);
		}

#ifdef MEDUSA_DEBUG
		//check exp and level is consistent
		const ServerProto::Config::HeroConfigItem* heroConfig=HeroConfig::Instance().GetHeroConfigItem(findHero->heroitemid());
		uint level= HeroLevelConfig::Instance().CalculateLevel(heroConfig->quality(),findHero->exp());
		Log::AssertFormat(level==findHero->level(),"Invalid exp:%d to level:%d !=hero's level:%d",findHero->exp(),level,findHero->level());
#endif

	}
	else
	{
		Log::LogErrorFormat("Player:UpdateHero: not find hero %llu",hireHero.id());
	}
}

void Player::UpdateHero(uint64 heroId,const ServerProto::Logic::RoleProperty& heroProperty)
{
	ServerProto::Logic::Hero* findHero= (ServerProto::Logic::Hero*)GetServerHero(heroId);
	findHero->mutable_property()->MergeFrom(heroProperty);
}


//hero soul
const ServerProto::Logic::Soul* Player::GetHeroSoul(uint itemId)const 
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().herosouls())
	{
		const ServerProto::Logic::Soul* soul=&(*i);

		if (soul->itemid()==itemId)
		{
			return soul;
		}
	}

	Log::LogErrorFormat("Not find hero soul from item id %d",itemId);
	return NULL;
}

void Player::AddHeroSoul( const ServerProto::Logic::Soul& hireSoul )
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().herosouls())
	{
		ServerProto::Logic::Soul* soul = (ServerProto::Logic::Soul*)(&(*i));
		if (soul->itemid()==hireSoul.itemid())
		{
			uint num = soul->num();
			soul->set_num(num+hireSoul.num());
			return;
		}
	}

	ServerProto::Logic::Soul* soul = NULL;
	soul = mPlayerData.mutable_serverplayer()->add_herosouls();
	soul->set_itemid(hireSoul.itemid());
	soul->set_num(hireSoul.num());
}

void Player::UpdateHeroSoul(const ServerProto::Logic::Soul& soul)
{
	ServerProto::Logic::Soul* finSoul = (ServerProto::Logic::Soul*)GetHeroSoul(soul.itemid());
	if (finSoul!=NULL)
	{
		finSoul->MergeFrom(soul);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateHeroSoul: not find hero soul itemId %d",soul.itemid());
	}
}

void Player::RemoveHeroSoul(const ServerProto::Logic::Soul &heroSoul)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().herosouls())
	{
		ServerProto::Logic::Soul* soul=(ServerProto::Logic::Soul*)(&(*i));
		if (soul->itemid()==heroSoul.itemid())
		{
			if (soul->num()==heroSoul.num())
			{
				Proto::RemoveItem<ServerProto::Logic::Soul>(mPlayerData.mutable_serverplayer()->mutable_herosouls(),index);
			} 
			else if(soul->num()>heroSoul.num())
			{
				mPlayerData.mutable_serverplayer()->mutable_herosouls(index)->set_num(soul->num()-heroSoul.num());
			} 
			else if (soul->num()<heroSoul.num())
			{
				Log::LogError("the soulNumber is error!");
			}
			return;
		}
		index++;
	}
	Log::LogErrorFormat("Not find heroSoul %d in player list",heroSoul.itemid());
}

//talent

void Player::AddPet(const ServerProto::Logic::Pet& hirepet)
{
	bool isHave = false;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().pets())
	{
		ServerProto::Logic::Pet* pet=(ServerProto::Logic::Pet*)(&(*i));
		if (pet->petitemid()==hirepet.petitemid())
		{
			isHave = true;
			pet->CopyFrom(hirepet);
			break;
		}
	}
	if (!isHave)
	{
		ServerProto::Logic::Pet* petS = mPlayerData.mutable_serverplayer()->add_pets();
		petS->CopyFrom(hirepet);
	}

	UpdatePet();
}

void Player::UpdatePet(const ServerProto::Logic::Pet& pet)
{
	bool isHave = false;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().pets())
	{
		ServerProto::Logic::Pet* petFind=(ServerProto::Logic::Pet*)(&(*i));
		if (petFind->petitemid()==pet.petitemid())
		{
			petFind->MergeFrom(pet);
			isHave = true;
			UpdatePet();
			break;
		}
	}

	if (!isHave)
	{
		AddPet(pet);
	}
}

void Player::RemovePet(const uint itemId,bool isUpdate)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().pets())
	{
		ServerProto::Logic::Pet* pet=(ServerProto::Logic::Pet*)(&(*i));
		if (pet->petitemid()==itemId)
		{
			Proto::RemoveItem<ServerProto::Logic::Pet>(mPlayerData.mutable_serverplayer()->mutable_pets() /*->mutable_heroes()*/,index);

			if (isUpdate)
			{
				UpdatePet();
			}
			return;
		}
		index++;
	}
	Log::LogErrorFormat("Not find talent %d in player list",itemId);
}

const ServerProto::Logic::Pet*Player:: GetServerPet(uint itemId)const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().pets())
	{
		const ServerProto::Logic::Pet* pet=&(*i);
		if (pet->petitemid()==itemId)
		{
			return pet;
		}
	}
	return NULL;
}

bool Player::IsPetOpen(uint itemId)
{
	return mOpenPetsId.Contains(itemId);
}

//item
const ServerProto::Logic::Item* Player::GetServerItem( uint id ) const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().items())
	{
		const ServerProto::Logic::Item* item = &(*i);
		if (item->itemid()==id)
		{
			return item;
		}
	}
	return NULL;
}

const int Player::GetServerItemNum( void ) const
{
	return mPlayerData.serverplayer().items_size();
}

const ServerProto::Logic::Item* Player::GetServerItemByIndex( uint index ) const
{
	return &(mPlayerData.serverplayer().items(index));
}

void Player::AddItem( uint itemId,uint num )
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().items())
	{
		ServerProto::Logic::Item* item = (ServerProto::Logic::Item*)(&(*i));
		if (item->itemid()==itemId)
		{
			uint numT = item->num();
			item->set_num(numT+num);
			return;
		}
	}

	ServerProto::Logic::Item* item = NULL;
	item = mPlayerData.mutable_serverplayer()->add_items();
	item->set_itemid(itemId);
	item->set_num(num);
}

void Player::RemoveItem( uint itemId,uint num )
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().items())
	{
		ServerProto::Logic::Item* item = (ServerProto::Logic::Item*)(&(*i));
		if (item->itemid()==itemId)
		{
			uint numT = item->num();

			if (numT-num == 0)
			{
				Proto::RemoveItem<ServerProto::Logic::Item>(mPlayerData.mutable_serverplayer()->mutable_items(),index);
			}
			else
			{
				item->set_num(numT-num);
			}
			return;;
		}
		index++;
	}
}

void Player::UpdateItem(const ServerProto::Logic::Item& changeItem)
{
	ServerProto::Logic::Item* findItem = (ServerProto::Logic::Item*)GetServerItem(changeItem.itemid());
	if (findItem!=NULL)
	{
		findItem->MergeFrom(changeItem);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateItem not find item id %d",changeItem.itemid());
	}
}

//equip
const ServerProto::Logic::Equip* Player::GetServerEquip( uint64 equipId )const
{
	const ServerProto::Logic::Equip* equip = mIDEquipDict.TryGetValueWithFailed(equipId,NULL);
	if (equip==NULL)
	{
		Log::LogErrorFormat("Not find equip from itemid %llu",equipId);
	}
	return equip;
}

void Player::UpdateEquip(const ServerProto::Logic::Equip& strengthenEquip)
{
	ServerProto::Logic::Equip* equip= (ServerProto::Logic::Equip*)GetServerEquip(strengthenEquip.id());
	equip->MergeFrom(strengthenEquip);
}

void Player::RemoveEquip(const uint64 equipId,bool isUpdate/*=true*/)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().equips())
	{
		ServerProto::Logic::Equip* equipFind = (ServerProto::Logic::Equip*)(&(*i));
		if (equipFind->id()==equipId)
		{
			Proto::RemoveItem<ServerProto::Logic::Equip>(mPlayerData.mutable_serverplayer()->mutable_equips(),index);
			if (isUpdate)
			{
				UpdateEquip();
			}
			return;
		}
		index++;
	}
	Log::LogErrorFormat("Not find equip %llu in player list",equipId);
}

const ServerProto::Logic::Hero* Player::GetEquipBelongHero(const ServerProto::Logic::Equip* equip)const
{
	if (!mEquipHeroDict.ContainsKey(equip))
	{
		Log::LogError("Can not find hero in Player:GetEquipBelongHero");
		return NULL;
	}
	ServerProto::Logic::Hero* heroFindOri = (ServerProto::Logic::Hero*)mEquipHeroDict.GetValue(equip);
	return heroFindOri;
}

void Player::RemoveEquips( const List<uint64>& equipIds )
{
	List<int> removeIndexs;
	FOR_EACH_COLLECTION(i,equipIds)
	{
		RemoveEquip(*i,false);
	}
	UpdateEquip();
}

void Player::ClearRoleEquip(uint64 heroId)
{
	ServerProto::Logic::Hero* heroFindTar = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	if (heroFindTar!=NULL)
	{
		FOR_EACH_COLLECTION_STL(i,heroFindTar->equips())
		{
			ServerProto::Logic::Equip* equip = (ServerProto::Logic::Equip*)(&(*i));
			mPlayerData.mutable_serverplayer()->add_equips()->CopyFrom(*equip);
		}
		heroFindTar->clear_equips();
	}
	UpdateEquip();
}

void Player::SetServerEquip(uint64 heroId,uint64 equipId,ServerProto::Logic::EquipType equipType)
{
	ServerProto::Logic::Hero* heroFindTar = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	const ServerProto::Logic::Equip* equipFindTar = mIDEquipDict.TryGetValueWithFailed(equipId,NULL);
	if (equipFindTar==NULL)
	{
		Log::LogError("Can not find equip");
	}
	if (!mEquipHeroDict.ContainsKey(equipFindTar))
	{
		Log::LogError("Can not find aura in EquipHeroDict");
	}
	ServerProto::Logic::Hero* heroFindOri = (ServerProto::Logic::Hero*)mEquipHeroDict.GetValue(equipFindTar);
	if (heroFindTar!=NULL && heroFindTar==heroFindOri)
	{
		Log::LogError("set equip is self hero.");
	}
	int  arrayIndex = 0;
	FOR_EACH_COLLECTION_STL(i,heroFindTar->equips())
	{
		const ServerProto::Logic::Equip& equip = *i;
		const ServerProto::Config::EquipConfigItem* equipConfig = EquipConfig::Instance().GetEquipConfigItem(equip.equipitemid());
		if (equipConfig->type()==equipType)
		{
			mPlayerData.mutable_serverplayer()->add_equips()->CopyFrom(heroFindTar->equips(arrayIndex));
			Proto::RemoveItem<ServerProto::Logic::Equip>(heroFindTar->mutable_equips(),arrayIndex);
			break;
		}
		arrayIndex++;
	}
	if (heroFindOri!=NULL)
	{
		int auraIndex = 0;
		FOR_EACH_COLLECTION_STL(i,heroFindOri->equips())
		{
			const ServerProto::Logic::Equip& equip = *i;
			if (equip.id()==equipId)
			{
				heroFindTar->add_equips()->CopyFrom(heroFindOri->equips(auraIndex));
				Proto::RemoveItem<ServerProto::Logic::Equip>(heroFindOri->mutable_equips(),auraIndex);
				break;
			}
			auraIndex++;
		}	
	}
	else
	{
		arrayIndex = 0;
		FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().equips())
		{
			const ServerProto::Logic::Equip& equip = *i;
			if (equip.id()==equipId)
			{
				heroFindTar->add_equips()->CopyFrom(mPlayerData.serverplayer().equips(arrayIndex));
				Proto::RemoveItem<ServerProto::Logic::Equip>(mPlayerData.mutable_serverplayer()->mutable_equips(),arrayIndex);
				break;
			}
			arrayIndex++;
		}
	}

	UpdateEquip();
}

void Player::AddEquip( const ServerProto::Logic::Equip& equip )
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().equips())
	{
		ServerProto::Logic::Equip* equipFind = (ServerProto::Logic::Equip*)(&(*i));
		if (equipFind->id()==equip.id())
		{
			equipFind->CopyFrom(equip);
			return;
		}
	}

	ServerProto::Logic::Equip* equipIn = mPlayerData.mutable_serverplayer()->add_equips();
	equipIn->CopyFrom(equip);
	UpdateEquip();
}

//aura


void Player::RemoveAura(const uint64 auraId,bool isUpdate)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().auras())
	{
		ServerProto::Logic::Aura* auraFind = (ServerProto::Logic::Aura*)(&(*i));
		if (auraFind->id()==auraId)
		{
			Proto::RemoveItem<ServerProto::Logic::Aura>(mPlayerData.mutable_serverplayer()->mutable_auras(),index);
			if (isUpdate)
			{
				UpdateAura();
			}
			return;
		}
		index++;
	}

	Log::LogErrorFormat("Not find aura %llu in player list",auraId);
}

void Player::RemoveAuras(const List<uint64>& auraIds)
{

	FOR_EACH_COLLECTION(i,auraIds)
	{
		RemoveAura(*i,false);
	}

	UpdateAura();
}

void Player::AddAura( const ServerProto::Logic::Aura& aura )
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().auras())
	{
		ServerProto::Logic::Aura* auraFind = (ServerProto::Logic::Aura*)(&(*i));
		if (auraFind->id()==aura.id())
		{
			auraFind->CopyFrom(aura);
			return;
		}
	}

	ServerProto::Logic::Aura* auraIn = mPlayerData.mutable_serverplayer()->add_auras();
	auraIn->CopyFrom(aura);

	UpdateAura();
}

void Player::SetServerAura(uint64 heroId,uint64 auraId,int index)
{
	//////////////////////////////////////////////////////////////////////////
	ServerProto::Logic::Hero* heroFindTar = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	const ServerProto::Logic::Aura* auraFindTar = mIDAurasDict.TryGetValueWithFailed(auraId,NULL);
	if (auraFindTar==NULL)
	{
		Log::LogError("Can not find aura");
	}
	if (!mAuraHeroDict.ContainsKey(auraFindTar))
	{
		Log::LogError("Can not find aura in AuraHeroDict");
	}
	ServerProto::Logic::Hero* heroFindOri = (ServerProto::Logic::Hero*)mAuraHeroDict.GetValue(auraFindTar);
	if (heroFindTar!=NULL && heroFindTar==heroFindOri)
	{
		Log::LogError("set area is self hero.");
	}

	int arrayIndex = 0;
	FOR_EACH_COLLECTION_STL(i,heroFindTar->auras())
	{
		const ServerProto::Logic::Aura& aura = *i;
		if (aura.pos()==index)
		{
			mPlayerData.mutable_serverplayer()->add_auras()->CopyFrom(heroFindTar->auras(arrayIndex));
			Proto::RemoveItem<ServerProto::Logic::Aura>(heroFindTar->mutable_auras(),arrayIndex);
			break;
		}
		arrayIndex++;
	}

	if (heroFindOri!=NULL)
	{
		int auraIndex = 0;
		FOR_EACH_COLLECTION_STL(i,heroFindOri->auras())
		{
			const ServerProto::Logic::Aura& aura = *i;
			if (aura.id()==auraId)
			{
				heroFindOri->mutable_auras(auraIndex)->set_pos(index);
				heroFindTar->add_auras()->CopyFrom(heroFindOri->auras(auraIndex));
				Proto::RemoveItem<ServerProto::Logic::Aura>(heroFindOri->mutable_auras(),auraIndex);
				break;
			}
			auraIndex++;
		}
	}
	else
	{
		arrayIndex = 0;
		FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().auras())
		{
			const ServerProto::Logic::Aura& aura = *i;
			if (aura.id()==auraId)
			{
				mPlayerData.mutable_serverplayer()->mutable_auras(arrayIndex)->set_pos(index);
				heroFindTar->add_auras()->CopyFrom(mPlayerData.serverplayer().auras(arrayIndex));

				Proto::RemoveItem<ServerProto::Logic::Aura>(mPlayerData.mutable_serverplayer()->mutable_auras(),arrayIndex);
				break;
			}
			arrayIndex++;
		}
	}
	UpdateAura();
}

const ServerProto::Logic::Aura* Player::GetServerAura(uint64 auraId)const
{
	const ServerProto::Logic::Aura* auraFind = mIDAurasDict.TryGetValueWithFailed(auraId,NULL);

	if (auraFind==NULL)
	{
		Log::LogErrorFormat("Player:GetServerAura:not find aura from aura id %llu",auraId);
	}

	return auraFind;
}

const ServerProto::Logic::Hero* Player::GetAuraBelongHero(const ServerProto::Logic::Aura* aura)const
{
	if (!mAuraHeroDict.ContainsKey(aura))
	{
		Log::LogError("Can not find aura in Player:GetAuraBelongHero");
		return NULL;
	}
	ServerProto::Logic::Hero* heroFindOri = (ServerProto::Logic::Hero*)mAuraHeroDict.GetValue(aura);
	return heroFindOri;
}

//aura fragment
const ServerProto::Logic::AuraFragment* Player::GetServerAuraFragment(uint auraFragmentItemId)const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().fragments())
	{
		const ServerProto::Logic::AuraFragment& auraFragment = *i;
		if (auraFragment.auraitemid()==auraFragmentItemId)
		{
			return &auraFragment;
		}
	}

	return NULL;
}

void Player::AddAuraFragment(const ServerProto::Logic::AuraFragment& auraFragment)
{
	ServerProto::Logic::AuraFragment* findAuraFragment = (ServerProto::Logic::AuraFragment*)GetServerAuraFragment(auraFragment.auraitemid());
	if (findAuraFragment==NULL)
	{
		findAuraFragment = mPlayerData.mutable_serverplayer()->add_fragments();
		findAuraFragment->CopyFrom(auraFragment);
	}
	else
	{
		findAuraFragment->set_num(findAuraFragment->num()+auraFragment.num());
	}
}

void Player::UpdateAuraFragment(const ServerProto::Logic::AuraFragment& auraFragment)
{
	ServerProto::Logic::AuraFragment* findAuraFragment = (ServerProto::Logic::AuraFragment*)GetServerAuraFragment(auraFragment.auraitemid());
	if (findAuraFragment!=NULL)
	{
		findAuraFragment->MergeFrom(auraFragment);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateAuraFragment: not find aura fragment id %d",auraFragment.auraitemid());
	}
}

void Player::RemoveAuraFragment(uint itemId,uint num)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().fragments())
	{
		ServerProto::Logic::AuraFragment* auraFragment = (ServerProto::Logic::AuraFragment*)(&(*i));
		if (auraFragment->auraitemid()==itemId)
		{
			uint numT = auraFragment->num();

			if (numT-num == 0)
			{
				Proto::RemoveItem<ServerProto::Logic::AuraFragment>(mPlayerData.mutable_serverplayer()->mutable_fragments(),index);
			}
			else
			{
				auraFragment->set_num(numT-num);
			}
			return;
		}
		index++;
	}
}

//rune

const ServerProto::Logic::Rune* Player::GetServerRune(uint64 runeId)const
{
	const ServerProto::Logic::Rune* runeFind = mIDRunesDict.TryGetValueWithFailed(runeId,NULL);
	if (runeFind==NULL)
	{
		Log::LogErrorFormat("Not find rune from rune id %llu",runeId);
	}
	return runeFind;
}

const ServerProto::Logic::Hero* Player::GetRuneBelongHero(const ServerProto::Logic::Rune* rune)const
{
	if (!mRuneHeroDict.ContainsKey(rune))
	{
		Log::LogError("Can not find rune in Player:GetRuneIdBelongHero");
		return NULL;
	}
	ServerProto::Logic::Hero* hero = (ServerProto::Logic::Hero*)mRuneHeroDict.GetValue(rune);
	return hero;
}

void Player::AddRune(const ServerProto::Logic::Rune& rune,bool isUpdate)
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().heroes())
	{
		const ServerProto::Logic::Hero& hero=*i;
		FOR_EACH_COLLECTION_STL(j,hero.runes())
		{
			ServerProto::Logic::Rune* runeFind = (ServerProto::Logic::Rune*)(&(*j));
			if (runeFind->id()==rune.id())
			{
				runeFind->CopyFrom(rune);
				return;
			}
		}
	}

	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().runes())
	{
		ServerProto::Logic::Rune* runeFind = (ServerProto::Logic::Rune*)(&(*i));
		if (runeFind->id()==rune.id())
		{
			runeFind->CopyFrom(rune);
			return;
		}
	}

	ServerProto::Logic::Rune* runeIn = mPlayerData.mutable_serverplayer()->add_runes();
	runeIn->CopyFrom(rune);
	if (isUpdate)
	{
		UpdateRune();
	}
}

void Player::UpdateRune(const ServerProto::Logic::Rune& rune)
{
	ServerProto::Logic::Rune* findRune = (ServerProto::Logic::Rune*)GetServerRune(rune.id());
	if (findRune!=NULL)
	{
		findRune->MergeFrom(rune);
	}
	else
	{
		Log::LogErrorFormat("Player:UpdateRune not find rune id %llu",rune.id());
	}
}

void Player::SetServerRune(uint64 heroId,uint64 targetRuneId,int forcePos)
{
	ServerProto::Logic::Hero* heroFindTar = (ServerProto::Logic::Hero*)GetServerHero(heroId);
	const ServerProto::Logic::Rune* runeFindTar = mIDRunesDict.TryGetValueWithFailed(targetRuneId,NULL);
	if (runeFindTar==NULL)
	{
		Log::LogError("Can not find rune");
	}
	if (!mRuneHeroDict.ContainsKey(runeFindTar))
	{
		Log::LogError("Can not find rune in mRuneHeroDict");
	}
	ServerProto::Logic::Hero* heroFindOri = (ServerProto::Logic::Hero*)mRuneHeroDict.GetValue(runeFindTar);
	if (heroFindTar!=NULL && heroFindTar==heroFindOri)
	{
		Log::LogError("set rune is self hero.");
	}

	int  arrayIndex = 0;
	FOR_EACH_COLLECTION_STL(i,heroFindTar->runes())
	{
		const ServerProto::Logic::Rune& rune = *i;
		if (rune.forcepos()==forcePos)
		{
			heroFindTar->mutable_runes(arrayIndex)->set_forcepos(-1);
			mPlayerData.mutable_serverplayer()->add_runes()->CopyFrom(heroFindTar->runes(arrayIndex));
			Proto::RemoveItem<ServerProto::Logic::Rune>(heroFindTar->mutable_runes(),arrayIndex);
			break;
		}
		arrayIndex++;
	}

	if (heroFindOri!=NULL)
	{
		int runeIndex = 0;
		FOR_EACH_COLLECTION_STL(i,heroFindOri->runes())
		{
			const ServerProto::Logic::Rune& rune = *i;
			if (rune.id()==targetRuneId)
			{
				heroFindOri->mutable_runes(runeIndex)->set_forcepos(forcePos);
				heroFindTar->add_runes()->CopyFrom(heroFindOri->runes(runeIndex));
				Proto::RemoveItem<ServerProto::Logic::Rune>(heroFindOri->mutable_runes(),runeIndex);
				break;
			}
			runeIndex++;
		}	
	}
	else
	{
		arrayIndex = 0;
		FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().runes())
		{
			const ServerProto::Logic::Rune& rune = *i;
			if (rune.id()==targetRuneId)
			{
				mPlayerData.mutable_serverplayer()->mutable_runes(arrayIndex)->set_forcepos(forcePos);
				heroFindTar->add_runes()->CopyFrom(mPlayerData.serverplayer().runes(arrayIndex));
				Proto::RemoveItem<ServerProto::Logic::Rune>(mPlayerData.mutable_serverplayer()->mutable_runes(),arrayIndex);
				break;
			}
			arrayIndex++;
		}
	}

	UpdateRune();
}

void Player::RemoveRune(const uint64 runeId,bool isUpdate)
{
	int index = 0;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().runes())
	{
		ServerProto::Logic::Rune* runeFind = (ServerProto::Logic::Rune*)(&(*i));
		if (runeFind->id()==runeId)
		{
			Proto::RemoveItem<ServerProto::Logic::Rune>(mPlayerData.mutable_serverplayer()->mutable_runes(),index);
			if (isUpdate)
			{
				UpdateRune();
			}
			return;
		}
		index++;
	}

	Log::LogErrorFormat("Not find rune %llu in player list",runeId);
}

void Player::RemoveRunes(const List<uint64>& runeIds)
{
	
	FOR_EACH_COLLECTION(i,runeIds)
	{
		RemoveRune(*i,false);
	}

	UpdateRune();
}


//mail
void Player::UpdateMailMaxId()
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.promptmails())
	{
		const ServerProto::Logic::Mail& mail=*i;
		mMailPromptMaxId=Math::Max(mMailPromptMaxId,mail.id());
	}
	FOR_EACH_COLLECTION_STL(i,mPlayerData.rewardmails())
	{
		const ServerProto::Logic::Mail& mail=*i;
		mMailRewardMaxId=Math::Max(mMailRewardMaxId,mail.id());
	}
}


const ServerProto::Logic::Mail* Player::GetPromptMail( uint64 mailId )const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.promptmails())
	{
		const ServerProto::Logic::Mail& mail = *i;
		if (mail.id()==mailId)
		{
			return &mail;
		}
	}

	Log::LogErrorFormat("Can not find mail %llu",mailId);
	return NULL;
}

const ServerProto::Logic::Mail* Player::GetRewardMail( uint64 mailId )const
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.rewardmails())
	{
		const ServerProto::Logic::Mail& mail = *i;
		if (mail.id()==mailId)
		{
			return &mail;
		}
	}

	Log::LogErrorFormat("Can not find mail %llu",mailId);
	return NULL;
}


const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Mail >& Player::GetPromptMails() const
{
	return mPlayerData.promptmails();
}

const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Mail >& Player::GetRewardMails() const
{
	return mPlayerData.rewardmails();
}

void Player::AddNoticeMails( const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Mail >& newMails )
{
	FOR_EACH_COLLECTION_STL(i,newMails)
	{
		const ServerProto::Logic::Mail& mail=*i;

		if (mail.id()<=mMailPromptMaxId)
		{
			continue;
		}

		mMailPromptMaxId=Math::Max(mMailPromptMaxId,mail.id());
		mPlayerData.add_promptmails()->CopyFrom(mail);
	}

	mPlayerData.set_unreadmailcount(mPlayerData.unreadmailcount()+newMails.size());

	UpdateNoticeMail();
	UpdateMailMaxId();
}

void Player::AddRewardMails( const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Mail >& newMails )
{
	FOR_EACH_COLLECTION_STL(i,newMails)
	{
		const ServerProto::Logic::Mail& mail=*i;

		if (mail.id()<=mMailRewardMaxId)
		{
			continue;
		}

		mMailRewardMaxId=Math::Max(mMailRewardMaxId,mail.id());
		mPlayerData.add_rewardmails()->CopyFrom(mail);
	}

	mPlayerData.set_unreadmailcount(mPlayerData.unreadmailcount()+newMails.size());

	UpdateRewardMail();
	UpdateMailMaxId();
}

void Player::ResetMailUnreadCount()
{
	mPlayerData.set_unreadmailcount(0);
}

void Player::RemoveNoticeMail( uint64 id )
{
	FOR_EACH_SIZE(i,(uint)mPlayerData.promptmails_size())
	{
		const ServerProto::Logic::Mail& mail = mPlayerData.promptmails(i);
		if (mail.id() == id)
		{
			Proto::RemoveItem<ServerProto::Logic::Mail>(mPlayerData.mutable_promptmails(),i);
			break;
		}
	}
}

void Player::RemoveNoticeMails( const List<uint64>& mailIds )
{
	FOR_EACH_COLLECTION(i,mailIds)
	{
		RemoveNoticeMail(*i);
	}
}

void Player::UpdateNoticeMail()
{
	int deleteCount = mPlayerData.promptmails_size() - ServerGameConfig::Instance().MailMaxCount();
	deleteCount = deleteCount<=0?0:deleteCount;
	FOR_EACH_SIZE(i,(uint)deleteCount)
	{
		Proto::RemoveItem<ServerProto::Logic::Mail>(mPlayerData.mutable_promptmails(),i);
	}
}

void Player::RemoveRewardMail( uint64 id )
{
	FOR_EACH_SIZE(i,(uint)mPlayerData.rewardmails_size())
	{
		ServerProto::Logic::Mail mail = mPlayerData.rewardmails(i);
		if (mail.id() == id)
		{
			Proto::RemoveItem<ServerProto::Logic::Mail>(mPlayerData.mutable_rewardmails(),i);
			break;
		}
	}
}

void Player::RemoveRewardMails( const List<uint64>& mailIds )
{
	FOR_EACH_COLLECTION(i,mailIds)
	{
		RemoveRewardMail(*i);
	}
}

void Player::UpdateRewardMail()
{

}

//notice
const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::SystemNotice >& Player::GetSystemNotices() const
{
	return mPlayerData.systemnotices();
}

const List<ServerProto::Logic::PlayerNotice,NoCompare<ServerProto::Logic::PlayerNotice>>& Player::GetPlayerNotices() const
{
	return mPlayerNotices;
}

void Player::UpdateSystemNoticeMaxId()
{
	FOR_EACH_COLLECTION_STL(i,mPlayerData.systemnotices())
	{
		const ServerProto::Logic::SystemNotice& item=*i;
		mSystemNoticeMaxId=Math::Max(mSystemNoticeMaxId,item.id());
	}
}

void Player::UpdateSystemNotice()
{
	FOR_EACH_SIZE(i,(uint)mPlayerData.systemnotices_size())
	{
		const ServerProto::Logic::SystemNotice& item = mPlayerData.systemnotices(i);
		if (GetCurServerSystemTime()>item.endtime())
		{
			Proto::RemoveItem<ServerProto::Logic::SystemNotice>(mPlayerData.mutable_systemnotices(),i);
			--i;
		}
	}
}




void Player::AddSystemNotices( const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::SystemNotice >& items ,uint version)
{
	if(mPlayerData.systemnoticeversion()!=version&&version!=0)
	{
		mPlayerData.clear_systemnotices();
		mSystemNoticeMaxId=0;
		mPlayerData.set_systemnoticeversion(version);
	}

	FOR_EACH_COLLECTION_STL(i,items)
	{
		const ServerProto::Logic::SystemNotice& item=*i;

		if (item.id()<=mSystemNoticeMaxId)
		{
			continue;
		}

		mSystemNoticeMaxId=Math::Max(mSystemNoticeMaxId,item.id());
		mPlayerData.add_systemnotices()->CopyFrom(item);
	}

	UpdateSystemNotice();
}

void Player::RemoveSystemNotice( uint64 id )
{
	FOR_EACH_SIZE(i,(uint)mPlayerData.systemnotices_size())
	{
		const ServerProto::Logic::SystemNotice& notice = mPlayerData.systemnotices(i);
		if (notice.id() == id)
		{
			Proto::RemoveItem<ServerProto::Logic::SystemNotice>(mPlayerData.mutable_systemnotices(),i);
			break;
		}
	}
}

void Player::AddPlayerNotices( const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::PlayerNotice >& items )
{
	FOR_EACH_COLLECTION_STL(i,items)
	{
		const ServerProto::Logic::PlayerNotice& item=*i;

		if (item.id()<=GetPlayerNoticeMaxId())
		{
			continue;
		}

		mPlayerData.set_playernoticemaxid(Math::Max(mPlayerData.playernoticemaxid(),item.id()));
		mPlayerNotices.Add(item);
	}
}

void Player::RemovePlayerNotice( uint64 id )
{
	FOR_EACH_SIZE(i,mPlayerNotices.GetCount())
	{
		const ServerProto::Logic::PlayerNotice& notice = mPlayerNotices.Get(i);
		if (notice.id() == id)
		{
			mPlayerNotices.RemoveAt(i);
			break;
		}
	}
}

void Player::RemovePlayerNotices(const List<uint64>& noticeIds)
{
	FOR_EACH_COLLECTION(i,noticeIds)
	{
		RemovePlayerNotice(*i);
	}
}

//新手引导
void Player::UpdateGuideIds()
{
	mGuideIdsDict.Clear();
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().finishguideids())
	{
		uint groupId = *i;
		mGuideIdsDict.Add(groupId,NULL);
	}
}

void Player::AddGuideId( uint id )
{
	bool isFind = false;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().finishguideids())
	{
		if (*i==id)
		{
			isFind = true;
			break;
		}
	}
	if (!isFind)
	{
		mPlayerData.mutable_serverplayer()->add_finishguideids(id);
		UpdateGuideIds();
	}
}

bool Player::IsGuideFinish( uint guideId )
{
	bool isFind = false;
	FOR_EACH_COLLECTION_STL(i,mPlayerData.serverplayer().finishguideids())
	{
		if (*i==guideId)
		{
			isFind = true;
			break;
		}
	}

	return isFind;
}

bool Player::IsGuideFinishAll()
{
	return mPlayerData.serverplayer().isfinishallguide();
}

void Player::SynchronizeServerSystemTime( uint time )
{
	mCurServerSystemTime = time;
	mAccumulateServerSystemTime = 0.0f;
	mIsLoopSystemTime = true;
}

void Player::AddAward( const ServerProto::Logic::Award& award ,PaperAnalyticsAwardReason reason/*=PaperAnalyticsReason::Unknown*/)
{
	switch (award.awardtype())
	{
	case ServerProto::Logic::ItemId:
		{
			AddItem(award.awarditem().itemid(),award.awarditem().num());
		}
		break;
	case ServerProto::Logic::AuraId:
		{
			AddAura(award.awardaura());
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			AddEquip(award.awardequip());
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			AddHero(award.awardhero());
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			AddHeroSoul(award.awardherosoul());
		}
		break;
	case ServerProto::Logic::RuneId:
		{

		}
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			AddAuraFragment(award.awardfragment());
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			mPlayerData.mutable_serverplayer()->set_money(mPlayerData.serverplayer().money()+award.awardmoney());
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			mPlayerData.mutable_serverplayer()->set_diamond(mPlayerData.serverplayer().diamond()+award.awarddiamond());
			Analytics::RewardCurrency(award.awarddiamond(),reason.ToString());
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		{
			mPlayerData.mutable_serverplayer()->set_pvepower(mPlayerData.serverplayer().pvepower()+award.awardpvepower());
		}
		break;
	case ServerProto::Logic::PVPPowerId:
		{
			mPlayerData.mutable_serverplayer()->set_pvppower(mPlayerData.serverplayer().pvppower()+award.awardpvppower());
		}
		break;
	default:
		break;
	}
}

const uint32 Player::GetTodayTotalSeconds()
{
	uint32   currentTime = GetCurServerSystemTime();
	DateTime currentTimeDateTime(currentTime,false);	//convert to local time
	DateTime todayBeginTime( currentTimeDateTime.GetYears(), currentTimeDateTime.GetMonths(), currentTimeDateTime.GetDays(), 0, 0, 0,false);
	return (uint32)(currentTime-todayBeginTime.GetTotalSeconds());
}

const uint32 Player::GetTodayTotalDaysRegister()
{
	uint32   currentTime = GetCurServerSystemTime();
	DateTime currentTimeDateTime(currentTime,false);
	DateTime todayBeginTime( currentTimeDateTime.GetYears(), currentTimeDateTime.GetMonths(), currentTimeDateTime.GetDays(), 0, 0, 0,false);

	uint32 createTime = this->GetServerPlayer().createplayertime();
	DateTime createTimeDateTime(createTime,false);
	DateTime createDayBeginTimeDateTime( createTimeDateTime.GetYears(), createTimeDateTime.GetMonths(), createTimeDateTime.GetDays(), 0, 0, 0,false);

	TimeSpan span = todayBeginTime - createDayBeginTimeDateTime;

	return span.GetDays();
}

void Player::SetBloodyGroupInfo( const ServerProto::Logic::GetBloodyChallengeGroupResponse& val )
{
	mBloodyGroupInfo.CopyFrom(val);
}

void Player::ClearBloodyGroupInfo()
{
	mBloodyGroupInfo.clear_grouptype();
}

void Player::ClearBloodyFiveLayersGifts()
{
	mBloodySettlementResponse.clear_fivelayersgifts();
}

void Player::ClearBloodyMissionAwards()
{
	mBloodySettlementResponse.clear_missionawards();
}


void Player::KnockClock(ServerProto::Logic::SignMode newMode,uint signTimes)
{
	GetServerPlayerMutable()->set_istodaysign(true);
	GetServerPlayerMutable()->set_signcontinuetimes(signTimes);
	GetServerPlayerMutable()->set_signmode(newMode);
	MarkChanged();
}

Medusa::FileId Player::GetIconFileId( ServerProto::Logic::IdType idType,uint itemId )
{
	FileId fileId;
	switch (idType)
	{
	case ServerProto::Logic::ItemId:
		{
			fileId.Name = "ItemIcon.png";
			uint iconId=ItemConfig::Instance().GetItemIconId(itemId);
			fileId.Order = iconId;
		}
		break;
	case ServerProto::Logic::SkillId:
		{
			fileId.Name = "SkillIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::AuraId:
		{
			fileId.Name = "AuraIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			fileId.Name = "EquipIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			fileId.Name = "HeroIcon.png";
			const ServerProto::Config::HeroConfigItem* heroConfig= HeroConfig::Instance().GetHeroConfigItem(itemId);
			itemId=heroConfig->herofaceiconid();
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::PetId:
		{
			fileId.Name = "PetIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			fileId.Name = "HeroIcon.png";
			const ServerProto::Config::HeroConfigItem* heroConfig= HeroConfig::Instance().GetHeroConfigItem(itemId);
			itemId=heroConfig->herofaceiconid();
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::RuneId:
		{
			fileId.Name = "RuneIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			fileId.Name = "AuraIcon.png";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			fileId.Name = "GoldIcon.png";
			fileId.Order = 0;
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			fileId.Name = "PointVolumeIcon.png";
			fileId.Order = 0;
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		{
			fileId.Name = "PVEPowerIcon.png";
			fileId.Order = 0;
		}
		break;
	case ServerProto::Logic::PVPPowerId:
		{
			fileId.Name = "PVPPowerIcon.png";
			fileId.Order = 0;
		}
		break;
	default:
		break;
	}
	return fileId;
}

FileId Player::GetIconFileId( const ServerProto::Logic::Award& award )
{
	uint itemId = 0;
	switch (award.awardtype())
	{
	case ServerProto::Logic::ItemId:
		{
			itemId = award.awarditem().itemid();
		}
		break;
	case ServerProto::Logic::SkillId:
		break;
	case ServerProto::Logic::AuraId:
		{
			itemId = award.awardaura().auraitemid();
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			itemId = award.awardequip().equipitemid();
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			itemId = award.awardhero().heroitemid();
		}
		break;
	case ServerProto::Logic::PetId:
		{
			itemId = award.awardpet().petitemid();
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			itemId = award.awardherosoul().itemid();
		}
		break;
	case ServerProto::Logic::RuneId:
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			itemId = award.awardfragment().auraitemid();
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			itemId = 0;
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			itemId = 0;
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		itemId = 0;
		break;
	case ServerProto::Logic::PVPPowerId:
		itemId = 0;
		break;
	default:
		break;
	}

	return GetIconFileId(award.awardtype(),itemId);
}

FileId Player::GetStringTableFileId( ServerProto::Logic::IdType idType,uint itemId )
{
	FileId fileId;
	switch (idType)
	{
	case ServerProto::Logic::ItemId:
		{
			fileId.Name = "ItemName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::SkillId:
		{
			fileId.Name = "SkillName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::AuraId:
		{
			fileId.Name = "AuraName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			fileId.Name = "EquipName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			fileId.Name = "HeroName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::PetId:
		{
			fileId.Name = "PetName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			fileId.Name = "HeroName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::RuneId:
		{
			fileId.Name = "RuneName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			fileId.Name = "AuraName";
			fileId.Order = itemId;
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			fileId.Name = "PlayerMoney";
			fileId.Order = 0;
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			fileId.Name = "PlayerDiamond";
			fileId.Order = 0;
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		{
			fileId.Name = "PlayerPvePower";
			fileId.Order = 0;
		}

		break;
	case ServerProto::Logic::PVPPowerId:
		{
			fileId.Name = "PlayerPvpPower";
			fileId.Order = 0;
		}
		break;
	default:
		break;
	}
	return fileId;
}

FileId Player::GetStringTableFileId( const ServerProto::Logic::Award& award )
{
	uint itemId = 0;
	switch (award.awardtype())
	{
	case ServerProto::Logic::ItemId:
		{
			itemId = award.awarditem().itemid();
		}
		break;
	case ServerProto::Logic::SkillId:
		break;
	case ServerProto::Logic::AuraId:
		{
			itemId = award.awardaura().auraitemid();
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			itemId = award.awardequip().equipitemid();
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			itemId = award.awardhero().heroitemid();
		}
		break;
	case ServerProto::Logic::PetId:
		{
			itemId = award.awardpet().petitemid();
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			itemId = award.awardhero().heroitemid();
		}
		break;
	case ServerProto::Logic::RuneId:
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			itemId = award.awardfragment().auraitemid();
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			itemId = 0;
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			itemId = 0;
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		{
			itemId = 0;
		}

		break;
	case ServerProto::Logic::PVPPowerId:
		{
			itemId = 0;
		}
		break;
	default:
		break;
	}

	return GetStringTableFileId(award.awardtype(),itemId);
}

RealtimeRoleProperty Player::GetRealHeroProperty( uint64 heroId ) const
{
	const ServerProto::Logic::Hero* hero= GetServerHero(heroId);
	return RealtimeRoleProperty::ParseFrom(mPlayerData.serverplayer(),*hero);
}

void Player::CostMoney(uint money,PaperCostMoneyReason reason/*=PaperCostMoneyReason::Unknown*/)
{
	mPlayerData.mutable_serverplayer()->set_money(mPlayerData.mutable_serverplayer()->money() - money);
	Analytics::LogEvent(PaperAnalyticsEventId::CostMoney,reason.ToString(),money);
}

void Player::CostDiamond(uint diamond,PaperCostDiamondReason reason/*=PaperCostDiamondReason::Unknown*/)
{
	mPlayerData.mutable_serverplayer()->set_diamond(mPlayerData.mutable_serverplayer()->diamond() - diamond);
	Analytics::LogEvent(PaperAnalyticsEventId::CostDiamond,reason.ToString(),diamond);

}

const ServerProto::Logic::BonusItem Player::AwardToBonus( const ServerProto::Logic::Award& award )
{
	uint itemId = 0;
	uint num = 0;
	switch (award.awardtype())
	{
	case ServerProto::Logic::ItemId:
		{
			itemId = award.awarditem().itemid();
			num = award.awarditem().num();
		}
		break;
	case ServerProto::Logic::SkillId:
		break;
	case ServerProto::Logic::AuraId:
		{
			itemId = award.awardaura().auraitemid();
			num = 1;
		}
		break;
	case ServerProto::Logic::EquipId:
		{
			itemId = award.awardequip().equipitemid();
			num = 1;
		}
		break;
	case ServerProto::Logic::HeroId:
		{
			itemId = award.awardhero().heroitemid();
			num = 1;
		}
		break;
	case ServerProto::Logic::PetId:
		{
			itemId = award.awardpet().petitemid();
			num = 1;
		}
		break;
	case ServerProto::Logic::HeroSoulId:
		{
			itemId = award.awardherosoul().itemid();
			num = award.awardherosoul().num();
		}
		break;
	case ServerProto::Logic::RuneId:
		break;
	case ServerProto::Logic::SkillFragmentId:
		{
			itemId = award.awardfragment().auraitemid();
			num = award.awardfragment().num();
		}
		break;
	case ServerProto::Logic::MoneyId:
		{
			itemId = 0;
			num = award.awardmoney();
		}
		break;
	case ServerProto::Logic::DiamondId:
		{
			itemId = 0;
			num = award.awarddiamond();
		}
		break;
	case ServerProto::Logic::PVEPowerId:
		{
			itemId = 0;
			num = award.awardpvepower();
		}

		break;
	case ServerProto::Logic::PVPPowerId:
		{
			itemId = 0;
			num = award.awardpvppower();
		}
		break;
	default:
		break;
	}

	ServerProto::Logic::BonusItem bonusItem;
	bonusItem.set_type(award.awardtype());
	bonusItem.set_id(itemId);
	bonusItem.set_count(num);

	return bonusItem;
}

uint Player::GetNewUnlockChapterId() const
{
	return mNewUnlockChapterId;
}

uint Player::GetUnlockedChapterId() const
{
	return mUnlockedChapterId;
}

uint Player::GetCurrentChapterId() const
{
	return mPlayerData.serverplayer().curchapter();
}

uint Player::GetCurSelectChapterID() const
{
	return mCurSelectChapterID;
}

uint Player::GetCardActivityMaxChooseCount() const
{
	uint maxCardChooseCount=ServerGameConfig::Instance().MaxCardChooseCount();
	return Math::Min(mPlayerData.serverplayer().logincontinuallydays(),maxCardChooseCount);
}

bool Player::IsFirstLogin() const
{
	return mPlayerData.serverplayer().loginaccumulatedays()==1;
}





#pragma endregion Update Data

const StringRef Player::mPlayerFileName="Player.bin";
