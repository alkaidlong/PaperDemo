#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/IO/Directory.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;


class System:public Pattern::Singleton<System>
{
	friend class Pattern::Singleton<System>;
	System(void);
	~System(void){}
public:

#ifdef MEDUSA_ANDROID
	void SetApkPath(StringRef apkPath,StringRef apkWritePath){mApplicationPath=apkPath;mWritablePath=apkWritePath;}
#endif


	StringRef GetApplicationPath()const{return mApplicationPath;}
	StringRef GetReadonlyPath()const{return mReadonlyPath;}
	StringRef GetWritablePath()const{return mWritablePath;}
	StringRef GetTempPath()const{return mTempPath;}

	void Initialize(StringRef readonlySubPath=StringRef::Empty,StringRef writableSubPath=StringRef::Empty,StringRef tempSubPath=StringRef::Empty)
	{
		mReadonlySubPath=readonlySubPath;
		mWritableSubPath=writableSubPath;
		mTempSubPath=tempSubPath;

		UpdatePaths();
		MakeAllPathExists();
	}

	StringRef GetReadonlySubPath() const { return mReadonlySubPath; }
	void SetReadonlySubPath(StringRef val) { mReadonlySubPath = val; UpdatePaths();}

	StringRef GetWritableSubPath() const { return mWritableSubPath; }
	void SetWritableSubPath(StringRef val) { mWritableSubPath = val;UpdatePaths(); MakeAllPathExists();}

	StringRef GetTempSubPath() const { return mTempSubPath; }
	void SetTempSubPath(StringRef val) { mTempSubPath = val;UpdatePaths(); MakeAllPathExists();}

	void MakeAllPathExists()
	{
		Directory::CreateDir(GetWritablePath());
		Directory::CreateDir(GetTempPath());
	}

	HeapString GetReadonlyPath(StringRef fileName) const{return Path::CombineNoChecks(GetReadonlyPath(),fileName);}
	HeapString GetWritablePath(StringRef fileName) const{return Path::CombineNoChecks(GetWritablePath(),fileName);}
	HeapString GetTempPath(StringRef fileName) const{return Path::CombineNoChecks(GetTempPath(),fileName);}

private:
	void UpdatePaths();
private:
	HeapString mApplicationPath;
	HeapString mReadonlyPath;
	HeapString mWritablePath;
	HeapString mTempPath;

	HeapString mReadonlySubPath;
	HeapString mWritableSubPath;
	HeapString mTempSubPath;

};

MEDUSA_END;
