#pragma once

#include "Core/Net/Socket/ISocket.h"
#include "Core/Net/Socket/ClientSocket.h"



MEDUSA_BEGIN;

namespace Socket
{
	class ServerSocket:public ISocket
	{
	public:
		ServerSocket(ushort port, SocketType::SocketType_t socketType=SocketType::TCP)
			:ISocket(socketType)
		{
			//设置服务器套接字的IP地址为特殊值INADDR_ANY
			//这表示服务器愿意接收来自任何网络设备接口的客户机
			mAddress.SetAddress(INADDR_ANY);
			mAddress.SetPortID(htons(port));
		}
		virtual ~ServerSocket(void){}

		
		ClientSocket* Accept()
		{
			sockaddr socketAddress;
			int len=sizeof(sockaddr);
			SOCKET clientSocketDescriptor=accept(mSocketDescriptor,&socketAddress,(socklen_t*)&len);

			if (clientSocketDescriptor<=0)	//如果无法接收请求
			{

				//int errorCode= GetError();
				return NULL;
			}

			return new ClientSocket(clientSocketDescriptor,socketAddress);
		}

		bool Bind()
		{
			int result=::bind(mSocketDescriptor,mAddress.GetGenearlAddressPtr(),sizeof(sockaddr));
			return result>=0;
		}

		bool Listen(unsigned int inQueueLength=5)
		{
			if (inQueueLength!=0)
			{
				int result=listen(mSocketDescriptor,inQueueLength);
				return result==0;
			}
			return false;
		}
	private:
		void operator=(const ServerSocket&);
		ServerSocket(const ServerSocket&);
	};

}
MEDUSA_END;
