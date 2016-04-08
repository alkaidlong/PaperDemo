#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "IBusinessPlatform.h"
MEDUSA_BEGIN;

class NdBusinessPlatform:public IBusinessPlatform
{
public:
	NdBusinessPlatform(const StringRef& appId,const StringRef& appKey):IBusinessPlatform(appId,appKey){}
	virtual ~NdBusinessPlatform(){}


	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
	virtual void EnableLog(bool val)override;
	virtual void EnableCrashReport(bool val)override;
	virtual void EnableDebug(bool val)override;

#pragma region UI
	virtual void ShowToolBar(Alignment alignment)override;
	virtual void HideToolBar()override;
	virtual void SetOrientation(Orientation val)override;
	virtual void EnableAutoRotation(bool val)override;
	virtual void ShowUserFeedback()override;
	virtual void ShowPausePage()override;
	virtual void ShowMainPage()override;
#pragma endregion UI

#pragma region Auth
	virtual void Login()override;
	virtual void LoginAsGuest()override;
	virtual void RegisterGuest()override;
	virtual bool IsLogined()override;
	virtual bool IsAutoLogin()override;

	virtual BusinessPlatformLoginState GetLoginState()override;
	virtual void Logout(bool isClearAutoLogin=true)override;
	virtual void LogoutAndSwitchAccount()override;
	virtual void EnterAccountManage()override;
	virtual HeapString GetSessionId()override;
	virtual HeapString GetUserId()override;
	virtual HeapString GetUserNickName()override;
#pragma endregion Auth
	virtual void SetUserId(StringRef userId){}
#pragma region Pay
	//若未登录调用则返回错误码，否则返回0
	virtual int Pay(const StringRef& orderSerial,const StringRef& productId,const StringRef& productName,float price,float originalPrice,uint count,const StringRef& description);
#pragma endregion Pay
protected:
    void* mNotificationHost;
};


MEDUSA_END;