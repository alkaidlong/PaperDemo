#pragma  once
#include "MedusaCorePreCompiled.h"
MEDUSA_BEGIN;

namespace Pattern
{
	class ISharable
	{
	public:
		ISharable():mRefCount(0){}
		ISharable(const ISharable& val){mRefCount=val.mRefCount;}
		ISharable& operator=(const ISharable& ptr){mRefCount=ptr.mRefCount;return *this;}
		virtual ~ISharable(){mRefCount=0;}
		int GetRefCount()const{return mRefCount;}
		bool IsShared()const{return mRefCount>1;}
		MEDUSA_VIRTUAL void Retain(){++mRefCount;}
		MEDUSA_VIRTUAL void Release()
		{
			--mRefCount;
			if(mRefCount<=0)
			{
				delete this;
			}
		}
	private:
		int mRefCount;
	};
}

MEDUSA_END;