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
		//MSG_DONTROUTE			不查找路由表 
		//MSG_OOB				接受或者发送带外数据 
		//MSG_PEEK				查看数据,并不从系统缓冲区移走数据 
		//MSG_WAITALL			等待所有数据  
		MemoryByteData messageData=stream.ReadBeginToCurrent(DataReadingMode::DirectMove);
		const char* tempCharBuffer=(const char*)messageData.GetData();		//临时数据缓存
		size_t messageSize=*(size_t*)tempCharBuffer;
		if (messageSize<4)
		{
			Log::AssertFailedFormat("Invalid ISocket::Send message size:%zu <4",messageSize);
			return SocketError::Fault;
		}

		intp writtenDataSize=0;		//已写数据量
		intp leftDataSize=messageData.GetSize();		//将要写数据量

		SocketError::SocketError_t result;
		while(leftDataSize>0) 
		{
			//开始写
			writtenDataSize=send(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag);	//返回已发送的数据量
			if(writtenDataSize<=0)			// 出错了 
			{
				result= SocketError::Fault; 
				break;
			}
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;     //从剩下的地方继续写 
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

		const char* tempCharBuffer=(const char*)messageData.GetData();		//临时数据缓存
		intp writtenDataSize=0;		//已写数据量
		intp leftDataSize=messageData.GetSize();		//将要写数据量
		while(leftDataSize>0) 
		{ 
			//开始写
			//返回已发送的数据量
			//注意这是用来发送数据报的,不保证成功.
			writtenDataSize=sendto(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag,address.GetGenearlAddressPtr(),sizeof(sockaddr));	
			if(writtenDataSize<=0)			// 出错了 
			{        
				result= SocketError::Fault; 
				break;
			} 
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;     //从剩下的地方继续写 

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
		//MSG_DONTROUTE			不查找路由表 
		//MSG_OOB				接受或者发送带外数据 
		//MSG_PEEK				查看数据,并不从系统缓冲区移走数据 
		//MSG_WAITALL			等待所有数据     
		SocketError::SocketError_t result;
		const int tempBufferSize=1024;
		char tempBuffer[tempBufferSize];

		while(true)
		{ 
			intp readDataSize=recv(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag);	//返回已读取的数据量

			if(readDataSize<0)				// 出错了
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

				//数据全部读完
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
			//返回已读取的数据量
			//注意这是用来接收数据报的,不保证成功.
			intp readDataSize=recvfrom(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag,address.GetGenearlAddressPtr(),(socklen_t*)&outFromDataSize);

			if(readDataSize<0)				// 出错了
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

		//根据主机名得到IP地址，允许点分十进制表示法
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

		//根据协议名得到协议号

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
