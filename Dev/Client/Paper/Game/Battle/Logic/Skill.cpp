#include "Game/Battle/Logic/Skill.h"
#include "Game/PaperScript.h"

Skill::Skill(uint id,uint level)
{
	PaperScript::Instance().LoadSkillScript(id);
	mScript = PaperScript::Instance().NewSkillScriptObject(id);
}

Skill::~Skill(void)
{
	
}

void Skill::LoadResource()
{
	mScript->Invoke("LoadResource");
}

void Skill::Initialize()
{
	mScript->Invoke("Initialize");
}

void Skill::Uninitialize()
{
	mScript->Invoke("Uninitialize");
	SAFE_DELETE(mScript);
}

void Skill::Update(float dt)
{
	mScript->Invoke("Update",dt);
}

void Skill::SetPause(bool isPause)
{
	mScript->Invoke("SetPause",isPause);
}
