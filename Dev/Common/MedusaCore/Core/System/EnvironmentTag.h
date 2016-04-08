#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/EnvironmentTag.pb.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

STRONG_FLAGS_2(PublishVersions,main,free);

//sd = 1, //480*320
//hd = 2, //960*640
//hd5 = 4, //1136*640
//ipad = 8, //1024*768
//ipad3 = 16, //2048*1536.

STRONG_FLAGS_5(PublishDevices,sd,hd,hd5,ipad,ipad3);
STRONG_FLAGS_2(PublishLanguages,enus,zhcn);


class EnvironmentTag
{
public:
	EnvironmentTag();
	EnvironmentTag(CoreProto::EnvironmentTag_Versions targetVersion,CoreProto::EnvironmentTag_Devices targetDevice,CoreProto::EnvironmentTag_Languages targetLanguage)
		:Version(targetVersion),Device(targetDevice),Language(targetLanguage){}

	EnvironmentTag(PublishVersions targetVersion,PublishDevices targetDevice,PublishLanguages targetLanguage)
		:Version(targetVersion),Device(targetDevice),Language(targetLanguage){}
	
	EnvironmentTag(int tag)
		:Version((tag&0xFF0000)>>16),Device((tag&0x00FF00)>>8),Language(tag&0x0000FF){}

	intp GetHashCode()const{return GetTag();}
	bool operator<(const EnvironmentTag& tag)const{return GetTag()<tag.GetTag();}
	int GetTag()const{return (Version.ToInt()<<16)|(Device.ToInt()<<8)|(Language.ToInt());}
	void SetTag(int tag){Version.ForceSet((tag&0xFF0000)>>16);Device.ForceSet((tag&0x00FF00)>>8);Language.ForceSet(tag&0x0000FF);}


	static int GetDiffScore(PublishVersions fileVersion,PublishVersions targetVersion);
	static int GetDiffScore(PublishDevices fileDevice,PublishDevices targetDevice);
	static int GetDiffScore(PublishLanguages fileLanguage,PublishLanguages targetLanguage);
	int GetDiffScore(const EnvironmentTag& tag)const;

	bool IsMatch(const EnvironmentTag& tag)const;

	bool operator==(const EnvironmentTag& tag)const{return Version==tag.Version&&Device==tag.Device&&Language==tag.Language;}

	static EnvironmentTag Parse(StringRef fileName);


	PublishVersions Version;
	PublishDevices Device;
	PublishLanguages Language;

	const static EnvironmentTag MatchAll;

private:
	static Dictionary<StringRef,int> mTagDict;
	static void InitializeDict();
	MEDUSA_DECLARE_STATIC_CONSTRUCTOR();
};

MEDUSA_END;
