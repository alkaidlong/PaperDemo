
#include "PaperCoreScript.h"
#include "Core/Script/ScriptManager.h"
#include "Core/Log/Log.h"
#include "Core/Threading/Thread.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/Event/EventArg/UserDataEventArg.h"


PaperCoreScript::PaperCoreScript( void )
{
	mUIScriptModule=NULL;
	mGameScriptModule=NULL;
	mCommonScriptModule=NULL;
}


bool PaperCoreScript::Initialize(bool includeClientConfig/*=true*/)
{
	ScriptManager::Instance().Initialize();
	InitialzeCommonScriptModule(includeClientConfig);
	InitialzeUIScriptModule();
	InitialzeGameScriptModule();

	mMainThreadId=Thread::GetCurrentThreadId();
	//register global functions


	return true;
}


bool PaperCoreScript::Uninitialize()
{
	ScriptManager::Instance().Uninitialize();
	mUIScriptModule=NULL;
	mGameScriptModule=NULL;
	mCommonScriptModule=NULL;
	return true;
}


void PaperCoreScript::InitialzeUIScriptModule()
{
	mUIScriptModule=ScriptManager::Instance().CreateModule("UI");
}

void PaperCoreScript::InitialzeGameScriptModule()
{
	mGameScriptModule=ScriptManager::Instance().CreateModule("Game");
}

void PaperCoreScript::InitialzeCommonScriptModule(bool includeClientConfig/*=true*/)
{
	mCommonScriptModule=ScriptManager::Instance().CreateModule("Common");
	if (includeClientConfig)
	{
		mCommonScriptModule->LoadScript("PaperConfig.cs");
	}
	mCommonScriptModule->LoadScript("ServerGameConfig.cs");

	if(!mCommonScriptModule->Build())
	{
		Log::AssertFailedFormat("Cannot build common module");
	}

}

void PaperCoreScript::ResetUIScriptModule()
{
	mUIScriptModule->Uninitialize();
}

void PaperCoreScript::ResetGameScriptModule()
{
	mGameScriptModule->Uninitialize();
}

void PaperCoreScript::ResetCommonScriptModule()
{
	mCommonScriptModule->Uninitialize();
}



ScriptObject* PaperCoreScript::NewPaperConfigObject()
{
	return NewScriptObjectHelper(mCommonScriptModule,"PaperConfig");
}

ScriptObject* PaperCoreScript::NewServerGameConfigObject()
{
	return NewScriptObjectHelper(mCommonScriptModule,"ServerGameConfig");
}

void PaperCoreScript::LoadScriptHelper( ScriptModule* module,StringRef name )
{
	StackString<128> scriptFile=name;
	scriptFile+=".cs";
	if(!module->LoadScript(scriptFile.c_str()))
	{
		Log::AssertFailedFormat("Cannot load script file:%s",scriptFile.c_str());
		return;
	}
	if(!module->Build())
	{
		Log::AssertFailedFormat("Cannot build script file:%s",scriptFile.c_str());
	}
}

void PaperCoreScript::LoadScriptHelper(ScriptModule* module,StringRef name,uint id )
{
	StackString<128> scriptFile=name;
	scriptFile+=StringParser::ToString(id);
	scriptFile+=".cs";

//	Log::LogInfoFormat("Load script:%s",scriptFile.c_str());
	if(!module->LoadScript(scriptFile.ToString()))
	{
		Log::AssertFailedFormat("Cannot load script file:%s",scriptFile.c_str());
		return;
	}
	if(!module->Build())
	{
		Log::AssertFailedFormat("Cannot build script file:%s",scriptFile.c_str());
	}
}

ScriptObject* PaperCoreScript::NewScriptObjectHelper( ScriptModule* module,StringRef typeName )
{
	if(Medusa::Thread::IsInSameThread(mMainThreadId))
	{
		return NewScript(module,typeName);
	}
	else
	{
		NewScript3 newScriptData;
		newScriptData.module = module;
		newScriptData.name = typeName;
		newScriptData.result = NULL;
		Medusa::UserDataEventArg<NewScript3>* e=new Medusa::UserDataEventArg<NewScript3>(newScriptData);

		Medusa::UIEventDispatcher::Instance().FireEventAsync(Medusa::Pattern::Delegate<void (void* sender,Medusa::UserDataEventArg<NewScript3>*)>(this,&PaperCoreScript::OnNewScriptObjectHelper),(void*)NULL,e);

		while (!e->Handled)
		{
			Medusa::Thread::Sleep(0);
		}

		ScriptObject* scriptObject = e->GetData().result;
		SAFE_DELETE(e);

		if (scriptObject==NULL)
		{
			Log::AssertFailedFormat("Invalid script class:%s",typeName.c_str());
			return NULL;
		}
		return scriptObject;
	}
}

ScriptObject* PaperCoreScript::NewScriptObjectHelper( ScriptModule* module,StringRef name,uint id )
{
	if(Medusa::Thread::IsInSameThread(mMainThreadId))
	{
		return NewScript(module,name,id);
	}
	else
	{
		NewScript4 newScriptData;
		newScriptData.module = module;
		newScriptData.name = name;
		newScriptData.id = id;
		newScriptData.result = NULL;
		Medusa::UserDataEventArg<NewScript4>* e=new Medusa::UserDataEventArg<NewScript4>(newScriptData);

		Medusa::UIEventDispatcher::Instance().FireEventAsync(Medusa::Pattern::Delegate<void (void* sender,Medusa::UserDataEventArg<NewScript4>*)>(this,&PaperCoreScript::OnNewScriptObjectHelper),(void*)NULL,e);

		while (!e->Handled)
		{
			Medusa::Thread::Sleep(0);
		}

		ScriptObject* scriptObject = e->GetData().result;
		SAFE_DELETE(e);

		if (scriptObject==NULL)
		{
			Log::AssertFailedFormat("Invalid script class:%s%d",name.c_str(),id);
			return NULL;
		}
		return scriptObject;
	}
}

ScriptObject* PaperCoreScript::NewScriptObjectHelper( ScriptModule* module,StringRef name,uint id,int address )
{
	if(Medusa::Thread::IsInSameThread(mMainThreadId))
	{
		return NewScript(module,name,id,address);
	}
	else
	{
		NewScript5 newScriptData;
		newScriptData.module = module;
		newScriptData.name = name;
		newScriptData.id = id;
		newScriptData.address = address;
		newScriptData.result = NULL;
		Medusa::UserDataEventArg<NewScript5>* e=new Medusa::UserDataEventArg<NewScript5>(newScriptData);

		Medusa::UIEventDispatcher::Instance().FireEventAsync(Medusa::Pattern::Delegate<void (void* sender,Medusa::UserDataEventArg<NewScript5>*)>(this,&PaperCoreScript::OnNewScriptObjectHelper),(void*)NULL,e);

		while (!e->Handled)
		{
			Medusa::Thread::Sleep(0);
		}

		ScriptObject* scriptObject = e->GetData().result;
		SAFE_DELETE(e);

		if (scriptObject==NULL)
		{
			Log::AssertFailedFormat("Invalid script class:%s%d",name.c_str(),id);
			return NULL;
		}
		return scriptObject;
	}
}


ScriptObject* PaperCoreScript::NewScript( ScriptModule* module,StringRef name,uint id,int address )
{
	StackString<128> typeName=name;
	typeName+=StringParser::ToString(id);

	ScriptObject* result=module->NewObjectWithInt(typeName,address);
	if (result==NULL)
	{
		Log::AssertFailedFormat("Invalid %s script class:%s",name.c_str(),typeName.c_str());
		return NULL;
	}

	return result;
}

ScriptObject* PaperCoreScript::NewScript( ScriptModule* module,StringRef name,uint id )
{
	StackString<128> typeName=name;
	typeName+=StringParser::ToString(id);

	ScriptObject* result=module->NewObject(typeName);
	if (result==NULL)
	{
		Log::AssertFailedFormat("Invalid %s script class:%s",name.c_str(),typeName.c_str());
		return NULL;
	}

	return result;
}

ScriptObject* PaperCoreScript::NewScript( ScriptModule* module,StringRef name )
{
	ScriptObject* result=module->NewObject(name);
	if (result==NULL)
	{
		Log::AssertFailedFormat("Invalid script class:%s",name.c_str());
		return NULL;
	}

	return result;
}

void PaperCoreScript::OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript5>* e )
{
	ScriptObject* scriptObject = NewScript(e->GetData().module,e->GetData().name,e->GetData().id,e->GetData().address);
	e->GetDataRef().result=scriptObject;
	e->Handled=true;
}

void PaperCoreScript::OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript4>* e )
{
	ScriptObject* scriptObject = NewScript(e->GetData().module,e->GetData().name,e->GetData().id);
	e->GetDataRef().result=scriptObject;
	e->Handled=true;
}

void PaperCoreScript::OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript3>* e )
{
	ScriptObject* scriptObject = NewScript(e->GetData().module,e->GetData().name);
	e->GetDataRef().result=scriptObject;
	e->Handled=true;
}


