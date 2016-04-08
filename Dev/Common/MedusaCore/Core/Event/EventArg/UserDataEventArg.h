#pragma once
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;
template<typename T>
class UserDataEventArg:public IEventArg
{
public:
	UserDataEventArg(T data):IEventArg(),mData(data){}
	UserDataEventArg():IEventArg(){}
	virtual ~UserDataEventArg(void){}

public:
	T GetData() const { return mData; }
	const T& GetDataRef() const { return mData; }
	T& GetDataRef() { return mData; }


	void SetData(T val) { mData = val; }
protected:
	T mData;

};

MEDUSA_END;