#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatformFactory.h"

#ifdef MEDUSA_BUSINESS_PLATFORM_ND
#include "NdBusinessPlatform.h"
#endif


#ifdef MEDUSA_BUSINESS_PLATFORM_DEV
#include "DevBusinessPlatform.h"
#endif

MEDUSA_BEGIN;

bool BusinessPlatformFactory::Initialize()
{
	FOR_EACH_COLLECTION(i,mPlatforms)
	{
		IBusinessPlatform* platform=*i;
		RETURN_FALSE_IF_FALSE(platform->Initialize());
	}

	return true;
}

bool BusinessPlatformFactory::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mPlatforms);
	return true;
}

void BusinessPlatformFactory::AddPlatform(IBusinessPlatform* platform )
{
	mPlatforms.Append(platform);
}


void BusinessPlatformFactory::AddNd(const StringRef& appId,const StringRef& appKey)
{
#ifdef MEDUSA_BUSINESS_PLATFORM_ND
	IBusinessPlatform* platform=new NdBusinessPlatform(appId,appKey);
	AddPlatform(platform);
#endif

	mCurrentPlatform=platform;

}


void BusinessPlatformFactory::AddDev()
{
#ifdef MEDUSA_BUSINESS_PLATFORM_ND
	IBusinessPlatform* platform=new DevBusinessPlatform();
	AddPlatform(platform);
#endif

	mCurrentPlatform=platform;
}


void BusinessPlatformFactory::EnableLog(bool val)
{
	FOR_EACH_COLLECTION(i,mPlatforms)
	{
		IBusinessPlatform* platform=*i;
		platform->EnableLog(val);
	}
}


void BusinessPlatformFactory::EnableCrashReport(bool val)
{
	FOR_EACH_COLLECTION(i,mPlatforms)
	{
		IBusinessPlatform* platform=*i;
		platform->EnableCrashReport(val);
	}
}

void BusinessPlatformFactory::EnableDebug(bool val)
{
	FOR_EACH_COLLECTION(i,mPlatforms)
	{
		IBusinessPlatform* platform=*i;
		platform->EnableDebug(val);
	}
}



List<IBusinessPlatform*> BusinessPlatformFactory::mPlatforms;
IBusinessPlatform* BusinessPlatformFactory::mCurrentPlatform=NULL;
MEDUSA_END;
