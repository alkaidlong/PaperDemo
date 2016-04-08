#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Message/IMessage.h"
#include "Core/Pattern/MapObjectFactory.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;


class MessageFactory:public Pattern::MapObjectFactory<StringRef,IMessage*()>
{
public:
	using Pattern::MapObjectFactory<StringRef,IMessage*()>::Create;
private:
	MessageFactory()
	{
		
	}
	~MessageFactory(){}
public:
	static MessageFactory& Instance()
	{
		static MessageFactory factory;
		return factory;
	}

};

MEDUSA_END;
