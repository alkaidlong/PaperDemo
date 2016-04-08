#pragma once
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;
namespace Pattern
{
	class PropertyChangedEventArg:public IEventArg
	{
		MEDUSA_DECLARE_RTTI(PropertyChangedEventArg);
	public:
		PropertyChangedEventArg(StringRef name):mName(name){}
		virtual ~PropertyChangedEventArg(void){}
	private:
		StringRef mName;
	};

}
MEDUSA_END;