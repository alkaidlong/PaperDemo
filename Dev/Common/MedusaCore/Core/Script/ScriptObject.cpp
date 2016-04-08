#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptObject.h"
#include "Core/Script/ScriptManager.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

ScriptObject::ScriptObject( asIScriptObject* scriptObject)
	:mScriptObject(scriptObject)
{
	Log::AssertNotNull(scriptObject,"scriptObject");
	mScriptObject->AddRef();
	CacheMemberAddresses();

}

ScriptObject::ScriptObject( const ScriptObject& obj )
{
	mScriptObject=obj.mScriptObject;
	if (mScriptObject!=NULL)
	{
		mScriptObject->AddRef();
	}
	CacheMemberAddresses();
}

ScriptObject& ScriptObject::operator=( const ScriptObject& obj )
{
	if (&obj!=this)
	{
		mScriptObject=obj.mScriptObject;
		if (mScriptObject!=NULL)
		{
			mScriptObject->AddRef();
		}
	}

	return *this;
}


ScriptObject::~ScriptObject()
{
	SAFE_RELEASE(mScriptObject);
}

void ScriptObject::Invoke( StringRef funcName )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();
	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,float f1 )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgFloat(0,f1);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,void* object )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();
	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgObject(0,object);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,uint64 number1 )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgQWord(0,number1);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,int number1 )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,int number1,int number2 )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->SetArgDWord(1,number2);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke( StringRef funcName,int number1,int number2,int number3 )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->SetArgDWord(1,number2);
	context->SetArgDWord(2,number3);
	context->Execute();

	asThreadCleanup();
}

void ScriptObject::Invoke(StringRef funcName,int number1,int number2,float f1)
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->SetArgDWord(1,number2);
	context->SetArgFloat(2,f1);
	context->Execute();

	asThreadCleanup();
}

float ScriptObject::InvokeReturnFloat( StringRef funcName )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return 0.f;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->Execute();

	float result = context->GetReturnFloat();
	asThreadCleanup();
	return result;
}


int ScriptObject::InvokeReturnInt(StringRef funcName,int number1)
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return 0;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->Execute();

	int result = context->GetReturnDWord();
	asThreadCleanup();
	return result;
}

int ScriptObject::InvokeReturnInt(StringRef funcName,int number1,int number2)
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return 0;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number1);
	context->SetArgDWord(1,number2);

	context->Execute();

	int result = context->GetReturnDWord();
	asThreadCleanup();
	return result;
}

int ScriptObject::InvokeReturnInt( StringRef funcName )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return 0;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->Execute();

	int result = context->GetReturnDWord();
	asThreadCleanup();
	return result;
}



bool ScriptObject::InvokeReturnBool( StringRef funcName )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return 0.f;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->Execute();


	bool result=context->GetReturnByte()!=0;
	asThreadCleanup();
	return result;
}

bool ScriptObject::InvokeReturnBool(StringRef funcName,int number)
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return false;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->SetArgDWord(0,number);
	context->Execute();


	bool result=context->GetReturnByte()!=0;
	asThreadCleanup();
	return result;
}

HeapString ScriptObject::InvokeReturnString( StringRef funcName )
{
	asIObjectType* scriptObjectType=mScriptObject->GetObjectType();

	asIScriptFunction* func=scriptObjectType->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",scriptObjectType->GetName(),funcName.c_str());
		return HeapString::Empty;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	context->Execute();

	HeapString str( (*(std::string*)context->GetReturnAddress()).c_str() );
	asThreadCleanup();
	return str;
}

float ScriptObject::GetPropertyFloat( StringRef propertyName )
{
	HeapString funcName("get_");
	funcName+=propertyName;

	asIScriptFunction* func= mScriptObject->GetObjectType()->GetMethodByName(funcName.c_str());
	if (func==NULL)
	{
		Log::AssertFailedFormat("Cannot find %s::%s",mScriptObject->GetObjectType()->GetName(),funcName.c_str());
		return 0.f;
	}

	asIScriptContext* context= ScriptManager::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);

	context->Execute();

	float result = context->GetReturnFloat();
	asThreadCleanup();
	return result;
}

void* ScriptObject::GetMemberAddress( StringRef memberName )
{
	return mMemberAddresses.TryGetValueWithFailed(memberName,NULL);
}


Medusa::StringRef ScriptObject::GetMemberString( StringRef memberName )
{
	std::string* p=(std::string*)GetMemberAddress(memberName);
	return p->c_str();
}

bool ScriptObject::SetMemberString( StringRef memberName,StringRef val )
{
	std::string* p=(std::string*)GetMemberAddress(memberName);
	if (p!=NULL)
	{
		*p=val.c_str();
		return true;
	}
	return false;
}

Medusa::StringRef ScriptObject::GetMemberStringOrDefault( StringRef memberName,StringRef defaultVal )
{
	std::string* p=(std::string*)GetMemberAddress(memberName);
	if (p!=NULL)
	{
		return p->c_str();
	}
	return defaultVal;
}

void ScriptObject::CacheMemberAddresses()
{
	mMemberAddresses.Clear();
	uint32 count=mScriptObject->GetPropertyCount();
	FOR_EACH_SIZE(i,count)
	{
		StringRef name=mScriptObject->GetPropertyName(static_cast<uint32>(i));
		void* result=mScriptObject->GetAddressOfProperty(static_cast<uint32>(i));
		mMemberAddresses.Add(name,result);
	}

}


MEDUSA_END;