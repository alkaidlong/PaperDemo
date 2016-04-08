#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Log/Log.h"
#include "Core/Message/MessageFactory.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/Proto/Proto.h"

MEDUSA_BEGIN;

template<typename TRequest,typename TResponse>
class BaseMessage:public IMessage
{
public:
	BaseMessage(){}
	virtual ~BaseMessage(void){}

public:
	virtual bool HasResponse()const{return mError==MessageError::Success&&this->mResponse.IsInitialized()&&mState==MessageState::Completed;}

	TRequest& GetRequestData(){ return mRequest; }
	void SetRequestData(const TRequest& val) { mRequest = val; }

	TResponse& GetResponseData() { return mResponse; }
	void SetResponseData(const TResponse& val) { mResponse = val; }


	virtual void PrintRequest()const
	{
		std::string outStr;
		Proto::SerializeToString(mRequest,outStr);
		Log::LogInfo(outStr.c_str());
	}

	virtual MemoryByteData SerializeRequest()const
	{
		return Proto::Serialize(mRequest);
	}

	virtual void ParseFromRequest(MemoryByteData data)
	{
		Proto::ParseFrom(mRequest,data);
	}

	virtual void PrintResponse()const
	{
		std::string outStr;
		Proto::SerializeToString(mResponse,outStr);
		Log::LogInfo(outStr.c_str());
	}

	virtual MemoryByteData SerializeResponse()const
	{
		return Proto::Serialize(mResponse);
	}

	virtual void ParseFromResponse(MemoryByteData data)
	{
		Proto::ParseFrom(mResponse,data);
	}
	
protected:
	TRequest mRequest;
	TResponse mResponse;

};


MEDUSA_END;
