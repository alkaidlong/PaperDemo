#pragma once
#include "Message/BaseRequestLoginGameMessage.h"
#include "Proto/Server/Logic/MissionCheckOutRequest.pb.h"
#include "Proto/Server/Logic/MissionCheckOutResponse.pb.h"

class MissionCheckOutRequest: public BaseRequestLoginGameMessage<ServerProto::Logic::MissionCheckOutRequest,ServerProto::Logic::MissionCheckOutResponse>
{
	DECLARE_REGISTER_REQUEST(MissionCheckOutRequest);
public:
	MissionCheckOutRequest():BaseRequestLoginGameMessage<ServerProto::Logic::MissionCheckOutRequest,ServerProto::Logic::MissionCheckOutResponse>(){}
	~MissionCheckOutRequest(void);

	void Initialize(uint missionId,bool isPassed,const List<uint64>& survialHeroes);

	virtual void BeforeEnd();
	virtual void Mock();

};

