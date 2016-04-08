// MockMessageCenter.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>

#include "Config/ServerGameConfig.h"
#include "Config/FeatureConfig.h"
#include "Config/PlayerLevelConfig.h"
#include "Config/HeroLevelConfig.h"
#include "Config/PetLevelConfig.h"
#include "Config/SkillLevelConfig.h"
#include "Config/AuraConfig.h"
#include "Config/BufferConfig.h"
#include "Config/EquipConfig.h"
#include "Config/HeroConfig.h"
#include "Config/MissionConfig.h"
#include "Config/MonsterConfig.h"
#include "Config/PetConfig.h"
#include "Config/PVEConfig.h"
#include "Config/SkillConfig.h"
#include "Config/VIPConfig.h"
#include "Config/ItemConfig.h"
#include "Config/ServerGameConfig.h"
#include "Config/EquipLevelConfig.h"
#include "Config/PaperConfig.h"



#include "Core/Log/Log.h"
#include "Core/System/System.h"
#include "Core/Memory/MemoryData.h"

#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/Event/ThreadEventDispatcher.h"
#include "Core/Message/MessageDispatcher.h"
#include "Core/String/FuckyString/FuckyString.h"
#include "Core/String/StringTable/StringTable.h"

#include "PaperCoreScript.h"
#include "Message/Player.h"

#include "MockMessageCenter.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/Coder/CoderPool.h"
#include "Core/Config/ServerConfig.h"
#include "Core/Config/ServerList.h"
USING_MEDUSA;

Player* gPlayer=NULL;

void Initialize()
{
	Log::Initialize();
	System::Instance().Initialize("","Save","Temp");
	//initialize coder, first decrypt,next decompress
	MemoryByteData xorKey=MemoryByteData::FromStatic(PaperConfig::Instance().mCryptoKey);
	FileSystem::Instance().GetFileList().InitializeDefaultCoder(PaperConfig::Instance().IsEncrypted,xorKey,PaperConfig::Instance().IsCompressed);

	//initialize resource manager
	FileSystem::Instance().Initialize("FileList.bin","FileSystem.bin");
	EnvironmentTag tag=EnvironmentTag::MatchAll;
	FileSystem::Instance().ApplyTag(tag);

	PaperCoreScript::Instance().Initialize();
	PaperConfig::Instance().Initialize();
	ThreadEventDispatcher::Instance().Start();
	StringTable::Instance().Initialize();
	ServerConfig::Instance().Initialize();

	ServerGameConfig::Instance().Initialize();
	MessageDispatcher::Instance().Initialize();
	
	ServerList::Instance().InitializeMessageServer(PaperConfig::Instance().MessageRetryTimes(),PaperConfig::Instance().MessageRetryInterval());

	FuckyString::Instance().Initialize();
	FeatureConfig::Instance().Initialize();
	PlayerLevelConfig::Instance().Initialize();
	HeroLevelConfig::Instance().Initialize();
	PetLevelConfig::Instance().Initialize();
	SkillLevelConfig::Instance().Initialize();
	EquipLevelConfig::Instance().Initialize();

	AuraConfig::Instance().Initialize();
	BufferConfig::Instance().Initialize();
	EquipConfig::Instance().Initialize();
	HeroConfig::Instance().Initialize();
	MissionConfig::Instance().Initialize();
	MonsterConfig::Instance().Initialize();
	PetConfig::Instance().Initialize();
	PVEConfig::Instance().Initialize();
	SkillConfig::Instance().Initialize();
	VIPConfig::Instance().Initialize();
	ItemConfig::Instance().Initialize();

	MessageDispatcher::Instance().Start();

	gPlayer=new Player();
	gPlayer->Load();

	MockMessageCenter::Instance().SetPlayer(gPlayer);


}

void Uninitialize()
{
	UIEventDispatcher::Instance().Clear();
	ThreadEventDispatcher::Instance().Stop();
	ThreadEventDispatcher::Instance().Clear();
	if (gPlayer!=NULL)
	{
		gPlayer->Save();
	}
	SAFE_DELETE(gPlayer);

	::google::protobuf::ShutdownProtobufLibrary();
	MessageDispatcher::Instance().Stop();
	MessageDispatcher::Instance().Uninitialize();

	MessageDispatcher::Instance().ClearUp();

	ServerGameConfig::Instance().Uninitialize();
	PaperConfig::Instance().Uninitialize();
	PaperCoreScript::Instance().Uninitialize();

	CoderPool::Instance().Clear();

}
void OnDumpPlayerCompleted(IMessage* sender,MessageEventArg e)
{
	Log::LogInfo("OK!");

}


void OnLoginCompleted(IMessage* sender,MessageEventArg e)
{
	MockMessageCenter::Instance().DumpPlayerData("12323434",OnDumpPlayerCompleted);
}

void BeginLogin()
{
	MockMessageCenter::Instance().Login("12323434",OnLoginCompleted);

}

bool Loop(float dt)
{
	MessageDispatcher::Instance().Update(dt);
	UIEventDispatcher::Instance().Dispatch();

	static bool isSendMessage=false;
	if (!isSendMessage)
	{
		BeginLogin();
		isSendMessage=true;
	}

	return true;
}



int main(int argc, TCHAR* argv[])
{
	Initialize();

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);
	float dt;
	while (1)
	{
		// Get current time tick.
		QueryPerformanceCounter(&nNow);
		dt=(float)(nNow.QuadPart - nLast.QuadPart)/nFreq.QuadPart;

		// If it's the time to draw next frame, draw it, else sleep a while.
		if (dt>1.0/60.f)
		{
			nLast.QuadPart = nNow.QuadPart;
			if(!Loop(dt))
			{
				break;
			}

		}
		else
		{
			Sleep(1);
		}

	}


	Uninitialize();

	return 0;
}

