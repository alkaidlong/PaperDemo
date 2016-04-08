#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/EnumPattern.h"


MEDUSA_BEGIN;

STRONG_ENUM_6(FileOpenMode,ReadOnly,DestoryWriteOrCreate,AppendKeepEOFOrCreate,ReadWrite,DestoryReadWriteOrCreate,AppendClearEOFOrCreate);
STRONG_ENUM_2(FileDataType,Binary,Text);
STRONG_ENUM_2(FileMode,File,Directory);





STRONG_ENUM_CUSTOM_12(FileType,Unknown,-1,png,0,jpeg,1,gif,2,pvr,3,wav,4,fsh,5,vsh,6,pod,7,pfx,8,ttf,9,fnt,10);
STRONG_ENUM_5(ImageFileType,raw,png,jpeg,gif,pvr);
STRONG_ENUM_CUSTOM_2(ShaderFileType,psh,5,vsh,6);

STRONG_ENUM_CUSTOM_3(FileBufferMode,Full,_IOFBF,Line,_IOLBF,None,_IONBF);


MEDUSA_END;