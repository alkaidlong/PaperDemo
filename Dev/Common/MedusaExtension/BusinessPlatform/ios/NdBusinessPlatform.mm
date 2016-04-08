#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatform/NdBusinessPlatform.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"
#include "BusinessPlatformLoginEventArg.h"
#include "BusinessPlatformPayEventArg.h"

#ifdef MEDUSA_BUSINESS_PLATFORM

#ifdef MEDUSA_BUSINESS_PLATFORM_ND
#include "NdComPlatform/NdComPlatform.h"
#include "NdComPlatform/NdComPlatformAPIResponse.h"
#include "NdComPlatform/NdCPNotifications.h"
#endif

#endif

@interface NdBusinessPlatformCallbackHandler : NSObject
{
    Medusa::NdBusinessPlatform* Platform;
}
-(id)initWithPlatform:(Medusa::NdBusinessPlatform*)platform;

-(void)OnSDKInitCompleted:(NSNotification*)notification;
-(void)OnLeavePlatform:(NSNotification*)notification;
-(void)OnLogin:(NSNotification*)notification;
-(void)OnPayAsyncResult:(NSNotification*)notification;

@end

@implementation NdBusinessPlatformCallbackHandler
-(id)initWithPlatform:(Medusa::NdBusinessPlatform*)platform
{
    Platform=platform;
    return self;
}
-(void)OnSDKInitCompleted:(NSNotification*)notification
{
	//...执行应用的逻辑，例如显示工具条、登录
	
}

-(void)OnLeavePlatform:(NSNotification*)notification
{
	//...执行应用的逻辑，例如显示工具条、登录
	
}

-(void)OnPayAsyncResult:(NSNotification*)notification
{
    Medusa::BusinessPlatformPayEventArg e;

	NSDictionary *dic = [notification userInfo];
	BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
	if (!bSuccess) 
	{
		int nErrorCode = [[dic objectForKey:@"error"] intValue];
		switch (nErrorCode) 
		{
			case ND_COM_PLATFORM_ERROR_USER_CANCEL:
				e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::UserCancel;
				break;
			case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
				e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::NetworkFailed;
				break;
			case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
				e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::ServerReturnError;
				break;
			case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED:
				//!!!: 异步支付，用户进入充值界面了
				e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::OrderEstablished;
				break;
			default:
				e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::OtherFailed;
				break;
		}
	}
	else 
	{
		e.ErrorCode=Medusa::BusinessPlatformPayEventArg::PayErrorCode::Success;
	}

	//本次购买的请求参数
	NdBuyInfo* buyInfo = (NdBuyInfo*)[dic objectForKey:@"buyInfo"];
	e.OrderSerial=[buyInfo.cooOrderSerial UTF8String];
	e.ProductId=[buyInfo.productId UTF8String];
	e.ProductName=[buyInfo.productName UTF8String];
	e.Price=buyInfo.productPrice;
	e.OriginalPrice=buyInfo.productOrignalPrice;
	e.Count=buyInfo.productCount;
	e.Description=[buyInfo.payDescription UTF8String];

	Medusa::BusinessPlatformPayDelegate payDelegate=Platform->GetPayDelegate();
    if (payDelegate.IsValid()) 
	{
        payDelegate(Platform,e);
    }

}

-(void)OnLogin:(NSNotification*)notification
{
    Medusa::BusinessPlatformLoginEventArg e;
	//...执行应用的逻辑，例如显示工具条、登录
	NSDictionary *dict = [notification userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
	NdGuestAccountStatus* guestStatus = (NdGuestAccountStatus*)[dict 
	objectForKey:@"NdGuestAccountStatus"];
	//登录成功后处理
	if([[NdComPlatform defaultPlatform] isLogined] && success) 
	{
        e.IsLogined=true;
		//也可以通过[[NdComPlatform defaultPlatform] getCurrentLoginState]判断是否游客登录状态
		if (guestStatus) 
		{ 
			if ([guestStatus isGuestLogined]) 
			{
				//游客账号登录成功;
                e.IsGuestLogined=true;
			}
			else if ([guestStatus isGuestRegistered]) 
			{
				//游客成功注册为普通账号
                e.IsGuestRegistered=true;
			}
		}
		else  
		{
			//普通账号登录成功！
		}
       
	}
	
	else 
	{
        
		//登录失败处理和相应提示
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) 
		{
			case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
				if (([[NdComPlatform defaultPlatform] getCurrentLoginState] == ND_LOGIN_STATE_GUEST_LOGIN)) 
				{
					strTip =  @"当前仍处于游客登录状态";
                    e.IsLogined=true;
                    e.IsGuestLogined=true;
				}
				else 
				{
					strTip = @"用户未登录";
				}
			break;
			case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
				strTip = @"登录失败, 请检查appId/appKey";
			break;
				case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
				strTip = @"登录失败, 无效的应用ID";
			break;
				case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
				strTip = @"有关联的91账号，不能以游客方式登录";
			break;
			default:
				//其他类型的错误提示
			break;
			}
	}


    Medusa::BusinessPlatformLoginDelegate loginDelegate=Platform->GetLoginDelegate();
    if (loginDelegate.IsValid()) 
	{
        loginDelegate(Platform,e);
    }
}


@end

MEDUSA_BEGIN;

bool NdBusinessPlatform::Initialize()
{
	mNotificationHost=NULL;
	//初始化平台
	NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
	cfg.appid =StringParser::StringTo<uint>(mAppId);
	cfg.appKey =[NSString stringWithUTF8String:mAppKey.c_str()];
	//单机，弱联网必须关注 versionCheckLevel 的设置说明，详见上面说明
	cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
	//orientation 的设置详见上面的说明(这里以设置竖屏为例)
	cfg.orientation = UIInterfaceOrientationLandscapeLeft;
	[[NdComPlatform defaultPlatform] NdInit:cfg];

	NdBusinessPlatformCallbackHandler* host=[[NdBusinessPlatformCallbackHandler alloc] initWithPlatform:this];
    mNotificationHost=host;

	[[NSNotificationCenter  defaultCenter] addObserver:host
	selector:@selector(OnSDKInitCompleted:) name:(NSString*)kNdCPInitDidFinishNotification object:nil];
    
	[[NSNotificationCenter defaultCenter] addObserver:host
	selector:@selector(OnLeavePlatform:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];

	[[NSNotificationCenter defaultCenter] addObserver:host
	selector:@selector(OnPayAsyncResult:) name:(NSString *)kNdCPBuyResultNotification object:nil];

	[[NSNotificationCenter defaultCenter] addObserver:host
	selector:@selector(OnLogin:) name:(NSString *)kNdCPLoginNotification object:nil];

    ShowToolBar(Medusa::Alignment::RightBottom);
	return true;
}

bool NdBusinessPlatform::Uninitialize()
{
  if (mNotificationHost!=NULL) 
  {
        [[NSNotificationCenter defaultCenter] removeObserver:(NdBusinessPlatformCallbackHandler*)mNotificationHost name:kNdCPInitDidFinishNotification object:nil];
		[[NSNotificationCenter defaultCenter] removeObserver:(NdBusinessPlatformCallbackHandler*)mNotificationHost name:kNdCPLeavePlatformNotification object:nil];
		[[NSNotificationCenter defaultCenter] removeObserver:(NdBusinessPlatformCallbackHandler*)mNotificationHost name:kNdCPLoginNotification object:nil];
		[[NSNotificationCenter defaultCenter] removeObserver:(NdBusinessPlatformCallbackHandler*)mNotificationHost name:kNdCPBuyResultNotification object:nil];
        [(NdBusinessPlatformCallbackHandler*)mNotificationHost dealloc];
        mNotificationHost=NULL;
    }

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
/*
设定为调试模式的支付功能和升级功能，参数为预留，默认为零。
其中的支付功能和升级功能具体包括：
	1.游戏版本的检测升级
	2.91 豆余额查询和支付
	3.代币充值中的 91 豆兑换
	4.虚拟商店自定义虚拟币充值中的 91 豆兑换
*/
	if(val)
	{
		[[NdComPlatform defaultPlatform] NdSetDebugMode:0];
	}
}


#pragma region UI
void NdBusinessPlatform::ShowToolBar(Alignment alignment)
{
	switch (alignment)
	{
	case Alignment::LeftTop:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtTopLeft];
		break;
	case Alignment::LeftCenter:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtMiddleLeft];
		break;
	case Alignment::LeftBottom:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtBottomLeft];
		break;
	case Alignment::RightTop:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtTopRight];
		break;
	case Alignment::RightCenter:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtMiddleRight];
		break;
	case Alignment::RightBottom:
		[[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtBottomRight];
		break;
	default:
		break;
	}
}

void NdBusinessPlatform::HideToolBar()
{
	[[NdComPlatform defaultPlatform] NdHideToolBar];
}

void NdBusinessPlatform::SetOrientation(Orientation val)
{
	switch (val)
	{
	case Orientation::Up:
		[[NdComPlatform defaultPlatform]  NdSetScreenOrientation:UIInterfaceOrientationPortrait];
		break;
	case Orientation::Down:
		[[NdComPlatform defaultPlatform]  NdSetScreenOrientation:UIInterfaceOrientationPortraitUpsideDown];
		break;
	case Orientation::Left:
		[[NdComPlatform defaultPlatform]  NdSetScreenOrientation:UIInterfaceOrientationLandscapeLeft];
		break;
	case Orientation::Right:
		[[NdComPlatform defaultPlatform]  NdSetScreenOrientation:UIInterfaceOrientationLandscapeRight];
		break;
	default:
		break;
	}
}

void NdBusinessPlatform::EnableAutoRotation(bool val)
{
	//iPad 默认开启自动旋转，iPhone 默认关闭自动旋转
	[[NdComPlatform defaultPlatform] NdSetAutoRotation:val?YES:NO];
}

void NdBusinessPlatform::ShowUserFeedback()
{
    [[NdComPlatform defaultPlatform] NdUserFeedBack];
}

void NdBusinessPlatform::ShowPausePage()
{
    [[NdComPlatform defaultPlatform] NdPause];
}


void NdBusinessPlatform::ShowMainPage()
{
    [[NdComPlatform defaultPlatform] NdEnterPlatform:0];
}


#pragma endregion UI


#pragma region Auth

void NdBusinessPlatform::Login()
{
    [[NdComPlatform defaultPlatform] NdLogin:0];
}

void NdBusinessPlatform::LoginAsGuest()
{
[   [NdComPlatform defaultPlatform] NdLoginEx:0];
}

void NdBusinessPlatform::RegisterGuest()
{
    [[NdComPlatform defaultPlatform] NdGuestRegist:0];
}

bool NdBusinessPlatform::IsLogined()
{
    return [[NdComPlatform defaultPlatform] isLogined];
}

bool NdBusinessPlatform::IsAutoLogin()
{
    return [[NdComPlatform defaultPlatform] isAutoLogin];
}

Medusa::BusinessPlatformLoginState NdBusinessPlatform::GetLoginState()
{
    ND_LOGIN_STATE state=[[NdComPlatform defaultPlatform] getCurrentLoginState];
	return (BusinessPlatformLoginState)state;
}

void NdBusinessPlatform::Logout(bool isClearAutoLogin/*=true*/)
{
    [[NdComPlatform defaultPlatform] NdLogout:isClearAutoLogin?1:0];
}

void NdBusinessPlatform::LogoutAndSwitchAccount()
{
    [[NdComPlatform defaultPlatform] NdSwitchAccount];
}

void NdBusinessPlatform::EnterAccountManage()
{
    [[NdComPlatform defaultPlatform] NdEnterAccountManage];
}

HeapString NdBusinessPlatform::GetSessionId()
{
    NSString* str=[[NdComPlatform defaultPlatform] sessionId];
    const char* str2= [str UTF8String];
	return HeapString(str2);
}

HeapString NdBusinessPlatform::GetUserId()
{
    NSString* str=[[NdComPlatform defaultPlatform] loginUin];
    const char* str2= [str UTF8String];
	return HeapString(str2);
}

HeapString NdBusinessPlatform::GetUserNickName()
{
    NSString* str=[[NdComPlatform defaultPlatform] nickName];
    const char* str2= [str UTF8String];
	return HeapString(str2);
}

#pragma endregion Auth

int NdBusinessPlatform::Pay(const StringRef& orderSerial,const StringRef& productId,const StringRef& productName,float price,float originalPrice,uint count,const StringRef& description)
{
	NdBuyInfo *buyInfo = [[NdBuyInfo new] autorelease];
	buyInfo.cooOrderSerial = [NSString stringWithUTF8String:orderSerial.c_str()];
	buyInfo.productId = [NSString stringWithUTF8String:productId.c_str()];  //自定义的产品ID
	buyInfo.productName =[NSString stringWithUTF8String:productName.c_str()];  //产品名称
	buyInfo.productPrice = price; //产品现价，价格大等于0.01,支付价格以此为准
	buyInfo.productOrignalPrice = originalPrice; //产品原价，同现价保持一致
	buyInfo.productCount = count;  //产品数量
	buyInfo.payDescription  =  [NSString stringWithUTF8String:description.c_str()];

	return [[NdComPlatform defaultPlatform] NdUniPay:buyInfo];
}

MEDUSA_END;
