#pragma once
#include "CorePlatform/CorePlatformDefines.h"


//Features

//#define MEDUSA_FREETYPE_ST
//#define MEDUSA_FREETYPE_MT

#define MEDUSA_PNG
#define MEDUSA_JPEG
#define MEDUSA_TIFF
#define MEDUSA_PVR


//#define MEDUSA_RENDER_ASSERT_ENABLED
#define MEDUSA_RENDER_STATE_CACHE_ENABLED
#define MEDUSA_PRE_GENERATED_INDEX_ENABLED


#ifdef MEDUSA_WINDOWS
#define MEDUSA_GLEW2

#endif

/************************************************************************/
//use this to identifier with open gl
#define MEDUSA_IS_OPENGL 1
#define MEDUSA_IS_DIRECTX 0

/************************************************************************/

#define MEDUSA_DEFAULT_FPS	60.f

