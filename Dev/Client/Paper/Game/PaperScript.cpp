
#include "Game/PaperScript.h"
#include "Core/Script/ScriptManager.h"
#include "Core/Log/Log.h"
#include "Engine/Animation/IAnimation.h"
#include "Engine/Animation/AnimationManager.h"
#include "Proto/Server/Config/SkillConfig.pb.h"
#include "Config/SkillConfig.h"
#include "Scene/Editor/LayerEditor.h"

PaperScript::PaperScript( void )
{
}


bool PaperScript::Initialize()
{
	PaperCoreScript::Instance().Initialize();

	InitialzeCommonScriptModule();
	InitialzeUIScriptModule();
	InitialzeGameScriptModule();


	return true;
}


bool PaperScript::Uninitialize()
{
	PaperCoreScript::Instance().Uninitialize();
	return true;
}


void PaperScript::InitialzeUIScriptModule()
{

}

void PaperScript::InitialzeGameScriptModule()
{
}

void PaperScript::InitialzeCommonScriptModule()
{

}


ScriptObject* PaperScript::NewPaperConfigObject()
{
	return PaperCoreScript::Instance().NewPaperConfigObject();
}

ScriptObject* PaperScript::NewServerGameConfigObject()
{
	return PaperCoreScript::Instance().NewServerGameConfigObject();
}

void PaperScript::LoadScript( StringRef name )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),name);
}

ScriptObject* PaperScript::NewScriptObject( StringRef name )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),name);
}

void PaperScript::LoadRoleScript( uint id )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Role",id);
}

ScriptObject* PaperScript::NewRoleScriptObject( uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Role",id);
}

void PaperScript::LoadMissionScript( uint id )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Mission",id);
}

ScriptObject* PaperScript::NewMissionScriptObject( uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Mission",id);
}

void PaperScript::LoadSkillScript( uint id )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Skill",id);
}

ScriptObject* PaperScript::NewSkillScriptObject( uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Skill",id);
}

void PaperScript::LoadBufferScript( uint id )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Buffer",id);
}

ScriptObject* PaperScript::NewBufferScriptObject( uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Buffer",id);
}

void PaperScript::LoadPetScript( uint id )
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Pet",id);
}

ScriptObject* PaperScript::NewPetScriptObject( uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetGameScriptModule(),"Pet",id);
}

void PaperScript::LoadGuideScript(StringRef name)
{
	PaperCoreScript::Instance().LoadScriptHelper(PaperCoreScript::Instance().GetCommonScriptModule(),name);
}

ScriptObject* PaperScript::NewGuideScriptObject( StringRef name,uint id )
{
	return PaperCoreScript::Instance().NewScriptObjectHelper(PaperCoreScript::Instance().GetCommonScriptModule(),name,id);
}
