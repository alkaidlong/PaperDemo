#pragma once
#include "Core/Pattern/Singleton.h"
#include "PaperHeader.h"
#include "Scene/Element/SpriteNode.h"
#include "Core/IO/Updater/FileUpdater.h"

class MissionCheckOutRequest;
struct BattleRewardInfo;
class Role;
USING_MEDUSA;

class PaperGame:public Pattern::Singleton<PaperGame>
{
	friend class Pattern::Singleton<PaperGame>;
	PaperGame(void);
	~PaperGame(void){}
public:
	bool Initialize();
	bool Load();
	bool Uninitialize();
	bool StartWithSelectRole();
	bool SwitchToBattle();
	bool SwitchToSelectRole();
	void StartWithGameBlackAround();

	void InitRoles();

	bool EnterBackGround();
	bool EnterForeground();
	Role* FindRole(uint roleID);
	const Dictionary<uint,Role*>& GetRoles() const { return mRoleLibrary; }
private:
	static void LoopCallback(float dt);
	static void EndCallback();
private:
	Dictionary<uint,Role*> mRoleLibrary;
};

