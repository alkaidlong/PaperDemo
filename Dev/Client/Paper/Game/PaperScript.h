#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Script/ScriptModule.h"
#include "Engine/Animation/IAnimation.h"
#include "PaperCoreScript.h"

USING_MEDUSA;
class BattleRole;
class PaperScript:public Pattern::Singleton<PaperScript>
{
	friend class Pattern::Singleton<PaperScript>;
	PaperScript(void);
	~PaperScript(void){}
public:
	bool Initialize();
	bool Uninitialize();

	ScriptModule* GetUIScriptModule() const { return PaperCoreScript::Instance().GetUIScriptModule(); }
	ScriptModule* GetGameScriptModule() const { return PaperCoreScript::Instance().GetGameScriptModule(); }
	ScriptModule* GetCommonScriptModule() const { return PaperCoreScript::Instance().GetCommonScriptModule(); }


public:
	ScriptObject* NewPaperConfigObject();
	ScriptObject* NewServerGameConfigObject();



public:
	void LoadScript(StringRef name);
	ScriptObject* NewScriptObject(StringRef name);

	void LoadMissionScript(uint id);
	ScriptObject* NewMissionScriptObject(uint id);

	void LoadRoleScript(uint id);
	ScriptObject* NewRoleScriptObject(uint id);

	void LoadSkillScript(uint id);
	ScriptObject* NewSkillScriptObject(uint id);

	void LoadBufferScript(uint id);
	ScriptObject* NewBufferScriptObject(uint id);

	void LoadPetScript(uint id);
	ScriptObject* NewPetScriptObject(uint id);

	void LoadGuideScript(StringRef name);
	ScriptObject* NewGuideScriptObject(StringRef name,uint id);
private:
	void InitialzeUIScriptModule();
	void InitialzeGameScriptModule();
	void InitialzeCommonScriptModule();

};

