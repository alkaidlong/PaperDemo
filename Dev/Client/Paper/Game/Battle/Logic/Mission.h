#pragma once
#include "Core/Script/ScriptObject.h"
#include "Game/Battle/Logic/Role.h"
#include "Core/Collection/Dictionary.h"
USING_MEDUSA;

class Mission
{
public:
	Mission(uint id);
	~Mission(void);
public:
	void LoadResource();
	void Initialize();
	void Uninitialize();
	void OnEnter();
public:
	void Update(float dt);
	void AddRole(Role* role,int index = -1);//0-4
	const ScriptObject* GetScript() const { return mScript; };
private:
	ScriptObject* mScript;
	List<Role*> mMissionRoles;
	Dictionary<uint,Role*> mPlayerRole; 	
};