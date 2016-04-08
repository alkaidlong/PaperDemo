#pragma once

#ifdef MEDUSA_WINDOWS
#include "ExtensionLib/win/ExtensionLib_win.h"

#elif MEDUSA_IOS
#include "ExtensionLib/ios/ExtensionLib_ios.h"

#elif MEDUSA_MAC

#elif MEDUSA_ANDROID
#include "ExtensionLib/android/ExtensionLib_android.h"
#elif MEDUSA_LINUX
#include "ExtensionLib/linux/ExtensionLib_linux.h"
#else

#endif


