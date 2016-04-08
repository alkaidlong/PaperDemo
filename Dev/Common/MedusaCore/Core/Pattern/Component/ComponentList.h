#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Component/IComponent.h"
#include "Core/Pattern/Component/ComponentFactory.h"
#include "Core/Collection/SortedList.h"
#include "Core/Compile/TypeInfo.h"


MEDUSA_BEGIN;

namespace Pattern
{
	class ComponentList:public SortedList<IComponent*,IComponentCompare>
	{
	public:
		ComponentList();
		virtual ~ComponentList();
	public:
		inline IComponent* GetComponent(StringRef name);
		template<typename T>
		inline T* GetComponent()
		{
			Compile::TypeInfo info=Compile::TypeInfoFactory::Create<T>();

			FOR_EACH_COLLECTION(i,*this)
			{
				IComponent* component=*i;
				if (component->GetRTTIClass().GetTypeInfo()==info)
				{
					return (T*)component;
				}
			}

			return NULL;
		}

		template<typename T>
		inline T* GetFirstComponentKindOf()const
		{
			FOR_EACH_COLLECTION(i,*this)
			{
				IComponent* component=*i;
				if (component->IsA<T>())
				{
					return (T*)component;
				}
			}

			return NULL;
		}

		template<typename T>
		inline bool HasComponentKindOf()const
		{
			return GetFirstComponentKindOf<T>()!=NULL;
		}

		inline IComponent* AddComponent(IComponent* component)
		{
			MEDUSA_ASSERT_NOT_NULL(component,"");
			Add(component);
			return component;

		}
		inline IComponent* AddComponent(StringRef name,ushort priorityDelta=0,void* userData=NULL)
		{
			IComponent* component= ComponentFactory::Instance().Create(name,priorityDelta,userData);
			RETURN_NULL_IF_NULL(component);
			AddComponent(component);
			return component;
		}

		template<typename T>
		inline T* AddComponent(ushort priorityDelta=0 ,void* userData=NULL)
		{
			T* component=(T*)ComponentFactory::Instance().Create<T>(priorityDelta,userData);
			RETURN_NULL_IF_NULL(component);

			AddComponent(component);
			return component;

		}

		inline void RemoveComponent(StringRef name);
		template<typename T>
		inline void RemoveComponent()
		{
            /*
			Compile::TypeInfo info=Compile::TypeInfoFactory::Create<T>();

			FOR_EACH_COLLECTION(i,*this)
			{
				IComponent* component=*i;
				if (component->GetType()==info)
				{
					RemoveAt(i);
					if (!component->IsManaged())
					{
						SAFE_DELETE(component);
					}
					break;
				}
			}
             */
		}

		inline void ClearComponents();
	};

}
MEDUSA_END;