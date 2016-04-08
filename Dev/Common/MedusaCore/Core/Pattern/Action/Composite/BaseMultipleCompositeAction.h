#pragma once
#include "Core/Pattern/Action/BaseInfiniteAction.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class BaseMultipleCompositeAction:public BaseInfiniteAction<TTarget>
	{
	public:
		BaseMultipleCompositeAction(){}
		virtual ~BaseMultipleCompositeAction(void){SAFE_DELETE_COLLECTION(mInnerActions);}
	public:
		virtual bool Reset()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Reset());
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}

			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Reset();
			}

			return true;
		}

		virtual bool Initialize(TTarget* target)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Initialize(target));
			bool isSuccess=true;
			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				if(!currentAction->Initialize(target))
				{
					isSuccess=false;
					break;
				}
			}

			return isSuccess;
		}
	public:
		const List<IAction<TTarget>*>& GetInnerActions() const { return mInnerActions; }
		List<IAction<TTarget>*>& GetInnerActions() { return mInnerActions; }

		void Add(IAction<TTarget>* action)
		{
			Log::AssertFormat(mState==Pattern::RunningState::None,"Cannot add action when running");
			mInnerActions.Add(action);
		}

		void Remove(IAction<TTarget>* action)
		{
			Log::AssertFormat(mState==Pattern::RunningState::None,"Cannot Remove action when running");
			mInnerActions.Remove(action);
		}

		bool Contains(IAction<TTarget>* action)
		{
			return mInnerActions.Contains(action);
		}
	protected:
		List<IAction<TTarget>*> mInnerActions;
	};
}
MEDUSA_END;
