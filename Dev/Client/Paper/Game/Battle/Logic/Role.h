#pragma once
#include "Core/Script/ScriptObject.h"
#include "Game/Battle/Data/RoleProperty.h"
#include "Core/IO/FileId.h"
#include "Game/Battle/BattleCommon.h"

USING_MEDUSA;

class Role
{
public:
	Role(uint id);
	~Role(void);
public:
	void LoadResource();
	void Initialize();
	void Uninitialize();
public:
//	void Update(float dt);
	void SetPause( bool isPause );
	void IntoBattle();
	void OutBattle();
public:
	const ScriptObject* GetScript() const { return mScript; };
	bool CanTirggerSkill() const { return mScript->InvokeReturnBool("CanTirggerSkill"); }
	int GetMP() const { return mScript->GetMemberValueOrDefault<float>("mMP",0); }
	int GetHP() const { return mScript->GetMemberValueOrDefault<float>("mHP",0); }
	StringRef GetFaceName()const{ return mScript->GetMemberStringOrDefault("IconName","JarvenIVIcon.png"); };
	int GetColorID() const { return mScript->GetMemberValueOrDefault<int>("ColorID",1); }
	StringRef GetColorName()const{ return mScript->GetMemberStringOrDefault("ColorName","RoleIconGreen.png"); };
	FileId GetColorFileID() const { return FileId(GetColorName(),GetColorID()); }
	const RoleProperty GetProperty() const { return mProperty;};
	RoleType GetTeam() const { return mTeam; }
	void SetTeam(RoleType team){ mTeam = team;mScript->SetMemberValue("mTeam",(int)mTeam); };
	float GetRoleProperty(BasePropertyType type);
private:
	RoleType mTeam;
	ScriptObject* mScript;
	RoleProperty mProperty;
};