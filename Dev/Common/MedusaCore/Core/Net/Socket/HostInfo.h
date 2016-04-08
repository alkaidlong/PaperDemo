#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Socket
{
	class HostInfo
	{
	public:
		HostInfo(hostent* inHostent=NULL):mHostent(inHostent){}

		bool IsValid()const{return mHostent!=NULL;}

		static HostInfo GetHost(StringRef inHostName)
		{
			hostent* result=gethostbyname(inHostName.c_str());
			return HostInfo(result);
		}
		static HostInfo GetHost(StringRef inAddress,int inAddressLength,int inAddressType)
		{
			hostent* result=gethostbyaddr(inAddress.c_str(),inAddressLength,inAddressType);
			return HostInfo(result);
		}

	public:
		hostent* GetHostent() { return mHostent; }

		StringRef GetHostName()const  {return mHostent->h_name;}
		void SetHostName(StringRef inNewHostName) { mHostent->h_name=(char*)inNewHostName.c_str(); }

		char** GetHostAliases()const  {return mHostent->h_aliases;}
		void SetHostAlias(char** inNewHostAlias) { mHostent->h_aliases=inNewHostAlias; }

		int GetHostAddressType()const  {return mHostent->h_addrtype;}
		void SetHostAddressType(int HostAddressType) { mHostent->h_addrtype=HostAddressType; }

		int GetHostAddressSize()const  {return mHostent->h_length;}
		void SetHostAddressSize(int inNewHostAddressSize) { mHostent->h_length=inNewHostAddressSize; }

		char** GetHostAddressList()const  {return mHostent->h_addr_list;}
		void SetHostAddressList(char** inHostAddressList) { mHostent->h_addr_list=inHostAddressList; }

		char* GetFirstHostAddress()const{return mHostent->h_addr_list[0];}
		void SetFirstHostAddress(char* inNewHostAddress) { mHostent->h_addr_list[0]=inNewHostAddress; }
	private:
		hostent* mHostent;		//主机信息
	};
}

MEDUSA_END;
