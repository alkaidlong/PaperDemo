#pragma  once

#include "Core/Pattern/Delegate.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename FuncSignature>
	class Event;


#define DEFINE_TEMPLATE_TYPENAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) typename T##N
#define DEFINE_TEMPLATE_TYPENAME(N, T)			MACRO_IF_ELSE(N,DEFINE_TEMPLATE_TYPENAME_1(N,T),MACRO_EMPTY)


#define DEFINE_PARAMETER_TYPE_NAME_1(N, T)			MACRO_COMMA_IF(MACRO_INT_DEC(N)) T##N  p##N
#define DEFINE_PARAMETER_TYPE_NAME(N, T)			MACRO_IF_ELSE(N,DEFINE_PARAMETER_TYPE_NAME_1(N,T),MACRO_EMPTY)

#define DEFINE_EVENT_CLASS(N,P)																									  \
	template<typename R MACRO_COMMA_IF(N)  MACRO_REPEAT(N, DEFINE_TEMPLATE_TYPENAME, T)>										  \
	class Event<R (MACRO_REPEAT_PARAM(N, T))>																					  \
	{																															  \
	public:																													  \
	typedef Delegate<R (MACRO_REPEAT_PARAM(N, T))> DelegateType;															  \
	private:																													  \
	List<DelegateType,EqualCompare<DelegateType> > mDelegates;																						  \
	public:																														  \
	Event(){}																												  \
	Event(const Event& inEvent):mDelegates(inEvent){			}															  \
	public:																														  \
	void Invoke(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))const														  \
	{																														  \
	size_t size= mDelegates.GetCount();																					  \
	FOR_EACH_SIZE(i,size)																								  \
	{																													  \
	const DelegateType& item=mDelegates[i];																			  \
	item.Invoke(MACRO_REPEAT_PARAM(N, p));																			  \
	}																													  \
	}																														  \
	\
	List<R> InvokeWithResults(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))const										  \
	{																														  \
	size_t size= mDelegates.GetCount();																					  \
	List<R> results;																									  \
	FOR_EACH_SIZE(i,size)																								  \
	{																													  \
	const DelegateType& item=mDelegates[i];																			  \
	results.Append(item.Invoke(MACRO_REPEAT_PARAM(N, p)));														  \
	}																													  \
	\
	return results;																										  \
	}																														  \
	\
	void Clear(){mDelegates.Clear();}																										  \
	bool IsEmpty()const																										  \
	{																														  \
	return mDelegates.IsEmpty();																						  \
	}																														  \
	\
	const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; }													  \
	public:																														  \
	void operator()(MACRO_REPEAT(N, DEFINE_PARAMETER_TYPE_NAME, T))const													  \
	{																														  \
	Invoke(MACRO_REPEAT_PARAM(N, p));																					  \
	}																														  \
	\
	void operator+=(const DelegateType& inDelegate)																			  \
	{																														  \
	Add(inDelegate);																									  \
	}																														  \
	\
	void operator-=(const DelegateType& inDelegate)																			  \
	{																														  \
	Remove(inDelegate);																									  \
	}																														  \
	\
	Event& operator=(const Event& inEvent)																					  \
	{																														  \
	mDelegates=inEvent.GetDelegates();return *this;																					  \
	}																														  \
	\
	public:																														  \
	\
	void Add(const DelegateType& inDelegate)																				  \
	{																														  \
	mDelegates.Append(inDelegate);																					  \
	}																														  \
	void Remove(const DelegateType& inDelegate)																				  \
	{																														  \
	mDelegates.RemoveLast(inDelegate);																					  \
	}																														  \
	bool Contains(const DelegateType& inDelegate)const																		  \
	{																														  \
	return mDelegates.Contains(inDelegate);																				  \
	}																														  \
	};

#ifdef WIN32
MACRO_REPEAT2(MACRO_MAX_LIMIT,DEFINE_EVENT_CLASS,MACRO_EMPTY);

#else
//BEGIN_AUTO_GENERATE_EVENT
template<typename R  > class Event<R ()> { public: typedef Delegate<R ()> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke()const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke(); } } List<R> InvokeWithResults()const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke()); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()()const { Invoke(); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1> class Event<R ( T1)> { public: typedef Delegate<R ( T1)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1); } } List<R> InvokeWithResults( T1 p1)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1)const { Invoke( p1); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2> class Event<R ( T1, T2)> { public: typedef Delegate<R ( T1, T2)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2); } } List<R> InvokeWithResults( T1 p1, T2 p2)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2)const { Invoke( p1, p2); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3> class Event<R ( T1, T2, T3)> { public: typedef Delegate<R ( T1, T2, T3)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3)const { Invoke( p1, p2, p3); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4> class Event<R ( T1, T2, T3, T4)> { public: typedef Delegate<R ( T1, T2, T3, T4)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4)const { Invoke( p1, p2, p3, p4); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5> class Event<R ( T1, T2, T3, T4, T5)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)const { Invoke( p1, p2, p3, p4, p5); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> class Event<R ( T1, T2, T3, T4, T5, T6)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5, T6)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5, p6); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5, p6)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)const { Invoke( p1, p2, p3, p4, p5, p6); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> class Event<R ( T1, T2, T3, T4, T5, T6, T7)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5, T6, T7)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5, p6, p7); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5, p6, p7)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)const { Invoke( p1, p2, p3, p4, p5, p6, p7); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> class Event<R ( T1, T2, T3, T4, T5, T6, T7, T8)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5, T6, T7, T8)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)const { Invoke( p1, p2, p3, p4, p5, p6, p7, p8); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> class Event<R ( T1, T2, T3, T4, T5, T6, T7, T8, T9)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5, T6, T7, T8, T9)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9)const { Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
template<typename R ,  typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> class Event<R ( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> { public: typedef Delegate<R ( T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)> DelegateType; private: List<DelegateType,EqualCompare<DelegateType> > mDelegates; public: Event(){} Event(const Event& inEvent):mDelegates(inEvent){ } public: void Invoke( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)const { size_t size= mDelegates.GetCount(); for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } } List<R> InvokeWithResults( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)const { size_t size= mDelegates.GetCount(); List<R> results; for(size_t i=0;i<size;++i) { const DelegateType& item=mDelegates[i]; results.Append(item.Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)); } return results; } void Clear(){mDelegates.Clear();} bool IsEmpty()const { return mDelegates.IsEmpty(); } const List<DelegateType,EqualCompare<DelegateType> >& GetDelegates() const { return mDelegates; } public: void operator()( T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8, T9 p9, T10 p10)const { Invoke( p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } void operator+=(const DelegateType& inDelegate) { Add(inDelegate); } void operator-=(const DelegateType& inDelegate) { Remove(inDelegate); } Event& operator=(const Event& inEvent) { mDelegates=inEvent.GetDelegates();return *this; } public: void Add(const DelegateType& inDelegate) { mDelegates.Append(inDelegate); } void Remove(const DelegateType& inDelegate) { mDelegates.RemoveLast(inDelegate); } bool Contains(const DelegateType& inDelegate)const { return mDelegates.Contains(inDelegate); } };
//END_AUTO_GENERATE_EVENT
#endif

#undef DEFINE_TEMPLATE_TYPENAME
#undef DEFINE_TEMPLATE_TYPENAME_1

#undef DEFINE_PARAMETER_TYPE_NAME
#undef DEFINE_PARAMETER_TYPE_NAME_1

//#undef DEFINE_EVENT_CLASS

}

MEDUSA_END;
