#include "MedusaCorePreCompiled.h"
#include "Core/Message/BaseCustomMessage.h"
#include "Core/Log/Log.h"
MEDUSA_BEGIN;

BaseCustomMessage::BaseCustomMessage()
{
	mState=MessageState::None;
	mLastError=0;
	mLastErrorMessage=NULL;
}

BaseCustomMessage::~BaseCustomMessage( void )
{
	FOR_EACH_COLLECTION(i,mPrevMessages)
	{
		IMessage* message=*i;
		message->Release();
	}

	FOR_EACH_COLLECTION(i,mNextMessages)
	{
		IMessage* message=*i;
		message->Release();
	}

}


void BaseCustomMessage::Update( float dt )
{
	switch(mState)
	{
	case MessageState::None:
		break;
	case MessageState::ReadyForSend:
		break;
	case MessageState::Running:
		{
			bool isFailed=false;
			bool isStillRunning=false;
			FOR_EACH_COLLECTION(i,mPrevMessages)
			{
				IMessage* message=*i;
				if (message->GetState()==MessageState::ConnectFail)
				{
					isFailed=true;
				}
				else if (message->GetState()==MessageState::Completed)
				{

				}
				else
				{
					isStillRunning=true;
					break;
				}

			}

			if (!isStillRunning)
			{
				mState=isFailed?MessageState::ConnectFail:MessageState::ReadyForNext;
			}
		}

		
		break;

	case MessageState::NextRunning:
		{
			bool isFailed=false;
			bool isStillRunning=false;
			FOR_EACH_COLLECTION(i,mNextMessages)
			{
				IMessage* message=*i;
				if (message->GetState()==MessageState::ConnectFail)
				{
					isFailed=true;
				}
				else if (message->GetState()==MessageState::Completed)
				{

				}
				else
				{
					isStillRunning=true;
					break;
				}
			}

			if (!isStillRunning)
			{
				mState=isFailed?MessageState::ConnectFail:MessageState::Completed;
			}
		}


		break;
	case MessageState::Completed:
		break;
	case MessageState::ConnectFail:
		break;
    default:
        break;
	}
}

void BaseCustomMessage::PrepareReadyForSend()
{
	SendPrevMessages();
	mState=MessageState::Running;
}

void BaseCustomMessage::PrepareToNextRunning()
{
	if (IsPrevMessagesResultOk())
	{
		UpdatePrevData();
		SendNextMessages();
	}
	mState=MessageState::NextRunning;
}

void BaseCustomMessage::AddPrevMessage( IMessage* message )
{
	LOG_ASSERT_NOT_NULL(message);
	message->Retain();
	mPrevMessages.Append(message);
	message->SetIsSubMessage(true);
}

void BaseCustomMessage::AddNextMessage( IMessage* message )
{
	LOG_ASSERT_NOT_NULL(message);
	message->Retain();
	mNextMessages.Append(message);
	message->SetIsSubMessage(true);

}

void BaseCustomMessage::BeforeEnd()
{
	if (IsNextMessagesResultOk())
	{
		UpdateNextData();

		//do all before end at one time
		FOR_EACH_COLLECTION(i,mPrevMessages)
		{
			IMessage* message=*i;
			if (message->IsResultOk())
			{
				message->BeforeEnd();
			}
		}

		FOR_EACH_COLLECTION(i,mNextMessages)
		{
			IMessage* message=*i;
			if (message->IsResultOk())
			{
				message->BeforeEnd();
			}
		}
	}

	IMessage::BeforeEnd();
}

bool BaseCustomMessage::IsResultOk() const
{
	FOR_EACH_COLLECTION(i,mPrevMessages)
	{
		IMessage* message=*i;
		if (!message->IsResultOk())
		{
			mLastErrorMessage=message;
			return false;
		}
	}

	FOR_EACH_COLLECTION(i,mNextMessages)
	{
		IMessage* message=*i;
		if (!message->IsResultOk())
		{
			mLastErrorMessage=message;
			return false;
		}
	}

	return true;
}

bool BaseCustomMessage::IsPrevMessagesResultOk()
{
	RETURN_TRUE_IF_EMPTY(mPrevMessages);
	bool isSuccess=true;
	FOR_EACH_COLLECTION(i,mPrevMessages)
	{
		IMessage* message=*i;
		switch(message->GetType())
		{
		case MessageType::Request:
			{
				if(!message->IsResultOk())
				{
					isSuccess=false;
				}
			}
			
			break;
		case MessageType::Custom:
			{
				BaseCustomMessage* customMessage=(BaseCustomMessage*)message;
				if (!customMessage->IsPrevMessagesResultOk())
				{
					isSuccess=false;
				}
			}
			break;
		}
		
		
	}

	return isSuccess;
}

bool BaseCustomMessage::IsNextMessagesResultOk()
{
	RETURN_TRUE_IF_EMPTY(mNextMessages);
	bool isSuccess=true;
	FOR_EACH_COLLECTION(i,mNextMessages)
	{
		IMessage* message=*i;
		switch(message->GetType())
		{
		case MessageType::Request:
			{
				if(!message->IsResultOk())
				{
					isSuccess=false;
				}
			}

			break;
		case MessageType::Custom:
			{
				BaseCustomMessage* customMessage=(BaseCustomMessage*)message;
				if (!customMessage->IsPrevMessagesResultOk())
				{
					isSuccess=false;
				}
			}
			break;
		}


	}

	return isSuccess;
}

int BaseCustomMessage::GetServerError() const
{
	if (mLastErrorMessage!=NULL)
	{
		return mLastErrorMessage->GetServerError();
	}
	return 0;
}
MEDUSA_END;
