#pragma  once

#include "CorePlatform/CorePlatform.h"
#include "Core/Assertion/CommonAssert.h"


#include "Core/Pattern/Delegate.h"
#include "Core/Collection/STLPort.h"
#include "Core/Collection/Dictionary.h"


MEDUSA_BEGIN;
namespace Pattern
{
	template <typename TBase, class TId>
	struct ObjectFactory_NULL_ErrorPolicy
	{
		static TBase* OnUnknownType(const TId& id)
		{
			return NULL;
		}
	};

	template <typename TBase, class TId>
	struct ObjectFactory_Exception_ErrorPolicy
	{
		struct Exception : public std::exception
		{
			const char* what() const throw() { return "Unknown Type"; }
		};

		static TBase* OnUnknownType(const TId& id)
		{
			throw Exception();
		}
	};

	template<typename TId,typename FuncSignature> 
	class MapObjectFactory;


#define DEFINE_TEMPLATE_TYPENAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) typename T##N
#define DEFINE_TEMPLATE_TYPENAME(N, T)			MACRO_IF_ELSE(N,DEFINE_TEMPLATE_TYPENAME_1(N,T),MACRO_EMPTY)

#define DEFINE_PARAMETER_TYPE_NAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) T##N  p##N
#define DEFINE_PARAMETER_TYPE_NAME(N, T)			MACRO_IF_ELSE(N,DEFINE_PARAMETER_TYPE_NAME_1(N,T),MACRO_EMPTY)

#define DEFINE_MAP_OBJECT_FACTORY_CLASS(N,P)  																				  \
	template<typename TId, typename TBase MACRO_COMMA_IF(N) MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T) >							  \
	class MapObjectFactory<TId,TBase*(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))> 																								  \
	{																													  \
	public:																												  \
		typedef TBase* CreateDerivedCallback(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T));							  \
		typedef CreateDerivedCallback* CreatorType;																		  \
	private:																											  \
		typedef Dictionary<TId,CreatorType> MapType;																			  \
		MapType mMap;																									  \
																														  \
		template<typename TDerived>																						  \
		static TBase* CreateDerivedHelper(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))								  \
		{																												  \
			MEDUSA_COMPILE_ASSERT(IS_SUPER_SUB_CLASS(TBase,TDerived),TDerived_NOT_INHERIT_FROM_TBase);							  \
			return new TDerived(MACRO_REPEAT_PARAM(N, p));																  \
		}																												  \
																														  \
	public:																												  \
		template<typename TDerived>																						  \
		void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);}											  \
		void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);}												  \
		template<typename TDerived>																						  \
		void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);}											  \
		void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);}												  \
		void UnRegister(const TId& id){mMap.RemoveKey(id);}																	  \
																														  \
		TBase* Create(const TId& id MACRO_COMMA_IF(N) MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))					  \
	{																													\
		CreatorType* outCreator=mMap.TryGetValue(id);																							\
		if(outCreator!=NULL)																				\
		{																												\
			return (*outCreator)(MACRO_REPEAT_PARAM(N, p));																\
		}																												\
		return NULL;																									\
	}																													\
	};


	

#ifdef WIN32
	MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_MAP_OBJECT_FACTORY_CLASS,MACRO_EMPTY)
#else
	//BEGIN_AUTO_GENERATE_MAP_OBJECT_FACTORY
template<typename TId, typename TBase   > class MapObjectFactory<TId,TBase*()> { public: typedef TBase* CreateDerivedCallback(); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper() { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived(); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id  ) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)(); } return 0; } };
template<typename TId, typename TBase ,  typename T1 > class MapObjectFactory<TId,TBase*( T1 p1)> { public: typedef TBase* CreateDerivedCallback( T1 p1); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5, p6); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5, p6); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5, p6, p7); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5, p6, p7); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5, p6, p7, p8); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5, p6, p7, p8); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5, p6, p7, p8, p9); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5, p6, p7, p8, p9); } return 0; } };
template<typename TId, typename TBase ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 > class MapObjectFactory<TId,TBase*( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)> { public: typedef TBase* CreateDerivedCallback( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10); typedef CreateDerivedCallback* CreatorType; private: typedef Dictionary<TId,CreatorType> MapType; MapType mMap; template<typename TDerived> static TBase* CreateDerivedHelper( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10) { { CompileError<((Compile::IsSuperSubclass<TBase,TDerived>::Value))> ERROR_TDerived_NOT_INHERIT_FROM_TBase; (void)ERROR_TDerived_NOT_INHERIT_FROM_TBase; }; return new TDerived( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } public: template<typename TDerived> void Register(const TId& id){mMap.Add(id,&CreateDerivedHelper<TDerived>);} void Register(const TId& id,CreatorType creator){mMap.Add(id,creator);} template<typename TDerived> void TryRegister(const TId& id){mMap.TryAdd(id,&CreateDerivedHelper<TDerived>);} void TryRegister(const TId& id,CreatorType creator){mMap.TryAdd(id,creator);} void UnRegister(const TId& id){mMap.RemoveKey(id);} TBase* Create(const TId& id ,  T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10) { CreatorType* outCreator=mMap.TryGetValue(id); if(outCreator!=0) { return (*outCreator)( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } return 0; } };
//END_AUTO_GENERATE_MAP_OBJECT_FACTORY
#endif


#undef DEFINE_TEMPLATE_TYPENAME
#undef DEFINE_TEMPLATE_TYPENAME_1

#undef DEFINE_PARAMETER_TYPE_NAME
#undef DEFINE_PARAMETER_TYPE_NAME_1

//#undef DEFINE_MAP_OBJECT_FACTORY_CLASS


}
MEDUSA_END;

