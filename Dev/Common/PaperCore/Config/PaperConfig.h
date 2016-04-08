#pragma once

#include "Core/Pattern/Singleton.h"
#include "Core/System/EnvironmentTag.h"
#include "Core/Script/ScriptObject.h"
#include "Core/Geometry/Size2.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point2.h"
#include "Core/IO/FileId.h"
#include "Core/Collection/List.h"
USING_MEDUSA;

class PaperConfig:public Pattern::Singleton<PaperConfig>
{
public:
	PaperConfig(void);
	~PaperConfig(void){}
	const static bool IsEncrypted;
	const static bool IsCompressed;
	const static uint32 MessageVersion;
	const static byte mCryptoKey[190];
public:
	bool Initialize();
	bool Uninitialize();
	Size2F GetDesignWinSize() const;
public:
	std::string CommonClickEffect()const{return mScriptObject->GetMemberValueOrDefault<std::string>("CommonClickEffect","CommonClick.wav");}
	Medusa::CoreProto::EnvironmentTag_Versions Version()const{return mScriptObject->GetMemberValueOrDefault<Medusa::CoreProto::EnvironmentTag_Versions>("Version",Medusa::CoreProto::EnvironmentTag_Versions_main);}
	Medusa::CoreProto::EnvironmentTag_Devices Device()const{return mScriptObject->GetMemberValueOrDefault<Medusa::CoreProto::EnvironmentTag_Devices>("Device",Medusa::CoreProto::EnvironmentTag_Devices_hd);}
	Medusa::CoreProto::EnvironmentTag_Languages Language()const{return mScriptObject->GetMemberValueOrDefault<Medusa::CoreProto::EnvironmentTag_Languages>("Language",Medusa::CoreProto::EnvironmentTag_Languages_zhcn);}
	EnvironmentTag GetEnvironmentTag()const{return EnvironmentTag(Version(),Device(),Language());}
	float ToastShowTime()const{return mScriptObject->GetMemberValueOrDefault<float>("ToastShowTime",0.5f);}
	List<uint> GetRolesConfig();
private:
	ScriptObject* mScriptObject;
};

