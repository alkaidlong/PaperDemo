#pragma once
#include "Core/Pattern/Singleton.h"
#include "Core/Script/ScriptObject.h"
#include "Game/Battle/Logic/Role.h"
#include "Game/Battle/Logic/Mission.h"
#include "Engine/Animation/IAnimation.h"
#include "Game/Battle/UI/BattleLayer.h"
#include "Config/PaperConfig.h"
#include "Game/Battle/BattleCommon.h"
USING_MEDUSA;


class BattleManager:public Pattern::Singleton<BattleManager>
{
	friend class Pattern::Singleton<BattleManager>;
private:
	BattleManager(void);
	~BattleManager(void);
public:
	bool Initialize();
	bool Uninitialize();
public:
	void ReadyToBattle(uint missionID);
	void LoadResource();
	void InitBattle();
	void SetBattleLayer(BattleLayer* battleLayer);
	void OnEnterBattle();
	void AddRoleToBattle( Role* role, int index=-1 );
public:
	void Update(float dt);
	void Run();
	void Pause();
public:
	int RandomNumber(int minNumber,int maxNumber);

	void LoadAniamtion(const std::string& animationName);
	int CreateAnimation(const std::string& animationName);
	int PlayAnimation(int layerOrder ,bool isRepeat,const std::string& animationName,float x,float y,int zOrder);
	int PlayAnimationForAnimation(int roleAniAdd,const std::string& animationName,float x,float y,bool isRepeat,int zOrder);
	int PlayAnimationFromRole(int layerOrder,int roleAniAdd,const std::string& animationName,float offsetX,float offsetY,bool isRepeat);
	int PlayAnimationFromRoleAndSetZOrder(int layerOrder,int roleAniAdd,const std::string& animationName,float offsetX,float offsetY,bool isRepeat,int zOrder);
	void AddAnimationToLayer(int layerOrder,int roleAniAdd);
	void ReloadAniamtion(int address,bool isRepeat,const std::string& animationName);
	void RemoveAnimation( int aniAdd );
	void EndAnimation(int address);
	void PauseAnimation(int address);
	void RunAnimation(int address);
	void SetAnimationTag(int address,int tag);
	void SetAnimationVisible(int address,bool isVisible);
	void SetAnimationIsRepeat(int address,bool isRepeat );
	void SetAnimationPauseOnLastFrame(int address);
	void SetAnimationRunningState(int address,bool isSequence);
	void SetAnimationScale(int address,float scale);
	void SetAnimationFlipX(int address,bool isFlipX);
	void SetAnimationPosition(int address,float x,float y);
	void MoveAnimation(int address,float x,float y);
	float GetAnimationPositionX(int address);
	float GetAnimationPositionY(int address);
	void SetAnimationDeltaColor(int address,int a,int r,int g,int b );

public:
	int AddMissionBGLayer( const std::string& layerName, int zOrder );
	float GetLayerWidth( int address );
	void SetLayerPosition( int address, float x, float y );
	CScriptHandle GetMissionScript();
public:
	CScriptHandle CreateRoleAndAddToMission( uint roleID ,RoleType type);
	float GetRoleProperty( int roleAdd, BasePropertyType type );
public:
	CScriptHandle GetScriptHandle(int scriptAdd);
public:
	void SetMissionProgressElementPosition(uint id,float pos);
	void AddMissionProgressElement(uint id,RoleType type,float pos);
	void RemoveMissionProgressElement(uint id);
public:
	void RegisterAnimationEvent( int aniAdd,uint index,int scriptAdd,const std::string& callbackName ,int callbackParameters );
	void RemoveAnimationCallback1(int aniAdd);
	void RemoveAnimationCallback2(int aniAdd,uint index);
	void RemoveAnimationCallback3(int aniAdd,uint index,int scriptAdd);
	void RemoveAnimationCallback4(int aniAdd,uint index,int scriptAdd,const std::string& callbackName,int callbackParameters);
public://Skill
	void SkillSettlement(int roleAddress,uint skillID,uint skillLevel,CScriptArray& targets);

public:
	float GetSceneWidth() const { return PaperConfig::Instance().GetDesignWinSize().Width; }
	float BloodTime() const { return mConfig->GetMemberValueOrDefault<float>("BloodTime",2.0f); }
	float EnergyTime() const { return mConfig->GetMemberValueOrDefault<float>("EnergyTime",2.0f); }
	bool EnableExitButton() const { return mConfig->GetMemberValueOrDefault<bool>("EnableExitButton",true);  }
	BattleLayer* GetBattleLayer() { return mBattleLayer; }
protected:
	void AnimationCallBack(IAnimation* sender,uint frameIndex);
private:
	void CleanUpCallbackDict();
private:
	Mission* mMission;
	BattleLayer* mBattleLayer;
	ScriptObject* mConfig;
	Dictionary< KeyValuePair< IAnimation* ,uint > ,List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >*> mAnimationCallbackDict;
};