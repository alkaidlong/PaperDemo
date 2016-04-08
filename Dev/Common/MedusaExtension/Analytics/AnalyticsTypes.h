#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

enum class AnalyticsReportPolicy
{
	RealTime = 0,       //实时发送
	Batch = 1,          //启动发送
	Daily = 4,      //每日发送
	WifiOnly = 5,   //仅在WIFI下启动时发送
	Interval = 6,   //按最小间隔发送
	OnExit = 7        //退出或进入后台时发送
};

// 帐户类型
enum class AnalyticsAccountType
{
	Anonymous = 0,      // 匿名帐户
	Registered = 1,     // 显性注册帐户
	SinaWeibo = 2,      // 新浪微博
	QQ = 3,             // QQ帐户
	TencentWeibo = 4,   // 腾讯微博
	ND91 = 5,           // 91帐户
	Type1 = 11,         // 预留1
	Type2 = 12,         // 预留2
	Type3 = 13,         // 预留3
	Type4 = 14,         // 预留4
	Type5 = 15,         // 预留5
	Type6 = 16,         // 预留6
	Type7 = 17,         // 预留7
	Type8 = 18,         // 预留8
	Type9 = 19,         // 预留9
	Type10 = 20         // 预留10
};

// 性别
enum class AnalyticsAccountGender
{
	Unknown = 0,     // 未知
	Male = 1,        // 男
	Female = 2       // 女
};

STRONG_ENUM_3(AnalyticsCurrencyType,CNY,USD,EUR);
STRONG_ENUM_8(AnalyticsPaymentType,AppStore,AliPay,WebBank,QQPay,ChinaMobile,Unicom,Telecom,Paypal);
STRONG_ENUM_3(AnalyticsRewardType,FromPlayer,FromCompany,FromGame);

typedef Pattern::Delegate<void()> AnalyticsOnlineConfigDelegate;

MEDUSA_END;