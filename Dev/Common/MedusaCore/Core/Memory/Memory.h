#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Compile/Type.h"
#include "Core/Compile/TypeTraits.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/MathHeader.h"
MEDUSA_BEGIN;

namespace Memory
{
	namespace MemoryPrivate
	{
		template <typename T,typename TCompare>
		inline int Compare_Imp(const T* first,const T* second,size_t count,Compile::Bool2Type<true>)
		{
			return memcmp(first,second,count);
		}

		template <typename T,typename TCompare>
		inline int Compare_Imp(const T* first,const T* second,size_t count,Compile::Bool2Type<false>)
		{
			FOR_EACH_SIZE(i,count)
			{
				int compare=TCompare::Compare(first[i],second[i]);
				RETURN_SELF_IF_NOT_ZERO(compare);
			}
			return 0;
		}

	}
	

	inline float Compare(const float* first,const float* second,size_t count)
	{
		FOR_EACH_SIZE(i,count)
		{
			float compare=Math::Compare(first[i],second[i]);
			if(compare!=0.f)
			{
				return compare;
			}
		}
		return 0.f;
	}

	inline double Compare(const double* first,const double* second,size_t count)
	{
		FOR_EACH_SIZE(i,count)
		{
			double compare=Math::Compare(first[i],second[i]);
			if(compare!=0.0)
			{
				return compare;
			}
		}
		return 0.0;
	}

	template <typename T>
	inline int Compare(const T* first,const T* second,size_t count)
	{
		return MemoryPrivate::Compare_Imp<T,DefaultCompare<T> >(first,second,count,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T,size_t N>
	inline int Compare(const T (&first)[N],const T (&second)[N])
	{
		return MemoryPrivate::Compare_Imp<T,DefaultCompare<T> >(first,second,N,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}


	template <typename T,typename TCompare>
	inline int Compare(const T* first,const T* second,size_t count)
	{
		return MemoryPrivate::Compare_Imp<T,TCompare>(first,second,count,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T,size_t N,typename TCompare>
	inline int Compare(const T (&first)[N],const T (&second)[N])
	{
		return MemoryPrivate::Compare_Imp<T,TCompare>(first,second,N,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	namespace MemoryPrivate
	{
		template<typename T,typename TP>
		inline void CopyConstruct_Imp(T* p,TP val,Compile::Bool2Type<true>)
		{
			*p=val;
		}

		template<typename T,typename TP>
		inline void CopyConstruct_Imp(T* p,TP val,Compile::Bool2Type<false>)
		{
			::new (static_cast<void*>(p)) T(val);
		}

		template <typename T>
		inline void Copy_Imp(T* dest,const T* src,size_t count,Compile::Bool2Type<true>)
		{
			memcpy(dest,src,count*sizeof(T));
		}

		template <typename T>
		inline void Copy_Imp(T* dest,const T* src,size_t count,Compile::Bool2Type<false>)
		{
			FOR_EACH_SIZE(i,count)
			{
				*dest++=*src++;
			}
		}

		template <typename T>
		inline void SafeCopy_Imp(T* dest,size_t destSize,const T* src,size_t count,Compile::Bool2Type<true>)
		{
#ifdef MEDUSA_WINDOWS
			memmove_s(dest,destSize*sizeof(T),src,count*sizeof(T));
#else
			memmove((void*)dest,(void*)src,count*sizeof(T));
#endif
		}

		template <typename T>
		inline void SafeCopy_Imp(T* dest,size_t destSize,const T* src,size_t count,Compile::Bool2Type<false>)
		{
			MEDUSA_ASSERT_IF(destSize>=count,"");

			if (dest <= src || (char *)dest >= ((char *)src + count))
			{
				/*
				* Non-Overlapping Buffers
				* copy from lower addresses to higher addresses
				*/
				while(count--)
				{
					*dest++=*src++;
				}
			}
			else 
			{
				/*
				* Overlapping Buffers
				* copy from higher addresses to lower addresses
				*/
				dest = dest + count - 1;
				src = src + count - 1;

				while (count--) 
				{
					*dest--=*src--;
				}
			}
		}


		template <typename T>
		inline void Copy_Imp(T begin,T end,T dest,Compile::Bool2Type<true>)
		{
			memcpy(dest,begin,(end-begin)*sizeof(T));
		}

		template <typename T>
		inline void Copy_Imp(T begin,T end,T dest,Compile::Bool2Type<false>)
		{
			for (T i=begin;i!=end;++i)
			{
				*dest++=*i++;
			}
		}


		template <typename T,typename TValue>
		inline void Set_Imp(T* src,TValue val,size_t count,Compile::Bool2Type<true>)
		{
			assert(sizeof(TValue)==1);
			memset(src,(int)val,count*sizeof(T));
		}

		template <typename T,typename TValue>
		inline void Set_Imp(T* src,TValue val,size_t count,Compile::Bool2Type<false>)
		{
#ifdef MEDUSA_IOS
            while(count-->0)
            {
                *src++=val;
            }
#else
            const static char compareBlock[sizeof(TValue)]={0};
			if (Compare((const char*)compareBlock,(const char*)&val,sizeof(TValue))==0)
			{
				memset(src,0,count*sizeof(T));
			}
			else
			{
				while(count-->0)
				{
					*src++=val;
				}
			}
#endif
			

		}

		template <typename T>
		inline void SetZero_Imp(T* src,size_t count,Compile::Bool2Type<true>)
		{
			memset(src,0,count*sizeof(T));
		}

		template <typename T>
		inline void SetZero_Imp(T* src,size_t count,Compile::Bool2Type<false>)
		{
			while(count-->0)
			{
				*src++=0;
			}
		}

		template <typename T>
		inline void Swap_Imp(T& left,T& right,Compile::Bool2Type<true>)
		{
			T temp=left;
			left=right;
			right=temp;
		}

		template <typename T>
		inline void Swap_Imp(T& left,T& right,Compile::Bool2Type<false>)
		{
			left.Swap(right);
		}

		template<typename T>
		inline void Destory_Imp(T* p,Compile::Bool2Type<true>)
		{
			//do nothing
		}

		template<typename T>
		inline void Destory_Imp(T* p,Compile::Bool2Type<false>)
		{
			p->~T();
		}

		template<typename T>
		inline void Delete_Imp(T p,Compile::Bool2Type<true>)
		{
			delete p;
		}

		template<typename T>
		inline void Delete_Imp(T p,Compile::Bool2Type<false>)
		{
			//do nothing
		}

		template<typename T>
		inline void DestoryRange_Imp(T* p,size_t size,Compile::Bool2Type<true>)
		{
			//do nothing
		}

		template<typename T>
		inline void DestoryRange_Imp(T* p,size_t size,Compile::Bool2Type<false>)
		{
			FOR_EACH_SIZE(i,size)
			{
				(p+i)->~T();
			}
		}


		template<typename T,typename TP>
		inline void CopyConstructRange_Imp(T* p,TP val,size_t size,Compile::Bool2Type<true>)
		{
			Set_Imp(p,val,size,Compile::Bool2Type<sizeof(TP)==1>());
		}

		template<typename T,typename TP>
		inline void CopyConstructRange_Imp(T* p,TP val,size_t size,Compile::Bool2Type<false>)
		{
			FOR_EACH_SIZE(i,size)
			{
				::new (static_cast<void*>(p+i)) T(val);
			}
		}

		template<typename T>
		inline void CopyConstructIterator_Imp(T* dest,const T* src,size_t size,Compile::Bool2Type<true>)
		{
			SafeCopy_Imp(dest,size,src,size,Compile::Bool2Type<true>());
		}

		template<typename T>
		inline void CopyConstructIterator_Imp(T* dest,const T* src,size_t size,Compile::Bool2Type<false>)
		{
			FOR_EACH_SIZE(i,size)
			{
				::new (static_cast<void*>(dest+i)) T(*(src+i));
			}
		}

		inline size_t FillCharArray_Imp(char* buffer,wchar_t wchar,Compile::Bool2Type<true>)	//sizeof(wchar_t)==2
		{
			*buffer++=(char)wchar;
			*buffer=(char)(wchar>>8);
			return 2;
		}

		inline size_t FillCharArray_Imp(char* buffer,wchar_t wchar,Compile::Bool2Type<false>)
		{
			*buffer++=(char)(int)wchar;
			*buffer++=(char)((int)wchar>>8);
			*buffer++=(char)((int)wchar>>16);
			*buffer=(char)((int)wchar>>24);
			return 4;
		}
	}

	inline const void* FindFirstChar(const void* src,size_t size,char val)
	{
		return memchr(src,val,size);
	}

	inline void* FindFirstChar(void* src,size_t size,char val)
	{
		return memchr(src,val,size);
	}

	inline const wchar_t* FindFirstWchar(const wchar_t* src,size_t size,wchar_t val)
	{
		return wmemchr(src,val,size);
	}

	inline wchar_t* FindFirstWchar(wchar_t* src,size_t size,wchar_t val)
	{
		return wmemchr(src,val,size);
	}

	inline int Compare(const void* p,const void* q,size_t num)
	{
		return memcmp(p,q,num);
	}

	inline int Compare(const wchar_t* p,const wchar_t* q,size_t num)
	{
		return wmemcmp(p,q,num);
	}

	template<typename T>
	inline T* Alloc(size_t count)
	{
		return (T*)malloc(count*sizeof(T));
	}

	template<typename T>
	inline void Realloc(T*& buffer,size_t count)
	{
		T* temp=buffer;
		buffer=(T*)realloc(buffer,count*sizeof(T));
		if (buffer==NULL&&temp!=NULL)
		{
			free(temp);
		}
	}

	template <typename T>
	inline void Copy(T* dest,const T* src,size_t count)
	{
		MemoryPrivate::Copy_Imp(dest,src,count,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T>
	inline void SafeCopy(T* dest,size_t destSize,const T* src,size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest,destSize,src,count,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T>
	inline void SafeCopyShallow(T* dest,size_t destSize,const T* src,size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest,destSize,src,count,Compile::Bool2Type<true>());
	}

	template <typename T>
	inline void SafeCopyDeep(T* dest,size_t destSize,const T* src,size_t count)
	{
		MemoryPrivate::SafeCopy_Imp(dest,destSize,src,count,Compile::Bool2Type<false>());
	}

	template <typename T,typename TValue>
	inline void Set(T* src,TValue val,size_t count)
	{
		MemoryPrivate::Set_Imp(src,val,count,Compile::Bool2Type<sizeof(TValue)==1>());
	}

	template <typename T>
	inline void ClearZero(T* src)
	{
		memset(src,0,sizeof(T));
	}

	template <typename T>
	inline void SetZero(T* src,size_t count)
	{
		MemoryPrivate::SetZero_Imp(src,count,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template <typename T,size_t N>
	inline void SetZero(T (&src)[N])
	{
		MemoryPrivate::SetZero_Imp(src,N,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}
	

	template <typename T>
	inline void Swap(T& left,T& right)
	{
		MemoryPrivate::Swap_Imp(left,right,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	

	template <typename T>
	inline bool Equals(const T* first,const T* second,size_t count)
	{
		return memcmp(first,second,count)==0;
	}

	inline bool EqualsFloat(const float* first,const float* second,size_t count)
	{
		FOR_EACH_SIZE(i,count)
		{
			if (!Math::IsEqual(first[i],second[i]))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T,size_t N>
	inline bool Equals(const T (&first)[N],const T (&second)[N])
	{
		return memcmp(first,second,N)==0;
	}

	template<typename T>
	inline void Construct(T* p)
	{
		::new (static_cast<void*>(p)) T();
	}

	template<typename T>
	inline void ConstructRange(T* p,size_t size)
	{
		FOR_EACH_SIZE(i,size)
		{
			Construct(p);
		}
	}

	template<typename T,typename TP>
	inline void CopyConstruct(T* p,TP val)
	{
		MemoryPrivate::CopyConstruct_Imp(p,val,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template<typename T,typename TP>
	inline void CopyConstructRange(T* p,TP val,size_t size)
	{
		MemoryPrivate::CopyConstructRange_Imp(p,val,size,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template<typename T>
	inline void CopyConstructIterator(T* dest,const T* src,size_t size)
	{
		MemoryPrivate::CopyConstructIterator_Imp(dest,src,size,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template<typename T>
	inline void Destory(T* p)
	{
		MemoryPrivate::Destory_Imp(p,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	template<typename T>
	inline void Delete(T p)
	{
		MemoryPrivate::Delete_Imp(p,Compile::Bool2Type<Compile::TypeTraits<T>::IsPointer>());
	}

	template<typename T>
	inline void DestoryRange(T* p,size_t size)
	{
		MemoryPrivate::DestoryRange_Imp(p,size,Compile::Bool2Type<Compile::TypeTraits<T>::IsPOD>());
	}

	inline size_t FillCharArray(char* buffer,wchar_t wchar)
	{
		return MemoryPrivate::FillCharArray_Imp(buffer,wchar,Compile::Bool2Type<sizeof(wchar_t)==2>());
	}
}


MEDUSA_END;
