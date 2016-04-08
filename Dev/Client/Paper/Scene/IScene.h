#pragma once
#include "Scene/INode.h"
#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/Stack.h"
#include "Core/Pattern/FlagsPattern.h"
#include "Core/Collection/Stack.h"
#include "Scene/SystemUI/SystemUI.h"
#include "Core/Pattern/TuplePattern.h"
USING_MEDUSA;

STRONG_FLAGS_1(LayerCreateFlags,AlwaysCreate);
STRONG_FLAGS_1(LayerDeleteFlags,Async);

STRONG_FLAGS_6(LayerPushFlags,ShowPrevLayer,SuppressUpdateLogic,AlwaysCreate,DisableTouch,HideAllPrevLayers,SaveStatusBeforePush);
STRONG_FLAGS_7(LayerPopFlags,ShowCurrentLayer,SuppressUpdateLogic,DisableTouch,IgnorePrevLayer,DeleteCurrentLayer,DeleteCurrentLayerAsync,RestoreStatusAfterPop);

MEDUSA_TUPLE_2(LayerStatus,bool,IsVisible,bool,EnableInput);

class LayerNode;

class IScene :public INode,public CCScene,public CCTouchDelegate, public CCAccelerometerDelegate, public CCKeypadDelegate
{
public:
	IScene();
	virtual ~IScene(void);
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual CCNode* GetDrawCCNode(){return this;}

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	virtual void keyBackClicked();
	virtual void keyMenuClicked();

	virtual bool UpdateLogicRecursively();
	virtual bool ResetLogicRecursively();


public://Stack
	LayerNode* GetCurrentLayer()const;

	template<typename T>
	T* PushLayer(LayerPushFlags pushFlags=LayerPushFlags::None,const IEventArg& e=IEventArg::Empty){return (T*)PushLayerHelper( T::ClassGetProtoName(),e,pushFlags);}

	LayerNode* PopLayer(LayerPopFlags popFlags=LayerPopFlags::None);
	void PopAllLayer(LayerPopFlags popFlags=LayerPopFlags::IgnorePrevLayer);

	template<typename T>
	T* ReplaceToLayer(LayerPopFlags popFlags=LayerPopFlags::None,LayerPushFlags pushFlags=LayerPushFlags::None,const IEventArg& e=IEventArg::Empty){return (T*)ReplaceToLayerHelper(T::ClassGetProtoName(),e,popFlags,pushFlags);}

	template<typename T>
	T* FindLayerInStack(){return (T*)FindLayerInStack(T::ClassGetProtoName());}
	bool IsLayerInStack(const StringRef& name)const;

	LayerNode* FindLayerInStack(const StringRef& name);
	const LayerNode* FindLayerInStack(const StringRef& name)const;
public:
	//System UI
	void ShowActivityIndicator();
	void HideActivityIndicator();

	void ShowAlertView(StringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);
	void ShowAlertView(WStringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);

	void ShowToast(StringRef text, float duration = 2.0f, ToastPosition position = ToastPosition::Center);
protected:	//Cache
	template<typename T>
	T* CreateLayer(const IEventArg& e=IEventArg::Empty,LayerCreateFlags createFlags=LayerCreateFlags::None){return (T*)CreateLayer( T::ClassGetProtoName(),e,createFlags);}
	void CreateLayers(const List<StringRef>& names,const IEventArg& e=IEventArg::Empty,LayerCreateFlags createFlags=LayerCreateFlags::None);
	LayerNode* CreateLayer(const StringRef& name,const IEventArg& e=IEventArg::Empty,LayerCreateFlags createFlags=LayerCreateFlags::None);

	template<typename T>
	void DeleteLayer(LayerDeleteFlags deleteFlags=LayerDeleteFlags::None){ DeleteLayer( T::ClassGetProtoName());}
	void DeleteLayers(const List<StringRef>& names,LayerDeleteFlags deleteFlags=LayerDeleteFlags::None);
	bool DeleteLayer(StringRef name,LayerDeleteFlags deleteFlags=LayerDeleteFlags::None);

	template<typename T>
	bool IsLayerCached()const{return IsLayerCached(T::ClassGetProtoName());}
	bool IsLayerCached(const StringRef& name)const;
	LayerNode* FindLayerInCache(const StringRef& name);

	void ReleaseCacheLayers();

protected:	//Stack
	LayerNode* PushLayerHelper(const StringRef& name,const IEventArg& e=IEventArg::Empty,LayerPushFlags pushFlags=LayerPushFlags::None);
	void PushLayerHelper(LayerNode* layer,LayerPushFlags pushFlags=LayerPushFlags::None);

	LayerNode* ReplaceToLayerHelper(const StringRef& name,const IEventArg& e=IEventArg::Empty,LayerPopFlags popFlags=LayerPopFlags::None,LayerPushFlags pushFlags=LayerPushFlags::None);
	LayerNode* ReplaceToLayerHelper(LayerNode* toLayer,LayerPopFlags popFlags=LayerPopFlags::None,LayerPushFlags pushFlags=LayerPushFlags::None);
protected:
	void AddLayer(LayerNode* layer);
	void RemoveLayer(LayerNode* layer);
	void ClearAll();


private:
	void OnDeleteLayer(IScene* sender,StringRef name);

	void SaveStatus();
	void RestoreStatus();
protected:
	Dictionary<StringRef,LayerNode*> mCachedLayers;
	Stack<LayerNode*> mLayerStack;
	Dictionary<StringRef,LayerStatus> mLayerStatusDict;
};


