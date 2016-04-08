#pragma  once


#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IComponent.h"
#include "Core/Pattern/MapObjectFactory.h"
#include "Core/Pattern/StaticConstructor.h"


MEDUSA_BEGIN;

namespace Pattern
{

	class ComponentFactory:public MapObjectFactory<StringRef,IComponent*(ushort priorityDelta,void* userData)>
	{
	public:
		using MapObjectFactory<StringRef,IComponent*(ushort priorityDelta,void* userData)>::Create;
	private:
		ComponentFactory(){}
		~ComponentFactory(){}
	public:
		static ComponentFactory& Instance()
		{
			static ComponentFactory factory;
			return factory;
		}

		template<typename T>
		IComponent* Create(ushort priorityDelta=0,void* userData=NULL)
		{
			return Create(typename T::GetRTTIClassStatic::GetClassName(),priorityDelta,userData);
		}
	};


#define MEDUSA_DECLARE_COMPONENT_FACTORY(className) 				   \
private:													   \
	const static Pattern::StaticConstructor mStaticConstructor;		   \
	static void RegisterComponent();

#define MEDUSA_IMPLEMENT_COMPONENT_FACTORY(className) 																 \
	const Pattern::StaticConstructor className::mStaticConstructor(RegisterComponent);						 \
	void className::RegisterComponent(){Pattern::ComponentFactory::Instance().Register<className>(#className);}				 

}
MEDUSA_END;