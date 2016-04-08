#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;
template<typename T>
class MemoryData
{
private:
	MemoryData(const T* data,size_t size,int* refCount):mData((T*)data),mSize(size),mRefCount(refCount)
	{
		
	}

public:
	MemoryData():mData(NULL),mSize(0),mRefCount(NULL){}

	MemoryData(const MemoryData& data ):mData((T*)data.GetData()),mSize(data.GetSize()),mRefCount(data.ForceGetRefCountPtr())
	{
		ForceRetain();
	}

	MemoryData& operator=(const MemoryData& data )
	{
		if (this!=&data)
		{
			ForceRelease();
			mData=(T*)data.mData;
			mSize=data.mSize;
			mRefCount=data.mRefCount;
			ForceRetain();
		}
		return *this;
	}

	bool operator==(const MemoryData& data )const
	{
		return mData==data.mData&&mSize==data.mSize&&mRefCount==data.mRefCount;
	}

	bool operator!=(const MemoryData& data )const
	{
		return mData!=data.mData||mSize!=data.mSize||mRefCount!=data.mRefCount;
	}

	~MemoryData()
	{
		ForceRelease();
	}
public:
	const T* GetData()const { return mData; }
	T* GetData() { return mData; }
	size_t GetSize() const { return mSize; }
	size_t GetByteSize() const { return mSize*sizeof(T); }

	int GetRefCount()const{return mRefCount!=NULL?*mRefCount:0;}


	bool IsNull()const{return mData==NULL||mSize==0;}
	bool IsEmpty()const{return mData==NULL||mSize==0;}

	bool IsValid()const{return !IsNull();}
	bool IsDataEqual(const MemoryData& data)const{return mData==data.mData;}

	operator T*()const{return mData;}

	void ClearZero()
	{
		Memory::SetZero(mData,mSize);
	}

	MemoryData Clone()const
	{
		T* outData=NULL;
		if(mData!=NULL)
		{
			outData=new T[mSize];
			Memory::SafeCopy(outData,mSize,mData,mSize);
		}
		return MemoryData(outData,mSize,mRefCount);
	}

	MemoryData Sub(size_t count)const
	{
		MEDUSA_ASSERT(count<=mSize,"");
		return MemoryData(mData,count,mRefCount);
	}


	template<typename T1>
	MemoryData<T1> Cast()const
	{
		return MemoryData<T1>::Share((T1*)mData,mSize*sizeof(T)/sizeof(T1),mRefCount);
	}

	static MemoryData CopyFrom(const T* buffer,size_t size)
	{
		T* result=new T[size];
		Memory::SafeCopy(result,size,buffer,size);
		return MemoryData(result,size,new int(1));
	}

public:
	static MemoryData FromStatic(const T* data,size_t size)
	{
		return MemoryData(data,size,NULL);
	}

	template<size_t size>
	static MemoryData FromStatic(const T (&data)[size])
	{
		return MemoryData((T*)data,size,NULL);
	}

	static MemoryData Take(const T* data,size_t size)
	{
		return MemoryData(data,size,new int(1));
	}

	template<size_t size>
	static MemoryData Take(const T (&data)[size])
	{
		return MemoryData((T*)data,size,new int(1));
	}

	static MemoryData Alloc(size_t size)
	{
		if (size==0)
		{
			return MemoryData::Empty;
		}
		T* buffer=new T[size];
		return MemoryData(buffer,size,new int(1));
	}

	static MemoryData Share(const T* data,size_t size,int* refCount)
	{
		if(refCount!=NULL)
		{
			++*refCount;
		}
		return MemoryData(data,size,refCount);
	}
public:
	void ForceSetData(T* val) { mData = val; }
	void ForceSetSize(size_t val) { mSize = val; }
	void ForceSetDataAndSize(T* val,size_t size){mData=val;mSize=size;}
	void ForceOffsetDataAndSize(int offset){mData+=offset;mSize-=offset;}

	void ForceRetain()
	{
		if (mRefCount!=NULL)
		{
			++*mRefCount;
		}
	}

	void ForceRelease()
	{
		if (mRefCount!=NULL)
		{
			--*mRefCount;
			if (*mRefCount<=0)
			{
				SAFE_DELETE_ARRAY(mData);
				mSize=0;
				delete mRefCount;
				mRefCount=NULL;
			}
		}
	}

	void ForceEnsureRefCount()
	{
		if (mRefCount==NULL)
		{
			mRefCount=new int(1);
		}
	}

	int* ForceGetRefCountPtr()const{return mRefCount;}
private:
	T* mData;
	size_t mSize;
	int* mRefCount;
public:
	const static MemoryData Empty;
};

template<typename T>
const MemoryData<T> MemoryData<T>::Empty;

//[PRE_DECLARE_BEGIN]
typedef MemoryData<short> MemoryShortData;
typedef MemoryData<byte> MemoryByteData;
typedef MemoryData<char> MemoryCharData;
typedef MemoryData<wchar_t> MemoryWCharData;
typedef MemoryData<int> MemoryIntData;
typedef MemoryData<uint> MemoryUIntData;

//[PRE_DECLARE_END]



MEDUSA_END;