#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class Version
{
public:
	const static Version Zero;
public:
	Version(uint major=0,uint minor=0,uint build=0,uint revision=0);
	Version(const StringRef& versionString);

	Version(const Version& val);
	Version& operator=(const Version& val);
	~Version(void);

	int Compare(const Version& val)const;

	bool operator==(const Version& val)const{return Compare(val)==0;}
	bool operator!=(const Version& val)const{return !operator==(val);}
	bool operator>(const Version& val)const{return Compare(val)>0;}
	bool operator<(const Version& val)const{return Compare(val)<0;}
	bool operator>=(const Version& val)const{return Compare(val)>=0;}
	bool operator<=(const Version& val)const{return Compare(val)<=0;}


	intp GetHashCode()const{return mMajor^mMinor^mRevision^mBuild;}
	HeapString ToString(uint fieldCount=4)const;

public:
	uint Major() const { return mMajor; }
	void SetMajor(uint val) { mMajor = val; }

	uint Minor() const { return mMinor; }
	void SetMinor(uint val) { mMinor = val; }

	uint Revision() const { return mRevision; }
	void SetRevision(uint val) { mRevision = val; }

	uint Build() const { return mBuild; }
	void SetBuild(uint val) { mBuild = val; }
public:
	static Version ParseFrom(const StringRef& versionString);
	static bool TryParse(const StringRef& versionString,Version& outVersion);


protected:
	uint mMajor;
	uint mMinor;
	uint mBuild;
	uint mRevision;
};

MEDUSA_END;
