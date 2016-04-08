#include "Scene/Story/StoryManager.h"
#include "Core/Script/ScriptManager.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/Log/Log.h"

StoryManager::StoryManager( void )
{
	Initialize();
}

StoryManager::~StoryManager( void )
{
	UnInitialize();
}

bool StoryManager::Initialize()
{
	mCurGroup = NULL;
	mStoryDelegate = NULL;
	return true ;
}

bool StoryManager::UnInitialize()
{
	RemoveAllGroup();

	return true;
}

bool StoryManager::Run()
{
   	RETURN_FALSE_IF(mCurGroup!=NULL);

	//TryToReomveGroup();

   	FOR_EACH_COLLECTION(i,mGroupList)
   	{
   		StoryGroup* group = *i;
   		if (mCurGroup==NULL && group->GetModel() == StoryGroupModel::Force&&!group->IsWillRemove()&&group->IsReach())
   		{
   			mCurGroup = group;
   			mCurGroup->Begin();
   			return true;
   		}
   	}
   
   	
   	FOR_EACH_COLLECTION(i,mGroupList)
   	{
   		StoryGroup* group = *i;
   		if (mCurGroup==NULL && !group->IsWillRemove()&&group->IsReach())
   		{
   			mCurGroup = group;
   			mCurGroup->Begin();
            
   			return true;
   		}
   	}
	return false;
}


void StoryManager::AddGroup( uint groupId,ScriptObject* script,StringRef groupType )
{
	StoryGroup* group = new StoryGroup(groupId,script);
	group->SetModel(StoryGroupModel::Normal);
	group->SetGroupType(groupType);
	mGroupList.Add(group);
}


void StoryManager::AddForceGroup( ScriptObject* script )
{
	StoryGroup* group = new StoryGroup(0,script);
	group->SetModel(StoryGroupModel::Force);
	mGroupList.Add(group);
}

void StoryManager::AddForceGroup( uint groupId,ScriptObject* script )
{
	StoryGroup* group = new StoryGroup(groupId,script);
	group->SetModel(StoryGroupModel::Force);
	mGroupList.Add(group);
}

void StoryManager::RemoveGroup( uint groupId )
{
	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group->GetGroupId() == groupId)
		{
			group->SetIsWillRemove(true);
			break;
		}
	}
}

void StoryManager::RemoveGroup( StoryGroup* storyGroup )
{
	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group == storyGroup)
		{
			group->SetIsWillRemove(true);
			break;
		}
	}
}

void StoryManager::RemoveAllGroup()
{
	SAFE_DELETE_COLLECTION(mGroupList);
	mCurGroup=NULL;
}


void StoryManager::GroupNextStep()
{
	if (mCurGroup!=NULL)
	{
		if (mStoryDelegate)
		{
			mStoryDelegate->NextStepBefore(*mCurGroup);
		}

		bool result = mCurGroup->NextStep();

		if (mStoryDelegate)
		{
			mStoryDelegate->NextStepAfter(*mCurGroup);
		}

		if (result==false)
		{
			if (mCurGroup->GetGroupId()!=0)
			{
				if (mStoryDelegate)
				{
					mStoryDelegate->StoryGroupEnd(*mCurGroup);
				}
			}

			if (mCurGroup->IsAutomaticRemoveGroup())
			{
				RemoveGroup(mCurGroup);
			}
			mCurGroup->End();
            
			mCurGroup = NULL;

			UIEventDispatcher::Instance().FireEventAsyncDefault(UIEventDispatcher::DefaultHandler(this,&StoryManager::OnNextGroup));
		}
	}
}

void StoryManager::SetMessageBack( StringRef messageName )
{
	if (mStoryDelegate)
	{
		mStoryDelegate->MessageBack(messageName);
	}
}

void StoryManager::OnNextGroup( void* sender,IEventArg e )
{
	Run();
}

void StoryManager::SwitchToOtherGuide( uint groupId )
{
	if (mCurGroup&&mCurGroup->GetGroupId()==groupId)
	{
		return;
	}

	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group->GetGroupId()==groupId)
		{
			mCurGroup = group;
			mCurGroup->Begin();
			break;
		}
	}
}

void StoryManager::TryToReomveGroup()
{
	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group->IsWillRemove())
		{
			mGroupList.Remove(group);
			SAFE_DELETE(group);
			break;
		}
	}
}

bool StoryManager::IsGroupWillFinish( uint groupId ) const
{
	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group->GetGroupId()==groupId)
		{
			return group->IsWillFinish();
		}
	}

	return false;
}

void StoryManager::SetGroupWillFinish( uint groupId,bool val )
{
	FOR_EACH_COLLECTION(i,mGroupList)
	{
		StoryGroup* group = *i;
		if (group->GetGroupId()==groupId)
		{
			group->SetIsWillFinish(val);
			break;
		}
	}
}
