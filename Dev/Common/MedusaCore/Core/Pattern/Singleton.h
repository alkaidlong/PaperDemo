#pragma  once

#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename T>
	class Singleton
	{
	private:
		Singleton(const Singleton&);
		Singleton & operator=(const Singleton&);
	public:
		FORCE_INLINE static T& Instance()
		{
			static T object;
			return object;
		}

	protected:
		Singleton() {}
		virtual ~Singleton() {}
	};
}
MEDUSA_END;