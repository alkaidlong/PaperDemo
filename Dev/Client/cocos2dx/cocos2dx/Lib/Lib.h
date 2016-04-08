#pragma once

#ifdef MEDUSA_WINDOWS
#include "Lib/win/Lib_win.h"

#elif MEDUSA_IOS
#include "Lib/ios/Lib_ios.h"

#elif MEDUSA_MAC

#elif MEDUSA_ANDROID
#include "Lib/android/Lib_android.h"
#elif MEDUSA_LINUX
#include "Lib/linux/Lib_linux.h"
#else

#endif


#if defined(MEDUSA_FREETYPE_ST) || defined(MEDUSA_FREETYPE_MT)

#include "Lib/Common/freetype/ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H
#include FT_LCD_FILTER_H

#ifdef MEDUSA_WINDOWS

#ifdef MEDUSA_FREETYPE_MT
#ifdef MEDUSA_DEBUG
#pragma comment(lib,"freetype250MT_D.lib")
#else
#pragma comment(lib,"freetype250MT.lib")
#endif
#endif

#ifdef MEDUSA_FREETYPE_ST
#ifdef MEDUSA_DEBUG
#pragma comment(lib,"freetype250ST_D.lib")
#else
#pragma comment(lib,"freetype250ST.lib")
#endif
#endif

#endif
#endif



#ifdef MEDUSA_PNG
#include "Lib/Common/libpng/png.h"
#endif

#ifdef MEDUSA_JPEG
#include "Lib/Common/libjpeg/jpeglib.h"
#endif

#ifdef MEDUSA_TIFF
#include "Lib/Common/libtiff/tiffio.h"
#endif







#ifdef MEDUSA_GLEW2
#define GLEW_STATIC
#include "Lib/win/GLEW/glew.h"

/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG			0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG			0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG			0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG			0x8C03
#endif

#ifndef GL_IMG_texture_compression_pvrtc2
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG			0x9137
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG			0x9138
#endif

#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_ETC1_RGB8_OES                                        0x8D64
#endif

#ifndef GL_OES_texture_half_float
#define GL_HALF_FLOAT_OES                                       0x8D61
#endif

#ifndef GL_IMG_shader_binary
#define GL_SGX_BINARY_IMG                                       0x8C0A
#endif

//#include "Lib/GLEW/glxew.h"
//#include "Lib/GLEW/wglew.h"

//#include "Lib/Common/OGLES/GLES2/gl2.h"
//#include "Lib/Common/OGLES/GLES2/gl2ext.h"
//#include "Lib/Common/OGLES/GLES2/gl2extimg.h"
//#include "Lib/Common/OGLES/GLES2/gl2platform.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glew32s.lib")


#endif

#ifdef MEDUSA_GLEW3
#define GLEW_STATIC
#include "Lib/Common/GLEW/glew.h"
//#include "CoreLib/Common/GLEW/glxew.h"
//#include "CoreLib/Common/GLEW/wglew.h"

//#include "CoreLib/Common/OGLES/GLES3/gl3.h"
//#include "CoreLib/Common/OGLES/GLES3/gl3ext.h"
//#include "CoreLib/Common/OGLES/GLES3/gl3platform.h"
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glew32s.lib")

#endif

#ifdef MEDUSA_GLES2
#include "Lib/Common/OGLES/EGL/egl.h"
#include "Lib/Common/OGLES/KHR/khrplatform.h"

#include "Lib/Common/OGLES/GLES2/gl2.h"
#include "Lib/Common/OGLES/GLES2/gl2ext.h"
#include "Lib/Common/OGLES/GLES2/gl2extimg.h"
#include "Lib/Common/OGLES/GLES2/gl2platform.h"

#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"libGLESv2.lib")

#endif

#ifdef MEDUSA_GLES3
#include "Lib/Common/OGLES/EGL/egl.h"
#include "Lib/Common/OGLES/KHR/khrplatform.h"

#include "Lib/Common/OGLES/GLES3/gl3.h"
#include "Lib/Common/OGLES/GLES3/gl3ext.h"
#include "Lib/Common/OGLES/GLES3/gl3platform.h"

#pragma comment(lib,"libEGL.lib")
#pragma comment(lib,"libGLESv3.lib")

#endif


#ifdef MEDUSA_PVR
#include "Lib/Common/PVR/PVRTDecompress.h"
#include "Lib/Common/PVR/OGLES2/PVRTTextureAPI.h"

#endif
