#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Profile/ProfileNode.h"
#include "Core/Pattern/Singleton.h"


MEDUSA_BEGIN;

class ProfileManager:public Pattern::Singleton<ProfileManager>
{
	friend class Pattern::Singleton<ProfileManager>;
private:
	ProfileManager():mRoot("Root",NULL),mCurrentNode(&mRoot),mFrameCount(0)
	{

	}
	~ProfileManager(){}
public:
	void Reset();
	void Begin(const StringRef& name,size_t count=1,size_t logCount=0);
	void End();
	void PrintResult()const;

	void StopAll();
public:
	size_t GetFrameCount() const { return mFrameCount; }
	void AddFrameCount() { ++mFrameCount ; }
private:
	ProfileNode mRoot;
	ProfileNode* mCurrentNode;
	size_t mFrameCount;

};


MEDUSA_END;