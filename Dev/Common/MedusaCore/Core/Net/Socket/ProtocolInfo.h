#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

namespace Socket
{
	class ProtocolInfo
	{
	public:
		ProtocolInfo(protoent* inProtoent=NULL):mProtoent(inProtoent){}
		bool IsValid()const{return mProtoent!=NULL;}

		static ProtocolInfo GetProtocol(StringRef inProtocolName)
		{
			protoent* result=getprotobyname(inProtocolName.c_str());
			return ProtocolInfo(result);

		}
		static ProtocolInfo GetProtocol(SocketProtocolType::SocketProtocolType_t protocol)
		{
			protoent* result=getprotobynumber(protocol);
			return ProtocolInfo(result);
		}
	public:
		protoent* GetProtoent()  { return mProtoent; }

		StringRef GetProtocolName() const { return mProtoent->p_name; }
		void SetProtocolName(StringRef inNewProtocolName) { mProtoent->p_name = (char*)inNewProtocolName.c_str(); }

		char** GetAliases() const { return mProtoent->p_aliases; }
		void SetAliases(char** inNewAliases) { mProtoent->p_aliases = inNewAliases; }

		int GetProtocolID() const { return mProtoent->p_proto; }
		void SetProtocolID(int inNewProtocolID) { mProtoent->p_proto = inNewProtocolID; }
	private:
		protoent* mProtoent;	
	};

}

MEDUSA_END;
