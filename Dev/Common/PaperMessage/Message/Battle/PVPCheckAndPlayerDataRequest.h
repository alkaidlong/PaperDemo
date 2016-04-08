#pragma once
#include "Message/BaseRequestLoginGameMessage.h"
#include "Proto/Server/Logic/PVPCheckAndPlayerDataRequest.pb.h"
#include "Proto/Server/Logic/PVPCheckAndPlayerDataResponse.pb.h"


class PVPCheckAndPlayerDataRequest: public BaseRequestLoginGameMessage<ServerProto::Logic::PVPCheckAndPlayerDataRequest,ServerProto::Logic::PVPCheckAndPlayerDataResponse>
{
	DECLARE_REGISTER_REQUEST(PVPCheckAndPlayerDataRequest);
public:
	PVPCheckAndPlayerDataRequest():BaseRequestLoginGameMessage<ServerProto::Logic::PVPCheckAndPlayerDataRequest,ServerProto::Logic::PVPCheckAndPlayerDataResponse>(){}
	~PVPCheckAndPlayerDataRequest(void);

	void Initialize(uint64 TargetID,ServerProto::Logic::PVPType type);

	virtual void BeforeEnd();

	virtual void Mock();

};

