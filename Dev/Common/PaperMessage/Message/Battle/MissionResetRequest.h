#pragma once
#include "Message/BaseRequestLoginGameMessage.h"
#include "Proto/Server/Logic/MissionResetRequest.pb.h"
#include "Proto/Server/Logic/MissionResetResponse.pb.h"
#include "Core/Pattern/TuplePattern.h"
#include "Core/Collection/Array.h"

class MissionResetRequest: public BaseRequestLoginGameMessage<ServerProto::Logic::MissionResetRequest,ServerProto::Logic::MissionResetResponse>
{
	DECLARE_REGISTER_REQUEST(MissionResetRequest);
public:
public:
	MissionResetRequest():BaseRequestLoginGameMessage<ServerProto::Logic::MissionResetRequest,ServerProto::Logic::MissionResetResponse>(){}
	~MissionResetRequest(void);

	void Initialize(uint missionItemID);

	virtual void BeforeEnd();
	virtual void Mock();

};

