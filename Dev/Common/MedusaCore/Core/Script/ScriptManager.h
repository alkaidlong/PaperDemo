#pragma  once
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Script/ScriptModule.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class ScriptManager:public Pattern::Singleton<ScriptManager>,public Pattern::IInitializable
{
	friend class Pattern::Singleton<ScriptManager>;
	ScriptManager();
	~ScriptManager();
public:
	bool Initialize();
	bool Uninitialize();
public:
	ScriptModule* CreateModule(StringRef name);
	ScriptModule* GetModule(StringRef name);
	void DestoryModule(ScriptModule* module);
	asIScriptEngine* GetScriptEngine() const { return mScriptEngine; }
	asIScriptContext* GetScriptContext();

private:
	void RegisterTypes();

	static void OnMessageCallback(const asSMessageInfo *msg, void *param);
	static int OnInclude(const char *include, const char *from, CScriptBuilder *builder, void *userParam);
	static void OnLog(const std::string &msg);
private:
	asIScriptEngine* mScriptEngine;

	List<asIScriptContext* > mScriptContexts;
	Dictionary<HeapString,ScriptModule*> mModules;
};

MEDUSA_END;