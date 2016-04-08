#include "MedusaCorePreCompiled.h"
#include "PackageHeader.h"
#include "Core/Log/Log.h"
#include "Core/IO/Stream/IStream.h"
MEDUSA_BEGIN;


bool PackageCoderInfo::ParseFrom( IStream& stream )
{
	Type=(PackageCoderType)stream.Read<uint>();
	uint keySize=stream.Read<uint>();
	if (keySize>0)
	{
		Key=stream.ReadData(keySize);
	}
	return true;
}

PackageHeader::PackageHeader():Version(0),FileListOffset(0)
{

}

PackageHeader::~PackageHeader()
{
	SAFE_DELETE_COLLECTION(Coders);
}

bool PackageHeader::ParseFrom( IStream& stream )
{
	uint signature=stream.Read<uint>();
	if (signature!=Signature)
	{
		Log::AssertFailedFormat("Invalid MPACK signature:%d",signature);
		return false;
	}

	Version=stream.Read<uint>();
	if (Version!=CurrentVersion)
	{
		Log::AssertFailedFormat("Invalid MPACK version:%d",Version);
		return false;
	}

	Flag.ForceSet(stream.Read<uint>());
	FileListOffset=stream.Read<uint>();

	//coders
	uint coderCount=stream.Read<uint>();
	FOR_EACH_SIZE(i,coderCount)
	{
		PackageCoderInfo* coderInfo=new PackageCoderInfo();
		if(!coderInfo->ParseFrom(stream))
		{
			SAFE_DELETE(coderInfo);
			return false;
		}
		Coders.Add(coderInfo);
	}

	//user data
	uint userDataSize=stream.Read<uint>();
	if (userDataSize>0)
	{
		UserData=stream.ReadData(userDataSize);
	}
	return true;
}


MEDUSA_END;