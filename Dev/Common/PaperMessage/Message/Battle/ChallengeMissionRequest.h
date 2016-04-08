#pragma once
#include "Message/BaseRequestLoginGameMessage.h"
#include "Proto/Server/Logic/ChallengeMissionRequest.pb.h"
#include "Proto/Server/Logic/ChallengeMissionResponse.pb.h"


class ChallengeMissionRequest: public BaseRequestLoginGameMessage<ServerProto::Logic::ChallengeMissionRequest,ServerProto::Logic::ChallengeMissionResponse>
{
	DECLARE_REGISTER_REQUEST(ChallengeMissionRequest);
public:
	ChallengeMissionRequest():BaseRequestLoginGameMessage<ServerProto::Logic::ChallengeMissionRequest,ServerProto::Logic::ChallengeMissionResponse>(){}
	~ChallengeMissionRequest(void);

	void Initialize(uint missionId);

	virtual void BeforeEnd();

	virtual void Mock();

};

