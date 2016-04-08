#pragma  once
#include "Core/Pattern/Action/IActionRunnable.h"
#include "Core/Pattern/Action/IAction.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Linq.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BaseActionRunner:public IActionRunnable<TTarget>
	{
	public:
		typedef IAction<TTarget> ActionType;
		virtual ~BaseActionRunner()
		{
			SAFE_DELETE_COLLECTION(mActions);
		}

		virtual bool UpdateActions(float dt)
		{
			RETURN_TRUE_IF_EMPTY(mActions);
			uint count=mActions.GetCount();
			FOR_EACH_SIZE(i,count)
			{
				ActionType* action=mActions[i];
				MEDUSA_ASSERT_NOT_NULL(action,"");
				action->Update(dt);
				if (action->IsDone())
				{
					mCompletedActionIndices.Add(i);
				}
			}

			Linq::DeleteIndexes(mActions,mCompletedActionIndices);
			mCompletedActionIndices.Clear();
			return true;
		}
	public:
		virtual IAction<TTarget>* RunAction(ActionType* action)
		{
			if(action->Initialize((TTarget*)this)&&action->Start())
			{
				if (!action->IsDone())	//instant action
				{
					mActions.Append(action);
					return action;
				}
			}

			ActionType* p=action;
			SAFE_DELETE(p);
			return NULL;
		}

		virtual ActionType* FindActionByTag(int tag)
		{
			FOR_EACH_COLLECTION(i,mActions)
			{
				ActionType* action=*i;
				if (action->GetTag()==tag)
				{
					return action;
				}
			}
			return NULL;
		}
		virtual void PauseAllActions()
		{
			FOR_EACH_COLLECTION(i,mActions)
			{
				ActionType* action=*i;
				action->Pause();
			}
		}
		virtual void ResumeAllActions()
		{
			FOR_EACH_COLLECTION(i,mActions)
			{
				ActionType* action=*i;
				action->Resume();
			}
		}
		virtual void StopAllActions()
		{
			FOR_EACH_COLLECTION(i,mActions)
			{
				ActionType* action=*i;
				action->Stop();
				delete action;
			}
			mActions.Clear();
		}

		virtual void PauseActionByTag(int tag)
		{
			ActionType* action=FindActionByTag(tag);
			if (action!=NULL)
			{
				action->Pause();
			}
		}
		virtual void ResumeActionByTag(int tag)
		{
			ActionType* action=FindActionByTag(tag);
			if (action!=NULL)
			{
				action->Resume();
			}
		}
		virtual void StopActionByTag(int tag)
		{
			ActionType* action=FindActionByTag(tag);
			if (action!=NULL)
			{
				action->Stop();
				mActions.Remove(action);
				SAFE_DELETE(action);
			}
		}

	protected:
		List<ActionType*> mActions;
	private:
		List<uint> mCompletedActionIndices;

	};
}

MEDUSA_END;