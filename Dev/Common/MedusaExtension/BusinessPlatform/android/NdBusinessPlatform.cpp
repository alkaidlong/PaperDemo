#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatform/NdBusinessPlatform.h"
#include "BusinessPlatform/BusinessPlatformLoginEventArg.h"
#include "BusinessPlatform/BusinessPlatformPayEventArg.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_ANDROID

bool NdBusinessPlatform::Initialize()
{
	return true;
}

bool NdBusinessPlatform::Uninitialize()
{
	return true;
}

void NdBusinessPlatform::EnableLog(bool val)
{

}

void NdBusinessPlatform::EnableCrashReport(bool val)
{

}


void NdBusinessPlatform::EnableDebug(bool val)
{

}

#pragma region UI
void NdBusinessPlatform::ShowToolBar(Alignment alignment)
{

}

void NdBusinessPlatform::HideToolBar()
{

}

void NdBusinessPlatform::SetOrientation(Orientation val)
{

}

void NdBusinessPlatform::EnableAutoRotation(bool val)
{

}

void NdBusinessPlatform::ShowUserFeedback()
{

}

void NdBusinessPlatform::ShowPausePage()
{

}


void NdBusinessPlatform::ShowMainPage()
{

}


#pragma endregion UI

#pragma region Auth

void NdBusinessPlatform::Login()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=true;

	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void NdBusinessPlatform::LoginAsGuest()
{
	BusinessPlatformLoginEventArg e;
	e.IsLogined=true;
	e.IsGuestLogined=true;


	if (mLoginDelegate.IsValid())
	{
		mLoginDelegate(this,e);
	}
}

void NdBusinessPlatform::RegisterGuest()
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

bool NdBusinessPlatform::IsLogined()
{
	return true;
}

bool NdBusinessPlatform::IsAutoLogin()
{
	return true;
}

Medusa::BusinessPlatformLoginState NdBusinessPlatform::GetLoginState()
{
	return BusinessPlatformLoginState::Normal;
}

void NdBusinessPlatform::Logout(bool isClearAutoLogin/*=true*/)
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

void NdBusinessPlatform::LogoutAndSwitchAccount()
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

void NdBusinessPlatform::EnterAccountManage()
{

}

HeapString NdBusinessPlatform::GetSessionId()
{
	return HeapString::Empty;
}

HeapString NdBusinessPlatform::GetUserId()
{
	return HeapString::Empty;
}

HeapString NdBusinessPlatform::GetUserNickName()
{
	return HeapString::Empty;
}

#pragma endregion Auth


#pragma region Pay

int NdBusinessPlatform::Pay(const StringRef& orderSerial,const StringRef& productId,const StringRef& productName,float price,float originalPrice,uint count,const StringRef& description)
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

#endif

MEDUSA_END;
