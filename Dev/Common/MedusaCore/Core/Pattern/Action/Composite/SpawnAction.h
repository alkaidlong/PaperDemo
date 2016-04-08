#pragma once
#include "Core/Pattern/Action/Composite/BaseMultipleCompositeAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class SpawnAction:public BaseMultipleCompositeAction<TTarget>
	{
	public:
		SpawnAction(){}
		virtual ~SpawnAction(void){}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Update(dt));
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}

			bool isAllDone=true;
			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Update(dt);
				if (!currentAction->IsDone())
				{
					isAllDone=false;
				}
			}

			if (isAllDone)
			{
				ForceSetState(Pattern::RunningState::Done);
			}

			return true;
		}

		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Start());
			bool isAllDone=true;
			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Start();
				if (!currentAction->IsDone())
				{
					isAllDone=false;
				}
			}

			if (isAllDone)
			{
				ForceSetState(Pattern::RunningState::Done);
			}

			return true;
		}

		virtual bool Pause()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Pause());

			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Pause();
			}
			return true;
		}
		virtual bool Resume()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Resume());
			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Resume();
			}
			return true;
		}
		virtual bool Stop()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Stop());
			FOR_EACH_COLLECTION(i,mInnerActions)
			{
				IAction<TTarget>* currentAction=*i;
				currentAction->Stop();
			}
			return true;
		}
	public:

		virtual SpawnAction* Clone()const override
		{
			return new SpawnAction(mInnerActions);
		}
		virtual SpawnAction* Reverse()const override
		{
			return new SpawnAction(mInnerActions);
		}

		static SpawnAction* CreateEmpty()
		{
			return new SpawnAction();
		}

		static SpawnAction* CreateWithNullEnd(IAction<TTarget>* a1,...) MEDUSA_REQUIRES_NULL_TERMINATION
		{
			va_list params;
			va_start(params, a1);
			SpawnAction* seq=new SpawnAction();
			seq->Add(a1);

			IAction<TTarget>* now=NULL;
			while(true)
			{
				now = va_arg(params, IAction<TTarget>*);
				BREAK_IF_NULL(now);
				seq->Add(now);
			}
			va_end(params);

			return seq;
		}

		static SpawnAction* Create(const List<IAction<TTarget>*>& actions)
		{
			return new SpawnAction(actions);
		}

		static SpawnAction* Create(IAction<TTarget>* a1)
		{
			SpawnAction* seq=new SpawnAction();
			seq->Add(a1);
			return seq;
		}

		static SpawnAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2)
		{
			SpawnAction* seq=new SpawnAction();
			seq->Add(a1);
			seq->Add(a2);

			return seq;
		}

		static SpawnAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2,IAction<TTarget>* a3)
		{
			SpawnAction* seq=new SpawnAction();
			seq->Add(a1);
			seq->Add(a2);
			seq->Add(a3);

			return seq;
		}

		static SpawnAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2,IAction<TTarget>* a3,IAction<TTarget>* a4)
		{
			SpawnAction* seq=new SpawnAction();
			seq->Add(a1);
			seq->Add(a2);
			seq->Add(a3);
			seq->Add(a4);

			return seq;
		}

	protected:
		List<IAction<TTarget>*> mInnerActions;
	};
}
MEDUSA_END;
