#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Socket
{
	class AddressInfo
	{
	public:
		AddressInfo(void)
		{
			SetAddressFamily(AF_INET);
		}
		AddressInfo(const sockaddr_in& inSockaddr):mAddress(inSockaddr){SetAddressFamily(AF_INET);}
		AddressInfo(const sockaddr& inSockaddr):mAddress(*(sockaddr_in*)(&inSockaddr)){SetAddressFamily(AF_INET);}
		
		static bool IsIPAddress(StringRef inAddress)
		{
			//IP地址格式:<ddd.ddd.ddd.ddd>
			RETURN_FALSE_IF_EMPTY(inAddress);
			if(inet_addr(inAddress.c_str())==INADDR_NONE)	//是否可以转换
			{
				return false;
			}
			return true;
		}

		
		static bool IsPort(StringRef inValue)
		{
			//端口格式:<d*>
			RETURN_FALSE_IF_EMPTY(inValue);
			
			size_t length=inValue.Length();
			for (size_t i=0;i<length;i++)
			{
				if (!isdigit(inValue[i]))
				{
					return false;
				}
			}
			return true;
		}
	public:
		const sockaddr_in& GetTCPIPAddress() const { return mAddress; }
		void SetTCPIPAddress(const sockaddr_in& inNewTCPIPAdress){mAddress = inNewTCPIPAdress;}

		const sockaddr& GetGenearlAddress()const{return *(sockaddr*)&mAddress;}
		sockaddr* GetGenearlAddressPtr()const{return (sockaddr*)&mAddress;}
		void SetGeneralAddress(const sockaddr& inNewGeneralAddress) { mAddress = *(sockaddr_in*)(&inNewGeneralAddress); }

		unsigned short GetPortID() const { return mAddress.sin_port; }
		unsigned int GetAddress() const { return mAddress.sin_addr.s_addr; }
		unsigned short GetAddressFamily() const { return mAddress.sin_family; }
		void SetAddressFamily(unsigned short inNewAddressType) { mAddress.sin_family = inNewAddressType; }
		void SetPortID(unsigned short inNewPortID) { mAddress.sin_port = inNewPortID; }
		void SetAddress(unsigned int inNewAddress) { mAddress.sin_addr.s_addr = inNewAddress; }
		void SetAddress(in_addr inNewAddress) { mAddress.sin_addr = inNewAddress; }
	private:
		sockaddr_in mAddress;

	};
}

MEDUSA_END;
