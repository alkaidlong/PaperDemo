#pragma once
#include "Core/Pattern/Action/Composite/BaseMultipleCompositeAction.h"

MEDUSA_BEGIN;
namespace Pattern
{
	template<typename TTarget>
	class SequenceAction:public BaseMultipleCompositeAction<TTarget>
	{
	public:
		SequenceAction():mCurrentIndex(0){}
		SequenceAction(const List<IAction<TTarget>*>& actions):mInnerActions(actions),mCurrentIndex(0){}
		SequenceAction(IAction<TTarget>* a1,IAction<TTarget>* a2):mCurrentIndex(0)
		{
			mInnerActions.Add(a1);
			mInnerActions.Add(a2);
		}

		virtual ~SequenceAction(void){}
	public:
		virtual bool Update(float dt)
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Update(dt));
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}

			IAction<TTarget>* currentAction=mInnerActions[mCurrentIndex];
			currentAction->Update(dt);
			if (!currentAction->IsDone())
			{
				return true;
			}

			++mCurrentIndex;

			while (mCurrentIndex<mInnerActions.GetCount())
			{
				currentAction=mInnerActions[mCurrentIndex];
				currentAction->Start();
				if (currentAction->IsDone())
				{
					++mCurrentIndex;
				}
				else
				{
					currentAction->Update(dt);
					if (currentAction->IsDone())
					{
						++mCurrentIndex;
					}
					else
					{
						return true;
					}
				}
			}

			ForceSetState(Pattern::RunningState::Done);
			return true;
		}

		virtual bool Start()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Start());
			mCurrentIndex=0;
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(RunningState::Done);
				return true;
			}

			while (mCurrentIndex<mInnerActions.GetCount())
			{
				IAction<TTarget>* currentAction=mInnerActions[mCurrentIndex];
				currentAction->Start();
				if (currentAction->IsDone())
				{
					++mCurrentIndex;
				}
				else
				{
					return true;
				}
			}

			ForceSetState(Pattern::RunningState::Done);
			return true;
		}


		virtual bool Pause()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Pause());
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}
			IAction<TTarget>* currentAction=mInnerActions[mCurrentIndex];
			return currentAction->Pause();
		}
		virtual bool Resume()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Resume());
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}
			IAction<TTarget>* currentAction=mInnerActions[mCurrentIndex];
			return currentAction->Resume();
		}
		virtual bool Stop()
		{
			RETURN_FALSE_IF_FALSE(BaseInfiniteAction<TTarget>::Stop());
			if (mInnerActions.IsEmpty())
			{
				ForceSetState(Pattern::RunningState::Done);
				return true;
			}

			IAction<TTarget>* currentAction=mInnerActions[mCurrentIndex];
			return currentAction->Stop();
		}

		virtual bool Reset()
		{
			mCurrentIndex=0;
			return BaseMultipleCompositeAction<TTarget>::Reset();
		}
	public:
		void ReverseSelf()
		{
			Reset();
			mInnerActions.Reverse();
		}

		virtual SequenceAction* Clone()const override
		{
			return new SequenceAction(mInnerActions);
		}
		virtual SequenceAction* Reverse()const override
		{
			SequenceAction* seq=new SequenceAction(mInnerActions);
			seq->ReverseSelf();
			return seq;
		}

		static SequenceAction* CreateEmpty()
		{
			return new SequenceAction();
		}

		static SequenceAction* CreateWithNullEnd(IAction<TTarget>* a1,...) MEDUSA_REQUIRES_NULL_TERMINATION
		{
			va_list params;
			va_start(params, a1);
			SequenceAction* seq=new SequenceAction();
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

		static SequenceAction* Create(const List<IAction<TTarget>*>& actions)
		{
			return new SequenceAction(actions);
		}

		static SequenceAction* Create(IAction<TTarget>* a1)
		{
			SequenceAction* seq=new SequenceAction();
			seq->Add(a1);
			return seq;
		}

		static SequenceAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2)
		{
			SequenceAction* seq=new SequenceAction();
			seq->Add(a1);
			seq->Add(a2);

			return seq;
		}

		static SequenceAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2,IAction<TTarget>* a3)
		{
			SequenceAction* seq=new SequenceAction();
			seq->Add(a1);
			seq->Add(a2);
			seq->Add(a3);

			return seq;
		}

		static SequenceAction* Create(IAction<TTarget>* a1,IAction<TTarget>* a2,IAction<TTarget>* a3,IAction<TTarget>* a4)
		{
			SequenceAction* seq=new SequenceAction();
			seq->Add(a1);
			seq->Add(a2);
			seq->Add(a3);
			seq->Add(a4);

			return seq;
		}
		
	protected:
		uint mCurrentIndex;
	};
}
MEDUSA_END;
