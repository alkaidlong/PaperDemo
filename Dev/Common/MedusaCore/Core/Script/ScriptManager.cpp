#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptManager.h"
#include "CoreLib/Common/angelscript/add_on/scriptmath/scriptmath.h"

MEDUSA_BEGIN;

ScriptManager::ScriptManager()
{
	mScriptEngine=NULL;
}

ScriptManager::~ScriptManager()
{
	Uninitialize();
}

void ScriptManager::OnMessageCallback( const asSMessageInfo *msg, void *param )
{
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	Log::LogInfoFormat("%s (%d, %d) : %s : %s", msg->section, msg->row, msg->col, type, msg->message);
}


void ScriptManager::OnLog( const std::string &msg )
{
	Log::LogInfo(msg.c_str());
}

bool ScriptManager::Initialize()
{
	Uninitialize();
	mScriptEngine= asCreateScriptEngine(ANGELSCRIPT_VERSION);
	mScriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES,true);
	mScriptEngine->SetEngineProperty(asEP_AUTO_GARBAGE_COLLECT,false);
	mScriptEngine->SetMessageCallback(asFUNCTION(OnMessageCallback),0,asCALL_CDECL);
	

	RegisterTypes();
	
	return true;
}

bool ScriptManager::Uninitialize()
{
	SAFE_DELETE_DICTIONARY_VALUE(mModules);

	FOR_EACH_COLLECTION(i,mScriptContexts)
	{
		asIScriptContext* context=*i;
		SAFE_RELEASE(context);
	}
	mScriptContexts.Clear();

	SAFE_RELEASE(mScriptEngine);
	return true;
}

void ScriptManager::RegisterTypes()
{
	RegisterStdString(mScriptEngine);
	RegisterScriptArray(mScriptEngine,true);
	RegisterScriptDictionary(mScriptEngine);
	RegisterScriptAny(mScriptEngine);
	RegisterScriptHandle(mScriptEngine);
	RegisterScriptMath(mScriptEngine);

	mScriptEngine->RegisterGlobalFunction("void Log(const string &in)",asFUNCTION(OnLog),asCALL_CDECL);

}

ScriptModule* ScriptManager::CreateModule( StringRef name )
{
	ScriptModule* module=GetModule(name);
	if (module!=NULL)
	{
		module->Initialize();
		return module;
	}

	module=new ScriptModule(name);
	module->Initialize();
	mModules.Add(name,module);
	return module;
}

ScriptModule* ScriptManager::GetModule( StringRef name )
{
	return mModules.TryGetValueWithFailedByOtherKey(name,name.GetHashCode(),NULL);
}

void ScriptManager::DestoryModule( ScriptModule* module )
{
	StringRef moduelName=module->GetName();
	bool isSuccess=mModules.RemoveOtherKey(moduelName,moduelName.GetHashCode());
	if (isSuccess)
	{
		SAFE_DELETE(module);
	}
}

asIScriptContext* ScriptManager::GetScriptContext()
{
	FOR_EACH_COLLECTION(i,mScriptContexts)
	{
		asIScriptContext* context=*i;
		if (context->GetState()==asEXECUTION_FINISHED)
		{
			return context;
		}
	}

	asIScriptContext* context=mScriptEngine->CreateContext();
	mScriptContexts.Add(context);
	return context;
}


MEDUSA_END;