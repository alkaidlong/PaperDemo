#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Delegate.h"


MEDUSA_BEGIN;
namespace Pattern
{
	class StaticConstructor
	{
	public:
		StaticConstructor(::Medusa::Pattern::Delegate<void()> callback)
		{
			callback();
		}
	};

#define MEDUSA_DECLARE_STATIC_CONSTRUCTOR() private:const static Pattern::StaticConstructor mStaticConstructor;
#define MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(className,callback) const Pattern::StaticConstructor className::mStaticConstructor(callback);

}
MEDUSA_END;