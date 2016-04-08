#pragma  once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;
namespace Dynamic
{
	template<typename TBase,typename TWin32,typename TIOS>
	inline TBase* CreatePlatformType()
	{
#ifdef WIN32
		return new TWin32();
#else
		return new TIOS();
#endif
	}

	template<typename TBase,typename TWin32,typename TIOS,typename TParam1>
	inline TBase* CreatePlatformType(TParam1 param1)
	{
#ifdef WIN32
		return new TWin32(param1);
#else
		return new TIOS(param1);
#endif
	}

	template<typename TBase,typename TWin32,typename TIOS,typename TParam1,typename TParam2>
	inline TBase* CreatePlatformType(TParam1 param1,TParam2 param2)
	{
#ifdef WIN32
		return new TWin32(param1,param2);
#else
		return new TIOS(param1,param2);
#endif
	}

	template<typename T>
	class Callbacks
	{
	public:
		typedef T (*FuncCallback)();
	};

}

MEDUSA_END;