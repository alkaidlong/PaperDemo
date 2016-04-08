#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/FrameNode.h"
#include "Scene/Element/ProgressBarNode.h"
#include "Scene/Element/SpriteNode.h"

USING_MEDUSA;
class IAnimation;
class Role;

class BattleSkillButtonLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	BattleSkillButtonLayer(const IEventArg& e=IEventArg::Empty);
	~BattleSkillButtonLayer();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual bool Update(float dt);
public:
	void Initialize(Role* role);
	void OnTirggerCallback(INode* sender,TapGestureEventArg&);
	void ClearEnergy();
	void ClearBlood();
	void UpdateEnergy();
	void UpdateBlood();
protected:
	IAnimation* mButtonEffect;
	SpriteNode* mRoleIcon;
	SpriteNode* mQuality;
	ProgressBarNode* mBloodProgress;
	ProgressBarNode* mBloodWhiteProgressBar;
	ProgressBarNode* mBloodReductionProgressBar;
	ProgressBarNode* mEnergyProgress;
	ProgressBarNode* mEnergyWhiteProgressBar;
	ProgressBarNode* mEnergyReductionProgressBar;
private:
	float mMaxPercentageValue;
	Role* mRole;
	float mCurMP;
	float mDesMP;
	float mMaxMP;
	float mCurHP;
	float mDesHP;
	float mMaxHP;
};
