#pragma once
#include "Core/Message/BaseMessage.h"
MEDUSA_BEGIN;

template<typename TRequest,typename TResponse>
class BaseRequestMessage:public BaseMessage<TRequest,TResponse>
{
public:
	BaseRequestMessage(){}
	virtual ~BaseRequestMessage(void){}
	virtual MessageType GetType()const{return MessageType::Request;}

	virtual bool IsResultOk()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errorcode()==0;	//0 means success
		}
		return false;
	}
	virtual int GetCustomError()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errordetail();
		}
		return (int)this->mError;
	}

	virtual int GetServerError()const
	{
		if (this->mResponse.IsInitialized())
		{
			return this->mResponse.errorcode();
		}
		return (int)this->mError;
	}

};

#define DECLARE_REGISTER_REQUEST(className) 													\
	MEDUSA_DECLARE_RTTI(className);														\
public:																							 \
	virtual StringRef GetResponseClassName()const{return mResponseClassName;}				\
	static StringRef GetResponseClassNameStatic(){return mResponseClassName;}				\
private:																				\
	const static StringRef mResponseClassName;												\
	const static Pattern::StaticConstructor mStaticConstructor;							\
	static void SelfStaticCallback();


#define IMPLEMENT_REGISTER_REQUEST(className,baseClassName,reponseName) 																					 \
	MEDUSA_IMPLEMENT_RTTI(className,baseClassName);	\
	WEAK_MULTIPLE_DEFINE const StringRef className::mResponseClassName=#reponseName;	\
	const Pattern::StaticConstructor className::mStaticConstructor(SelfStaticCallback);					 \
	void className::SelfStaticCallback(){MessageFactory::Instance().Register<className>(#className);}

MEDUSA_END;
