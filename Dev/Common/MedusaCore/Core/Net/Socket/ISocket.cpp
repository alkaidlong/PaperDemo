#include "MedusaCorePreCompiled.h"
#include "Core/Net/Socket/ISocket.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

namespace Socket
{
	SocketError::SocketError_t ISocket::Send( IStream& stream,int inControlFlag )
	{
		if (mSocketType!=SocketType::TCP)
		{
			return SocketError::Fault;
		}

		//inControlFlag:
		//MSG_DONTROUTE			������·�ɱ� 
		//MSG_OOB				���ܻ��߷��ʹ������� 
		//MSG_PEEK				�鿴����,������ϵͳ�������������� 
		//MSG_WAITALL			�ȴ���������  
		MemoryByteData messageData=stream.ReadBeginToCurrent(DataReadingMode::DirectMove);
		const char* tempCharBuffer=(const char*)messageData.GetData();		//��ʱ���ݻ���
		size_t messageSize=*(size_t*)tempCharBuffer;
		if (messageSize<4)
		{
			Log::AssertFailedFormat("Invalid ISocket::Send message size:%zu <4",messageSize);
			return SocketError::Fault;
		}

		intp writtenDataSize=0;		//��д������
		intp leftDataSize=messageData.GetSize();		//��Ҫд������

		SocketError::SocketError_t result;
		while(leftDataSize>0) 
		{
			//��ʼд
			writtenDataSize=send(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag);	//�����ѷ��͵�������
			if(writtenDataSize<=0)			// ������ 
			{
				result= SocketError::Fault; 
				break;
			}
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;     //��ʣ�µĵط�����д 
		} 

		if (leftDataSize<=0)
		{
			result=SocketError::Success;
		}
		return result; 
	}

	SocketError::SocketError_t ISocket::SendTo(const AddressInfo& address,IStream& stream,int inControlFlag )
	{
		if (mSocketType!=SocketType::UDP)
		{
			return SocketError::Fault;
		}
		SocketError::SocketError_t result;
		MemoryByteData messageData=stream.ReadToEnd(DataReadingMode::DirectMove);

		const char* tempCharBuffer=(const char*)messageData.GetData();		//��ʱ���ݻ���
		intp writtenDataSize=0;		//��д������
		intp leftDataSize=messageData.GetSize();		//��Ҫд������
		while(leftDataSize>0) 
		{ 
			//��ʼд
			//�����ѷ��͵�������
			//ע�����������������ݱ���,����֤�ɹ�.
			writtenDataSize=sendto(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag,address.GetGenearlAddressPtr(),sizeof(sockaddr));	
			if(writtenDataSize<=0)			// ������ 
			{        
				result= SocketError::Fault; 
				break;
			} 
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;     //��ʣ�µĵط�����д 

		} 
		if (leftDataSize<=0)
		{
			result=SocketError::Success;
		}
		return result; 
	}

	SocketError::SocketError_t ISocket::Receive(IStream& stream,ReceiveCompleteChecker checker,int inControlFlag )
	{
		if (mSocketType!=SocketType::TCP)
		{
			return SocketError::Fault;
		}
		//inControlFlag:
		//MSG_DONTROUTE			������·�ɱ� 
		//MSG_OOB				���ܻ��߷��ʹ������� 
		//MSG_PEEK				�鿴����,������ϵͳ�������������� 
		//MSG_WAITALL			�ȴ���������     
		SocketError::SocketError_t result;
		const int tempBufferSize=1024;
		char tempBuffer[tempBufferSize];

		while(true)
		{ 
			intp readDataSize=recv(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag);	//�����Ѷ�ȡ��������

			if(readDataSize<0)				// ������
			{ 
				Log::LogErrorFormat("SocketError:read size:%d",readDataSize);
				result= SocketError::Fault; 
				break;
			} 
			else if (readDataSize>0)
			{
				stream.WriteData(MemoryByteData::FromStatic((const byte*)tempBuffer,readDataSize));
				if (checker(stream))
				{
					result=SocketError::Success;
					break;
				}

			} 
			else
			{
				Log::LogErrorFormat("SocketError:read size:%d",readDataSize);

				//����ȫ������
				result= SocketError::Fault; 
				break;
			}
		} 


		return result; 
	}

	SocketError::SocketError_t ISocket::ReceiveFrom(const AddressInfo& address,IStream& stream,ReceiveCompleteChecker checker,int inControlFlag)
	{
		if (mSocketType!=SocketType::UDP)
		{
			return SocketError::Fault;
		}
		SocketError::SocketError_t result;
		const int tempBufferSize=1024;
		char tempBuffer[tempBufferSize];


		int outFromDataSize=sizeof(sockaddr);

		while(true) 
		{ 
			//�����Ѷ�ȡ��������
			//ע�����������������ݱ���,����֤�ɹ�.
			intp readDataSize=recvfrom(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag,address.GetGenearlAddressPtr(),(socklen_t*)&outFromDataSize);

			if(readDataSize<0)				// ������
			{ 
				result= SocketError::Fault; 
				break;
			} 
			else if(readDataSize>0)
			{
				stream.WriteData(MemoryByteData::FromStatic((const byte*)tempBuffer,readDataSize));
				if (checker(stream))
				{
					result=SocketError::Success;
					break;
				}
			}
			else
			{
				result= SocketError::Fault; 
				break;
			}
		} 

		return result; 
	}


	void ISocket::Close()
	{
#ifdef WIN32
		::closesocket(mSocketDescriptor);
#else
		::close(mSocketDescriptor);
#endif // WIN32
	}

	bool ISocket::ShutDown( SocketPipeType::SocketPipeType_t inControlFlag )
	{

		return shutdown(mSocketDescriptor,inControlFlag)==0;
	}

	bool ISocket::InitializeAPI()
	{
#ifdef WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD( 2, 2 );
		int err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) 
		{
			return false;
		}
#endif // WIN32
		return true;
	}

	bool ISocket::UninitializeAPI()
	{
#ifdef WIN32
		WSACleanup();
#endif // WIN32

		return true;
	}


	bool ISocket::Initialize()
	{
		return CreateSocket();
	}

	bool ISocket::Uninitialize()
	{
		return true;
	}

	const char* ISocket::GetProtocolName() const
	{
		if (mSocketType==SocketType::TCP)
		{
			return "tcp";
		}
		else if (mSocketType==SocketType::UDP)
		{
			return "udp";
		} 
		return NULL;
	}

	SocketProtocolType::SocketProtocolType_t ISocket::GetProtocolType(SocketType::SocketType_t socketType)
	{
		if (socketType==SocketType::TCP)
		{
			return SocketProtocolType::TCP;
		}
		else if (socketType==SocketType::UDP)
		{
			return SocketProtocolType::UDP;
		} 
		return SocketProtocolType::TCP;
	}

	bool ISocket::CreateSocket()
	{
		mSocketDescriptor=socket(mAddress.GetAddressFamily(),mSocketType,GetProtocolType(mSocketType));
		if (mSocketDescriptor<=0)
		{
			return false;
		}
		return true;
	}

	int ISocket::GetError()
	{
#ifdef WIN32
		return WSAGetLastError();
#endif 
		return 0;
	}

	void ISocket::SetSendTimeout( int milliSeconds )
	{
#ifdef WIN32
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_SNDTIMEO,(char *)&milliSeconds,sizeof(int));
#else
		struct timeval timeout = {milliSeconds*1000,0}; 
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(struct timeval)); 
#endif 
	}

	void ISocket::SetReceiveTimeout( int milliSeconds )
	{
#ifdef WIN32
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_RCVTIMEO,(char *)&milliSeconds,sizeof(int));
#else
		struct timeval timeout = {milliSeconds*1000,0}; 
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval)); 
#endif 
	}

	bool ISocket::ParseAddress( StringRef inHostName, ushort port,SocketType::SocketType_t socketType,AddressInfo& outAddress,ProtocolInfo& outProtocolInfo )
	{
		RETURN_FALSE_IF_EMPTY(inHostName);
		outAddress.SetPortID(htons(port));

		//�����������õ�IP��ַ��������ʮ���Ʊ�ʾ��
		HostInfo hostInfo=HostInfo::GetHost(inHostName);
		if(hostInfo.IsValid())
		{
			sockaddr_in temp;
			memcpy(&temp.sin_addr,hostInfo.GetFirstHostAddress(),hostInfo.GetHostAddressSize());
			outAddress.SetAddress(temp.sin_addr);
		}
		else
		{
			unsigned int addr=inet_addr(inHostName.c_str());
			outAddress.SetAddress(addr);
		}

		//����Э�����õ�Э���

		outProtocolInfo=ProtocolInfo::GetProtocol(GetProtocolType(socketType));
		return true;
	}

	void ISocket::SetIsAsync( bool isAsync )
	{
		//unsigned long   ul=   1; 

		//ioctlsocket(mSocketDescriptor,FIONBIO,&ul);

	}

}
MEDUSA_END;
