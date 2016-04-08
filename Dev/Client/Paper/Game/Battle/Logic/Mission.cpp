#include "Game/Battle/Logic/Mission.h"
#include "Game/PaperScript.h"
#include "Game/Battle/BattleManager.h"
#include "Game/Battle/UI/BattleSkillButtonLayer.h"

Mission::Mission(uint id)
{
	PaperScript::Instance().LoadMissionScript(id);
	mScript = PaperScript::Instance().NewMissionScriptObject(id);
}

Mission::~Mission(void)
{
	
}

void Mission::LoadResource()
{
	mScript->Invoke("LoadResource");
}

void Mission::Initialize()
{
 	FOR_EACH_COLLECTION(i,mPlayerRole)
 	{
 		Role* role = (*i).Value;
 		BattleSkillButtonLayer* button = BattleManager::Instance().GetBattleLayer()->GetSkillButton((*i).Key);
 		button->Initialize(role);
 	}
	mScript->Invoke("Initialize");
}

void Mission::Uninitialize()
{
	mScript->Invoke("Uninitialize");
	SAFE_DELETE(mScript);
	FOR_EACH_COLLECTION(i,mMissionRoles)
	{
		Role* role = *i;
		role->Uninitialize();
		SAFE_DELETE(role);
	}

	FOR_EACH_COLLECTION(i,mPlayerRole)
	{
		Role* role = (*i).Value;
		role->Uninitialize();
	}
}

void Mission::OnEnter()
{
	mScript->Invoke("IntoBattle");
}

void Mission::Update(float dt)
{
	mScript->Invoke("Update",dt);
}

void Mission::AddRole(Role* role,int index)
{
	RETURN_IF_NULL(role);
	if(index<0)
	{
		mMissionRoles.Add(role);
	}
	else if(role->GetTeam() == RoleType::Player)
	{
		mPlayerRole.Add(index,role);
	}
	mScript->Invoke("AddRole",(int)role->GetScript(),index);
}

