
#include "Scene/Event/InputManager.h"
#include "Core/Log/Log.h"
#include "Scene/Event/InputDispatcher.h"
#include "Scene/IScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/Event/EventArg/KeyDownEventArg.h"
#include "Scene/Event/EventArg/KeyUpEventArg.h"
#include "Scene/Event/EventArg/ScrollEventArg.h"
#include "Scene/Event/EventArg/CharInputEventArg.h"
#include "Core/Event/UIEventDispatcher.h"



InputManager::InputManager()
{
	mIsDirty=false;
}

InputManager::~InputManager()
{
	SAFE_DELETE_DICTIONARY_VALUE(mDispatchers);
}

InputDispatcher* InputManager::Register( INode* node )
{
	auto result= mDispatchers.TryGetValueWithFailed(node,NULL);
	if (result==NULL)
	{
		result=new InputDispatcher(node);
		mDispatchers.Add(node,result);
		mIsDirty=true;
	}

	return result;
}

void InputManager::Unregister( InputDispatcher* dispatcher )
{
	if(!mDispatchers.ContainsKey(dispatcher->GetNode()))
	{
		Log::LogError("Cannot find dispatcher");
		return;
	}

	mDispatchers.RemoveKey(dispatcher->GetNode());
	SAFE_DELETE(dispatcher);
	mIsDirty=true;
}


void InputManager::UpdateInputPassingRecursively()
{
	RETURN_IF_FALSE(mIsDirty);
	IScene* scene= SceneManager::Instance().GetRunningScene();
	scene->ResetInputPassing();

	FOR_EACH_COLLECTION(i,mDispatchers)
	{
		INode* node=(*i).Key;
		node->EnableInputPassing();
	}

	mIsDirty=false;


}


bool InputManager::Update( float dt )
{
	UpdateInputPassingRecursively();
	return true;
}

void InputManager::TouchesBegan( TouchEventArg& e )
{
	IScene* scene= SceneManager::Instance().GetRunningScene();
	TouchesBeganHelper(scene,e);
	UIEventDispatcher::Instance().Dispatch();

}

void InputManager::TouchesMoved( TouchEventArg& e )
{
	IScene* scene= SceneManager::Instance().GetRunningScene();
	TouchesMovedHelper(scene,e);
	UIEventDispatcher::Instance().Dispatch();

}

void InputManager::TouchesEnded( TouchEventArg& e )
{
	IScene* scene= SceneManager::Instance().GetRunningScene();
	TouchesEndedHelper(scene,e);
	UIEventDispatcher::Instance().Dispatch();

}

void InputManager::TouchesCancelled( TouchEventArg& e )
{
	IScene* scene= SceneManager::Instance().GetRunningScene();
	TouchesCancelledHelper(scene,e);
	UIEventDispatcher::Instance().Dispatch();

}

void InputManager::KeyDown( KeyDownEventArg& keyDownEventArg )
{

}

void InputManager::KeyUp( KeyUpEventArg& keyUpEventArg )
{

}

void InputManager::CharInput( CharInputEventArg& charInputEventArg )
{

}

void InputManager::Scroll( ScrollEventArg& scrollEventArg )
{

}

void InputManager::TouchesBeganHelper( INode* node,TouchEventArg& e )
{

	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();

	//Log::LogInfoFormat("Touch Began [%d]:%s %x",count,node->GetName().c_str(),node);

	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];

		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			//Log::LogInfoFormat("%d Touch Began %d:%s %x",i,child->GetLogicZ(),child->GetName().c_str(),child);

			TouchesBeganHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
			//Log::LogInfoFormat("%d Touch Ignore %d:%s %x",i,child->GetLogicZ(),child->GetName().c_str(),child);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			e.UpdateValidTouches(node);
			dispatcher->TouchesBegan(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}
	
	}

	
	
	for (;i>=0;--i)
	{
		INode* child=nodeList[i];

		if (child->IsInputPassingEnabled())
		{
			//Log::LogInfoFormat("%d Touch Began Child<=0:%s",i,child->GetName().c_str());
			TouchesBeganHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
			//Log::LogInfoFormat("%d Touch Ignore Child<=0:%s",i,child->GetName().c_str());
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

}

void InputManager::TouchesMovedHelper( INode* node,TouchEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			TouchesMovedHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			e.UpdateValidTouches(node);
			dispatcher->TouchesMoved(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesMovedHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}

void InputManager::TouchesEndedHelper( INode* node,TouchEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();

	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			TouchesEndedHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			e.UpdateValidTouches(node);
			dispatcher->TouchesEnded(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesEndedHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}


void InputManager::TryFireEventHelper( INode* node,TouchEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			TryFireEventHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			e.UpdateValidTouches(node);
			dispatcher->TryFireEvent(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TryFireEventHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}

void InputManager::TouchesCancelledHelper( INode* node,TouchEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			TouchesCancelledHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			e.UpdateValidTouches(node);
			dispatcher->TouchesCancelled(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesCancelledHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}

void InputManager::KeyDownHelper( INode* node,KeyDownEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			KeyDownHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			dispatcher->KeyDown(e);
			RETURN_IF_TRUE(e.Handled);
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyDownHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}
	}
}

void InputManager::KeyUpHelper( INode* node,KeyUpEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			KeyUpHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			dispatcher->KeyUp(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyUpHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}

void InputManager::CharInputHelper( INode* node,CharInputEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			CharInputHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			dispatcher->CharInput(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}

	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			CharInputHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}

void InputManager::ScrollHelper( INode* node,ScrollEventArg& e )
{
	auto nodeList= node->GetChildren();
	uint count=nodeList.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=nodeList[i];
		BREAK_IF(child->GetLogicZ()<0);

		if (child->IsInputPassingEnabled())
		{
			ScrollHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	{
		InputDispatcher* dispatcher=node->GetInputDispatcher();
		if (dispatcher!=NULL)
		{
			dispatcher->Scroll(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled=true;
			return;
		}
	}

	for (;i>=0;--i)
	{
		INode* child=nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			ScrollHelper(child,e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled=true;
			return;
		}
	}
}




