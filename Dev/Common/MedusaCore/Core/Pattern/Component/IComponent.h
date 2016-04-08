#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;


namespace Pattern
{
	STRONG_ENUM_CUSTOM_6(ComponentGroupType,Data,1,Check,1024,Logic,2048,Script,3072,Renderable,4096,Nodes,8192);

	class IComponent:public Pattern::RTTIObject
	{
		MEDUSA_DECLARE_RTTI(IComponent);
	public:
		//virtual StringRef GetName()=0;
		//virtual TypeInfo GetType()=0;
	public:
		IComponent(ComponentGroupType group,ushort priorityDelta=0,void* userData=NULL);
		virtual ~IComponent(){}
	public:
		ushort GetPriority() const { return mPriority; }
		void* GetUserData() const { return mUserData; }
		void SetUserData(void* val) { mUserData = val; }
	public:
		virtual bool Update(float dt);
	protected:
		const ushort mPriority;
		void* mUserData;
		
	};

	struct IComponentCompare
	{
		static int Compare(const IComponent* t1,const IComponent* t2)
		{
			return (int)((int)t1->GetPriority()-(int)t2->GetPriority());
		}
	};
}
	
MEDUSA_END;