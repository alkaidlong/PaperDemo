#pragma  once
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Script/ScriptObject.h"
#include "Core/Collection/Dictionary.h"
#include "Core/IO/FileId.h"
#include "Core/Pattern/IInitializable.h"
MEDUSA_BEGIN;

class ScriptModule:public Pattern::IInitializable
{
public:
	ScriptModule(StringRef name);
	~ScriptModule();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();

	bool Build();

	StringRef GetName()const{return mName;}


	bool LoadScript( FileId scriptFile);
	bool UnloadScript( FileId scriptFile);


	ScriptObject* NewObject(StringRef className);
	ScriptObject* NewObjectWithInt(StringRef className,int address);

	bool NewObjects(StringRef className,size_t count,List<ScriptObject*>& outObjects);

	asIScriptModule* GetScriptModule() const { return mScriptModule; }

private:
	static int OnInclude(const char *include, const char *from, CScriptBuilder *builder, void *userParam);
private:
	HeapString mName;
	asIScriptModule* mScriptModule;
	CScriptBuilder mScriptBuilder;

	Dictionary<FileId,HeapString> mBuiltScriptFiles;
	Dictionary<FileId,HeapString> mLoadingScriptFiles;

};

MEDUSA_END;