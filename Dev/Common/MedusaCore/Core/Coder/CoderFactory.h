#pragma  once

#include "Core/Pattern/MapObjectFactory.h"
#include "Core/Coder/ICoder.h"

MEDUSA_BEGIN;

class CoderFactory:public Pattern::MapObjectFactory<CoreProto::FileList::FileCoder::FileCoderType,ICoder*(const IEventArg&)>
{
public:
	using Pattern::MapObjectFactory<CoreProto::FileList::FileCoder::FileCoderType,ICoder*(const IEventArg&)>::Create;
private:
	CoderFactory();
	~CoderFactory(){}
public:
	static CoderFactory& Instance()
	{
		static CoderFactory factory;
		return factory;
	}
};

MEDUSA_END;
