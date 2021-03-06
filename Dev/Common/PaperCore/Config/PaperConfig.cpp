
#include "Config/PaperConfig.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/Log/Log.h"
#include "PaperCoreScript.h"

USING_MEDUSA;

PaperConfig::PaperConfig( void )
{
	mScriptObject=NULL;
}

bool PaperConfig::Initialize()
{
	Uninitialize();
	mScriptObject=PaperCoreScript::Instance().NewPaperConfigObject();

#ifdef MEDUSA_DEBUG
	FileSystem::Instance().ApplyTag(GetEnvironmentTag());
#else
	FileSystem::Instance().ApplyTag( Environment::Instance().GetTag());
#endif
	return mScriptObject!=NULL;
}

bool PaperConfig::Uninitialize()
{
	SAFE_DELETE(mScriptObject);
	return true;
}

Size2F PaperConfig::GetDesignWinSize() const
{

#ifdef MEDUSA_DEBUG
	Medusa::CoreProto::EnvironmentTag_Devices device=Device();
#else
	const EnvironmentTag& tag=Environment::Instance().GetTag();
	Medusa::CoreProto::EnvironmentTag_Devices device=(Medusa::CoreProto::EnvironmentTag_Devices)tag.Device.ToInt();
#endif
	switch(device)
	{
	case Medusa::CoreProto::EnvironmentTag::sd:
		return Size2F(480,320);
	case Medusa::CoreProto::EnvironmentTag::hd:
		return Size2F(800,480);		//retina will *2
	case Medusa::CoreProto::EnvironmentTag::hd5:
		return Size2F(1136,640);		
	case Medusa::CoreProto::EnvironmentTag::ipad:
		return Size2F(1024,768);
	case Medusa::CoreProto::EnvironmentTag::ipad3:
		return Size2F(2048,1536);	//retina will *2
	default:
		Log::AssertFailed("Error device");
		break;
	}
	return Size2F::Zero;
}

const byte PaperConfig::mCryptoKey[190]={0x7b,0x38,0x30,0x33,0x43,0x45,0x38,0x46,0x32,0x2d,0x38,0x43,0x30,0x45,0x2d,
	0x34,0x31,0x35,0x39,0x2d,0x39,0x36,0x43,0x42,0x2d,0x39,0x32,0x31,0x44,0x38,0x39,0x43,0x30,
	0x38,0x45,0x31,0x33,0x7d,0x7b,0x32,0x35,0x31,0x39,0x43,0x30,0x37,0x37,0x2d,0x31,0x32,0x34,
	0x37,0x2d,0x34,0x41,0x46,0x35,0x2d,0x38,0x43,0x37,0x31,0x2d,0x43,0x37,0x33,0x36,0x37,0x41,0x34,
	0x38,0x31,0x43,0x32,0x44,0x7d,0x7b,0x39,0x37,0x35,0x43,0x36,0x35,0x30,0x35,0x2d,0x35,0x34,0x39,
	0x34,0x2d,0x34,0x41,0x33,0x36,0x2d,0x39,0x41,0x44,0x36,0x2d,0x42,0x34,0x38,0x39,0x30,0x42,0x30,0x45,
	0x32,0x46,0x37,0x39,0x7d,0x7b,0x42,0x30,0x44,0x43,0x36,0x42,0x37,0x32,0x2d,0x38,0x33,0x43,0x43,0x2d,
	0x34,0x45,0x38,0x31,0x2d,0x38,0x35,0x36,0x36,0x2d,0x41,0x44,0x33,0x41,0x43,0x33,0x30,0x36,0x46,0x45,
	0x33,0x41,0x7d,0x7b,0x34,0x42,0x37,0x35,0x46,0x45,0x36,0x35,0x2d,0x31,0x41,0x44,0x43,0x2d,0x34,0x37,
	0x41,0x43,0x2d,0x38,0x39,0x30,0x41,0x2d,0x32,0x39,0x33,0x41,0x44,0x32,0x41,0x31,0x39,0x36,0x38,0x44,0x7d};

List<uint> PaperConfig::GetRolesConfig()
{
	CScriptArray* ids=(CScriptArray*)mScriptObject->GetMemberAddress("RoleIDs");
	List<uint> roles;
	FOR_EACH_SIZE(i,ids->GetSize())
	{
		uint roleID = *(uint*)ids->At(i);
		roles.Add(roleID);
	}
	return roles;
}

const bool PaperConfig::IsEncrypted=false;
const bool PaperConfig::IsCompressed=false;
const uint PaperConfig::MessageVersion=2;