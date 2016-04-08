#pragma  once

#include "Core/Compile/Type.h"

MEDUSA_BEGIN;
namespace Compile
{
	template <class THead, class TTail>
	struct Typelist;

	namespace PrivateTypelistUtility
	{
		template <class TList> 
		struct Length;

		template <> 
		struct Length<NullType>
		{
			const static size_t Value=0;
		};

		template <class T, class U>
		struct Length< Typelist<T, U> >
		{
			const static size_t Value=1+Length<U>::Value ;
		};
		//////////////////////////////////////////////////////////////////////////
		template <class TList, size_t index> 
		struct TypeAt;

		template <class Head, class Tail>
		struct TypeAt<Typelist<Head, Tail>, 0>
		{
			typedef Head ResultType;
		};

		template <class Head, class Tail, size_t i>
		struct TypeAt<Typelist<Head, Tail>, i>
		{
			typedef typename TypeAt<Tail, i - 1>::ResultType ResultType;
		};
		//////////////////////////////////////////////////////////////////////////

		template <class TList, unsigned int index,typename DefaultType = NullType>
		struct TypeAtNonStrict
		{
			typedef DefaultType ResultType;
		};

		template <class Head, class Tail, typename DefaultType>
		struct TypeAtNonStrict<Typelist<Head, Tail>, 0, DefaultType>
		{
			typedef Head Result;
		};

		template <class Head, class Tail, unsigned int i, typename DefaultType>
		struct TypeAtNonStrict<Typelist<Head, Tail>, i, DefaultType>
		{
			typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
		};

		//////////////////////////////////////////////////////////////////////////

		template <class TList, class T> 
		struct IndexOf;

		template <class T>
		struct IndexOf<NullType, T>
		{
			const static int Value=-1;
		};

		template <class T, class Tail>
		struct IndexOf<Typelist<T, Tail>, T>
		{
			const static int Value=0;
		};

		template <class Head, class Tail, class T>
		struct IndexOf<Typelist<Head, Tail>, T>
		{
		private:
			const static int mTemp=IndexOf<Tail, T>::Value;
		public:
			const static int Value=(mTemp==-1?-1:1+mTemp);
		};

		//////////////////////////////////////////////////////////////////////////
		template <class TList, class T> 
		struct Append;

		template <> 
		struct Append<NullType, NullType>
		{
			typedef NullType ResultType;
		};

		template <class T> 
		struct Append<NullType, T>
		{
			typedef Typelist<T,NullType> ResultType;
		};

		template <class Head, class Tail>
		struct Append<NullType, Typelist<Head, Tail> >
		{
			typedef Typelist<Head, Tail> ResultType;
		};

		template <class Head, class Tail, class T>
		struct Append<Typelist<Head, Tail>, T>
		{
			typedef Typelist<Head, typename Append<Tail, T>::ResultType> ResultType;
		};
		//////////////////////////////////////////////////////////////////////////

		template <class TList, class T> 
		struct Erase;

		template <class T>                         // Specialization 1
		struct Erase<NullType, T>
		{
			typedef NullType ResultType;
		};

		template <class T, class Tail>             // Specialization 2
		struct Erase<Typelist<T, Tail>, T>
		{
			typedef Tail ResultType;
		};

		template <class Head, class Tail, class T> // Specialization 3
		struct Erase<Typelist<Head, Tail>, T>
		{
			typedef Typelist<Head, typename Erase<Tail, T>::ResultType> ResultType;
		};

		//////////////////////////////////////////////////////////////////////////

		template <class TList, class T> 
		struct EraseAll;

		template <class T>
		struct EraseAll<NullType, T>
		{
			typedef NullType ResultType;
		};

		template <class T, class Tail>
		struct EraseAll<Typelist<T, Tail>, T>
		{
			// Go all the way down the list removing the type
			typedef typename EraseAll<Tail, T>::ResultType ResultType;
		};

		template <class Head, class Tail, class T>
		struct EraseAll<Typelist<Head, Tail>, T>
		{
			// Go all the way down the list removing the type
			typedef Typelist<Head, typename EraseAll<Tail, T>::ResultType> ResultType;
		};
		//////////////////////////////////////////////////////////////////////////

		template <class TList> 
		struct NoDuplicates;

		template <> 
		struct NoDuplicates<NullType>
		{
			typedef NullType ResultType;
		};

		template <class Head, class Tail>
		struct NoDuplicates< Typelist<Head, Tail> >
		{
		private:
			typedef typename NoDuplicates<Tail>::ResultType L1;
			typedef typename Erase<L1, Head>::ResultType L2;
		public:
			typedef Typelist<Head, L2> ResultType;
		};
		//////////////////////////////////////////////////////////////////////////

		template <class TList, class T, class U> 
		struct Replace;

		template <class T, class U>
		struct Replace<NullType, T, U>
		{
			typedef NullType ResultType;
		};

		template <class T, class Tail, class U>
		struct Replace<Typelist<T, Tail>, T, U>
		{
			typedef Typelist<U, Tail> ResultType;
		};

		template <class Head, class Tail, class T, class U>
		struct Replace<Typelist<Head, Tail>, T, U>
		{
			typedef Typelist<Head,typename Replace<Tail, T, U>::ResultType> ResultType;
		};
		//////////////////////////////////////////////////////////////////////////
		template <class TList, class T, class U> 
		struct ReplaceAll;

		template <class T, class U>
		struct ReplaceAll<NullType, T, U>
		{
			typedef NullType ResultType;
		};

		template <class T, class Tail, class U>
		struct ReplaceAll<Typelist<T, Tail>, T, U>
		{
			typedef Typelist<U, typename ReplaceAll<Tail, T, U>::ResultType> ResultType;
		};

		template <class Head, class Tail, class T, class U>
		struct ReplaceAll<Typelist<Head, Tail>, T, U>
		{
			typedef Typelist<Head,typename ReplaceAll<Tail, T, U>::ResultType> ResultType;
		};
		//////////////////////////////////////////////////////////////////////////
		template <class TList> 
		struct Reverse;

		template <>
		struct Reverse<NullType>
		{
			typedef NullType ResultType;
		};

		template <class Head, class Tail>
		struct Reverse< Typelist<Head, Tail> >
		{
			typedef typename Append<typename Reverse<Tail>::Result, Head>::ResultType ResultType;
		};
		//////////////////////////////////////////////////////////////////////////
		template <class TList, class T> 
		struct MostDerived;

		template <class T>
		struct MostDerived<NullType, T>
		{
			typedef T ResultType;
		};

		template <class Head, class Tail, class T>
		struct MostDerived<Typelist<Head, Tail>, T>
		{
		private:
			typedef typename MostDerived<Tail, T>::Result Candidate;
		public:
			typedef typename IfElse<IsSuperSubclass<Candidate,Head>::Value,Head, Candidate>::Result ResultType;
		};
		//////////////////////////////////////////////////////////////////////////
		template <class TList> 
		struct DerivedToFront;

		template <>
		struct DerivedToFront<NullType>
		{
			typedef NullType ResultType;
		};

		template <class Head, class Tail>
		struct DerivedToFront< Typelist<Head, Tail> >
		{
		private:
			typedef typename MostDerived<Tail, Head>::ResultType TheMostDerived;
			typedef typename Replace<Tail,TheMostDerived, Head>::ResultType Temp;
			typedef typename DerivedToFront<Temp>::Result L;
		public:
			typedef Typelist<TheMostDerived, L> ResultType;
		};
	}

}

MEDUSA_END;