#pragma once
#include "CorePlatform/CorePlatform.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/TuplePattern.h"
#include "Core/String/StringRef.h"
#include "Core/Threading/Thread.h"

USING_MEDUSA;


struct NewScript5
{
	ScriptModule* module;
	StringRef name;
	uint id;
	int address;
	ScriptObject* result;
};

struct NewScript4
{
	ScriptModule* module;
	StringRef name;
	uint id;
	ScriptObject* result;
};

struct NewScript3
{
	ScriptModule* module;
	StringRef name;
	ScriptObject* result;
};

class PaperCoreScript:public Pattern::Singleton<PaperCoreScript>
{
	friend class Pattern::Singleton<PaperCoreScript>;
	PaperCoreScript(void);
	~PaperCoreScript(void){}

public:
	bool Initialize(bool includeClientConfig=true);
	bool Uninitialize();

	ScriptModule* GetUIScriptModule() const { return mUIScriptModule; }
	ScriptModule* GetGameScriptModule() const { return mGameScriptModule; }
	ScriptModule* GetCommonScriptModule() const { return mCommonScriptModule; }

public:
	ScriptObject* NewPaperConfigObject();
	ScriptObject* NewServerGameConfigObject();
public:
	void LoadScriptHelper(ScriptModule* module,StringRef name);
	void LoadScriptHelper(ScriptModule* module,StringRef name,uint id);

	ScriptObject* NewScriptObjectHelper(ScriptModule* module,StringRef typeName);
	ScriptObject* NewScriptObjectHelper(ScriptModule* module,StringRef name,uint id);
	ScriptObject* NewScriptObjectHelper(ScriptModule* module,StringRef name,uint id,int address);

	void OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript3>* e );
	void OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript4>* e );
	void OnNewScriptObjectHelper( void* sender,Medusa::UserDataEventArg<NewScript5>* e );
public:
	void InitialzeUIScriptModule();
	void InitialzeGameScriptModule();
	void InitialzeCommonScriptModule(bool includeClientConfig=true);

	void ResetUIScriptModule();
	void ResetGameScriptModule();
	void ResetCommonScriptModule();

private:
	ScriptObject* NewScript(ScriptModule* module,StringRef name);
	ScriptObject* NewScript(ScriptModule* module,StringRef name,uint id);
	ScriptObject* NewScript(ScriptModule* module,StringRef name,uint id,int address);
private:
	ScriptModule* mUIScriptModule;
	ScriptModule* mGameScriptModule;
	ScriptModule* mCommonScriptModule;
	ThreadIdType mMainThreadId;
};

