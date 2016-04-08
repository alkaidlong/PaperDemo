#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatform/DevBusinessPlatform.h"
#include "BusinessPlatform/BusinessPlatformLoginEventArg.h"
#include "BusinessPlatform/BusinessPlatformPayEventArg.h"

MEDUSA_BEGIN;

bool DevBusinessPlatform::Initialize()
{
	return true;
}

bool DevBusinessPlatform::Uninitialize()
{
	return true;
}

void DevBusinessPlatform::EnableLog(bool val)
{

}

void DevBusinessPlatform::EnableCrashReport(bool val)
{

}


void DevBusinessPlatform::EnableDebug(bool val)
{

}

#pragma region UI
void DevBusinessPlatform::ShowToolBar(Alignment alignment)
{

}

void DevBusinessPlatform::HideToolBar()
{

}

void DevBusinessPlatform::SetOrientation(Orientation val)
{

}

void DevBusinessPlatform::EnableAutoRotation(bool val)
{

}

void DevBusinessPlatform::ShowUserFeedback()
{

}

void DevBusinessPlatform::ShowPausePage()
{

}


void DevBusinessPlatform::ShowMainPage()
{

}


#pragma endregion UI

#pragma region Auth

void DevBusinessPlatform::Login()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=true;

	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void DevBusinessPlatform::LoginAsGuest()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=true;
	e.IsGuestLogined=true;


	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void DevBusinessPlatform::RegisterGuest()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=true;
	e.IsGuestLogined=true;
	e.IsGuestRegistered=true;

	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

bool DevBusinessPlatform::IsLogined()
{
	return true;
}

bool DevBusinessPlatform::IsAutoLogin()
{
	return true;
}

Medusa::BusinessPlatformLoginState DevBusinessPlatform::GetLoginState()
{
	return BusinessPlatformLoginState::Normal;
}

void DevBusinessPlatform::Logout(bool isClearAutoLogin/*=true*/)
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=false;
	e.IsGuestLogined=false;
	e.IsGuestRegistered=false;

	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void DevBusinessPlatform::LogoutAndSwitchAccount()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=false;
	e.IsGuestLogined=false;
	e.IsGuestRegistered=false;

	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void DevBusinessPlatform::EnterAccountManage()
{

}

HeapString DevBusinessPlatform::GetSessionId()
{
	return HeapString::Empty;
}

HeapString DevBusinessPlatform::GetUserId()
{
	return mUserId;
}

HeapString DevBusinessPlatform::GetUserNickName()
{
	return HeapString::Empty;
}

void DevBusinessPlatform::SetUserId(StringRef userId)
{
	mUserId=userId;
}

#pragma endregion Auth
#pragma region Pay

int DevBusinessPlatform::Pay(const StringRef& orderSerial,const StringRef& productId,const StringRef& productName,float price,float originalPrice,uint count,const StringRef& description)
{
	BusinessPlatformPayEventArg e;
	e.ErrorCode=BusinessPlatformPayEventArg::PayErrorCode::Success;
	e.OrderSerial=orderSerial;
	e.ProductId=productId;
	e.ProductName=productName;
	e.Price=price;
	e.OriginalPrice=originalPrice;
	e.Count=count;
	e.Description=description;

	if (mPayDelegate.IsValid())
	{
		mPayDelegate(this,e);
	}

	return 0;
}

#pragma endregion Pay

MEDUSA_END;
