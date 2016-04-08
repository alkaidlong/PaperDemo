
#include "Scene/SystemUI/AlertLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Event/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Core/IO/Updater/FileUpdater.h"

#include "Scene/SceneManager.h"
#include "Scene/IScene.h"

AlertLayer::AlertLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

AlertLayer::~AlertLayer()
{
}

bool AlertLayer::Initialize()
{
	mLabel = (LabelNode*)FindChild("InformationLabel");
	Log::AssertNotNull(mLabel,"InformationLabel");

	AddTapGestureHandler(TapEventHandler(this,&AlertLayer::OnButtonTap));
	EnableInput(true);
	return true;
}

bool AlertLayer::Uninitialize()
{
	return true;
}

void AlertLayer::OnButtonTap( INode* sender,TapGestureEventArg& e )
{
	SceneManager::Instance().GetRunningScene()->PopLayer(LayerPopFlags::DeleteCurrentLayerAsync|LayerPopFlags::SuppressUpdateLogic);
	if (mCallback!=NULL)
	{
		mCallback();
	}
}


void AlertLayer::Show( StringRef text,Pattern::Action0 callback/*=Pattern::Action0::Empty*/ )
{
	mLabel->setString(text.c_str());
	mCallback=callback;
}

void AlertLayer::Show( WStringRef text,Pattern::Action0 callback/*=Pattern::Action0::Empty*/ )
{
	HeapString aString=StringParser::ToA(text);
	mLabel->setString(aString.c_str());
	mCallback=callback;


}


IMPLEMENT_REGISTER_LAYER(AlertLayer,"Alert.layer");
