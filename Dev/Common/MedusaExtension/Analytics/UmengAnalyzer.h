#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "IAnalyzer.h"
MEDUSA_BEGIN;

class UmengAnalyzer:public IAnalyzer
{
public:
	UmengAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy=AnalyticsReportPolicy::RealTime):IAnalyzer(appKey,channelId){}
	virtual ~UmengAnalyzer(){}


	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
	virtual void EnableLog(bool val)override;
	virtual void EnableCrashReport(bool val)override;

#pragma region Account
public:
	//accountId < 64
	//accountName < 64
	//1<=level <=1000
	//0<=age <=120
	//gameServerName <16
	virtual void InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level=1,int age=18,AnalyticsAccountType accountType=AnalyticsAccountType::Registered,AnalyticsAccountGender gender=AnalyticsAccountGender::Unknown)override;
	//1<=level <=1000
	virtual void UpdateAccountLevel(int level)override;
#pragma endregion Account


#pragma region Payment
public:
	//orderId < 64
	//itemId < 32
	virtual void RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)override;
	virtual void SucceedPay(const StringRef& orderId)override;

	virtual void RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)override;

#pragma endregion Payment

#pragma region Reward
public:
	//reason < 32, support <=100 different types
	virtual void RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)override;
	virtual void RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)override;

#pragma endregion Reward

#pragma region Purchase
public:
	//itemName <=32
	virtual void Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)override;
	virtual void Use(const StringRef& itemName,int count=1,double price=0)override;
#pragma endregion Purchase

#pragma region Mission
public:
	//missionId <=32, count <500
	virtual void BeginMission(const StringRef& missionId)override;
	virtual void CompeleteMission(const StringRef& missionId)override;
	virtual void FailedMission(const StringRef& missionId,const StringRef& reason=StringRef::Empty)override;
#pragma endregion Mission

#pragma region Event
public:
	/*
	注：在某key的value取值较离散情况下，不要直接填充具体数值，而应划分
	区间后传入，否则value不同取值很可能超过平台最大数目限制，而影响最终
	展示数据的效果。
	*/
	//key,value <=32

	//每款游戏可定义最多200个不同eventId，每个eventId下，可以支持20种
	//不同key的500种不同value取值（NSString类型），并且注意每个单次事件调用时，最多只能附带10种不同key。

	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)override;

	//如果为NSNumber类型，那么TalkingData会统计value的总和/平均值。
	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)override;
	virtual void LogEvent(const StringRef& eventId)override;


	virtual void LogEvent(const StringRef& eventId,const StringRef& label)override;
	virtual void LogEvent(const StringRef& eventId,int count)override;
	virtual void LogEvent(const StringRef& eventId,const StringRef& label,int count)override;


	virtual void BeginEvent(const StringRef& eventId)override;
	virtual void EndEvent(const StringRef& eventId)override;

	virtual void BeginEvent(const StringRef& eventId,const StringRef& label)override;
	virtual void EndEvent(const StringRef& eventId,const StringRef& label)override;

	//primarykey这个参数用于和event_id一起标示一个唯一事件，并不会被统计；
	//对于同一个事件在beginEvent和endEvent 中要传递相同的eventId 和 primarykey
	//每个event的attributes不能超过10个
	//eventId、attributes中key和value都不能使用空格和特殊字符，且长度不能超过255个字符（否则将截取前255个字符）
	//id， ts， du是保留字段，不能作为eventId及key的名称
	virtual void BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)override;
	virtual void EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)override;


	virtual void LogEventTime(const StringRef& eventId,int microseconds)override;
	virtual void LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)override;
	virtual void LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)override;


	virtual void LogPageStay(const StringRef& pageName,int seconds)override;
	virtual void BeginPageStay(const StringRef& pageName)override;
	virtual void EndPageStay(const StringRef& pageName)override;
#pragma endregion Event

#pragma region Location
public:
	virtual void SetLocation(double latitude,double longitude)override;
#pragma endregion Location

#pragma region OnlineConfig
public:

	virtual void SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)override;
	virtual void UpdateConfig()override;

	virtual HeapString GetConfigString(const StringRef& key)override;
#pragma endregion OnlineConfig
    
    AnalyticsOnlineConfigDelegate GetOnlineConfigDelegate()const{return mDelegate;}
protected:
    AnalyticsOnlineConfigDelegate mDelegate;
    void* mNotificationHost;
};


MEDUSA_END;