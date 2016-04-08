#pragma once
#include "Core/Net/Socket/ISocket.h"

MEDUSA_BEGIN;

namespace Socket
{
	class ClientSocket:public ISocket
	{
	public:
		ClientSocket(SocketType::SocketType_t socketType=SocketType::TCP)
			:ISocket(socketType)
		{
			
		}

		ClientSocket(const AddressInfo& address,const ProtocolInfo& protocolInfo):ISocket(SocketType::TCP)
		{
			mAddress=address;
			mProtocol=protocolInfo;
		}

		ClientSocket(SOCKET socketDescriptor,const sockaddr& address):ISocket(SocketType::TCP)
		{
			mSocketDescriptor=socketDescriptor;
			mAddress.SetGeneralAddress(address);
		}

		virtual ~ClientSocket(void){}
		
		int Connect()
		{
			int connectState=connect(mSocketDescriptor,mAddress.GetGenearlAddressPtr(),sizeof(sockaddr));

			return connectState;
		}

	private://≤ª‘ –Ì∏¥÷∆
		void operator=(const ClientSocket&);
		ClientSocket(const ClientSocket&);

	protected:
		//string 
	};

}
MEDUSA_END;
