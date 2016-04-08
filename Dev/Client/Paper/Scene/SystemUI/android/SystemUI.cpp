
#include "Platform/Platform.h"
#include "Scene/SystemUI/SystemUI.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"


#ifdef MEDUSA_ANDROID

SystemUI::SystemUI( void )
{
	mShowAlertViewCallback=NULL;
	mActivityIndicatorView=NULL;
}



void SystemUI::ShowAlertView( StringRef text,Pattern::Action0 callback )
{
	if (mShowAlertViewCallback!=NULL)
	{
		mShowAlertViewCallback(text.c_str(),"Error");
	}
	if (callback!=NULL)
	{
		callback();
		assert(false);
	}
}

void SystemUI::ShowAlertView( WStringRef text,Pattern::Action0 callback )
{
	//CCMessageBox(text.c_str(),"Error");	
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



