
#include "Message/Battle/ChallengeMissionRequest.h"

#include "Message/Player.h"
#include "Config/MissionConfig.h"


ChallengeMissionRequest::~ChallengeMissionRequest(void)
{
}

void ChallengeMissionRequest::Initialize(uint missionId)
{
	mRequest.set_missionitemid(missionId);
}

void ChallengeMissionRequest::BeforeEnd()
{
	if (IsResultOk())
	{
		if (GetCustomError()==ServerProto::Logic::ChallengeMissionResponse_ErrorDetailCode_Ok)
		{
			StringParser::ResultStringType idStr=StringParser::ToString(mRequest.missionitemid());
			Analytics::BeginMission(idStr);
		}
	}

	IMessage::BeforeEnd();
}

void ChallengeMissionRequest::Mock()
{
	mResponse.set_errorcode(ServerProto::Ok);
	mResponse.set_errordetail(ServerProto::Logic::ChallengeMissionResponse_ErrorDetailCode_Ok);
}

IMPLEMENT_REGISTER_REQUEST(ChallengeMissionRequest,IMessage,ChallengeMissionResponse);
