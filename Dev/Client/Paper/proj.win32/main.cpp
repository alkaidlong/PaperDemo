

#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
 #if ENABLE_VLD==0
 #include "CoreLib/win/vld/vld.h"
 #endif

#include "Config/PaperConfig.h"
#include "Game/PaperGame.h"

#include "Core/Profile/ProfileSample.h"
USING_MEDUSA;

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // create the application instance
    AppDelegate app;
	PaperGame::Instance().Initialize();

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("PaperHero");
	Size2F winSize=PaperConfig::Instance().GetDesignWinSize();
    eglView->setFrameSize(winSize.Width,winSize.Height);
	PaperGame::Instance().Load();
    int result= CCApplication::sharedApplication()->run();
	::google::protobuf::ShutdownProtobufLibrary();


	return result;
}
