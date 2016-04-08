
#include "IScene.h"
#include "Scene/Event/Touch.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Scene/Element/LayerNode.h"
#include "Core/Log/Log.h"
#include "Scene/Event/EventArg/TouchEventArg.h"
#include "Scene/Event/InputManager.h"
#include "Scene/Editor/LayerEditor.h"
#include "Engine/Animation/AnimationManager.h"
#include "Scene/SystemUI/AlertLayer.h"
#include "Scene/SystemUI/ToastLayer.h"
#include "Scene/SystemUI/ActivityLayer.h"


IScene::IScene():INode(StringRef::Empty)
{
}


IScene::~IScene(void)
{
	ClearAll();
}


bool IScene::Initialize()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
	return true;
}

bool IScene::Uninitialize()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	
	return true;
}

void IScene::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	TouchEventArg touchEventArg;

	for (CCSetIterator i=pTouches->begin(); i!=pTouches->end(); ++i)
	{
		CCTouch uiTouch;
		CCTouch* touch = (CCTouch*)(*i);
		CCPoint point=touch->getLocation();
		touchEventArg.AddTouch(Touch(touch->getID(),Point2F(point.x,point.y)));
	}

	InputManager::Instance().TouchesBegan(touchEventArg);

}

void IScene::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
	TouchEventArg touchEventArg;
	for (CCSetIterator i=pTouches->begin(); i!=pTouches->end(); ++i)
	{
		CCTouch uiTouch;
		CCTouch* touch = (CCTouch*)(*i);
		CCPoint point=touch->getLocation();
		touchEventArg.AddTouch(Touch(touch->getID(),Point2F(point.x,point.y)));
	}
	InputManager::Instance().TouchesMoved(touchEventArg);
}

void IScene::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	TouchEventArg touchEventArg;
	for (CCSetIterator i=pTouches->begin(); i!=pTouches->end(); ++i)
	{
		CCTouch uiTouch;
		CCTouch* touch = (CCTouch*)(*i);
		CCPoint point=touch->getLocation();
		touchEventArg.AddTouch(Touch(touch->getID(),Point2F(point.x,point.y)));
	}

	InputManager::Instance().TouchesEnded(touchEventArg);
}

void IScene::ccTouchesCancelled( CCSet *pTouches, CCEvent *pEvent )
{
	TouchEventArg touchEventArg;
	for (CCSetIterator i=pTouches->begin(); i!=pTouches->end(); ++i)
	{
		CCTouch uiTouch;
		CCTouch* touch = (CCTouch*)(*i);
		CCPoint point=touch->getLocation();
		touchEventArg.AddTouch(Touch(touch->getID(),Point2F(point.x,point.y)));
	}

	InputManager::Instance().TouchesMoved(touchEventArg);
}

void IScene::didAccelerate( CCAcceleration* pAccelerationValue )
{

}

void IScene::keyBackClicked()
{

}

void IScene::keyMenuClicked()
{

}

void IScene::AddLayer( LayerNode* layer )
{
	AddChild(layer);
}

void IScene::RemoveLayer( LayerNode* layer )
{
	RemoveChild(layer);
}


bool IScene::UpdateLogicRecursively()
{
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		if (layer->isVisible())
		{
			layer->UpdateLogicRecursively();
		}
		
	}

	return true;
}

bool IScene::ResetLogicRecursively()
{
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		layer->ResetLogicRecursively();
	}

	FOR_EACH_COLLECTION(i,mCachedLayers)
	{
		LayerNode* layer=(*i).Value;
		layer->ResetLogicRecursively();
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
void IScene::CreateLayers( const List<StringRef>& names,const IEventArg& e/*=IEventArg::Empty*/,LayerCreateFlags createFlags/*=LayerCreateFlags::None*/)
{
	FOR_EACH_COLLECTION(i,names)
	{
		CreateLayer(*i,e,createFlags);
	}
}


LayerNode* IScene::CreateLayer( const StringRef& name,const IEventArg& e/*=IEventArg::Empty*/,LayerCreateFlags createFlags/*=LayerCreateFlags::None*/)
{
	LayerNode* layer=NULL;
	if (createFlags.HasFlag(LayerCreateFlags::AlwaysCreate))
	{
		layer= LayerEditor::Instance().CreateLayer(name,e,false);
		if (layer!=NULL)
		{
			layer->Initialize();
		}
	}
	else
	{
		layer= mCachedLayers.TryGetValueWithFailed(name,NULL);
		if (layer==NULL)
		{
			layer= LayerEditor::Instance().CreateLayer(name,e,false);
			if (layer!=NULL)
			{
				layer->Initialize();
				layer->retain();
				mCachedLayers.Add(name,layer);
			}
		}

	}
	return layer;

}


bool IScene::DeleteLayer( StringRef name,LayerDeleteFlags deleteFlags/*=LayerDeleteFlags::None*/)
{
	if (deleteFlags.HasFlag(LayerDeleteFlags::Async))
	{
		bool result=mCachedLayers.ContainsKey(name);
		UIEventDispatcher::Instance().FireEventAsync(Pattern::Delegate<void (IScene*,StringRef)>(this,&IScene::OnDeleteLayer),this,name);
		return result;
	}
	else
	{
		LayerNode* layer=mCachedLayers.RemoveKeyWithValueReturned(name,NULL);
		if (layer==NULL)
		{
			Log::LogErrorFormat("Cannot delete layer with name:%s",name.c_str());
			return false;
		}
		else
		{
			layer->Uninitialize();
			layer->release();
			return true;
		}
	}
	
}


void IScene::DeleteLayers( const List<StringRef>& names,LayerDeleteFlags deleteFlags/*=LayerDeleteFlags::None*/)
{
	FOR_EACH_COLLECTION(i,names)
	{
		DeleteLayer(*i,deleteFlags);
	}
}


void IScene::OnDeleteLayer( IScene* sender,StringRef name)
{
	DeleteLayer(name);
}


LayerNode* IScene::FindLayerInCache( const StringRef& name )
{
	return mCachedLayers.TryGetValueWithFailed(name,NULL);
}

bool IScene::IsLayerCached( const StringRef& name ) const
{
	return mCachedLayers.ContainsKey(name);
}


void IScene::ReleaseCacheLayers()
{
	//release all cached layer
	FOR_EACH_COLLECTION(i,mCachedLayers)
	{
		LayerNode* layer=(*i).Value;
		layer->Uninitialize();
		layer->release();
	}

	mCachedLayers.Clear();
}


//////////////////////////////////////////////////////////////////////////

LayerNode* IScene::GetCurrentLayer() const
{
	RETURN_NULL_IF_EMPTY(mLayerStack);
	return (LayerNode*)mLayerStack.Top();
}



void IScene::PushLayerHelper( LayerNode* layer ,LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	Log::Assert(layer!=NULL,"thisLayer should not be null.");

#ifdef MEDUSA_DEBUG
	if (HasChild(layer))
	{
		Log::AssertFailed("The layer pushed is already in layer stack.");
	}
#endif

	if (pushFlags.HasFlag(LayerPushFlags::SaveStatusBeforePush))
	{
		SaveStatus();
	}


	LayerNode* originalLayer=GetCurrentLayer();
	if (originalLayer!=NULL)
	{
		if (pushFlags.HasFlag(LayerPushFlags::HideAllPrevLayers))
		{
			FOR_EACH_COLLECTION(i,mLayerStack)
			{
				LayerNode* prevLayer=*i;
				if (prevLayer->isVisible())
				{
					prevLayer->setVisible(false);
					prevLayer->ExitRecursively();
					prevLayer->EnableInput(false);
				}
			}
		}

		if (!pushFlags.HasFlag(LayerPushFlags::ShowPrevLayer))
		{
			originalLayer->setVisible(false);
			originalLayer->ExitRecursively();
		}


		originalLayer->EnableInput(pushFlags.HasFlag(LayerPushFlags::ShowPrevLayer));
	}

	layer->retain();
	mLayerStack.Push(layer);
	AddLayer(layer);
	layer->OnCreated();

	layer->setVisible(true);
	layer->EnterRecursively();

	if (!pushFlags.HasFlag(LayerPushFlags::SuppressUpdateLogic))
	{
		layer->UpdateLogicRecursively();
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->SetEnableTargetTouches(!layer->IsModal());
	layer->EnableInput(!pushFlags.HasFlag(LayerPushFlags::DisableTouch));
}

LayerNode* IScene::PushLayerHelper( const StringRef& name,const IEventArg& e/*=IEventArg::Empty*/,LayerPushFlags pushFlags/*=LayerPushFlags::None*/)
{
	LayerNode* layer=FindLayerInStack(name);
	Log::AssertFormat(layer==NULL,"Cannot push Layer:%s which is already in stack.",name.c_str());

	LayerCreateFlags createFlags;
	if(pushFlags.HasFlag(LayerPushFlags::AlwaysCreate))
	{
		createFlags=LayerCreateFlags::AlwaysCreate;
	}

	layer=CreateLayer(name,e,createFlags);
	Log::AssertFormat(layer!=NULL,"Cannot create Layer:%s",name.c_str());

	PushLayerHelper(layer,pushFlags);

	return layer;
}

LayerNode* IScene::PopLayer(LayerPopFlags popFlags/*=LayerPopFlags::None*/)
{
	LayerNode* layer=GetCurrentLayer();
	Log::AssertNotNull(layer,"Layer stack should not be empty when pop.");

	if (!popFlags.HasFlag(LayerPopFlags::ShowCurrentLayer)||popFlags.HasFlag(LayerPopFlags::DeleteCurrentLayer)||popFlags.HasFlag(LayerPopFlags::DeleteCurrentLayerAsync))
	{
		layer->setVisible(false);
		layer->ExitRecursively();
		layer->EnableInput(false);
	}

	RemoveLayer(layer);
	mLayerStack.Pop();
	layer->release();

	if (popFlags.HasFlag(LayerPopFlags::DeleteCurrentLayer)||popFlags.HasFlag(LayerPopFlags::DeleteCurrentLayerAsync))
	{
		LayerDeleteFlags deleteFlags;
		if (popFlags.HasFlag(LayerPopFlags::DeleteCurrentLayerAsync))
		{
			deleteFlags=LayerDeleteFlags::Async;
		}

		DeleteLayer(layer->GetName(),deleteFlags);
		layer=NULL;
	}

	if (!popFlags.HasFlag(LayerPopFlags::IgnorePrevLayer))
	{
		LayerNode* prevLayer=GetCurrentLayer();
		if (prevLayer!=NULL)
		{
			prevLayer->setVisible(true);
			prevLayer->EnableInput(!popFlags.HasFlag(LayerPopFlags::DisableTouch));
			if(!popFlags.HasFlag(LayerPopFlags::SuppressUpdateLogic))
			{
				prevLayer->UpdateLogicRecursively();
			}

			CCDirector::sharedDirector()->getTouchDispatcher()->SetEnableTargetTouches(!prevLayer->IsModal());

		}
	}

	if (popFlags.HasFlag(LayerPopFlags::RestoreStatusAfterPop))
	{
		RestoreStatus();
	}
	return layer;
}

void IScene::PopAllLayer( LayerPopFlags popFlags/*=LayerPopFlags::IgnorePrevLayer*/ )
{
	while (!mLayerStack.IsEmpty())
	{
		PopLayer(popFlags);
	}
}


void IScene::ClearAll()
{
	PopAllLayer(LayerPopFlags::DeleteCurrentLayer|LayerPopFlags::IgnorePrevLayer);
	ReleaseCacheLayers();

}

LayerNode* IScene::ReplaceToLayerHelper( const StringRef& name,const IEventArg& e/*=IEventArg::Empty*/,LayerPopFlags popFlags/*=LayerPopFlags::None*/,LayerPushFlags pushFlags/*=LayerPushFlags::None*/ )
{
	LayerNode* prevLayer=PopLayer(popFlags);
	return PushLayerHelper(name,e,pushFlags);
}

LayerNode* IScene::ReplaceToLayerHelper( LayerNode* toLayer,LayerPopFlags popFlags/*=LayerPopFlags::None*/,LayerPushFlags pushFlags/*=LayerPushFlags::None*/ )
{
	LayerNode* prevLayer=PopLayer(popFlags);
	PushLayerHelper(toLayer,pushFlags);
	return prevLayer;
}


LayerNode* IScene::FindLayerInStack( const StringRef& name )
{
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		if (layer->GetName()==name)
		{
			return layer;
		}
	}

	return NULL;
}

const LayerNode* IScene::FindLayerInStack( const StringRef& name ) const
{
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		if (layer->GetName()==name)
		{
			return layer;
		}
	}

	return NULL;
}

bool IScene::IsLayerInStack( const StringRef& name ) const
{
	return FindLayerInStack(name)!=NULL;
}

void IScene::ShowActivityIndicator()
{
	ActivityLayer* activityLayer=CreateLayer<ActivityLayer>();//only allow one, so use the cache one
	if (GetDrawCCNode()!=NULL&&activityLayer->GetDrawCCNode()!=NULL&&activityLayer->getParent()==NULL)
	{
		GetDrawCCNode()->addChild(activityLayer->GetDrawCCNode());
	}
	activityLayer->Show();
}

void IScene::HideActivityIndicator()
{
	ActivityLayer* activityLayer=CreateLayer<ActivityLayer>();//only allow one, so use the cache one
	if (GetDrawCCNode()!=NULL&&activityLayer->GetDrawCCNode()!=NULL&&activityLayer->getParent()==NULL)
	{
		GetDrawCCNode()->addChild(activityLayer->GetDrawCCNode());
	}
	activityLayer->Hide();
}

void IScene::ShowAlertView( StringRef text,Pattern::Action0 callback/*=Pattern::Action0::Empty*/ )
{
	AlertLayer* layer= PushLayer<AlertLayer>(LayerPushFlags::ShowPrevLayer);
	layer->Show(text,callback);
}

void IScene::ShowAlertView( WStringRef text,Pattern::Action0 callback/*=Pattern::Action0::Empty*/ )
{
	AlertLayer* layer= PushLayer<AlertLayer>(LayerPushFlags::ShowPrevLayer);
	layer->Show(text,callback);
}

void IScene::ShowToast( StringRef text, float duration /*= 2.0f*/, ToastPosition position /*= ToastPosition::Center*/ )
{
	ToastLayer* toastLayer= CreateLayer<ToastLayer>(IEventArg::Empty,LayerCreateFlags::AlwaysCreate);
	toastLayer->SetString(text);
	toastLayer->Run();

	if (GetDrawCCNode()!=NULL&&toastLayer->GetDrawCCNode()!=NULL)
	{
		GetDrawCCNode()->addChild(toastLayer->GetDrawCCNode());
	}
}

void IScene::SaveStatus()
{
	mLayerStatusDict.Clear();
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		bool isVisible=layer->isVisible();
		bool enableInput=layer->IsInputEnabled();
		mLayerStatusDict.Add(layer->GetName(),LayerStatus(isVisible,enableInput));
	}
}

void IScene::RestoreStatus()
{
	FOR_EACH_COLLECTION(i,mLayerStack)
	{
		LayerNode* layer=*i;
		LayerStatus* statusPtr=mLayerStatusDict.TryGetValue(layer->GetName());
		if (statusPtr!=NULL)
		{
			layer->setVisible(statusPtr->IsVisible);
			layer->EnableInput(statusPtr->EnableInput);
			if (statusPtr->IsVisible)
			{
				layer->EnterRecursively();
			}
			else
			{
				layer->ExitRecursively();
			}
		}
	}

	mLayerStatusDict.Clear();

}







