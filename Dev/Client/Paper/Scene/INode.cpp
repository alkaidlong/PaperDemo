
#include "Scene/INode.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Pattern/Ptr/LazyStrongPtr.inl"
#include "Scene/Event/InputDispatcher.h"
#include "Scene/Event/InputManager.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"



INode::INode(StringRef name/*=StringRef::Empty*/):mName(name)
{
	mInputDispatcher=NULL;
	mParentNode = NULL;
	mInputEnabled=false;
}


INode::~INode( void )
{
	if (mInputDispatcher!=NULL)
	{
		InputManager::Instance().Unregister(mInputDispatcher);
		mInputDispatcher=NULL;
	}

	RemoveAllChilds();
}

void INode::AddChild( INode* node )
{
	MEDUSA_ASSERT_NULL(node->GetParentNode(),"");

	mNodes.Add(node);
	node->SetParentNode(this);
	if (!node->GetName().IsEmpty())
	{
		if (mNodeDict.ContainsKey(node->GetName()))
		{
			Log::LogErrorFormat("Duplicate add node:%s",node->GetName().c_str());
		}
		mNodeDict.Add(node->GetName(),node);

	}
	if (GetDrawCCNode()!=NULL&&node->GetDrawCCNode()!=NULL)
	{
		GetDrawCCNode()->addChild(node->GetDrawCCNode());
	}
}

void INode::RemoveChild( INode* node )
{
	if (mNodeDict.RemoveKey(node->GetName()))
	{
		mNodes.RemoveFirst(node);
		node->SetParentNode(NULL);
		if (GetDrawCCNode()!=NULL&&node->GetDrawCCNode()!=NULL)
		{
			GetDrawCCNode()->removeChild(node->GetDrawCCNode(),true);
		}
	}

}

void INode::DeleteChild( INode* node )
{
	if (mNodeDict.RemoveKey(node->GetName()))
	{
		mNodes.RemoveFirst(node);
		node->SetParentNode(NULL);
		if (GetDrawCCNode()!=NULL&&node->GetDrawCCNode()!=NULL)
		{
			GetDrawCCNode()->removeChild(node->GetDrawCCNode());
		}
		SAFE_DELETE(node);

	}
	
}


void INode::RemoveAllChilds()
{
	CCNode* curCCNode=GetDrawCCNode();
	if (curCCNode!=NULL)
	{
		FOR_EACH_COLLECTION(i,mNodes)
		{
			INode* node=*i;
			node->SetParentNode(NULL);
			if (node->GetDrawCCNode()!=NULL)
			{
				curCCNode->removeChild(node->GetDrawCCNode());
			}
		}
	}
	
	mNodes.Clear();
	mNodeDict.Clear();

}



void INode::SetParentNode( INode* val )
{
	mParentNode = val;
}

INode* INode::FindChild( StringRef name )
{
	INode** node=mNodeDict.TryGetValue(name);
	if (node!=NULL)
	{
		return *node;
	}
	return NULL;
}

const INode* INode::FindChild( StringRef name ) const
{
	INode** const node=mNodeDict.TryGetValue(name);
	if (node!=NULL)
	{
		return *node;
	}
	return NULL;
}

INode* INode::FindChildConfidently(StringRef name)
{
	INode** node=mNodeDict.TryGetValue(name);
	if (node==NULL)
	{
		Log::AssertFailedFormat("Cannot find child by %s",name.c_str());
		return NULL;
	}
	return *node;
}

const INode* INode::FindChildConfidently(StringRef name) const
{
	INode** const node=mNodeDict.TryGetValue(name);
	if (node==NULL)
	{
		Log::AssertFailedFormat("Cannot find child by %s",name.c_str());
		return NULL;
	}
	return *node;
}



bool INode::HasChild( INode* node ) const
{
	return mNodes.Contains(node);
}


INode* INode::FindChildRecursively( StringRef name )
{
	INode* node= FindChild(name);
	RETURN_SELF_IF_NOT_NULL(node);

	FOR_EACH_COLLECTION(i,mNodes)
	{
		node=*i;
		node=node->FindChildRecursively(name);
		RETURN_SELF_IF_NOT_NULL(node);
	}
	return NULL;
}

const INode* INode::FindChildRecursively( StringRef name ) const
{
	const INode* node= FindChild(name);
	RETURN_SELF_IF_NOT_NULL(node);

	FOR_EACH_COLLECTION(i,mNodes)
	{
		node=*i;
		node=node->FindChildRecursively(name);
		RETURN_SELF_IF_NOT_NULL(node);
	}
	return NULL;
}


INode* INode::FindChildWithPath( StringRef path )
{
	List<HeapString> paths;
	StringParser::Split<char>(path,"/",paths);

	INode* cur=this;
	while (!paths.IsEmpty())
	{
		cur=cur->FindChild(paths.First());
		if (cur==NULL)
		{
			Log::LogErrorFormat("can not find child %s",paths.First().c_str());
			return NULL;
		}

		paths.RemoveFirst();
	}

	return cur;
}



bool INode::HasChildRecursively( INode* node ) const
{
	bool hasChild=HasChild(node);
	RETURN_TRUE_IF_TRUE(hasChild);

	FOR_EACH_COLLECTION(i,mNodes)
	{
		hasChild=(*i)->HasChildRecursively(node);
		RETURN_TRUE_IF_TRUE(hasChild);
	}
	return false;
}

void INode::ResetInputPassing()
{
	mInputPassingEnabled=false;
	FOR_EACH_COLLECTION(i,mNodes)
	{
		INode* node=*i;
		if (!node->IsInputPassingEnabled())
		{
			node->ResetInputPassing();
		}
	}
}

void INode::EnableInputPassing()
{
	mInputPassingEnabled = true;
	if (mParentNode!=NULL)
	{
		mParentNode->EnableInputPassing();
	}
}

bool INode::UpdateRecursively( float dt )
{
	//Log::LogInfoFormat("Begin Update:%s",mName.c_str());
	RETURN_FALSE_IF_FALSE(BeforeUpdate(dt));

	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		RETURN_FALSE_IF_FALSE(child->UpdateRecursively(dt));
	}

	if (mInputDispatcher!=NULL)
	{
		mInputDispatcher->Update(dt);
	}
	RETURN_FALSE_IF_FALSE(Update(dt));

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		RETURN_FALSE_IF_FALSE(child->UpdateRecursively(dt));
	}

	RETURN_FALSE_IF_FALSE(AfterUpdate(dt));
	//Log::LogInfoFormat("After Update:%s",mName.c_str());

	return true;
}

bool INode::EnterRecursively()
{
	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		RETURN_FALSE_IF_FALSE(child->EnterRecursively());
	}

	RETURN_FALSE_IF_FALSE(Enter());

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		RETURN_FALSE_IF_FALSE(child->EnterRecursively());
	}

	return true;
}

bool INode::ExitRecursively()
{
	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		RETURN_FALSE_IF_FALSE(child->ExitRecursively());
	}

	RETURN_FALSE_IF_FALSE(Exit());

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		RETURN_FALSE_IF_FALSE(child->ExitRecursively());
	}

	return true;
}


bool INode::UpdateLogicRecursively()
{
	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		RETURN_FALSE_IF_FALSE(child->UpdateLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(UpdateLogic());

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		RETURN_FALSE_IF_FALSE(child->UpdateLogicRecursively());
	}

	return true;
}

bool INode::ResetLogicRecursively()
{
	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		RETURN_FALSE_IF_FALSE(child->ResetLogicRecursively());
	}

	RETURN_FALSE_IF_FALSE(ResetLogic());

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		RETURN_FALSE_IF_FALSE(child->ResetLogicRecursively());
	}

	return true;
}
void INode::EnableInput( bool val )
{
	if (mInputEnabled!=val)
	{
		InputManager::Instance().SetDirty();
	}
	mInputEnabled = val;

}

InputDispatcher* INode::GetInputDispatcher()
{
	if (mInputDispatcher==NULL)
	{
		mInputDispatcher=InputManager::Instance().Register(this);
	}
	return mInputDispatcher;
}

int INode::GetLogicZ() const
{
	const CCNode* ccNode=GetDrawCCNode();
	if (ccNode!=NULL)
	{
		return ccNode->getZOrder();
	}

	return 0;
}

bool INode::AddTapGestureHandler( StringRef name,TapEventHandler handler ,const FileId& audioEffect/*=FileId::Empty*/,GestureFlags flags/*=GestureFlags::None*/)
{
	INode* image1= FindChild(name);
	if (image1==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}

	FileId defaultClickEffect=image1->GetDefaultClickEffect();
	if (audioEffect.IsValid())
	{
		defaultClickEffect=audioEffect;
	}

	InputDispatcher* input=image1->GetInputDispatcher();
	bool isSuccess=input->AddTapGestureHandler(handler,defaultClickEffect,flags);
	return isSuccess;
}

bool INode::AddTapGestureHandler( TapEventHandler handler ,const FileId& audioEffect/*=FileId::Empty*/,GestureFlags flags/*=GestureFlags::None*/)
{
	FileId defaultClickEffect=GetDefaultClickEffect();
	if (audioEffect.IsValid())
	{
		defaultClickEffect=audioEffect;
	}

	InputDispatcher* input=GetInputDispatcher();
	bool isSuccess=input->AddTapGestureHandler(handler,defaultClickEffect,flags);
	Log::Assert(isSuccess,"INode::AddTapGestureHandler");
	return isSuccess;
}

bool INode::RemoveTapGestureHandler( StringRef name,TapEventHandler handler )
{
	INode* image1= FindChild(name);
	if (image1==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}
	InputDispatcher* input=image1->GetInputDispatcher();
	return input->RemoveTapGestureHandler(handler);
}

bool INode::RemoveTapGestureHandler( TapEventHandler handler )
{
	InputDispatcher* input=GetInputDispatcher();
	return input->RemoveTapGestureHandler(handler);
}

bool INode::AddSwipeGestureHandler( StringRef name,SwipeEventHandler handler,GestureDirection direction /*= GestureDirection::Horizontal*/,float minMoveDuration/*=10.0f*/, float minMovement/*=5.0f*/,float minVelocity/*=30.0f*/ ,GestureFlags flags/*=GestureFlags::None*/)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}

	InputDispatcher* input=node->GetInputDispatcher();
	bool isSuccess=input->AddSwipeGestureHandler(handler,direction,minMoveDuration,minMovement,minVelocity,flags);
	return isSuccess;
}

bool INode::AddSwipeGestureHandler( SwipeEventHandler handler,GestureDirection direction /*= GestureDirection::Horizontal*/,float minMoveDuration/*=10.0f*/, float minMovement/*=5.0f*/,float minVelocity/*=30.0f*/,GestureFlags flags/*=GestureFlags::None*/ )
{
	InputDispatcher* input=GetInputDispatcher();
	bool isSuccess=input->AddSwipeGestureHandler(handler,direction,minMoveDuration,minMovement,minVelocity,flags);
	Log::Assert(isSuccess,"INode::AddSwipeGestureHandler");
	return isSuccess;
}

bool INode::RemoveSwipeGestureHandler(StringRef name,SwipeEventHandler handler)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}
	InputDispatcher* input=node->GetInputDispatcher();
	return input->RemoveSwipeGestureHandler(handler);
}

bool INode::RemoveSwipeGestureHandler(SwipeEventHandler handler)
{
	InputDispatcher* input=GetInputDispatcher();
	return input->RemoveSwipeGestureHandler(handler);
}

bool INode::AddPanGestureHandler( StringRef name,PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler,float minDistance ,GestureFlags flags/*=GestureFlags::None*/)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}

	InputDispatcher* input=node->GetInputDispatcher();
	bool isSuccess=input->AddPanGestureHandler(handler,beginHandler,endHandler,minDistance,flags);
	return isSuccess;
}

bool INode::AddPanGestureHandler( PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler ,float minDistance,GestureFlags flags/*=GestureFlags::None*/)
{
	InputDispatcher* input=GetInputDispatcher();
	bool isSuccess=input->AddPanGestureHandler(handler,beginHandler,endHandler,minDistance,flags);
	Log::Assert(isSuccess,"INode::AddPanGestureHandler");
	return isSuccess;
}

bool INode::RemovePanGestureHandler( StringRef name,PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler )
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}
	InputDispatcher* input=node->GetInputDispatcher();
	return input->RemovePanGestureHandler(handler,beginHandler,endHandler);
}

bool INode::RemovePanGestureHandler( PanEventHandler handler,PanBeginEventHandler beginHandler,PanEndEventHandler endHandler )
{
	InputDispatcher* input=GetInputDispatcher();
	return input->RemovePanGestureHandler(handler,beginHandler,endHandler);
}

bool INode::AddPinchGestureHandler( StringRef name,PinchEventHandler handler ,GestureFlags flags/*=GestureFlags::None*/)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}

	InputDispatcher* input=node->GetInputDispatcher();
	bool isSuccess=input->AddPinchGestureHandler(handler,flags);
	return isSuccess;
}

bool INode::AddPinchGestureHandler( PinchEventHandler handler ,GestureFlags flags/*=GestureFlags::None*/)
{
	InputDispatcher* input=GetInputDispatcher();
	bool isSuccess=input->AddPinchGestureHandler(handler,flags);
	Log::Assert(isSuccess,"INode::AddPinchGestureHandler");
	return isSuccess;
}

bool INode::RemovePinchGestureHandler( StringRef name,PinchEventHandler handler )
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}
	InputDispatcher* input=node->GetInputDispatcher();
	return input->RemovePinchGestureHandler(handler);
}

bool INode::RemovePinchGestureHandler( PinchEventHandler handler )
{
	InputDispatcher* input=GetInputDispatcher();
	return input->RemovePinchGestureHandler(handler);
}

void INode::CancelOtherRecognizers(IGestureRecognizer* self)
{
	if (mInputDispatcher!=NULL)
	{
		mInputDispatcher->CancelOtherRecognizers(self);
	}
}

bool INode::AddDoubleTapGestureHandler(StringRef name,TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration/*=0.25f*/,GestureFlags flags/*=GestureFlags::None*/)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}

	InputDispatcher* input=node->GetInputDispatcher();
	bool isSuccess=input->AddDoubleTapGestureHandler(tapHandler,doubleTapHandler,maxDuration,flags);
	return isSuccess;
}

bool INode::AddDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler,float maxDuration/*=0.25f*/,GestureFlags flags/*=GestureFlags::None*/)
{
	InputDispatcher* input=GetInputDispatcher();
	bool isSuccess=input->AddDoubleTapGestureHandler(tapHandler,doubleTapHandler,maxDuration,flags);
	Log::Assert(isSuccess,"INode::AddDoubleTapGestureHandler");
	return isSuccess;
}

bool INode::RemoveDoubleTapGestureHandler(StringRef name,TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler)
{
	INode* node= FindChild(name);
	if (node==NULL)
	{
		Log::LogErrorFormat("Cannot find node:%s",name.c_str());
		return false;
	}
	InputDispatcher* input=node->GetInputDispatcher();
	return input->RemoveDoubleTapGestureHandler(tapHandler,doubleTapHandler);
}

bool INode::RemoveDoubleTapGestureHandler(TapEventHandler tapHandler,DoubleTapEventHandler doubleTapHandler)
{
	InputDispatcher* input=GetInputDispatcher();
	return input->RemoveDoubleTapGestureHandler(tapHandler,doubleTapHandler);
}

void INode::ResetRecognizers()
{
	if (mInputDispatcher!=NULL)
	{
		mInputDispatcher->Reset();
	}
}

void INode::ResetRecognizersRecursively()
{
	uint count=mNodes.GetCount();
	int i=count-1;
	for(;i>=0;--i)
	{
		INode* child=mNodes[i];
		BREAK_IF(child->GetLogicZ()<0);
		child->ResetRecognizersRecursively();
	}

	ResetRecognizers();

	for (;i>=0;--i)
	{
		INode* child=mNodes[i];
		child->ResetRecognizersRecursively();
	}

}



