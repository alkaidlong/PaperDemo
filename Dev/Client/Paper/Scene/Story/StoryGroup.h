#pragma once
#include "Core/Pattern/Singleton.h"
USING_MEDUSA;

#include "Core/Script/ScriptObject.h"
#include "Scene/Story/StoryStep.h"
#include "Core/Event/EventArg/IEventArg.h"

enum class StoryGroupModel
{
	Normal = 1,
	Force = 2,
};

class StoryGroup 
{
	
public:
	StoryGroup(uint groupId,ScriptObject* script);
	
	~StoryGroup();

	bool Initialize();
	bool UnInitialize();

	uint GetGroupId() const { return mGroupId; }
	void SetGroupId(uint val) { mGroupId = val; }

	ScriptObject* GetGroupScript() const { return mGroupScript; }
	void SetGroupScript(ScriptObject* val) { mGroupScript = val; }

	StoryGroupModel GetModel() const { return mModel; }
	void SetModel(StoryGroupModel val) { mModel = val; }

	StringRef GetGroupType() const { return mGroupType; }
	void SetGroupType(StringRef val) { mGroupType = val; }

	bool IsWillRemove() const { return mIsWillRemove; }
	void SetIsWillRemove(bool val) { mIsWillRemove = val; }

	bool IsWillFinish() const { return mIsWillFinish; }
	void SetIsWillFinish(bool val) { mIsWillFinish = val; }

	bool IsReach();

	bool IsAutomaticRemoveGroup();

	void Begin();
	bool NextStep();
	void End();
private:
	uint mGroupId;
	ScriptObject* mGroupScript;
	StoryGroupModel mModel;
	HeapString mGroupType;
	
	uint mStepCount;
	List<StoryStep,NoCompare<StoryStep>> mStepList;
	uint mCurStepIndex;

	bool mIsWillRemove;
	bool mIsWillFinish;
	
};