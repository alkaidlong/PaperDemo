
#include "BaseCustomGameMessage.h"

BaseCustomGameMessage::BaseCustomGameMessage()
{

}

BaseCustomGameMessage::~BaseCustomGameMessage(void)
{
}

int BaseCustomGameMessage::GetCustomError() const
{
	if (IsResultOk())
	{
		return GameMessageLogicError::Success.ToInt();
	}
	else
	{
		int lastError=mLastErrorMessage->GetServerError();
		switch(lastError)
		{
		case 1:
			return GameMessageLogicError::ServiceUnavailable.ToInt();
		case 2:
			return GameMessageLogicError::AuthFaied.ToInt();
			break;
		default:
			return GetFurtherCustomError();
		}
	}
}

int BaseCustomGameMessage::GetFurtherCustomError()const
{
	return mLastErrorMessage->GetServerError();
}

