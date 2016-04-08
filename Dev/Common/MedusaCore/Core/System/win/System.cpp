#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_WINDOWS

#include "Core/System/System.h"
#include "Core/IO/Directory.h"
#include "Core/String/StringParser.h"
#include "Core/IO/File.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

System::System( void )
{
	UpdatePaths();
}


void System::UpdatePaths()
{
	wchar_t buffer[512];
	GetCurrentDirectory(sizeof(buffer),buffer);
	mApplicationPath=StringParser::ToA(buffer);
	mReadonlyPath=mApplicationPath;
	//mReadonlyPath="assets";	//TODO: just for test

	mWritablePath=mApplicationPath;

	::GetTempPath(sizeof(buffer)/sizeof(wchar_t),buffer);
	mTempPath=StringParser::ToA(buffer);

	mReadonlyPath=Path::CombineNoChecks(mReadonlyPath,mReadonlySubPath);
	mWritablePath=Path::CombineNoChecks(mWritablePath,mWritableSubPath);
	mTempPath=Path::CombineNoChecks(mTempPath,mTempSubPath);


}

MEDUSA_END;
#endif
