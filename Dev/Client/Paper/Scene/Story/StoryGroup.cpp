#include "Scene/Story/StoryGroup.h"

#include "Game/PaperScript.h"
#include "Core/Script/ScriptManager.h"
#include "Config/ServerGameConfig.h"
#include "Core/String/StackString.h"



StoryGroup::StoryGroup( uint groupId,ScriptObject* script ):
	mGroupId(groupId),
	mGroupScript(script)
{
	Initialize();
}

StoryGroup::~StoryGroup()
{
	UnInitialize();
}

bool StoryGroup::Initialize()
{
	mIsWillRemove = false;
	mIsWillFinish = false;
	mModel = StoryGroupModel::Normal;
	mCurStepIndex = 0;
	mStepCount = mGroupScript->GetMemberValueOrDefault<int>("StepCount",0);

	FOR_EACH_SIZE(i,mStepCount)
	{
		StackString<64> str;
		str.Format("Step%d",i+1);

		mStepList.Add(StoryStep(str));
	}

	return true;
}

bool StoryGroup::UnInitialize()
{
	SAFE_DELETE(mGroupScript);
	return true;
}

bool StoryGroup::IsReach()
{
	if (mStepCount==0)
	{
		return false;
	}

	switch (mModel)
	{
	case StoryGroupModel::Normal:
		{
			return mGroupScript->InvokeReturnBool("IsReach");
		}
		break;
	case StoryGroupModel::Force:
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

void StoryGroup::Begin()
{
	mGroupScript->Invoke("Begin");
	mCurStepIndex = 0;
	NextStep();
}

bool StoryGroup::NextStep()
{
	if (mCurStepIndex>=mStepCount)
	{
		return false;
	}

	if (mCurStepIndex<mStepCount)
	{
		mGroupScript->Invoke(mStepList[mCurStepIndex].GetFunName());
	}

	mCurStepIndex++;
	return true;
}

void StoryGroup::End()
{
	mGroupScript->Invoke("End");
}

bool StoryGroup::IsAutomaticRemoveGroup()
{
	return mGroupScript->InvokeReturnBool("IsAutomaticRemoveGroup");
}
