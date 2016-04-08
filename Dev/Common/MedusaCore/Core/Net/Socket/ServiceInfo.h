#pragma once

#include "MedusaCorePreCompiled.h"




MEDUSA_BEGIN;
namespace Socket
{
	class ServiceInfo
	{
	public:
		ServiceInfo(servent* inServent=NULL):mServent(inServent){}

		static ServiceInfo GetService(StringRef inServiceName,StringRef inProtocolName)
		{
			servent* result=getservbyname(inServiceName.c_str(),inProtocolName.c_str());
			return ServiceInfo(result);

		}
		static ServiceInfo GetService(int inPortID,StringRef inProtocolName)
		{
			servent* result=getservbyport(inPortID,inProtocolName.c_str());
			return ServiceInfo(result);
		}
	public:
		bool IsValid()const{return mServent!=NULL;}

		StringRef GetServiceName() const { return  mServent->s_name; }
		void SetServiceName(StringRef inNewServiceName) { mServent->s_name = (char*)inNewServiceName.c_str(); }

		char** GetServiceAliases() const { return  mServent->s_aliases; }
		void SetServiceAliases(char** inNewServiceAliases) { mServent->s_aliases = inNewServiceAliases; }

		int GetPortID() const { return  mServent->s_port; }
		void SetPortID(int inNewPortID) { mServent->s_port = inNewPortID; }

		StringRef GetProtocolName() const { return mServent->s_proto; }
		void SetProtocolName(StringRef inNewProtocolName) { mServent->s_proto =(char*) inNewProtocolName.c_str(); }
	private:
		servent* mServent;
	};

}

MEDUSA_END;
