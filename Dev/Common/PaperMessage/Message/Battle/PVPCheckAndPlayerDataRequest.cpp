
#include "Message/Battle/PVPCheckAndPlayerDataRequest.h"

#include "Message/Player.h"


PVPCheckAndPlayerDataRequest::~PVPCheckAndPlayerDataRequest(void)
{
}

void PVPCheckAndPlayerDataRequest::Initialize(uint64 TargetID,ServerProto::Logic::PVPType type)
{
	mRequest.set_targetid(TargetID);
	mRequest.set_type(type);
}

void PVPCheckAndPlayerDataRequest::BeforeEnd()
{
	if (IsResultOk())
	{
		if (GetCustomError()==ServerProto::Logic::PVPCheckAndPlayerDataResponse_ErrorDetailCode_Ok)
		{
		}
	}

	IMessage::BeforeEnd();
}

void PVPCheckAndPlayerDataRequest::Mock()
{
	mResponse.set_errorcode(ServerProto::Ok);
	mResponse.set_errordetail(ServerProto::Logic::PVPCheckAndPlayerDataResponse_ErrorDetailCode_Ok);
}

IMPLEMENT_REGISTER_REQUEST(PVPCheckAndPlayerDataRequest,IMessage,PVPCheckAndPlayerDataResponse);
