//
//  SystemTool_ios.m
//  Fly
//
//  Created by quyou on 12-12-4.
//
//
#include "Platform/Platform.h"

#ifdef MEDUSA_IOS

#include "Scene/SystemUI/SystemUI.h"
#import "EAGLView.h"
#import <UIKit/UIKit.h>
#include "Core/Log/Log.h"
#import "Toast+UIView.h"

#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/Path.h"

SystemUI::SystemUI( void )
{
	mActivityIndicatorView=NULL;
	mSupportedOrientation=OrientationMask::LeftAndRight;
	mAutoRotateEnabled=true;

}


void SystemUI::ShowAlertView( StringRef text, Pattern::Action0 callback)
{
    NSString* context = [[NSString alloc] initWithUTF8String:text.c_str()];
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"请跑步通知程序员！"
                                                    message:context
                                                   delegate:nil
                                          cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alertView show];
    if (callback != NULL)
    {
        // Callback
        callback();
    }
    [alertView release];
    [context release];
}

void SystemUI::ShowAlertView( WStringRef text, Pattern::Action0 callback)
{
    NSString* context = [[NSString alloc] initWithBytes:text.c_str() length:text.Length()*sizeof(wchar_t) encoding:kCFStringEncodingUTF32LE];
    UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"请跑步通知程序员！"
                                                        message:context
                                                       delegate:nil
                                              cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alertView show];
    if (callback != NULL)
    {
        // Callback
        callback();
    }
    [alertView release];
    [context release];
}

void SystemUI::ShowActivityIndicator()
{
    if (mActivityIndicatorView == NULL)
    {
        mActivityIndicatorView = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
        
        UIView* eaglView = [EAGLView sharedEGLView];
        ((UIActivityIndicatorView*)mActivityIndicatorView).frame = eaglView.frame;
        ((UIActivityIndicatorView*)mActivityIndicatorView).center = eaglView.center;
        ((UIActivityIndicatorView*)mActivityIndicatorView).layer.zPosition = 10;
        [[EAGLView sharedEGLView] addSubview:((UIActivityIndicatorView*)mActivityIndicatorView)];
    }
    
    [((UIActivityIndicatorView*)mActivityIndicatorView) startAnimating];
    [[EAGLView sharedEGLView] setUserInteractionEnabled:false];
}

void SystemUI::HideActivityIndicator()
{
    Log::Assert((mActivityIndicatorView != NULL), "ActivityIndicator SHOULD not be NULL");
    
    [((UIActivityIndicatorView*)mActivityIndicatorView) stopAnimating];
    [[EAGLView sharedEGLView] setUserInteractionEnabled:true];
}

void SystemUI::ShowToast(StringRef text, float duration/* = 2.0f*/, ToastPosition position/* = ToastPosition::Center*/)
{
    [[EAGLView sharedEGLView] makeToast:[NSString stringWithUTF8String:text.c_str()]
                               duration:2.0f
                               position:@"center"];
}




#endif