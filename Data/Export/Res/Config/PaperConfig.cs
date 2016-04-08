class PaperConfig
{
    uint Version = 1;	//版本    main=1，free=2
    uint Language = 2;   //语言  enus=1,zhcn=2
    uint Device = 4;   //设备  sd=1,hd=2,hd5=4,ipad=8,ipad3=16

	
    string UpdateServerUrl = "http://static.hhyx.wyximg.com:9999/version1/";    //更新服务器地址

    bool IsMockEnabled = false; //是否开启mock
    bool IsCheatEnabled = false;    //是否开启作弊?
    bool IsDebugEnabled = false;    //是否开启调试?

    float MessageTimeout = 100000.0;    //消息超时时间
    float AutoSaveDuration = 5.0;    //自动保存时间
	
	uint MessageRetryTimes=5;	//消息连接重试次数
	uint MessageRetryInterval=1000;	//消息连接重试间隔，毫秒
	
    uint HTTPConnectTimeoutSeconds = 5;  //HTTP连接的超时秒数?
    uint HTTPReadTimeoutSeconds = 5;   //HTTP下载的超时秒数?
    uint HTTPReadLowSpeedLimit = 10;   //HTTP下载的最小速度限制，单位：字节/s
    uint HTTPReadLowSpeedTime = 10;    //HTTP下载的小速度时间限制，当处于小速度*时间之后，将自动断开连接，单位秒

    float CompanyLogoTime = 2.0;  //公司Logo显示的时间?
	
	uint MessageRechargeTimes=5;	//充值消息连接重发次数
	uint MessageRechargeOneTime=1;	//充值认证间隔时间消息

    string DebugAnimation = "My.ani";   //调试时显示的动画名称
	
    uint BuyItemDefaultNumber = 1;  //购买商品，默认的个数
    uint DisplayStrengthenAnimationLevel = 2;  //装备强化暴击出现的等级差要求
    uint LimitUpLevelAuraNumber = 5;  //技能升级时，限制最多可以选择5个光环
    uint PetMaxLevel = 65;  //技Pet能升级的最大的等级

    uint RuneIconNumber = 3;//符文界面的一个item的显示个数
	uint RuneLevelNumber=5;//符文等级数目
	uint RuneUpMaxNum=7;//符文灌注7次
	uint RuneAcquisitionMoveWidth=1400;//符文横向移动
	float RuneAcquisitionScale = 1.0;  //符文放大
	
	uint RechargeCellNumber = 2;//充值界面的一个item的显示个数
	float VIPCellMoveTime = 0.2f;//VIP查看界面移动时间
	float VIPButtonBig = 1.05f;//VIP按钮放大时间
	float VIPButtonSmall = 0.95f;//VIP按钮缩小时间
	uint RechargeCellLabelNumber = 10;//VIP标签个数

    uint QualityColorValueWhite = 0xffdddddd;
    uint QualityColorValueGreen = 0xff10d774;
    uint QualityColorValueBlue = 0xffee9550;
    uint QualityColorValuePurple = 0xffee08c5;
    uint QualityColorValueOrange = 0xff18beff;
	
	uint ColorValueAddProperty = 0xff00ff00;
	uint ColorValueLowerProperty = 0xff0000ff;
    uint ColorValueNormalProperty = 0xffffffff;
	
	uint ColorValueLoveReached = 0xffff003c;
	uint ColorValueLoveNotReached = 0xff828282;

    uint ColorValuePetFeedSelected = 0xff828282;
    uint ColorValueRuneLevelUpSelected = 0xff828282;

    uint ColorValueLevelNotSelect = 0x6bd334;
    uint ColorValueNumberNotSelect = 0xffffff;
	
	uint ColorValueItemNumInsufficient = 0xff0000ff;
    uint ColorValueItemNumNormal = 0xffffffff;
	
	float BattleArraySelectHeroScale = 1.0;
	float BattleArrayNormalHeroScale = 0.7;
	
	//天赋界面颜色
	uint ColorValueTalentNameOpen = 0xff00ff00;
	uint ColorValueTalentNameLock = 0xff828282;
	uint ColorValueTalentNameFull = 0xff00ffff;
	uint ColorValueTalentDirectionsOpen = 0xff00ff00;
	uint ColorValueTalentDirectionsLock = 0xff0000ff;
	
	//公告
	float NoticeMoveSpeed = 100.0f;//像素/秒
	uint SystemNoticeCollectItemNum = 4;
	uint ColorValuePlayerNotice = 0xff00ff00;
	uint ColorValueGameTip = 0xffffffff;
	//符文
	string FuWenUpdateAnimation="UIFuWenUpdate.ani";
	//装备
	string EquipStrengthAnimation="UIEquipStrength.ani";
	//天赋
	string TalentSuccessAnimation="UITalentSuccess.ani";
	//突破
	string InheritanceSuccessAnimation="UIInheritanceSuccessGreen.ani";
	//技能升级
	string SkillUpgradeAnimation="UISkillUpgrade.ani";
	//活动
	//翻牌
	string CardActivityCompereImage="HeroLargeIcon.ani";
	uint CardActivityCompereImageOrder      = 111;
	string CardActivityBackAnimation="CardBack.ani";	//翻牌的动画
	float CardActivityBonusDelayTime=1.0;	//奖励牌翻开后的等待时间
	float CardActivityShowDelayTime=1.0;	//展示牌翻开后的等待时间
	
	//七日礼
	string SevenGiftActivityCompereImage="StudioCommentator2.ani";
	uint SevenGiftActivityCompereImageOrder      = 0;
	//升级
	string UpgradeActivityCompereImage="StudioCommentator1.ani";
	uint UpgradeActivityCompereImageOrder      = 0;
	//敲钟
	string ClockActivityCompereImage="StudioCommentator4.ani";
	uint ClockActivityCompereImageOrder      = 0;
	string ClockActivityAnimation="UIFrameRollBig.ani";	//敲钟的动画
	//喝酒
	string WineActivityCompereImage="StudioCommentator3.ani";
	uint WineActivityCompereImageOrder      = 0;
	string WineActivityAnimation="UIFrameRollBig.ani";	//喝酒的动画
	
	uint ColorValueEventsLevelUpLevelEnough      = 0xff00aa00;
	uint ColorValueEventsLevelUpLevelNotEnough   = 0xffaa0000;
	uint ColorValueEventsLevelUpAleadyGotAward   = 0xffaaaaaa;
	
	//cd key
	uint CDKeyLengtn = 16;
	string CDKeyCharacters = "1234567890abcdefjhigklmnopqrstuvwxyzABCDEFJHIGKLMNOPQRSTUVWXYZ";
	
	//地图
	float MapMaxScale=2.0;
	float MapHeroSpeed=200.f; //每秒的速度
	string MapUnlockAnimation="UIBigMap.ani";
	string MapAnimation="Map1.ani";
	float MapUnlockMoveDuration=1;
	float MapHeroMarginX=50;	//英雄隔开的距离X
	float MapHeroMarginY=50;	//英雄隔开的距离Y
	float MapNewBadgeAnimateDuration=0.1f;		//New标志的动画时间
	float MapNewBadgeMoveByY=10.0f;		//New标志的移动间隔Y
	
	array<string> CloudAnimations;
	
	//创建角色
	array<string> CreatePlayerHeroesFile;

	//符文
    float RunePerfusionMoveBeginTime=0.3;
    float RunePerfusionMoveEndTime=0.3;
	
    //关卡过关颜色
    uint TipChapterColorWin = 0xff00ff00;
    uint TipChapterColorLost = 0xff0000ff;
	
	
	float MissionCheckoutStartDuration=0.0f;	//结算界面开始播放水晶动画的时间
	string MissionCheckoutStarAnimation="UIBattleSettlementStar.ani";	//星星动画
	float MissionCheckoutStarDuration=0.3;	//星星动画的时间
	string MissionCheckoutHeroLevelAnimation="UIBattleSattlementUpgrade.ani";	//英雄升级动画
	float MissionCheckoutNumberRollDuration=1.5;	//数字滚动的时间，
	float MissionCheckoutHeroExpGrowDuration=0.5;	//英雄经验条增长的时间
	float MissionCheckoutItemDuration=0.5;	//道具显示的时间
	string MissionCheckoutPlayerLevelAnimation="MotherFuckerUpgrade.ani";	//玩家升级动画
	float MissionCheckoutPlayerLevelDuration=0.5;	//玩家动画显示的时间
	
	//缘分
	uint ColorValueLoveNotReach = 0xffdcfcff;
	uint ColorValueLoveReach = 0xffa200ff;
	
	//统计
	string TalkingDataAppKey="50482234633C82D9F23F9DAC6B4CF123";
	string TalkingDataChannelId="SelfTest";
	
	string UmengAppkey="5336752356240bc79d026d94";
	string UmengChannelId="SelfTest";
	uint GameAssistantCount=10;//游戏助手索引
	float GameAssistantMailTime=.5f;//游戏助手索引
	
	//array界面动画数据
	float EquipRuneSwitchingTime = 0.2f;
	float ArraySelectMoveTime = 0.2f;
	float EquipRuneSwitchingMoveDistance = 500.0f;
	float ArraySelectMoveDistance = 745.0f;
	
	//英雄强化动画数据
	float HeroSelectMoveTime = 0.2f;
	float HeroSelectLayerMoveDistance = 745.0f;
	float HeroHeadIconMoveDistance = 380.0f;
	uint ColorValueLevelUp = 0xff00ff00;
	
	//pvp排行榜动画数据
	float PvpListMoveTime = 0.2f;
	float PvpListMoveDistance = 745.0f;
	
	//公告
	uint SystemAnnouncementInterpolation = 20;
	uint SystemAnnouncementInterMinpolation = 5;
	float SystemAnnouncementInterpolationBeginTime = 0.8f;
	float SystemAnnouncementInterpolationEndTime = 0.2f;
	uint SystemAnnouncementInterpolationHeight = 200;
	float SystemAnnouncementInterpolationSpeed = 0.7f;
	
	//提示框动作数据
	float ToastShowTime = 0.5f;


    array<uint> RoleIDs;
    array<uint> RoleLevels;


    PaperConfig()
    {
		CloudAnimations.insertLast("CloudMap.ani");
		
		CreatePlayerHeroesFile.insertLast("UICreateRoleGaren.ani");
		CreatePlayerHeroesFile.insertLast("UICreateRoleAshe.ani");
		CreatePlayerHeroesFile.insertLast("UICreateRoleRyze.ani");

        RoleIDs.insertLast(1);
        RoleIDs.insertLast(2);
        RoleIDs.insertLast(3);

        RoleLevels.insertLast(1);
        RoleLevels.insertLast(2);
        RoleLevels.insertLast(3);

    }
    
    
	
	
}