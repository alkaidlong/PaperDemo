#pragma once
#include "Scene/Element/LayerNode.h"
USING_MEDUSA;
#include "Scene/Element/SpriteNode.h"
#include "Core/Collection/Dictionary.h"
#include "Game/Battle/BattleCommon.h"

// class BattleMissionProgressLayer:public LayerNode
// {
// 	DECLARE_REGISTER_LAYER();
// public:
// 	struct MonsterWave
// 	{
// 		SpriteNode* SpriteIcon;
// 		float Time;
// 
// 		MonsterWave()
// 		{
// 			SpriteIcon = NULL;
// 			Time = 0.0f;
// 		}
// 
// 		~MonsterWave()
// 		{
// 			if (SpriteIcon!=NULL)
// 			{
// 				SpriteIcon->GetParentNode()->RemoveChild(SpriteIcon);
// 			}
// 			SpriteIcon=NULL;
// 		}
// 	};
// public:
// 	BattleMissionProgressLayer(const IEventArg& e=IEventArg::Empty);
// 	~BattleMissionProgressLayer();
// 
// 	virtual bool Initialize();
// 	virtual bool Uninitialize();
// 
// 	bool BeforeUpdate( float dt );
// 
// 	bool SetLimitTime(float limitTime);
// 	void Run();
// 	void Pause();
// 
// 	void AddMonsterWave(float time,bool isBoss);
// 
// protected:
// 	float mLimitTime;
// 	float mCurTime;
// 
// 	float mMoveSpeed;
// 	bool mIsRun;
// 
// 	SpriteNode* mSpriteHero;
// 	List<MonsterWave*> mMonsterWaveIcons;
// };

class BattleMissionProgressLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	BattleMissionProgressLayer(const IEventArg& e=IEventArg::Empty);
	~BattleMissionProgressLayer();
public:
	virtual bool Uninitialize();
public:
	void SetElementPosition(uint id,float pos);//位置百分比
	void AddElement(uint id,RoleType team,float pos);//位置百分比
	void RemoveElement(uint id);
public:
	Dictionary< uint, SpriteNode* > mSprites;
};