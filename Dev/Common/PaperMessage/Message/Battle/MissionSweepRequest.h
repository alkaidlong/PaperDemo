#pragma once
#include "Message/BaseRequestLoginGameMessage.h"
#include "Proto/Server/Logic/MissionSweepRequest.pb.h"
#include "Proto/Server/Logic/MissionSweepResponse.pb.h"
#include "Core/Pattern/TuplePattern.h"
#include "Core/Collection/Array.h"

class MissionSweepRequest: public BaseRequestLoginGameMessage<ServerProto::Logic::MissionSweepRequest,ServerProto::Logic::MissionSweepResponse>
{
	DECLARE_REGISTER_REQUEST(MissionSweepRequest);
public:
public:
	MissionSweepRequest():BaseRequestLoginGameMessage<ServerProto::Logic::MissionSweepRequest,ServerProto::Logic::MissionSweepResponse>(){}
	~MissionSweepRequest(void);

	void Initialize(uint missionItemID,ServerProto::Logic::MissionSweepRequest_SweepType sweepType);

	virtual void BeforeEnd();
	virtual void Mock();

};

