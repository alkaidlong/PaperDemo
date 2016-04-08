#pragma  once

#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/RTTI/RTTIClass.h"
#include "Core/Compile/TypeInfo.h"

/*
The reason why we need to implement my own's RTTI instead of dynamic_cast is that performance!
1. RTTI support multiple derived,but we don't need
2. RTTI throws exception when failing to cast ref,but we only need to case pointers

Performance data:
When cast derived pointer to base pointer, we 2 hava the same perf
When cast base pointer to derived pointer, here's the data:
Release:
My:				0.000003ms,10000000
dynamic_cast:	0.456289ms,10000000

Debug:
My:				1.331812ms,10000000
dynamic_cast:	0.696640ms,10000000

Test Code:
MyObject2* obj=new MyObject2();
RTTIObject* p=obj;
MyObject2* q=NULL;
const int count=10000000;
int sum1=0;
int sum2=0;


StopWatch watch(count);

watch.Start();
FOR_EACH_SIZE(i,count)
{
q=(MyObject2*)p;
bool isKind= p->IsA<MyObject2>();
if (isKind)
{
++sum1;
}
else
{
++sum2;
}
}
watch.Stop();

watch.Start();
FOR_EACH_SIZE(i,count)
{
q= dynamic_cast<MyObject2*>(p);

bool isKind= q!=NULL;
if (isKind)
{
++sum1;
}
else
{
++sum2;
}
}
watch.Stop();

system("PAUSE");

So we can see that in release mode, my RTTI version will get optimezed; I think it results from IsA don't need to call virtual functions and can be inlined.
*/


MEDUSA_BEGIN;

namespace Pattern
{
#define MEDUSA_DECLARE_RTTI(className)										\
public:																				\
	virtual const Pattern::RTTIClass& GetRTTIClass()const{return mRTTIClass;}				\
	static const Pattern::RTTIClass& GetRTTIClassStatic(){return mRTTIClass;}				\
	template<typename T> bool IsA()const{return IsA(T::GetRTTIClassStatic());}	\
	bool IsA(const Pattern::RTTIClass& rttiClass)const{const Pattern::RTTIClass* p=&GetRTTIClass();const Pattern::RTTIClass* q=&rttiClass;do {if (p==q){return true;}p=p->GetBaseClass();} while (p!=NULL);return false;}	\
	template<typename T> bool IsExtractly()const{return IsExtractly(typename T::GetRTTIClassStatic());}	\
	bool IsExtractly(const Pattern::RTTIClass& rttiClass)const{return &GetRTTIClass()==&rttiClass;}	\
	template<typename T> T* As(){return IsA<T>()?(T*)this:NULL;}					\
private:																			\
	const static Pattern::RTTIClass mRTTIClass;												

#define MEDUSA_IMPLEMENT_RTTI(className,baseClassName) WEAK_MULTIPLE_DEFINE const Pattern::RTTIClass className::mRTTIClass=Pattern::RTTIClass(Compile::TypeInfoFactory::Create<className>(),#className,&(baseClassName::GetRTTIClassStatic()));
#define MEDUSA_IMPLEMENT_RTTI_ROOT(className) WEAK_MULTIPLE_DEFINE const Pattern::RTTIClass className::mRTTIClass=Pattern::RTTIClass(Compile::TypeInfoFactory::Create<className>(),#className,NULL);


	class RTTIObject
	{
	protected:
		virtual ~RTTIObject()=0;
		MEDUSA_DECLARE_RTTI(RTTIObject);
	};

	namespace RTTI
	{
		template<typename T>
		inline T* SafeCast(const RTTIObject* obj)
		{
			RETURN_NULL_IF_NULL(obj);
			return obj->IsA<T>()?(T*)obj:NULL;
		}
	}

}
MEDUSA_END;