#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "Core/Pattern/IInitializable.h"
#include "BusinessPlatformTypes.h"
#include "Core/Geometry/GeometryDefines.h"

MEDUSA_BEGIN;


class IBusinessPlatform:public Pattern::IInitializable
{
public:
	IBusinessPlatform(const StringRef& appId=StringRef::Empty,const StringRef& appKey=StringRef::Empty):mAppId(appId),mAppKey(appKey),mIsFirstTimeLogin(true){}
	virtual ~IBusinessPlatform(){}

	bool IsFirstTimeLogin() const { return mIsFirstTimeLogin; }
	void SetIsFirstTimeLogin(bool val) { mIsFirstTimeLogin = val; }

	virtual void EnableLog(bool val)=0;
	virtual void EnableCrashReport(bool val)=0;
	virtual void EnableDebug(bool val)=0;

#pragma region UI
	virtual void ShowToolBar(Alignment alignment)=0;
	virtual void HideToolBar()=0;
	virtual void SetOrientation(Orientation val)=0;
	virtual void EnableAutoRotation(bool val)=0;
	virtual void ShowUserFeedback()=0;
	virtual void ShowPausePage()=0;
	virtual void ShowMainPage()=0;


#pragma endregion UI

#pragma region Auth
	virtual void Login()=0;
	virtual void LoginAsGuest()=0;
	virtual void RegisterGuest()=0;
	virtual bool IsLogined()=0;
	virtual bool IsAutoLogin()=0;

	virtual BusinessPlatformLoginState GetLoginState()=0;
	virtual void Logout(bool isClearAutoLogin=true)=0;
	virtual void LogoutAndSwitchAccount()=0;
	virtual void EnterAccountManage()=0;

	virtual HeapString GetSessionId()=0;
	virtual HeapString GetUserId()=0;
	virtual HeapString GetUserNickName()=0;

	BusinessPlatformLoginDelegate GetLoginDelegate() const { return mLoginDelegate; }
	void SetLoginDelegate(BusinessPlatformLoginDelegate val) { mLoginDelegate = val; }

	Medusa::BusinessPlatformPayDelegate GetPayDelegate() const { return mPayDelegate; }
	void SetPayDelegate(Medusa::BusinessPlatformPayDelegate val) { mPayDelegate = val; }
#pragma endregion Auth
	
#pragma region Pay
	//若未登录调用则返回错误码，否则返回0
	virtual int Pay(const StringRef& orderSerial,const StringRef& productId,const StringRef& productName,float price,float originalPrice,uint count,const StringRef& description)=0;
#pragma endregion Pay

	virtual void SetUserId(StringRef userId)=0;

protected:
	HeapString mAppId;
	HeapString mAppKey;
	bool mIsFirstTimeLogin;
	
	BusinessPlatformLoginDelegate mLoginDelegate;
	BusinessPlatformPayDelegate mPayDelegate;
	
	
};


MEDUSA_END;