#include "Game/Battle/BattleManager.h"
#include "Core/Collection/Linq.h"
#include "Engine/Animation/AnimationManager.h"
#include "Core/Math/Random.h"
#include "Core/Script/ScriptManager.h"
#include "Game/PaperScript.h"
#include "Game/PaperGame.h"
#include "Scene/Editor/LayerEditor.h"
#include "Scene/Editor/LayerFactory.h"

BattleManager::BattleManager(void)
{
	mMission = NULL;
	mBattleLayer = NULL;
	mConfig = NULL;
}

BattleManager::~BattleManager(void)
{
	
}

bool BattleManager::Initialize()
{
	asIScriptEngine* engine= ScriptManager::Instance().GetScriptEngine();
	engine->SetDefaultNamespace("Game");

	engine->RegisterEnum("RoleType");
	engine->RegisterEnumValue("RoleType", "Player", (int)RoleType::Player);
	engine->RegisterEnumValue("RoleType", "NPC", (int)RoleType::NPC);
	engine->RegisterEnumValue("RoleType", "Monster", (int)RoleType::Monster);
	engine->RegisterEnumValue("RoleType", "Boss", (int)RoleType::Boss);

	engine->RegisterEnum("BasePropertyType");
	engine->RegisterEnumValue("BasePropertyType", "HP", (int)BasePropertyType::HP);
	engine->RegisterEnumValue("BasePropertyType", "HpRegeneration", (int)BasePropertyType::HpRegeneration);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalAttack", (int)BasePropertyType::PhysicalAttack);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalDefense", (int)BasePropertyType::PhysicalDefense);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalDefensePenetration", (int)BasePropertyType::PhysicalDefensePenetration);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalLifeSteal", (int)BasePropertyType::PhysicalLifeSteal);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalCritical", (int)BasePropertyType::PhysicalCritical);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalCriticalDamage", (int)BasePropertyType::PhysicalCriticalDamage);
	engine->RegisterEnumValue("BasePropertyType", "PhysicalToughness", (int)BasePropertyType::PhysicalToughness);
	engine->RegisterEnumValue("BasePropertyType", "MP", (int)BasePropertyType::MP);
	engine->RegisterEnumValue("BasePropertyType", "MPRegeneration", (int)BasePropertyType::MPRegeneration);
	engine->RegisterEnumValue("BasePropertyType", "MagicalAttack", (int)BasePropertyType::MagicalAttack);
	engine->RegisterEnumValue("BasePropertyType", "MagicalDefense", (int)BasePropertyType::MagicalDefense);
	engine->RegisterEnumValue("BasePropertyType", "MagicalDefensePenetration", (int)BasePropertyType::MagicalDefensePenetration);
	engine->RegisterEnumValue("BasePropertyType", "MagicalLifeSteal", (int)BasePropertyType::MagicalLifeSteal);
	engine->RegisterEnumValue("BasePropertyType", "MagicalCritical", (int)BasePropertyType::MagicalCritical);
	engine->RegisterEnumValue("BasePropertyType", "MagicalCriticalDamage", (int)BasePropertyType::MagicalCriticalDamage);
	engine->RegisterEnumValue("BasePropertyType", "MagicalToughness", (int)BasePropertyType::MagicalToughness);
	engine->RegisterEnumValue("BasePropertyType", "CoolingReduction", (int)BasePropertyType::CoolingReduction);
	engine->RegisterEnumValue("BasePropertyType", "AttackSpeed", (int)BasePropertyType::AttackSpeed);
	engine->RegisterEnumValue("BasePropertyType", "MoveSpeed", (int)BasePropertyType::MoveSpeed);

	engine->RegisterGlobalFunction("int Random(int minNumber,int maxNumber)",asMETHOD(BattleManager,RandomNumber),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void LoadAniamtion(string& in)",asMETHOD(BattleManager,LoadAniamtion),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("int CreateAnimation(string& in)",asMETHOD(BattleManager,CreateAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("int PlayAnimation(int layerOrder ,bool isRepeat,string& in,float x,float y,int zOrder)",asMETHOD(BattleManager,PlayAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("int PlayAnimationForAnimation(int roleAniAdd,string& in,float x,float y,bool isRepeat,int zOrder)",asMETHOD(BattleManager,PlayAnimationForAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("int PlayAnimationFromRole(int layerOrder,int roleAniAdd,string& in,float offsetX,float offsetY,bool isRepeat)",asMETHOD(BattleManager,PlayAnimationFromRole),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("int PlayAnimationFromRoleAndSetZOrder(int layerOrder,int roleAniAdd,string& in,float offsetX,float offsetY,bool isRepeat,int zOrder)",asMETHOD(BattleManager,PlayAnimationFromRoleAndSetZOrder),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void AddAnimationToLayer(int layerOrder,int roleAniAdd)",asMETHOD(BattleManager,AddAnimationToLayer),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void ReloadAniamtion(int address,bool isRepeat,string& in)",asMETHOD(BattleManager,ReloadAniamtion),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveAnimation(int aniAdd)",asMETHOD(BattleManager,RemoveAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void EndAnimation(int aniAdd)",asMETHOD(BattleManager,EndAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void PauseAnimation(int aniAdd)",asMETHOD(BattleManager,PauseAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RunAnimation(int aniAdd)",asMETHOD(BattleManager,RunAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationTag(int aniAdd,int tag)",asMETHOD(BattleManager,SetAnimationTag),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationVisible(int address,bool isVisible)",asMETHOD(BattleManager,SetAnimationVisible),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationIsRepeat(int address,bool isRepeat)",asMETHOD(BattleManager,SetAnimationIsRepeat),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationPauseOnLastFrame(int address)",asMETHOD(BattleManager,SetAnimationPauseOnLastFrame),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationRunningState(int address,bool isSequence)",asMETHOD(BattleManager,SetAnimationRunningState),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationScale(int address,float scale)",asMETHOD(BattleManager,SetAnimationScale),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationFlipX(int address,bool isFlipX)",asMETHOD(BattleManager,SetAnimationFlipX),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationPosition(int address,float x,float y)",asMETHOD(BattleManager,SetAnimationPosition),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void MoveAnimation(int address,float x,float y)",asMETHOD(BattleManager,MoveAnimation),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void GetAnimationPositionX(int address)",asMETHOD(BattleManager,GetAnimationPositionX),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void GetAnimationPositionY(int address)",asMETHOD(BattleManager,GetAnimationPositionY),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetAnimationDeltaColor(int address,int a,int r,int g,int b)",asMETHOD(BattleManager,SetAnimationDeltaColor),asCALL_THISCALL_ASGLOBAL,this);
	
	engine->RegisterGlobalFunction("int AddMissionBGLayer( string& in, int zOrder )",asMETHOD(BattleManager,AddMissionBGLayer),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("float GetLayerWidth( int address )",asMETHOD(BattleManager,GetLayerWidth),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void SetLayerPosition( int addrress, float x, float y )",asMETHOD(BattleManager,SetLayerPosition),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("ref@ GetMissionScript()",asMETHOD(BattleManager,GetMissionScript),asCALL_THISCALL_ASGLOBAL,this);

	engine->RegisterGlobalFunction("ref@ CreateRoleAndAddToMission( uint roleID ,RoleType type )",asMETHOD(BattleManager,CreateRoleAndAddToMission),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("float GetRoleProperty( int roleAdd, BasePropertyType type )",asMETHOD(BattleManager,GetRoleProperty),asCALL_THISCALL_ASGLOBAL,this);

	engine->RegisterGlobalFunction("ref@ GetScriptHandle( int scriptAdd )",asMETHOD(BattleManager,GetScriptHandle),asCALL_THISCALL_ASGLOBAL,this);

	engine->RegisterGlobalFunction("void SetMissionProgressElementPosition(uint id,float pos)",asMETHOD(BattleManager,SetMissionProgressElementPosition),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void AddMissionProgressElement(uint id,RoleType type,float pos)",asMETHOD(BattleManager,AddMissionProgressElement),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveMissionProgressElement(uint id)",asMETHOD(BattleManager,RemoveMissionProgressElement),asCALL_THISCALL_ASGLOBAL,this);

	engine->RegisterGlobalFunction("void RegisterAnimationEvent(int aniAdd,uint index,int scriptAdd,string& in,int callbackParameters)",asMETHOD(BattleManager,RegisterAnimationEvent),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveAnimationCallback(int aniAdd)",asMETHOD(BattleManager,RemoveAnimationCallback1),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveAnimationCallback(int aniAdd,uint index)",asMETHOD(BattleManager,RemoveAnimationCallback2),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveAnimationCallback(int aniAdd,uint index,int scriptAdd)",asMETHOD(BattleManager,RemoveAnimationCallback3),asCALL_THISCALL_ASGLOBAL,this);
	engine->RegisterGlobalFunction("void RemoveAnimationCallback(int aniAdd,uint index,int scriptAdd,string& in,int callbackParameters)",asMETHOD(BattleManager,RemoveAnimationCallback4),asCALL_THISCALL_ASGLOBAL,this);

	
	engine->RegisterGlobalFunction("float GetSceneWidth()",asMETHOD(BattleManager,GetSceneWidth),asCALL_THISCALL_ASGLOBAL,this);
	engine->SetDefaultNamespace("");

	ScriptModule* gameModel = PaperScript::Instance().GetGameScriptModule();
	gameModel->LoadScript("Common.cs");
	gameModel->LoadScript("RoleSkill.cs");
	gameModel->LoadScript("Role.cs");
	gameModel->LoadScript("Buffer.cs");
	gameModel->LoadScript("Mission.cs");
	gameModel->LoadScript("Skill.cs");
	gameModel->LoadScript("BattleConfig.cs");

	return true;
}

bool BattleManager::Uninitialize()
{
	if(mMission!=NULL)
	{
		mMission->Uninitialize();
		SAFE_DELETE(mMission);
	}
	CleanUpCallbackDict();
	SAFE_DELETE(mConfig);
	return true;
}

void BattleManager::CleanUpCallbackDict()
{
	SAFE_DELETE_DICTIONARY_VALUE(mAnimationCallbackDict);
	mAnimationCallbackDict.Clear();
}

void BattleManager::Update(float dt)
{
	RETURN_IF_NULL(mMission);
	mMission->Update(dt);
}

void BattleManager::Run()
{

}

void BattleManager::Pause()
{

}

void BattleManager::ReadyToBattle(uint missionID)
{
	SAFE_DELETE(mMission);
	mMission = new Mission(missionID);
	ScriptModule* gameModel = PaperScript::Instance().GetGameScriptModule();
	gameModel->Build();
	mConfig = gameModel->NewObject("BattleConfig");
}

void BattleManager::LoadResource()
{
	RETURN_IF_NULL(mMission);
	mMission->LoadResource();
}

void BattleManager::InitBattle()
{
	RETURN_IF_NULL(mMission);
	mMission->Initialize();
}

void BattleManager::SetBattleLayer(BattleLayer* battleLayer)
{
	mBattleLayer = battleLayer;
}

void BattleManager::OnEnterBattle()
{
	RETURN_IF_NULL(mMission);
	mMission->OnEnter();
}

void BattleManager::AddRoleToBattle(Role* role, int index )
{
	RETURN_IF_NULL(mMission);
	mMission->AddRole(role,index);
}

int BattleManager::RandomNumber(int minNumber,int maxNumber)
{
	Random random;
	return random.Next(minNumber,maxNumber);
}

void BattleManager::LoadAniamtion(const std::string& animationName)
{
	FileId fileID(animationName);
	RETURN_IF_FALSE(fileID.IsValid());
	IAnimation* ani = AnimationManager::Instance().CreateAnimation(false,0,fileID);
	AnimationManager::Instance().RemoveAnimation(ani);
}

int BattleManager::CreateAnimation(const std::string& animationName)
{
	FileId fileID(animationName);
	RETURN_ZERO_IF_FALSE(fileID.IsValid());
	IAnimation* ani = AnimationManager::Instance().CreateAnimation(true,0,fileID);
	ani->retain();
	return (int)ani;
}

int BattleManager::PlayAnimation(int layerOrder ,bool isRepeat,const std::string& animationName,float x,float y,int zOrder)
{
	FileId fileID(animationName);
	RETURN_ZERO_IF_FALSE(fileID.IsValid());
	IAnimation* ani = AnimationManager::Instance().CreateAnimation(isRepeat,zOrder,fileID);
	ani->setPosition(ccp(x,y));
	ani->Run();
	mBattleLayer->AddAnimationToBattlefield(layerOrder,ani);
	return (int)ani;
}

int BattleManager::PlayAnimationForAnimation(int roleAniAdd,const std::string& animationName,float x,float y,bool isRepeat,int zOrder)
{
	RETURN_ZERO_IF_ZERO(roleAniAdd);
	IAnimation* fAni = (IAnimation*) roleAniAdd;
	FileId fileID(animationName);
	RETURN_ZERO_IF_FALSE(fileID.IsValid());
	IAnimation* ani = AnimationManager::Instance().CreateAnimation(isRepeat,zOrder,fileID);
	ani->setPosition(ccp(x,y));
	ani->Run();
	fAni->addChild(ani);
	return (int)ani;
}


int BattleManager::PlayAnimationFromRole(int layerOrder,int roleAniAdd,const std::string& animationName,float offsetX,float offsetY,bool isRepeat)
{
	RETURN_ZERO_IF_ZERO(roleAniAdd);
	IAnimation* fAni = (IAnimation*) roleAniAdd;
	return PlayAnimation(layerOrder,isRepeat,animationName,fAni->getPositionX()+offsetX,fAni->getPositionY()+offsetY,fAni->getZOrder());
}

int BattleManager::PlayAnimationFromRoleAndSetZOrder(int layerOrder,int roleAniAdd,const std::string& animationName,float offsetX,float offsetY,bool isRepeat,int zOrder)
{
	RETURN_ZERO_IF_ZERO(roleAniAdd);
	IAnimation* fAni = (IAnimation*) roleAniAdd;
	return PlayAnimation(layerOrder,isRepeat,animationName,fAni->getPositionX()+offsetX,fAni->getPositionY()+offsetY,zOrder);
}

void BattleManager::AddAnimationToLayer(int layerOrder,int roleAniAdd)
{
	RETURN_IF_NULL(mBattleLayer);
	RETURN_IF_ZERO(roleAniAdd);
	IAnimation* ani = (IAnimation*)roleAniAdd;
	mBattleLayer->AddAnimationToBattlefield(layerOrder,ani);
}

void BattleManager::ReloadAniamtion(int address,bool isRepeat,const std::string& animationName)
{
	RETURN_IF_ZERO(address);
	FileId fileID(animationName);
	RETURN_IF_FALSE(fileID.IsValid());
	IAnimation* ani = (IAnimation*)address;
	ani->ReloadAnimation(isRepeat,fileID);
	ani->Run();
}

void BattleManager::EndAnimation(int address)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->End();
}

void BattleManager::PauseAnimation(int address)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->Pause();
}

void BattleManager::RunAnimation(int address)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->Run();
}

void BattleManager::SetAnimationTag(int address,int tag)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->setTag(tag);
}

void BattleManager::SetAnimationVisible(int address,bool isVisible)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->setVisible(isVisible);
}

void BattleManager::SetAnimationIsRepeat(int address,bool isRepeat)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->SetIsRepeat(isRepeat);
}

void BattleManager::SetAnimationPauseOnLastFrame(int address)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->SetPauseOnLastFrame(true);
}

void BattleManager::SetAnimationRunningState(int address,bool isSequence)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	if(isSequence)
	{
		ani->SetSequence();
	}
	else
	{
		ani->SetInverted();
	}
}

void BattleManager::SetAnimationScale(int address,float scale)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->setScale(scale);
}

void BattleManager::SetAnimationFlipX(int address,bool isFlipX)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*) address;
	ani->setFlipX(isFlipX);
}

void BattleManager::SetAnimationPosition(int address,float x,float y)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*)address;
	ani->setPosition(CCPoint(x,y));
}

void BattleManager::MoveAnimation(int address,float x,float y)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*)address;
	ani->setPositionX(ani->getPositionX()+x);
	ani->setPositionY(ani->getPositionY()+y);
}

float BattleManager::GetAnimationPositionX(int address)
{
	RETURN_ZERO_IF_ZERO(address);
	IAnimation* ani = (IAnimation*)address;
	return ani->getPositionX();
}

float BattleManager::GetAnimationPositionY(int address)
{
	RETURN_ZERO_IF_ZERO(address);
	IAnimation* ani = (IAnimation*)address;
	return ani->getPositionY();
}

void BattleManager::SetAnimationDeltaColor(int address,int a,int r,int g,int b)
{
	RETURN_IF_ZERO(address);
	IAnimation* ani = (IAnimation*)address;
	ccColor4B color4;
	color4.a = a ;
	color4.r = r ;
	color4.g = g ;
	color4.b = b ;
	ani->SetDeltaColor(color4);
}

int BattleManager::AddMissionBGLayer(const std::string& layerName, int zOrder)
{
	RETURN_ZERO_IF_NULL( mBattleLayer );
	LayerNode* node = LayerEditor::Instance().CreateLayer(FileId(layerName));
	node->setZOrder(zOrder);
	mBattleLayer->AddBGLayer(node);
	return (int)node;
}

float BattleManager::GetLayerWidth(int address)
{
	RETURN_ZERO_IF_NULL( mBattleLayer );
	RETURN_ZERO_IF_ZERO( address );
	LayerNode* node = (LayerNode*)address;
	return node->getContentSize().width;
}

void BattleManager::SetLayerPosition(int address, float x, float y)
{
	RETURN_IF_NULL( mBattleLayer );
	RETURN_IF_ZERO( address );
	LayerNode* node = (LayerNode*)address;
	node->setPosition(x,y);
}

CScriptHandle BattleManager::GetMissionScript()
{
	Log::AssertNotNull(mMission,"Mission is NULL!!");
	const ScriptObject* script = mMission->GetScript();
	return CScriptHandle(script->GetData(),script->GetData()->GetObjectType());
}

CScriptHandle BattleManager::CreateRoleAndAddToMission(uint roleID,RoleType type)
{
	Log::AssertNotNull(mMission,"Mission is NULL!!");
	Log::Assert(roleID!=0,"roleID is 0");
	Role* role = new Role(roleID);
	role->LoadResource();
	role->SetTeam(type);
	role->Initialize();
	mMission->AddRole(role);
	role->IntoBattle();
	const ScriptObject* script = role->GetScript();
	return CScriptHandle(script->GetData(),script->GetData()->GetObjectType());
}

float BattleManager::GetRoleProperty(int roleAdd, BasePropertyType type)
{
	RETURN_ZERO_IF_ZERO(roleAdd);
	Role* role = (Role*)roleAdd;
	return role->GetRoleProperty(type);
}

CScriptHandle BattleManager::GetScriptHandle(int scriptAdd)
{
	ScriptObject* script = (ScriptObject*)scriptAdd;
	return CScriptHandle(script->GetData(),script->GetData()->GetObjectType());
}

void BattleManager::SetMissionProgressElementPosition(uint id,float pos)
{
	RETURN_IF_NULL( mBattleLayer );
	BattleMissionProgressLayer* layer = mBattleLayer->GetMissionProgressLayer();
	layer->SetElementPosition(id,pos);
}

void BattleManager::AddMissionProgressElement(uint id,RoleType type,float pos)
{
	RETURN_IF_NULL( mBattleLayer );
	BattleMissionProgressLayer* layer = mBattleLayer->GetMissionProgressLayer();
	layer->AddElement(id,type,pos);
}

void BattleManager::RemoveMissionProgressElement(uint id)
{
	RETURN_IF_NULL( mBattleLayer );
	BattleMissionProgressLayer* layer = mBattleLayer->GetMissionProgressLayer();
	layer->RemoveElement(id);
}

void BattleManager::RemoveAnimation(int aniAdd)
{
	RETURN_IF_ZERO(aniAdd);
	IAnimation* ani = (IAnimation*) aniAdd;
	ani->release();
	AnimationManager::Instance().RemoveAnimation(ani);
}

void BattleManager::RegisterAnimationEvent( int aniAdd,uint index,int scriptAdd,const std::string& callbackName ,int callbackParameters )
{
	IAnimation* ani = (IAnimation*)aniAdd;

	uint resultIndex = index;
	if(index>=(uint)ani->GetFrameCount())
	{
		resultIndex = IAnimation::AnimationCallBackLast;
	}
	KeyValuePair<IAnimation*,uint> keyPair;
	KeyValuePair<int,KeyValuePair<HeapString,int> > callbackKeyPair;
	keyPair.Key = ani;
	keyPair.Value = resultIndex;
	callbackKeyPair.Key = scriptAdd;
	callbackKeyPair.Value.Key = HeapString(callbackName);
	callbackKeyPair.Value.Value = callbackParameters;
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(keyPair,NULL);
	if(callbackList==NULL)
	{
		callbackList = new List< KeyValuePair<int ,KeyValuePair<HeapString,int>> >();
		mAnimationCallbackDict.Add(keyPair,callbackList);
		ani->RegisterEvent( resultIndex, AnimationEvent::FrameHandler( this, &BattleManager::AnimationCallBack ) );
	}
	callbackList->Add(callbackKeyPair);
}

void BattleManager::RemoveAnimationCallback1(int aniAdd)
{
	List< KeyValuePair< IAnimation* ,uint > > removeList;
	FOR_EACH_COLLECTION(i,mAnimationCallbackDict)
	{
		KeyValuePair< IAnimation* ,uint > &key = (*i).Key;
		if( key.Key == (IAnimation*)aniAdd )
		{
			removeList.Add(key);
		}
	}
	RETURN_IF_ZERO( removeList.GetCount() );
	FOR_EACH_COLLECTION(i,removeList)
	{
		KeyValuePair< IAnimation* ,uint > &key = *i;

		List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(key,NULL);
		mAnimationCallbackDict.RemoveKey(key);
		SAFE_DELETE(callbackList);
	}
}

void BattleManager::RemoveAnimationCallback2(int aniAdd,uint index)
{
	KeyValuePair< IAnimation* ,uint > removeKeyPair;
	removeKeyPair.Key = (IAnimation*) aniAdd;
	uint resultIndex = index;
	if(index>=(uint)removeKeyPair.Key->GetFrameCount())
	{
		resultIndex = IAnimation::AnimationCallBackLast;
	}
	removeKeyPair.Value = resultIndex;
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(removeKeyPair,NULL);
	mAnimationCallbackDict.RemoveKey(removeKeyPair);
	SAFE_DELETE(callbackList);
}

void BattleManager::RemoveAnimationCallback3(int aniAdd,uint index,int scriptAdd)
{
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > > removeList;
	KeyValuePair< IAnimation* ,uint > removeKeyPair;
	removeKeyPair.Key = (IAnimation*) aniAdd;
	uint resultIndex = index;
	if(index>=(uint)removeKeyPair.Key->GetFrameCount())
	{
		resultIndex = IAnimation::AnimationCallBackLast;
	}
	removeKeyPair.Value = resultIndex;
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(removeKeyPair,NULL);
	RETURN_IF_NULL(callbackList);
	FOR_EACH_COLLECTION(i,*callbackList)
	{
		KeyValuePair<int ,KeyValuePair<HeapString,int> >& removeCallback = *i;
		if(removeCallback.Key == scriptAdd)
		{
			removeList.Add(removeCallback);
		}
	}
	Linq::DeleteItems(*callbackList,removeList);
	if(callbackList->IsEmpty())
	{
		mAnimationCallbackDict.RemoveKey(removeKeyPair);
		SAFE_DELETE(callbackList);
	}
}

void BattleManager::RemoveAnimationCallback4(int aniAdd,uint index,int scriptAdd,const std::string& callbackName,int callbackParameters)
{
	IAnimation* ani = (IAnimation*)aniAdd;
	uint resultIndex = index;
	if(index>=(uint)ani->GetFrameCount())
	{
		resultIndex = IAnimation::AnimationCallBackLast;
	}
	KeyValuePair<IAnimation*,uint> keyPair;
	KeyValuePair<int,KeyValuePair<HeapString,int> > callbackKeyPair;
	keyPair.Key = ani;
	keyPair.Value = resultIndex;
	callbackKeyPair.Key = scriptAdd;
	callbackKeyPair.Value.Key = HeapString(callbackName);
	callbackKeyPair.Value.Value = callbackParameters;
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(keyPair,NULL);
	RETURN_IF_NULL(callbackList);
	callbackList->Remove(callbackKeyPair);
	if(callbackList->IsEmpty())
	{
		mAnimationCallbackDict.RemoveKey(keyPair);
		SAFE_DELETE(callbackList);
	}
}

void BattleManager::SkillSettlement(int roleAddress,uint skillID,uint skillLevel,CScriptArray& targets)
{
	//结算数据
	//改变状态
	//蹦出数字
//  CScriptArray&范例
// 	RETURN_FALSE_IF_ZERO(address);
// 	RETURN_FALSE_IF_ZERO(targetRoleObjectID);
// 	BattleSkill* skill = (BattleSkill*) address;
// 	BattleRole* targetRole = mMission->TryFindRole(targetRoleObjectID);
// 	List<BattleRole*> roles;
// 	if(skill->TargetInRange(roles,targetRole,minX,maxX,isEnemy))
// 	{
// 		FOR_EACH_COLLECTION(i,roles)
// 		{
// 			BattleRole* role = *i;
// 			int id=role->GetObjectID();
// 			targets.InsertLast((void*)&id);
// 		}
// 		return true;
// 	}
// 	return false;

}

void BattleManager::AnimationCallBack( IAnimation* sender,uint frameIndex )
{
	KeyValuePair<IAnimation*,uint> keyPair;
	keyPair.Key = sender;
	keyPair.Value = frameIndex;
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > >* callbackList = mAnimationCallbackDict.TryGetValueWithFailed(keyPair,NULL);
	Log::AssertFormat(callbackList!=NULL,"Animation %x is NULL   !   index : %d " ,sender ,frameIndex );
	List< KeyValuePair<int ,KeyValuePair<HeapString,int> > > copy=*callbackList;
	FOR_EACH_COLLECTION(i,copy)
	{
		const KeyValuePair<int ,KeyValuePair<HeapString,int> >& callbackKeyPair = *i;
		ScriptObject* script = (ScriptObject*) callbackKeyPair.Key;
		script->Invoke(callbackKeyPair.Value.Key,callbackKeyPair.Value.Value);		//这里回调会被内部的给释放掉,so make a copy
	}
}
