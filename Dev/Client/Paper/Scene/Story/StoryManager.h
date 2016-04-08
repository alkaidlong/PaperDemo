#pragma once
#include "Core/Pattern/Singleton.h"
#include "Scene/Story/StoryDelegate.h"
USING_MEDUSA;

#include "Core/Script/ScriptObject.h"
#include "Scene/Story/StoryGroup.h"

class StoryManager:public Pattern::Singleton<StoryManager>
{
	friend class Pattern::Singleton<StoryManager>;
	StoryManager(void);
	~StoryManager(void);
public:
	bool Initialize();
	bool UnInitialize();

	void AddGroup(uint groupId,ScriptObject* script,StringRef groupType);
	void AddGroup(uint groupId,ScriptObject* script);
	void AddForceGroup(ScriptObject* script);
	void AddForceGroup(uint groupId,ScriptObject* script);
	void RemoveGroup(uint groupId);
	void RemoveGroup(StoryGroup* storyGroup);
	void RemoveAllGroup();

	bool IsGroupWillFinish(uint groupId) const;
	void SetGroupWillFinish(uint groupId,bool val);

	void SetMessageBack(StringRef messageName);

	StoryDelegate* GetStoryDelegate() const { return mStoryDelegate; }
	void SetStoryDelegate(StoryDelegate* val) { mStoryDelegate = val; }

	bool Run();
	void GroupNextStep();

	bool IsStorying(){ return mCurGroup!=NULL;}

	void SwitchToOtherGuide(uint groupId);

	void TryToReomveGroup();
protected:
	void OnNextGroup( void* sender,IEventArg e );
private:
	List<StoryGroup*> mGroupList;
	
	StoryGroup* mCurGroup;

	StoryDelegate* mStoryDelegate;
	
};