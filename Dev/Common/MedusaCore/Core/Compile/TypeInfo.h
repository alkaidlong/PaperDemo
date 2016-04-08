#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Utility/HashUtility.h"

MEDUSA_BEGIN;
namespace Compile
{
	class TypeInfo
	{
	public:
		TypeInfo()
		{
			class MyNil {};
			mTypeInfo = &typeid(MyNil);
			assert(mTypeInfo);
		}

		TypeInfo(const std::type_info& ti):mTypeInfo(&ti)
		{
			assert(mTypeInfo);
		}

		const std::type_info& Get() const
		{
			return *mTypeInfo;
		}

		bool Before(const TypeInfo& rhs) const
		{
			return mTypeInfo->before(*rhs.mTypeInfo) != 0;
		}

		const char* GetName() const
		{
			return mTypeInfo->name();
		}

		intp GetHashCode()const
		{
			return HashUtility::HashString(GetName());
		}
		bool operator==(const TypeInfo& rhs)const	{ return *mTypeInfo == rhs.Get(); }
		bool operator<(const TypeInfo& rhs)const	{ return Before(rhs); }
		bool operator!=(const TypeInfo& rhs)const	{ return !(*this== rhs); }    
		bool operator>(const TypeInfo& rhs)const	{ return *this>rhs; }
		bool operator<=(const TypeInfo& rhs)const	{ return !(*this > rhs); }
		bool operator>=(const TypeInfo& rhs)const	{ return !(*this < rhs); }
	private:
		const std::type_info* mTypeInfo;
	};


	namespace TypeInfoFactory
	{
		template<typename T>
		static TypeInfo Create()
		{
			return TypeInfo(typeid(T));
		}

		template<typename T>
		static const char* GetFixClassName()
		{
			//a little trick
			const char* name=typeid(T).name();	//return "struct C" or "class C"
			const char* p=name;
			while (*name!='\0')
			{
				if (*name==' '||*name==':')	//remove str before name
				{
					p=name+1;
				}
				++name;
			}

			return p;
		}

	}

}

MEDUSA_END;