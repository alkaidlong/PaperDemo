
enum QualityValues
{
    None=0,
	White=1,  
	Green=2,
	Blue=3,
	Purple=4,
	Orange=5,
}

enum HireType
{
	Normal=1,
	Middle=2,
	High=3,
}

enum HeroTrainType
{
	Normal=1,
    NormalTen=2,

    Diamond=3,
    DiamondTen=4,
}

enum ChargeType
{
    MonthCard=0, ///月卡
	FirstAndAdditional=1,  ///首冲并赠送
	FirstOnly=2,		/// 仅首冲
	AdditionalOnly=3,	/// 仅赠送
}

class HireInfo
{
     HireType Type;  //招募类型
     uint	TimeOfDaySeconds;   // 一天中的指定时刻
	 uint	DayInterval;        // 每几天刷新
     uint   CountLimit;    //次数限制
     uint   CountLimitDay; //次数限制作用的天数
     uint   RefreshDiamondCost;    //刷新花费的钻石
     array<QualityValues> AvailableQualities;    //可招募到品质
     QualityValues QualityAfterRefresh;  //首次刷新之后，必然出现的品质
}

class HeroTrainInfo
{
     HeroTrainType Type; //培养类型
     uint ItemCost;  //培养丹消耗
     uint MinPotentialCost;  //最小潜力值消耗
     uint MaxPotentialCost;  //最大潜力值消耗
     uint DiamondCost;       //钻石消耗
     array<int> PropertySubRandRange; // 扣除属性随机取值范围
     array<int> PropertyAddRandRange; // 增加属性随机取值范围
}

class HeroBreakInfo
{
     QualityValues Quality; //英雄品质
     uint PotentialGrow;  //突破后的潜力值增长
}

/// 吞噬提供的经验
class SwallowQualityExp
{
    QualityValues Quality; //品质
    uint Exp;      //提供的经验值; 
}

class BonusInfo
{
	uint ItemId;
     uint Position;
	 uint ItemCount;
	 BonusInfo()
	 {
		ItemId=0;
		Position=0;
		ItemCount=1;
	 }
}


class SkillRobFragmentProbInfo
{
    QualityValues Quality;  //品质
    float          Prob;      //每点灵魂提供的经验值; 
}
class ChargeInfo
{
	string ProductId;		// 产品id
	uint ShowPosition;		// 显示位置
	uint ChargeLevel;		// 充值档
	uint RMB;  				//花费人民币
    uint GotDiamonds;  		//获得晶钻
	uint FirstChargeDiamonds; // 首冲赠送
	uint AdditionalDiamonds; //非首冲赠送
	uint BenefitPerDay;		// 每日获利
	uint DayDuration;		// 有效时间段
	uint IconId;//图标id
	ChargeType ChargeType;//类型
}

class ServerGameConfig
{
    //服务器配置
     uint ServerResetTime = 0;   //服务器重置所有计数的时间，值为从零点开始的秒数

    float AutoMessageDuration = 30.0;    // 定时消息的间隔(心跳时间间隔)
    uint MaxFailedBeatCount = 2;         // 最大心跳失败次数
	
	array<ChargeInfo@> ChargeInfos;		//充值数据表
	array<BonusInfo@> ChargeRewardInfos;		//充值奖励数据表
    //玩家属性
     uint PlayerInitialMoney = 10000;    //玩家初始金币
     uint PlayerInitialDiamond = 0;    //玩家初始钻石
     uint PlayerMaxPVEPower = 30;    //玩家最大PVE体力
     uint PlayerMaxPVPPower = 30;    //玩家最大PVP体力
     uint PlayerMaxEnergy = 300; //玩家最大能量值
     float PlayerInitialEnergyRecover = 1.0; //玩家初始能量恢复速度
     uint HeroSadnessAddValue = 1;       // 玩家使用高级召唤英雄未招到紫色时增加的悲情值;
    uint  SadnessValueToCertainValueGetPurpleHero = 10;
     uint PetSadnessAddValue = 1;        // 玩家使用高级召唤宠物时为召唤到紫色宠物是增加的悲情值;
     uint PlayerMaxLevel = 50;
     uint VIPMaxLevel = 12;

     //道具
     uint ItemBuyNumMax = 10;
	 uint AddPVEPowerItemId = 21011;

    //英雄招募
     array<HireInfo@> HeroHireInfos; //英雄招募信息

     uint  HeroHireNormalUseCDSeconds = 10*60;  // 普通招募使用CD , 与刷新CD有异;

    //英雄培养
     uint HeroTrainItemId = 21010; //培养丹的道具Id
     array<HeroTrainInfo@> HeroTrainInfos; //英雄培养信息

    //英雄传承
     uint HeroInheritNormalItemId = 21007; //普通传承消耗的道具Id
     uint HeroInheritHighItemId = 21008; //高级传承消耗的道具Id

     float HeroInheritNormalExpPercent = 0.8; //普通传承经验的百分比
     float HeroInheritHighExpPercent = 1.0; //高级传承经验的百分比
     QualityValues HeroInheritPromtQuality = QualityValues::Purple;

     uint  HeroLevelLimitToPlayerLevel = 3;  //装备强化上限 = 玩家当前等级 * 3


    //英雄突破
     array<HeroBreakInfo@> HeroBreakInfos; //英雄突破信息
     uint HeroBreakMaxCount = 10;    //英雄最大突破次数

    //技能升级
     uint SkillMaxLevel = 9;    //技能最大等级

    //装备
	uint  EquipSlotMaxCount = 6;  //装备装配槽的最大数量
    uint  EquipLevelLimitToPlayerLevel = 3;  //装备强化上限 = 玩家当前等级 * 3
    float EquipUpgradeCritical = 0.5;       // 装备强化暴击率
	 
	//英雄队列
	uint ForceIndexMax = 6;//战斗位置最大数
	uint ForceNumMax = 5;//战斗部队的最大数

	//创建可选择英雄Id列表
	array<uint> CreatePlayerChooseHeroID;
	
	//VIP礼包范围
	uint VIPGiftIdMin = 21013;//vip1
	uint VIPGiftIdMax = 21024;//vip12
	uint MonthCardExpireMidTime = 259200;//月卡提前3天可领

   
    

	//符文
	uint MaxRuneLevel=10;	//符文等级上限
	uint MaxRuneShopLevel=5;	//符文商店等级上限
	uint InitialRuneShopCount=1;	//玩家初始符文商店可用次数
    uint RuneShopRefreshTimeOfDay = 0;
	uint RuneShopRefreshDayInterval = 1;	//符文商店免费的CD时间，单位天
	uint RuneMaxCountInPack=40;		//背包里最大的符文个数
	uint RuneSlotMaxCount=6;		//英雄身上的符文插槽个数
    uint HighDrawRuneDiamondCost = 200;         // 符文高级灌注点券消费数
    uint HighDrawRuneRelatedShopLevel = 4;      // 高级灌注对应的等级
	array<uint> RuneSlotUnlockHeroLevels;	    //英雄符文插槽的解锁等级
	
	//缘分
	uint MaxLoveNum=6;//缘分的最大数量
	uint MaxLoveFactorNum=4;//缘分条件元素最大数量
	
	//PVP
	uint PVPLeaderboardMaxChallengeCount=5;		//排行榜挑战上限
	uint PVPPowerRecoverCD=30*60;				//PVP体力恢复的CD,单位：秒
	uint PVPLeaderboardFactor=100;				//排行榜因子
	uint PVPLeaderboardRange=5;				//排行榜前后的玩家个数
	uint PVPLeaderboardTopCount=10;				//排行榜顶部的玩家个数
	uint PVPLeaderboardScoreDuration=10*60;		//排行榜积分需要排名持续的时间
	uint PVPLeaderboardBonusTopCount=100;		//排行榜额外奖励的玩家个数
	uint PVPLeaderboardBonusValue=4*60*60;		//排行榜额外奖励的积分时间
	uint PVPLeaderboardScoreBegin=0;			//排行榜积分初始值
	uint PVPLeaderboardScoreMax=99999999;		//排行榜最大值
	uint PVPLeaderboardScoreToItemId=21010;		//排行榜积分兑换的道具Id
	uint PVPLeaderboardScoreToItemCount1=5;		//排行榜积分兑换的道具数量1
	uint PVPLeaderboardScoreToItemCount2=50;	//排行榜积分兑换的道具数量2
	uint PVPLeaderboardScoreToItemScore1=1000;	//排行榜积分兑换的积分1
	uint PVPLeaderboardScoreToItemScore2=10000;	//排行榜积分兑换的积分2
    uint PVPLeaderboardBounsTimeOfDay =19*60*60;		//排行榜额外奖励的发放时间
    uint PVPLeaderboardBounsDayInterval = 1;            // 刷新时间间隔
    uint PVPChallengeTimesRefreshTimeOfDay = 0; 
    uint PVPChallengeTimesRefreshDayInterval = 1; //pvp挑战次数刷新时间间隔
	
	uint PVPLeaderboardTopBonusItemId=21010;		//排行榜头名奖励的道具Id
	array<BonusInfo@> PVPLeaderboardTopBonusInfos;		//排行榜首次到达名次的奖励
	
	//技能抢夺
	array<uint> SkillRobInitialList;	//技能抢夺的初始技能列表
	uint SkillRobInitialCount=3;		//技能抢夺的初始技能个数，从SkillRobInitialList里随机抽取
	uint SkillFragmentMaxCount=999;		//技能碎片的最大个数
	uint SkillRobTargetLevelRange=3;	//技能抢夺对象的等级浮动范围
	uint SkillRobTargetCount=3;			//技能抢夺列表的玩家个数，包括NPC
	array<QualityValues> SkillRobNPCHeroQualities;	//技能抢夺NPC的英雄品质范围
	array<SkillRobFragmentProbInfo@> SkillRobFragmentProbs;	//技能抢夺碎片的掉落几率
    uint  CreatePlayerGetFragmentItemId = 30022; //创建玩家获得技能碎片
	//仇人
    uint EnemyMaxNum = 20;
	
	//宠物2.0系统
	uint PetMaxLevel=20;	//宠物等级上限
    /// 英雄提供经验值
    array<SwallowQualityExp@>    PetSwallowHeroExp;
    
    /// 英雄灵魂提供经验值
    array<SwallowQualityExp@> PetSwallowHeroSoulExp;
	
	//邮件
	uint MailMaxCount=50;		//最多保留的邮件数目
	uint RewardMailKeepTime = 48*60*60;
	
	//公告
	float NoticeMoveSpeed=100.0;	//公告移动的速度
	float NoticePlayInterval=3.0;	//公告播放的间隔
	QualityValues NoticeMinHeroQuality=QualityValues::Blue;	//玩家抽到蓝色品质及以上的英雄都会有全服公告
	QualityValues NoticeMinEquipQuality=QualityValues::Blue;	//玩家抽到蓝色品质及以上的装备都会有全服公告
	QualityValues NoticeMinAuraQuality=QualityValues::Blue;	//玩家抽到蓝色品质及以上的技能都会有全服公告
	uint NoticeMinEquipLevel=50;	//玩家某件装备强化到50、60、70、80以此类推从50级开始，10的倍数等级都会有系统播报
	uint NoticeEquipLevelInterval=10;	//玩家某件装备强化到50、60、70、80以此类推从50级开始，10的倍数等级都会有系统播报
	uint NoticeMinAuraLevel=5;		//玩家某个技能强化到5级以上，5、6、7、8、9,，都有系统播报
	uint PlayerNoticeMaxCount=50;	//玩家公告的条数限制

    /// 新手礼包
    uint NewPlayerGiftItemID        = 21032; //通过邮件发放
	array<uint> LoginGiftItemIDs;	//连续登陆的奖励，和活动的不同

	//血战
	uint MaxBloodBattlePerDay=3;	//每日可参加的次数
    uint BloodBattleRefreshTimeOfDay = 0;
    uint BloodBattleRefreshDayInterval = 1;
	array<uint> BloodBattleLeaderboardLevels;	//血战排行榜的分组级别限制,	逆序排列
	uint BloodBattleLeaderboardBonusItemId=1001;						//血战排行榜奖励的道具Id
	float BloodBattleMode1Prob=0.7;	//血战模式1概率
	float BloodBattleMode2Prob=0.3;	//血战模式2概率
	float BloodBattleInitialBufferValueFactor=4.0;	//用户每天血战开始时可从五项属性中任选一项作为初始buff，数值为昨天获得的最多总星/4
	uint BloodBattleMissionBufferStartCount0=30;	//花费30个星加30%属性buff
	float BloodBattleMissionBufferValue0=0.3;		//花费30个星加30%属性buff
	uint BloodBattleMissionBufferStartCount1=15;	//花费15个星加15%属性buff
	float BloodBattleMissionBufferValue1=0.15;		//花费15个星加15%属性buff
	uint BloodBattleMissionBufferStartCount2=3;	//花费3个星加3%属性buff
	float BloodBattleMissionBufferValue2=0.03;		//花费3个星加3%属性buff
	uint BloodBattleBonusMoneyPerStar=1000;			//固定奖励，每颗星星奖励的游戏币
	uint BloodBattleBonusMoneyGrowMissionInterval=5;			//固定奖励，每颗星星奖励的游戏币，结果=BloodBattleBonusMoneyPerStar*(关卡数/BloodBattleBonusMoneyGrowMissionInterval+1)
	uint BloodBattleMailTopPlayerCount=20;						//每天0:00点以邮件的形式发放表给每个组别的前20的玩家
	uint BloodBattleAddPorpertyBuffLayerCount = 3; //每3关加属性buff
	uint BloodBattleRewardLayerCount = 5; //每5关奖励
    uint BloodBattleMissionTotalProb = 100;//总权重
    uint BloodBattleBeginMissionID   = 30000; //血战开始的missionID
    uint BloodBattleInRankGetItemID  = 21010; //上榜奖励道具

    uint BloodBattleNoHeroDieGetStar  = 3;             //无人死亡得 3 星
    uint BloodBattleOneHeroDieGetStar = 2;             //死一个人得 2 星
    uint BloodBattleMoreHerosDieGetStar = 1;           //两人以上死亡得 1星
    uint BloodBattleDifficultHightGetStarTimes = 3;         //困难倍数
    uint BloodBattleDifficultMediumGetStarTimes = 2;       //中等倍数
    uint BloodBattleDifficultLowGetStarTimes  = 1;         //低难度倍数
	
	//活动
	uint MaxCardCount=8;		//玩家翻牌时牌的数量
	uint MaxCardChooseCount=3;		//玩家翻牌的最大次数
	uint CardBonusItemId=30000;	//发放奖励的礼包id
	uint CardShowItemId=30001;	//展示奖励的礼包id
	
	//七日礼
	uint SevenGiftActivityItemId=30002;	//玩家签到获得的奖励的礼包id1
	
	array<BonusInfo@> PlayerUpgradeBonusInfos;		//玩家升级获得的奖励

	uint SignInModeCount1=1;		//玩家第一次发奖励的最小签到次数
	uint SignInModeCount2=3;		//玩家第二次发奖励的最小签到次数
	uint SignInModeCount3=5;		//玩家第二次发奖励的最小签到次数
	
	uint ClockBonusItemId1=30003;	//玩家签到获得的奖励的礼包id1
	uint ClockBonusItemId2=30004;	//玩家签到获得的奖励的礼包id2
	uint ClockBonusItemId3=30005;	//玩家签到获得的奖励的礼包id3
		
	uint DrinkBeginTime1=12*60*60;	//每天喝酒增加体力的开始时间，第一个时间段，数值表示从当天0点已过的秒数
	uint DrinkEndTime1=13*60*60;	//每天喝酒增加体力的结束时间，第一个时间段，数值表示从当天0点已过的秒数
	uint DrinkPVEPowerDelta1=10;	//每天喝酒增加的体力数值，第一个时间段
	uint DrinkBeginTime2=18*60*60;	//每天喝酒增加体力的开始时间，第二个时间段，数值表示从当天0点已过的秒数
	uint DrinkEndTime2=19*60*60;	//每天喝酒增加体力的结束时间，第二个时间段，数值表示从当天0点已过的秒数
	uint DrinkPVEPowerDelta2=10;//每天喝酒增加的体力数值，第二个时间段
    uint DrinkRefreshTime = 24*60*60;//每天0点刷新饮酒掩码
	
	
	//战斗
	float BattleHitProb=200;
	float BattleMinHitProb=0.5;
	float BattleCriticalProb=0.1;
	float BattleCriticalFactor=1.5;
    float BattleCriticalEnergyFactor=1.0f;
    uint BattleKillEnergy=20;
	float BattleMinAttack=1.0;
	uint BattleMPGrowPerAttack=1;
	
	float BattleMaxMP=60;	//魔法值上限
	float BattleMPGrowPerSecond=3;	//每秒上涨的魔法值
    uint  BattleGetMaxStar=3;//战斗获得最高星
    uint  FirstGetMaxStarExpTimes=3;//第一次达到最高星经验翻倍数
    //扫荡
    uint SweepFreeTimesRefreshTimeOfDay = 0; 
    uint  SweepFreeTimesRefreshDayInterval = 1; //扫荡次数刷新时间间隔
    uint  MissionSweepFreeTimesOfDay = 20;//免费扫荡次数
    uint  ExtraOneSweepCostDiamonds = 10; //一次扫荡花费钻石数
    uint  SweepLimitPlayerLevel = 16;//等级限制
    uint  MissionDropTAllProb = 1000; //关卡掉落总权重
	uint  MaxMissionSweep = 10; //扫荡最大次数
	uint  MinMissionSweep = 1; //扫荡最小次数
    //关卡充值话费钱数
    array<uint> MissonResetCostDiamond;
	

    //平台配置
    uint   PlatformID = 0;		//当前的平台，指定是Dev,91,appStore等，值分别为0,1,2
    string PlatformAuthUrl = "http://service.sj.91.com/usercenter/ap.aspx";
    string PlatformPayUrl  = "http://service.sj.91.com/usercenter/ap.aspx";
    string AppID = "113968";				//91平台
    string AppKey = "ce51bcc82e0a842efcaf00699259af40517f05839aca2d07";		//91平台
    //新手引导
    uint GuideHireTimes = 2;
    //购买体力
    uint BuyPowerTimesRefreshTimeOfDay = 0; 
    uint BuyPowerTimesRefreshDayInterval = 1; //购买体力次数刷新时间间隔
    array<uint> BuyPowerDiamondCost;	/// vip 体力购买花费钻石数 per times
	uint    BuyPVEPowerGot = 30;    /// 每次购买获得的体力值
	uint    BuyPVPPowerGot = 10;    /// 每次购买获得的体力值
	//消息Key
	uint MessageEncoderType=2;
	uint MessageDecoderType=102;
	
	string MessageEncryptKey  = "20F12DFAC3D34355932C907C15255E856AB65A9F82B243208EFFAC3A176DE164D7E91916403844018AF05D7E501540B5DC7F1FA409724CBFAD2FAEA441D41759BE8D34716132442582CA19F1884F9AB6369185EED57744E8AB88B24233BA2FC4";
	
	 
    ServerGameConfig()
    {
        //英雄招募
        {
            HireInfo info;
            info.Type = HireType::Normal;
            info.TimeOfDaySeconds = 0;
            info.DayInterval = 1;
            info.CountLimit = 5;
            info.CountLimitDay = 1;
            info.RefreshDiamondCost = 10;
            info.QualityAfterRefresh = QualityValues::None;
            info.AvailableQualities.insertLast(QualityValues::White);
            info.AvailableQualities.insertLast(QualityValues::Green);
            info.AvailableQualities.insertLast(QualityValues::Blue);
            HeroHireInfos.insertLast(info);

        }

          {
            HireInfo info;
            info.Type = HireType::Middle;
            info.TimeOfDaySeconds = 0;
            info.DayInterval = 1;
            info.CountLimit = 1;
            info.CountLimitDay = 2;
            info.RefreshDiamondCost = 100;
            info.QualityAfterRefresh = QualityValues::Blue;
            info.AvailableQualities.insertLast(QualityValues::Green);
            info.AvailableQualities.insertLast(QualityValues::Blue);
            info.AvailableQualities.insertLast(QualityValues::Purple);
            HeroHireInfos.insertLast(info);

        }

          {
            HireInfo info;
            info.Type = HireType::High;
            info.TimeOfDaySeconds = 0;
            info.DayInterval = 3;
            info.CountLimit = 1;
            info.CountLimitDay = 3;
            info.RefreshDiamondCost = 300;
            info.QualityAfterRefresh = QualityValues::Purple;
            info.AvailableQualities.insertLast(QualityValues::Blue);
            info.AvailableQualities.insertLast(QualityValues::Purple);
            HeroHireInfos.insertLast(info);

        }

    

    //英雄培养

        {
            HeroTrainInfo info;
            info.Type = HeroTrainType::Normal;
            info.ItemCost = 5;
            info.MinPotentialCost = 1;
            info.MaxPotentialCost = 4;
            info.DiamondCost = 0;
            // -1、 -2、 -3
            info.PropertySubRandRange.insertLast(-1);
            info.PropertySubRandRange.insertLast(-2);
            info.PropertySubRandRange.insertLast(-3);
            // +2、 +3、 +4、 +5
            info.PropertyAddRandRange.insertLast(2);
            info.PropertyAddRandRange.insertLast(3);
            info.PropertyAddRandRange.insertLast(4);
            info.PropertyAddRandRange.insertLast(5);
            HeroTrainInfos.insertLast(info);
        }

          {
            HeroTrainInfo info;
            info.Type = HeroTrainType::NormalTen;
            info.ItemCost = 50;
            info.MinPotentialCost = 10;
            info.MaxPotentialCost = 30;
            info.DiamondCost = 0;
            // -10、 -20、 -30 
            info.PropertySubRandRange.insertLast(-10);
            info.PropertySubRandRange.insertLast(-20);
            info.PropertySubRandRange.insertLast(-30);
            // +20、 +30、 +40、 +50
            info.PropertyAddRandRange.insertLast(20);
            info.PropertyAddRandRange.insertLast(30);
            info.PropertyAddRandRange.insertLast(40);
            info.PropertyAddRandRange.insertLast(50);
            HeroTrainInfos.insertLast(info);
        }

          {
            HeroTrainInfo info;
            info.Type = HeroTrainType::Diamond;
            info.ItemCost = 5;
            info.MinPotentialCost = 1;
            info.MaxPotentialCost = 7;
            info.DiamondCost = 1;
            // -1、 -2、 -3
            info.PropertySubRandRange.insertLast(-1);
            info.PropertySubRandRange.insertLast(-2);
            info.PropertySubRandRange.insertLast(-3);
            // +3、+4、 +5、+6、+7、+8
            info.PropertyAddRandRange.insertLast(3);
            info.PropertyAddRandRange.insertLast(4);
            info.PropertyAddRandRange.insertLast(5);
            info.PropertyAddRandRange.insertLast(6);
            info.PropertyAddRandRange.insertLast(7);
            info.PropertyAddRandRange.insertLast(8);
            HeroTrainInfos.insertLast(info);
        }

          {
            HeroTrainInfo info;
            info.Type = HeroTrainType::DiamondTen;
            info.ItemCost = 50;
            info.MinPotentialCost = 10;
            info.MaxPotentialCost = 70;
            info.DiamondCost = 10;
            // -10、 -20、 -30
            info.PropertySubRandRange.insertLast(-10);
            info.PropertySubRandRange.insertLast(-20);
            info.PropertySubRandRange.insertLast(-30);
            // +30、 +40、 +50、 +60、 +70、 +80
            info.PropertyAddRandRange.insertLast(30);
            info.PropertyAddRandRange.insertLast(40);
            info.PropertyAddRandRange.insertLast(50);
            info.PropertyAddRandRange.insertLast(60);
            info.PropertyAddRandRange.insertLast(70);
            info.PropertyAddRandRange.insertLast(80);
            HeroTrainInfos.insertLast(info);
        }

    //英雄突破
          {
            HeroBreakInfo info;
            info.Quality = QualityValues::White;
            info.PotentialGrow = 10;
            HeroBreakInfos.insertLast(info);
        }

         {
            HeroBreakInfo info;
            info.Quality = QualityValues::Green;
            info.PotentialGrow = 20;
            HeroBreakInfos.insertLast(info);
        }

         {
            HeroBreakInfo info;
            info.Quality = QualityValues::Blue;
            info.PotentialGrow = 60;
            HeroBreakInfos.insertLast(info);
        }

         {
            HeroBreakInfo info;
            info.Quality = QualityValues::Purple;
            info.PotentialGrow = 75;
            HeroBreakInfos.insertLast(info);
        }

         {
            HeroBreakInfo info;
            info.Quality = QualityValues::Orange;
            info.PotentialGrow = 100;
            HeroBreakInfos.insertLast(info);
        }

		//创建可选择英雄
		{
		   CreatePlayerChooseHeroID.insertLast(1031);
		   CreatePlayerChooseHeroID.insertLast(1032);
		   CreatePlayerChooseHeroID.insertLast(1033);
		}


        //////////////////////////////////////////////////////////////////////////
        /// 宠物吞噬
        /// 英雄
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::White;
            provide.Exp = 1;
            PetSwallowHeroExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Green;
            provide.Exp = 6;
            PetSwallowHeroExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Blue;
            provide.Exp = 27;
            PetSwallowHeroExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Purple;
            provide.Exp = 72;
            PetSwallowHeroExp.insertLast(provide);
        }
        ///宠物
      
        /// 英雄灵魂
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::White;
            provide.Exp     = 1;
            PetSwallowHeroSoulExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Green;
            provide.Exp     = 2;
            PetSwallowHeroSoulExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Blue;
            provide.Exp     = 3;
            PetSwallowHeroSoulExp.insertLast(provide);
        }
        {
            SwallowQualityExp provide;
            provide.Quality = QualityValues::Purple;
            provide.Exp     = 4;
            PetSwallowHeroSoulExp.insertLast(provide);
        }
	   //符文
	   //RuneSlotUnlockHeroLevels.insertLast(50);
	   //RuneSlotUnlockHeroLevels.insertLast(65);
	   //RuneSlotUnlockHeroLevels.insertLast(80);
	   //RuneSlotUnlockHeroLevels.insertLast(95);
	   //RuneSlotUnlockHeroLevels.insertLast(110);
	   //RuneSlotUnlockHeroLevels.insertLast(125);
	   
	   //test data
	   RuneSlotUnlockHeroLevels.insertLast(60);
	   RuneSlotUnlockHeroLevels.insertLast(70);
	   RuneSlotUnlockHeroLevels.insertLast(80);
	   RuneSlotUnlockHeroLevels.insertLast(90);
	   RuneSlotUnlockHeroLevels.insertLast(100);
	   RuneSlotUnlockHeroLevels.insertLast(200);
	   
	 
        //关卡充值话费钱数
        MissonResetCostDiamond.insertLast(50);
        MissonResetCostDiamond.insertLast(100);
        MissonResetCostDiamond.insertLast(100);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
        MissonResetCostDiamond.insertLast(200);
		
		  //充值数据
	    {
			ChargeInfo info;
			info.ProductId="113968-20140711-121501173-19";
			info.ShowPosition=0;		// 显示位置
			info.ChargeLevel=0;		// 充值档
			info.RMB=328;  				//花费人民币
			info.GotDiamonds=3280;  		//获得晶钻
			info.FirstChargeDiamonds=0; // 首冲赠送
			info.AdditionalDiamonds=488; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::AdditionalOnly;//类型
			ChargeInfos.insertLast(info);
	   }
	   {
			ChargeInfo info;
			info.ProductId="113968-20140711-121613047-34";
			info.ShowPosition=1;		// 显示位置
			info.ChargeLevel=1;		// 充值档
			info.RMB=648;  				//花费人民币
			info.GotDiamonds=6480;  		//获得晶钻
			info.FirstChargeDiamonds=6480; // 首冲赠送
			info.AdditionalDiamonds=1088; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::FirstAndAdditional;//类型
			ChargeInfos.insertLast(info);
	   }
	    {
			ChargeInfo info;
			info.ProductId="113968-20140711-121703374-20";
			info.ShowPosition=2;		// 显示位置
			info.ChargeLevel=2;		// 充值档
			info.RMB=68;  				//花费人民币
			info.GotDiamonds=680;  		//获得晶钻
			info.FirstChargeDiamonds=0; // 首冲赠送
			info.AdditionalDiamonds=85; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::AdditionalOnly;//类型
			ChargeInfos.insertLast(info);
	   }
	    {
			ChargeInfo info;
			info.ProductId="113968-20140711-121740608-42";
			info.ShowPosition=3;		// 显示位置
			info.ChargeLevel=3;		// 充值档
			info.RMB=198;  				//花费人民币
			info.GotDiamonds=1980;  		//获得晶钻
			info.FirstChargeDiamonds=1980; // 首冲赠送
			info.AdditionalDiamonds=258; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::FirstAndAdditional;//类型
			ChargeInfos.insertLast(info);
	   }
	   
	    {
			ChargeInfo info;
			info.ProductId="113968-20140711-121813983-34";
			info.ShowPosition=4;		// 显示位置
			info.ChargeLevel=4;		// 充值档
			info.RMB=1;  				//花费人民币
			info.GotDiamonds=10;  		//获得晶钻
			info.FirstChargeDiamonds=20; // 首冲赠送
			info.AdditionalDiamonds=0; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::AdditionalOnly;//类型
			ChargeInfos.insertLast(info);
	   }
	   {
			ChargeInfo info;
			info.ProductId="113968-20140711-122040263-21";
			info.ShowPosition=5;		// 显示位置
			info.ChargeLevel=5;		// 充值档
			info.RMB=30;  				//花费人民币
			info.GotDiamonds=300;  		//获得晶钻
			info.FirstChargeDiamonds=300; // 首冲赠送
			info.AdditionalDiamonds=30; //非首冲赠送
			info.BenefitPerDay=0;		// 每日获利
			info.DayDuration=0;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::FirstAndAdditional;//类型
			ChargeInfos.insertLast(info);
	   }
	    {
			ChargeInfo info;
			info.ProductId="113968-20140711-122632680-96";
			info.ShowPosition=6;		// 显示位置
			info.ChargeLevel=6;		// 充值档
			info.RMB=1;  				//花费人民币
			info.GotDiamonds=250;  		//获得晶钻
			info.FirstChargeDiamonds=0; // 首冲赠送
			info.AdditionalDiamonds=0; //非首冲赠送
			info.BenefitPerDay=100;		// 每日获利
			info.DayDuration=30;		// 有效时间段
			info.IconId=10;//图标id
			info.ChargeType=ChargeType::MonthCard;//类型
			ChargeInfos.insertLast(info);
	   }
	   
		//充值累计奖励，必须有顺序，按照奖励值从低到高
	    {
			BonusInfo chargeRewardInfo;
			chargeRewardInfo.ItemId=1050;
			chargeRewardInfo.Position=10;
			chargeRewardInfo.ItemCount=1;
			ChargeRewardInfos.insertLast(chargeRewardInfo);
	   }
	    {
			BonusInfo chargeRewardInfo;
			chargeRewardInfo.ItemId=1051;
			chargeRewardInfo.Position=100;
			chargeRewardInfo.ItemCount=1;
			ChargeRewardInfos.insertLast(chargeRewardInfo);
	   }
	   {
			BonusInfo chargeRewardInfo;
			chargeRewardInfo.ItemId=1052;
			chargeRewardInfo.Position=1000;
			chargeRewardInfo.ItemCount=1;
			ChargeRewardInfos.insertLast(chargeRewardInfo);
	   }
	   {
			BonusInfo chargeRewardInfo;
			chargeRewardInfo.ItemId=1053;
			chargeRewardInfo.Position=10000;
			chargeRewardInfo.ItemCount=1;
			ChargeRewardInfos.insertLast(chargeRewardInfo);
	   }
	   //PVP排行榜
	    {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=1;
			info.ItemCount=600;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	   {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=10;
			info.ItemCount=600;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=50;
			info.ItemCount=300;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=100;
			info.ItemCount=300;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	   
	    {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=200;
			info.ItemCount=300;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	   {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=500;
			info.ItemCount=300;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	   {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=1000;
			info.ItemCount=300;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   }
	   {
			BonusInfo info;
			info.ItemId=21010;
			info.Position=200000;
			info.ItemCount=200;
			PVPLeaderboardTopBonusInfos.insertLast(info);
	   } 
	   //技能抢夺
	   SkillRobNPCHeroQualities.insertLast(QualityValues::White);
	   SkillRobNPCHeroQualities.insertLast(QualityValues::Green);
	   SkillRobNPCHeroQualities.insertLast(QualityValues::Blue);
	   
	    {
            SkillRobFragmentProbInfo info;
            info.Quality = QualityValues::Green;
            info.Prob     = 0.4;
            SkillRobFragmentProbs.insertLast(info);
        }
		
		 {
            SkillRobFragmentProbInfo info;
            info.Quality = QualityValues::Blue;
            info.Prob     = 0.3;
            SkillRobFragmentProbs.insertLast(info);
        }
		
		 {
            SkillRobFragmentProbInfo info;
            info.Quality = QualityValues::Purple;
            info.Prob     = 0.2;
            SkillRobFragmentProbs.insertLast(info);
        }
		
		//血战
		BloodBattleLeaderboardLevels.insertLast(15);
		BloodBattleLeaderboardLevels.insertLast(10);
		BloodBattleLeaderboardLevels.insertLast(1);
		
		 //活动
		 //连续登陆
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
        LoginGiftItemIDs.insertLast(21025);
		
		
		//玩家升级获得的奖励
	    {
			BonusInfo info;
			info.ItemId=30006;
			info.Position=5;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	   {
			BonusInfo info;
			info.ItemId=30007;
			info.Position=10;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30008;
			info.Position=12;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30009;
			info.Position=15;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30010;
			info.Position=18;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30011;
			info.Position=20;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }	   
	    {
			BonusInfo info;
			info.ItemId=30012;
			info.Position=23;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }	   
	    {
			BonusInfo info;
			info.ItemId=30013;
			info.Position=25;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30014;
			info.Position=28;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }	
	    {
			BonusInfo info;
			info.ItemId=30015;
			info.Position=30;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30016;
			info.Position=33;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30017;
			info.Position=36;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30018;
			info.Position=38;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
        {
			BonusInfo info;
			info.ItemId=30019;
			info.Position=40;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30020;
			info.Position=45;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }
	    {
			BonusInfo info;
			info.ItemId=30021;
			info.Position=50;
			PlayerUpgradeBonusInfos.insertLast(info);
	   }

	
        
     {/// vip 体力购买花费钻石数
         BuyPowerDiamondCost.insertLast(50);
         BuyPowerDiamondCost.insertLast(100);
         BuyPowerDiamondCost.insertLast(150);
         BuyPowerDiamondCost.insertLast(200);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);         
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
         BuyPowerDiamondCost.insertLast(250);
     }
	}/// end of constructor
}/// end of class ServerGameConfig
