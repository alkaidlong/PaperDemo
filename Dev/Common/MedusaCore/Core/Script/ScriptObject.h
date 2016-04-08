#pragma  once
#include "Core/String/HeapString.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class ScriptObject
{
public:
	ScriptObject(asIScriptObject* scriptObject);
	~ScriptObject();
	ScriptObject(const ScriptObject& obj);
	ScriptObject& operator=(const ScriptObject& obj);
public:
	StringRef GetClassName()const{return mScriptObject->GetObjectType()->GetName();}

	void Invoke(StringRef funcName);
	void Invoke(StringRef funcName,float f1);
	void Invoke(StringRef funcName,void* object);
	void Invoke(StringRef funcName,uint64 number1);
	void Invoke(StringRef funcName,int number1);
	void Invoke(StringRef funcName,int number1,int number2);
	void Invoke(StringRef funcName,int number1,int number2,int number3);
	void Invoke(StringRef funcName,int number1,int number2,float f1);
	
	int InvokeReturnInt(StringRef funcName);
	int InvokeReturnInt(StringRef funcName,int number1);
	int InvokeReturnInt(StringRef funcName,int number1,int number2);


	float InvokeReturnFloat(StringRef funcName);
	HeapString InvokeReturnString(StringRef funcName);
	bool InvokeReturnBool(StringRef funcName);
	bool InvokeReturnBool(StringRef funcName,int number);

	float GetPropertyFloat(StringRef propertyName);
	
	asIScriptObject* GetData() const { return mScriptObject; }

public:
	void* GetMemberAddress(StringRef memberName);

	StringRef GetMemberString(StringRef memberName);
	bool SetMemberString(StringRef memberName,StringRef val);
	StringRef GetMemberStringOrDefault(StringRef memberName,StringRef defaultVal);


	template<typename T>
	T GetMemberValue(StringRef memberName)
	{
		return *(T*)GetMemberAddress(memberName);
	}

	template<typename T>
	T GetMemberValueOrDefault(StringRef memberName,T defaultVal)
	{
		T* p=(T*)GetMemberAddress(memberName);
		if (p!=NULL)
		{
			return *p;
		}
		return defaultVal;
	}

	template<typename T>
	bool SetMemberValue(StringRef memberName,T val)
	{
		T* p=(T*)GetMemberAddress(memberName);
		if (p!=NULL)
		{
			*p=val;
			return true;
		}
		return false;
	}
private:
	void CacheMemberAddresses();
private:
	asIScriptObject* mScriptObject;
	Dictionary<StringRef,void*> mMemberAddresses;	//cache member address to improve performance!
};

MEDUSA_END;