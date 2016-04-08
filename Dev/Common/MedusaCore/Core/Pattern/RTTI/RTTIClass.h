#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Compile/TypeInfo.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Pattern
{
	class RTTIClass
	{
	public:
		RTTIClass(const Compile::TypeInfo& typeInfo,StringRef className,const RTTIClass* baseClass=NULL)
			:mTypeInfo(typeInfo),mClassName(className),mBaseClass(baseClass)
		{

		}

		RTTIClass()
			:mBaseClass(NULL)
		{

		}
        ~RTTIClass(){}
		bool operator==(const RTTIClass& rhs)const	{ return mTypeInfo == rhs.GetTypeInfo(); }
		bool operator!=(const RTTIClass& rhs)const	{ return !(*this== rhs); }    
		bool operator<(const RTTIClass& rhs)const	{ return mTypeInfo<rhs.mTypeInfo; }
		bool operator>(const RTTIClass& rhs)const	{ return mTypeInfo>rhs.mTypeInfo; }
		bool operator<=(const RTTIClass& rhs)const	{ return mTypeInfo<=rhs.mTypeInfo; }
		bool operator>=(const RTTIClass& rhs)const	{ return mTypeInfo>=rhs.mTypeInfo; }


		RTTIClass& operator=(const RTTIClass& rhs){mTypeInfo=rhs.mTypeInfo;mBaseClass=rhs.mBaseClass;mClassName=rhs.mClassName;return *this;}
	public:
		const Compile::TypeInfo& GetTypeInfo() const { return mTypeInfo; }
		const StringRef& GetClassName()const{return mClassName;}
		const RTTIClass* GetBaseClass() const { return mBaseClass; }
		intp GetHashCode()const{return mTypeInfo.GetHashCode();}
		int GetInheritDistance(const RTTIClass* baseClass)const;
		int GetInheritDistance(const RTTIClass& baseClass)const;
		template<typename T> bool IsExtractly()const{return *this==typename T::GetRTTIClassStatic();}
	private:
		Compile::TypeInfo mTypeInfo;
		const RTTIClass* mBaseClass;
		StringRef mClassName;
	};
}
MEDUSA_END;