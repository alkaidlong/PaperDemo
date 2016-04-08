#pragma once

#include "Core/Threading/Mutex.h"

MEDUSA_BEGIN;


template<typename THost>
class NoThreadingLockPolicy
{
public:
	class Lock
	{
	public:
		Lock(const THost&){}
		Lock(const THost*){}
		Lock(){}
		~Lock(){}
	private:
		Lock(const Lock &);
		Lock& operator=(const Lock &);
	};
};

template<typename THost>
class ClassThreadingLockPolicy
{
public:
	class Lock
	{
	public:
		Lock(const THost&){mMutex.Enter();}
		Lock(const THost*){mMutex.Enter();}
		Lock(){mMutex.Enter();}
		~Lock(){mMutex.Leave();}
	private:
		Lock(const Lock &);
		Lock& operator=(const Lock &);
	};
private:
	static Mutex mMutex;
};

template<typename THost>
class ObjectThreadingLockPolicy
{
public:
	class Lock
	{
	public:
		Lock(const THost&){mMutex.Enter();}
		Lock(const THost*){mMutex.Enter();}
		~Lock(){mMutex.Leave();}
	private:
		Lock(const Lock &);
		Lock& operator=(const Lock &);
		Mutex mMutex;
	};
};

MEDUSA_END;
