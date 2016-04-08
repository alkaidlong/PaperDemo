
#include "Game/PaperGame.h"
#include "Config/PaperConfig.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/IO/Updater/FileUpdater.h"
#include "Core/Profile/ProfileSample.h"
#include "Core/Event/ThreadEventDispatcher.h"
#include "Core/Message/MessageDispatcher.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/System/System.h"
#include "Scene/SceneManager.h"
#include "Core/String/StringTable/StringTable.h"
#include "Core/String/FuckyString/FuckyString.h"
#include "Core/String/RandomName/RandomName.h"
#include "Engine/Animation/AnimationManager.h"
#include "Engine/Resource/ResourceManager.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/IO/FileId.h"
#include "Scene/Editor/LayerEditor.h"

#include "Core/IO/FileSystem/FileSystem.h"
#include "Game/PaperScript.h"

#include "Scene/Event/InputManager.h"


#include "Core/Coder/XOR/XORDecoder.h"
#include "Core/Coder/LZMA/LZMADecoder.h"

#include "Core/Coder/CoderPool.h"
#include "Core/Event/EventArg/UserDataEventArg.h"

#include "Engine/Audio/AudioManager.h"
#include "Analytics/Analytics.h"

#include "BusinessPlatform/BusinessPlatformFactory.h"
#include "PaperVersion.h"
#include "Scene/Story/StoryManager.h"

#include "Core/IO/File.h"
#include "Core/Log/Log.h"

#include "Config/RoleConfig.h"
#include "Config/SkillConfig.h"
#include "Config/PaperConfig.h"
#include "Config/BufferConfig.h"
#include "Game/UI/Main/MainScene.h"
#include "Game/UI/Main/GameBlackAroundLayer.h"

#include "Game/Battle/BattleManager.h"
#include "Game/Battle/UI/BattleScene.h"

PaperGame::PaperGame( void )
{

}


bool PaperGame::Initialize()
{
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//MEDUSA_PROFILE("Initialize");


	Log::Initialize();

#ifdef MEDUSA_ANDROID
	System::Instance().SetApkPath(cocos2d::CCFileUtils::sharedFileUtils()->GetApplicationPath(),cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath());
	SystemUI::Instance().SetShowAlertViewCallback(cocos2d::CCMessageBox);
#endif

	System::Instance().Initialize("","Save","Temp");


	CCDirector::sharedDirector()->SetLoopCallback(LoopCallback);
	CCDirector::sharedDirector()->SetEndCallback(EndCallback);

	//initialize coder, first decrypt,next decompress
	MemoryByteData xorKey=MemoryByteData::FromStatic(PaperConfig::mCryptoKey);
	FileSystem::Instance().GetFileList().InitializeDefaultCoder(PaperConfig::IsEncrypted,xorKey,PaperConfig::IsCompressed);

	//initialize resource manager
	FileSystem::Instance().Initialize("FileList.bin","FileSystem.bin");
	ResourceManager::Instance().Load();

	PaperScript::Instance().Initialize();
	PaperConfig::Instance().Initialize();
	RoleConfig::Instance().Initialize();
	BufferConfig::Instance().Initialize();
	SkillConfig::Instance().Initialize();
	BattleManager::Instance().Initialize();
	CCDirector::sharedDirector()->SetVersionInfo(PaperVersion::AssemblyVersion.ToString().c_str());


#ifdef MEDUSA_WINDOWS
#ifdef MEDUSA_DEBUG
	Environment::Instance().SetTag(PaperConfig::Instance().GetEnvironmentTag());
#endif
#endif
		
//	ThreadEventDispatcher::Instance().Start();
	StringTable::Instance().Initialize();

	Log::LogInfo("*****Application Start*****");
	Log::LogInfoFormat("Version:%d",PaperConfig::Instance().Version());
	Log::LogInfoFormat("Device:%d",PaperConfig::Instance().Device());
	Log::LogInfoFormat("Language:%d",PaperConfig::Instance().Language());

	return true;
}


bool PaperGame::Load()
{
	FileSystem::Instance().Uninitialize();
	FileSystem::Instance().Initialize("FileList.bin","FileSystem.bin");

	//reload resource manager
	ResourceManager::Instance().Load();

	//reload paper config
	MessageDispatcher::Instance().ClearUp();

	PaperConfig::Instance().Uninitialize();		//must before PaperScript
	PaperScript::Instance().Uninitialize();

	PaperScript::Instance().Initialize();
	PaperConfig::Instance().Initialize();


	StringTable::Instance().Unload();
	StringTable::Instance().Initialize();

	RandomName::Instance().Initialize();


	FuckyString::Instance().Initialize();
	SkillConfig::Instance().Initialize();
	RoleConfig::Instance().Initialize();
	BattleManager::Instance().Initialize();

	AudioManager::Instance().SetIsMusicEnabled(true);
	AudioManager::Instance().SetIsEffectEnabled(true);

	Log::LogInfo("*****Application Reload*****");
	Log::LogInfoFormat("Version:%d",PaperConfig::Instance().Version());
	Log::LogInfoFormat("Device:%d",PaperConfig::Instance().Device());
	Log::LogInfoFormat("Language:%d",PaperConfig::Instance().Language());


	return true;
}

bool PaperGame::Uninitialize()
{
	BusinessPlatformFactory::Uninitialize();

	FileUpdater::Instance().Uninitialize();

	SceneManager::Instance().Uninitialize();
	UIEventDispatcher::Instance().ClearWithoutRun();
// 	ThreadEventDispatcher::Instance().Stop();
// 	ThreadEventDispatcher::Instance().Clear();


	::google::protobuf::ShutdownProtobufLibrary();
	MessageDispatcher::Instance().Stop();
	MessageDispatcher::Instance().Uninitialize();
	HTTPClient::Uninitialize();


	MessageDispatcher::Instance().ClearUp();

	PaperConfig::Instance().Uninitialize();
	FOR_EACH_COLLECTION(i,mRoleLibrary)
	{
		Role* role = (*i).Value;
		role->Uninitialize();
	}
	BattleManager::Instance().Uninitialize();
	SAFE_DELETE_DICTIONARY_VALUE(mRoleLibrary);
	PaperScript::Instance().Uninitialize();
	AnimationManager::Instance().UnInitialize();
	CoderPool::Instance().Clear();

	Log::Uninitialize();
	Analytics::Uninitialize();
	
	MEDUSA_PROFILE_PRINT();
	return true;
}


void PaperGame::LoopCallback( float dt )
{
	AnimationManager::Instance().Update(dt);
	InputManager::Instance().Update(dt);
	MessageDispatcher::Instance().Update(dt);
	SceneManager::Instance().Update(dt);
	BattleManager::Instance().Update(dt);
	UIEventDispatcher::Instance().Dispatch();
}

void PaperGame::EndCallback()
{
	PaperGame::Instance().Uninitialize();
}

void PaperGame::StartWithGameBlackAround()
{
	GameBlackAroundLayer *layer=LayerEditor::Instance().CreateLayer<GameBlackAroundLayer>();
	layer->Initialize();
}

void PaperGame::InitRoles()
{
	List<uint> roles = PaperConfig::Instance().GetRolesConfig();
	FOR_EACH_COLLECTION(i,roles)
	{
		Role* role = new Role(*i);
		role->LoadResource();
		role->SetTeam(RoleType::Player);
		mRoleLibrary.Add(*i,role);
	}
}

bool PaperGame::EnterBackGround()
{
	AudioManager::Instance().PauseBackgroundMusic();
	AudioManager::Instance().PauseAllEffect();
	return true;
}

bool PaperGame::EnterForeground()
{
	AudioManager::Instance().ResumeBackgroundMusic();
	AudioManager::Instance().ResumeAllEffect();
	return true;
}

Role* PaperGame::FindRole(uint roleID)
{
	Role* role = mRoleLibrary.TryGetValueWithFailed(roleID,NULL);
	Log::AssertNotNullFormat(role," RoleID    %d ! ",roleID);
	return role;
}

bool PaperGame::StartWithSelectRole()
{
	MainScene* scene=new MainScene();
	if (scene->init())
	{
		scene->autorelease();
		SceneManager::Instance().PushScene(scene);
		scene->Initialize();
		scene->SwitchToSelectRole();
		return true;
	}
	else
	{
		SAFE_DELETE(scene);
		return false;
	}
	return true;
}

bool PaperGame::SwitchToBattle()
{
	BattleManager::Instance().LoadResource();
	BattleScene* battleScene=new BattleScene();
	if (battleScene->init())
	{
		battleScene->autorelease();
		battleScene->Initialize();
		BattleManager::Instance().InitBattle();
		SceneManager::Instance().ReplaceScene(battleScene,false);
		BattleManager::Instance().OnEnterBattle();
		return true;
	}
	else
	{
		SAFE_DELETE(battleScene);
		return false;
	}
	return true;
}

bool PaperGame::SwitchToSelectRole()
{
	MainScene* scene=new MainScene();
	if (scene->init())
	{
		scene->autorelease();
		SceneManager::Instance().ReplaceScene(scene,false);
		scene->Initialize();
		scene->SwitchToSelectRole();
		return true;
	}
	else
	{
		SAFE_DELETE(scene);
		return false;
	}
	return true;
}
