#pragma once
#ifdef MEDUSA_PROTOBUF
#define NOMINMAX
#endif

#include <list>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdarg>
#include <cassert>
#include <ctime>
#include <typeinfo>
#include <math.h>
#include <assert.h>

#include <stdio.h>
#include <ios>
#include <stdarg.h>
#include <sys/stat.h>   
#include <fcntl.h>   
#include <stdlib.h>  
#include <fstream>
#include <memory>
#include <stdint.h>

#ifdef MEDUSA_WINDOWS
#include "CoreLib/win/CoreLib_win.h"

#elif MEDUSA_IOS
#include "CoreLib/ios/CoreLib_ios.h"

#elif MEDUSA_MAC

#elif MEDUSA_ANDROID
#include "CoreLib/android/CoreLib_android.h"
#elif MEDUSA_LINUX
#include "CoreLib/linux/CoreLib_linux.h"
#else

#endif



#ifdef MEDUSA_PROTOBUF

#undef TYPE_BOOL //avoid collision from Mac OS X's ConditionalMacros.h
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/descriptor.h>

#undef NOMINMAX

#endif


#ifdef MEDUSA_ZIP
#include "CoreLib/Common/zip/zip.h"
#include "CoreLib/Common/zip/unzip.h"
#endif

#ifdef MEDUSA_VFP
#include "CoreLib/Common/vfp/matrix_impl.h"
#endif

#ifdef MEDUSA_NEON
#include "CoreLib/Common/neon/math_neon.h"
#include "CoreLib/Common/neon/neon_matrix_impl.h"
#endif

#ifdef MEDUSA_ZLIB
#include "CoreLib/Common/zlib/zlib.h"
#endif

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript/include/angelscript.h"
#include "CoreLib/Common/angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "CoreLib/Common/angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "CoreLib/Common/angelscript/add_on/scriptarray/scriptarray.h"
#include "CoreLib/Common/angelscript/add_on/scriptdictionary/scriptdictionary.h"
#include "CoreLib/Common/angelscript/add_on/scripthelper/scripthelper.h"
#include "CoreLib/Common/angelscript/add_on/scriptany/scriptany.h"
#include "CoreLib/Common/angelscript/add_on/scripthandle/scripthandle.h"
#endif

#include "CoreLib/Common/Unicode/ConvertUTF.h"


#ifdef MEDUSA_7Z

#include "CoreLib/Common/7z/LzmaDec.h"

#endif


#ifdef MEDUSA_XML
#include "CoreLib/Common/pugixml/pugixml.hpp"

#endif // MEDUSA_XML

