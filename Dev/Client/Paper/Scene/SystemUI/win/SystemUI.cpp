
#include "Platform/Platform.h"
#include "Scene/SystemUI/SystemUI.h"


#ifdef MEDUSA_WINDOWS

SystemUI::SystemUI( void )
{
	mActivityIndicatorView=NULL;
	mSupportedOrientation=OrientationMask::None;
	mAutoRotateEnabled=true;
}



void SystemUI::ShowAlertView( StringRef text,Pattern::Action0 callback )
{
	MessageBoxA(NULL, text.c_str(), "请跑步通知程序员！", MB_OK);
	if (callback!=NULL)
	{
		callback();
		assert(false);
	}
}

void SystemUI::ShowAlertView( WStringRef text,Pattern::Action0 callback )
{
	MessageBoxW(NULL, text.c_str(), L"请跑步通知程序员！", MB_OK);
	if (callback!=NULL)
	{
		callback();
		assert(false);
	}
}

void SystemUI::ShowActivityIndicator()
{
	
}

void SystemUI::HideActivityIndicator()
{
}

void SystemUI::ShowToast(StringRef text, float duration/* = 2.0f*/, ToastPosition position/* = ToastPosition::Center*/)
{

}


#endif

