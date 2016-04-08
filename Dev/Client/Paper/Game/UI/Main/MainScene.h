#pragma once
#include "Scene/IScene.h"
USING_MEDUSA;

class MissionCheckOutRequest;
struct BattleRewardInfo;

class MainScene :public IScene
{
public:
	MainScene();
	virtual ~MainScene(void);

	virtual bool Initialize();
	virtual bool Uninitialize();

	bool SwitchToSelectRole();
	bool SwitchToBattle();
protected:

};

