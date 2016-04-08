#pragma  once

#include "Core/Pattern/MapObjectFactory.h"
#include "Core/String/StringRef.h"

class LayerNode;
USING_MEDUSA;

class LayerFactory:public Pattern::MapObjectFactory<StringRef,LayerNode*(const IEventArg&)>
{
public:
	using Pattern::MapObjectFactory<StringRef,LayerNode*(const IEventArg&)>::Create;
private:
	LayerFactory()
	{
		
	}
	~LayerFactory(){}
public:
	static LayerFactory& Instance()
	{
		static LayerFactory factory;
		return factory;
	}

};


