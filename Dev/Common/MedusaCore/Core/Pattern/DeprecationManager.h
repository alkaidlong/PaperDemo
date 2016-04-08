#pragma  once

#include "MedusaCorePreCompiled.h"



MEDUSA_BEGIN;
namespace Pattern
{
	class DeprecationManager
	{
	public:
		static DeprecationManager& Instance()
		{
			static DeprecationManager inst;
			return inst;
		}

		void AddDeprecateFunction(const char* funcName,const char* comment,const char* fileName,const char* lineName);

		~DeprecationManager();
	private:
		DeprecationManager(){}
	private:
		std::map<const char*,const char*> mDeprecatedFunction;
	};


#ifdef MEDUSA_DEBUG
#define MEDUSA_DEPRECATE(funcName,comment) DeprecationManager::Instance().AddDeprecateFunction(funcName,comment,__FILE__,__LINE__);
#else
#define MEDUSA_DEPRECATE(funcName,comment)
#endif
}
MEDUSA_END;