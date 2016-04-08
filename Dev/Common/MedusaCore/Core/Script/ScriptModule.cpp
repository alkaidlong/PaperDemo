#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptModule.h"
#include "Core/Script/ScriptManager.h"

MEDUSA_BEGIN;

ScriptModule::ScriptModule(StringRef name):mName(name)
{
	mScriptModule=NULL;
	mScriptBuilder.SetIncludeCallback(OnInclude,NULL);

	
}

ScriptModule::~ScriptModule()
{
	Uninitialize();
}

bool ScriptModule::Initialize()
{
	Uninitialize();
	mScriptBuilder.StartNewModule(ScriptManager::Instance().GetScriptEngine(),mName.c_str());
	mScriptModule=mScriptBuilder.GetModule();

	return true;
}

bool ScriptModule::Uninitialize()
{
	if (mScriptModule!=NULL)
	{
		mScriptModule->Discard();
		mScriptModule=NULL;
	}
	return true;
}

int ScriptModule::OnInclude( const char *include, const char *from, CScriptBuilder *builder, void *userParam )
{
	HeapString readPath=FileSystem::Instance().GetReadFilePath(FileId(include));

	if (!builder->IsIncluded(readPath.c_str()))
	{
		MemoryByteData fileData=FileSystem::Instance().ReadAllData(include);
		if (!fileData.IsNull())
		{
			builder->AddSectionFromMemory(readPath.c_str(),(const char*)fileData.GetData(),static_cast<uint32>(fileData.GetSize()));
		}
		else
		{
			Log::LogErrorFormat("Cannot read script:%s",readPath.c_str());
		}
	}
	
	return 0;
}

bool ScriptModule::LoadScript( FileId scriptFile)
{
	if(mBuiltScriptFiles.ContainsKey(scriptFile)||mLoadingScriptFiles.ContainsKey(scriptFile))
	{
		return true;
	}

	HeapString readPath=FileSystem::Instance().GetReadFilePath(scriptFile);

	if (readPath.IsEmpty())
	{
		Log::LogErrorFormat("Cannot find script file:%s",scriptFile.Name.c_str());
		return false;
	}

	mLoadingScriptFiles.Add(scriptFile,readPath);

	return true;
}

bool ScriptModule::UnloadScript( FileId scriptFile )
{
	return mLoadingScriptFiles.RemoveKey(scriptFile);
}


bool ScriptModule::Build()
{
	FOR_EACH_COLLECTION(i,mLoadingScriptFiles)
	{
		const FileId& fileId=(*i).Key;
		const HeapString& file=(*i).Value;
		
		if (!mScriptBuilder.IsIncluded(file.c_str()))
		{
			MemoryByteData fileData=FileSystem::Instance().ReadAllData(fileId);
			if (!fileData.IsNull())
			{
				mScriptBuilder.AddSectionFromMemory(file.c_str(),(const char*)fileData.GetData(),static_cast<uint32>(fileData.GetSize()));
			}
			else
			{
				Log::LogErrorFormat("Cannot read script:%s",file.c_str());
			}
		}
		
		mBuiltScriptFiles.Add(*i);
	}

	mLoadingScriptFiles.Clear();

	return mScriptBuilder.BuildModule(false)>=0;
}

ScriptObject* ScriptModule::NewObject( StringRef className )
{
	asIObjectType* scriptObjectType=mScriptModule->GetObjectTypeByName(className.c_str());
	RETURN_NULL_IF_NULL(scriptObjectType);

	HeapString factoryName=className;
	factoryName+="@ ";
	factoryName+=className;
	factoryName+="()";
	asIScriptFunction* factory= scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	RETURN_NULL_IF_NULL(factory);

	asIScriptContext* context=ScriptManager::Instance().GetScriptContext();
	context->Prepare(factory);
	context->Execute();
	asIScriptObject* scriptObject=*(asIScriptObject**) context->GetAddressOfReturnValue();
	
	return new ScriptObject(scriptObject);
}

ScriptObject* ScriptModule::NewObjectWithInt( StringRef className,int address )
{
	asIObjectType* scriptObjectType=mScriptModule->GetObjectTypeByName(className.c_str());
	if (scriptObjectType==NULL)
	{
		Log::LogErrorFormat("Cannot find class by %s",className.c_str());
	}
	RETURN_NULL_IF_NULL(scriptObjectType);

	HeapString factoryName=className;
	factoryName+="@ ";
	factoryName+=className;
	factoryName+="(int address)";
	asIScriptFunction* factory= scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	if (factory==NULL)
	{
		Log::LogErrorFormat("Cannot find class factory by %s",factoryName.c_str());
	}
	RETURN_NULL_IF_NULL(factory);

	asIScriptContext* context=ScriptManager::Instance().GetScriptContext();
	context->Prepare(factory);
	context->SetArgDWord(0,address);
	
	context->Execute();
	asIScriptObject* scriptObject=*(asIScriptObject**) context->GetAddressOfReturnValue();

	return new ScriptObject(scriptObject);
}


bool ScriptModule::NewObjects( StringRef className,size_t count,List<ScriptObject*>& outObjects )
{
	outObjects.Clear();
	asIObjectType* scriptObjectType=mScriptModule->GetObjectTypeByName(className.c_str());
	RETURN_FALSE_IF_NULL(scriptObjectType);

	HeapString factoryName=className;
	factoryName+="@ ";
	factoryName+=className;
	factoryName+="()";
	asIScriptFunction* factory= scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	RETURN_FALSE_IF_NULL(factory);
	asIScriptContext* context=ScriptManager::Instance().GetScriptContext();

	List<ScriptObject*> result;
	FOR_EACH_SIZE(i,count)
	{
		context->Prepare(factory);
		context->Execute();
		asIScriptObject* scriptObject=*(asIScriptObject**) context->GetAddressOfReturnValue();
		ScriptObject* temp= new ScriptObject(scriptObject);
		outObjects.Add(temp);
	}

	return true;
	
}
MEDUSA_END;