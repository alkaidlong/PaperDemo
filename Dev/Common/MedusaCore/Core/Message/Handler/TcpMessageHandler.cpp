#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Log/Log.h"
#include "Core/Net/Socket/AddressInfo.h"
#include "Core/Net/Socket/ProtocolInfo.h"
#include "Core/Message/MessageFactory.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Threading/Thread.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Profile/AutoStopWatch.h"
#include "Core/Coder/ICoder.h"





MEDUSA_BEGIN;

TcpMessageHandler::TcpMessageHandler(size_t id, StringRef hostName, ushort port ,uint retryTimes,uint retryInternal,uint messageVersion,CoreProto::FileList::FileCoder::FileCoderType sendCoderType,CoreProto::FileList::FileCoder::FileCoderType receiveCoderType,const MemoryByteData& encryptKey)
	:IMessageHandler(id,hostName,port,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey),mSendMessageStream(mInitialMessageBufferSize),mReceiveMessageStream(mInitialMessageBufferSize)
{
	Socket::AddressInfo addressInfo;
	Socket::ProtocolInfo protocolInfo;
	Socket::ISocket::ParseAddress(hostName,port,Socket::SocketType::TCP,addressInfo,protocolInfo);
	mSocket.SetAddress(addressInfo);
	mSocket.SetProtocol(protocolInfo);

}

TcpMessageHandler::~TcpMessageHandler()
{

}

Socket::ClientSocket& TcpMessageHandler::GetSocket()
{
	bool isSuccess=mSocket.Initialize();
	Log::Assert(isSuccess,"Failed to initialize socket");

	/*mSocket.SetSendTimeout(5000);
	mSocket.SetReceiveTimeout(5000);*/

	return mSocket;
}

void TcpMessageHandler::Process()
{
	RETURN_IF_EMPTY(mMessageQueue);
	AutoStopWatch totalAutoStopWatch(mTotalStopWatch);
	

	bool isSuccess=mSocket.Initialize();
    mConnectStopWatch.Start();
    
    int curRetryTimes=0;
	if(isSuccess)
	{
		int socketError=mSocket.Connect();
		if (socketError<0)
		{
			int retryTimes=mRetryTimes;
			while(socketError<0&&retryTimes>0)
			{
				mSocket.Close();
				isSuccess=mSocket.Initialize();

				Thread::Sleep(mRetryInternal);
				socketError=mSocket.Connect();
				--retryTimes;
                curRetryTimes++;
			}
		}

		mConnectStopWatch.Stop();

		if (socketError<0)
		{
			GiveUpAllMessages();
		}
		else
		{
			while(mMessageQueue.GetCount()>0)
			{
				IMessage* message=mMessageQueue.Head();
				mMessageQueue.Pop();
				SendMessage(message);
				message->SetSendElapsedMilliseconds(mSendStopWatch.GetElapsedMilliseconds());
				message->SetReceiveElapsedMilliseconds(mReceiveStopWatch.GetElapsedMilliseconds());

				SAFE_RELEASE(message);
			}
		}

		mSocket.Close();
		//mSocket.ShutDown(Socket::SocketPipeType::ReadWrite);
	}
	else
	{
		GiveUpAllMessages();
		mConnectStopWatch.Stop();
	}

#ifdef MEDUSA_DEBUG
	Log::LogInfoFormat("MessageConnect:%.3f %d",mConnectStopWatch.GetElapsedMilliseconds(),curRetryTimes);
#endif
}


void TcpMessageHandler::GiveUpAllMessages()
{
	while(mMessageQueue.GetCount()>0)
	{
		IMessage* message=mMessageQueue.Head();
		mMessageQueue.Pop();
		message->SetError(MessageError::ConnectFail);
		message->SetSocketError(errno);
		FailSocket(message);

		SAFE_RELEASE(message);
	}
}

IMessage* TcpMessageHandler::SendMessage( IMessage* message )
{
	Socket::SocketError::SocketError_t socketError;
	MemoryByteData buffer=message->SerializeRequest();

	mSendMessageStream.Rewind();
	StringRef messageName=message->GetRTTIClass().GetClassName();
	uint32 messageNameSize=messageName.Length()+1;
	uint32 messageAllSize=messageNameSize+buffer.GetSize()+sizeof(uint32)*2;
	if (messageAllSize<4)
	{
		Log::AssertFailedFormat("Invalid messageAllSize:%d <4 and messageNameSize:%d",messageAllSize,messageNameSize);
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->GetReceiveHandler(),message);
		return message;
	}


	mSendMessageStream.Write(messageAllSize);
	mSendMessageStream.Write(mMessageVersion);
	mSendMessageStream.Write(messageNameSize);
	mSendMessageStream.WriteString(messageName);
	mSendMessageStream.WriteData(buffer);

	//encrypt
	MemoryByteData sendData=mSendMessageStream.ReadBeginToCurrent(DataReadingMode::DirectMove);
	sendData.ForceOffsetDataAndSize(sizeof(uint));
	MemoryByteData encryptedSendData=mSendCoder->CodeSmart(sendData);
	mSendMessageStream.Rewind();
	mSendMessageStream.Write(encryptedSendData.GetByteSize());
	mSendMessageStream.WriteData(encryptedSendData);


	int timeout=(int)(message->GetTimeout()*1000);
	mSocket.SetSendTimeout(timeout);
	mSocket.SetReceiveTimeout(timeout);


	{
		AutoStopWatch autoSendStopWatch(mSendStopWatch);
		socketError=mSocket.Send(mSendMessageStream);
	}


	message->SetError(socketError);

	if (socketError==Socket::SocketError::Success)
	{
		Log::LogInfoFormat("Send:%s",message->GetRTTIClass().GetClassName().c_str());
	}


	FireUIEventAsync(message->GetSendHandler(),message);

	if (socketError==Socket::SocketError::Success)
	{
		mReceiveMessageStream.Rewind();

		{
			AutoStopWatch autoReceiveStopWatch(mReceiveStopWatch);
			socketError=mSocket.Receive(mReceiveMessageStream,Socket::ReceiveCompleteChecker(this,&TcpMessageHandler::OnReceiveCompeleteCheck));
		}
		

		message->SetError(socketError);

		if (socketError==Socket::SocketError::Success)
		{
			uint64 receiveLength=mReceiveMessageStream.GetPosition();
			mReceiveMessageStream.Rewind();
			/*uint length=*/mReceiveMessageStream.Read<uint>();
			//decrypt
			MemoryByteData receivedData=mReceiveMessageStream.GetCurrentBuffer();
			receivedData.ForceSetSize((size_t)receiveLength-sizeof(uint));
			MemoryByteData encryptedReceiveData=mReceiveCoder->CodeSmart(receivedData);
			mReceiveMessageStream.WriteData(encryptedReceiveData);


			mReceiveMessageStream.Rewind();
			/*uint length=*/mReceiveMessageStream.Read<uint>();

			uint version=mReceiveMessageStream.Read<uint>();
			if (version<mMessageVersion)
			{
				//incompatible message version
				Log::AssertFailedFormat("Error message version:%d< %d",version,mMessageVersion);

				message->SetSocketError(errno);
				message->SetState(MessageState::ConnectFail);
				FireUIEventAsync(message->GetReceiveHandler(),message);
			}
			else
			{
				/*uint nameLength=*/mReceiveMessageStream.Read<uint>();
				StringRef responseMessageName=mReceiveMessageStream.ReadString();

				StringRef expectedResponseClassName=message->GetResponseClassName();
				if (expectedResponseClassName==responseMessageName)
				{

					message->SetError(socketError);
					MemoryByteData receiveData=mReceiveMessageStream.ReadData((size_t)(receiveLength-mReceiveMessageStream.GetPosition()),DataReadingMode::DirectMove);
					message->ParseFromResponse(receiveData);
					Log::LogInfoFormat("Receive:%s",responseMessageName.c_str());

					message->SetState(MessageState::Completed);
					FireUIEventAsync(message->GetReceiveHandler(),message);
				}
				else
				{
					Log::AssertFailedFormat("Error response id:%s for %s",responseMessageName.c_str(),message->GetRTTIClass().GetClassName().c_str());

					message->SetSocketError(errno);
					message->SetState(MessageState::ConnectFail);
					FireUIEventAsync(message->GetReceiveHandler(),message);
				}
			}
		}
		else
		{
			Log::LogErrorFormat("Cannot Receive response for:%s",message->GetRTTIClass().GetClassName().c_str());

			message->SetSocketError(errno);
			message->SetState(MessageState::ConnectFail);
			FireUIEventAsync(message->GetReceiveHandler(),message);
		}
	}
	else
	{
		Log::LogErrorFormat("Cannot Send:%s",message->GetRTTIClass().GetClassName().c_str());

		message->SetSocketError(errno);
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->GetReceiveHandler(),message);

	}

	return message;
}

void TcpMessageHandler::FailSocket( IMessage* message )
{
	char buffer[1024];
	int errorCode= mSocket.GetError();
#ifdef WIN32
	strerror_s(buffer,errorCode);
#else
	strerror_r(errorCode, buffer, 1024);
#endif


	Log::LogErrorFormat("Connect error:%d %s",errorCode,buffer);
	message->SetState(MessageState::ConnectFail);

	//give up all message?
	while (!mMessageQueue.IsEmpty()) 
	{
		IMessage* message=mMessageQueue.Head();
		message->SetError(MessageError::ConnectFail);
		message->SetState(MessageState::ConnectFail);
		mMessageQueue.Pop();
	}

	mSocket.ShutDown(Socket::SocketPipeType::ReadWrite);
}

bool TcpMessageHandler::OnReceiveCompeleteCheck( IStream& stream )
{
	RETURN_FALSE_IF(stream.GetLength()<sizeof(size_t));

	uint64 pos=stream.GetPosition();
	stream.Rewind();
	size_t length=stream.Read<size_t>();
	bool isComplted=(length==pos-sizeof(size_t));
	stream.SetPosition(pos);

	return isComplted;
}

MEDUSA_END;
