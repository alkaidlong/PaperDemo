#pragma once
#include "Scene/IScene.h"
USING_MEDUSA;

class BattleScene :public IScene
{
public:
	BattleScene();
	virtual ~BattleScene(void);
	virtual bool Initialize();
	virtual bool Uninitialize();

	bool PauseBattle();

protected:

};

