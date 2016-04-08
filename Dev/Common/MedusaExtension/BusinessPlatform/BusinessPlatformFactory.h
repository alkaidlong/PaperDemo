#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "BusinessPlatformTypes.h"
#include "Core/Collection/List.h"
#include "IBusinessPlatform.h"

MEDUSA_BEGIN;

class BusinessPlatformFactory
{

public:
	static bool Uninitialize();

	//1. add analyzers
	static void AddPlatform(IBusinessPlatform* platform);
	
	static void AddNd(const StringRef& appId,const StringRef& appKey);
	static void AddDev();


	//2.set  options
	static void EnableLog(bool val);
	static void EnableCrashReport(bool val);
	static void EnableDebug(bool val);


	//3.init
	static bool Initialize();
	static IBusinessPlatform* GetCurrentPlatform() { return mCurrentPlatform; }
private:
	static List<IBusinessPlatform*> mPlatforms;
	static IBusinessPlatform* mCurrentPlatform;
};


MEDUSA_END;