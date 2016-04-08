
#include "Game/UI/Main/SelectHeroListTabLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Game/UI/Main/SelectHeroLayer.h"
#include "Scene/IScene.h"
#include "Scene/SceneManager.h"

SelectHeroListTabLayer::SelectHeroListTabLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

SelectHeroListTabLayer::~SelectHeroListTabLayer()
{
}

bool SelectHeroListTabLayer::Initialize()
{
	mTag = getTag();

	StackString<64> str;
	FOR_EACH_SIZE(i,mHeroList.Size)
	{
		str.Format("LayerRef%d",i+1);
		mHeroList[i] = (SelectHeroListIconLayer*)FindChildConfidently(str);

		mHeroList[i]->AddTapGestureHandler(TapEventHandler(this,&SelectHeroListTabLayer::OnButtonTap));
		
	}
	return true;
}

bool SelectHeroListTabLayer::Uninitialize()
{
	return true;
}


bool SelectHeroListTabLayer::UpdateLogic()
{
	const Dictionary<uint,Role*>& roleDic = PaperGame::Instance().GetRoles();

	SelectHeroLayer* layer = SceneManager::Instance().GetRunningScene()->FindLayerInStack<SelectHeroLayer>();
	FOR_EACH_SIZE(i,mHeroList.Size)
	{
		if (mTag*mHeroList.Size+i<roleDic.GetCount())
		{
			const SelectHeroLayer::SelectRoleInfo* role = layer->GetRoleByIndex(mTag*mHeroList.Size+i);
			mHeroList[i]->SetHeroInfo(role->RoleData);
			mHeroList[i]->setVisible(true);
			mHeroList[i]->EnableInput(true);

			if (role->IsSelect)
			{
				mHeroList[i]->SetIconStatus(SelectHeroIconStatus::Selected);
			}
			else
			{
				mHeroList[i]->SetIconStatus(SelectHeroIconStatus::Normal);
			}

			if (role->IsInForce)
			{
				mHeroList[i]->SetIconStatus(SelectHeroIconStatus::Disabled);
			}
		}
		else
		{
			mHeroList[i]->setVisible(false);
			mHeroList[i]->EnableInput(false);
		}
	}

	return true;
}

void SelectHeroListTabLayer::OnButtonTap( INode* sender,TapGestureEventArg& e )
{
	SelectHeroLayer* layer = SceneManager::Instance().GetRunningScene()->FindLayerInStack<SelectHeroLayer>();
	FOR_EACH_SIZE(i,mHeroList.Size)
	{
		SelectHeroListIconLayer* iconLayer = (SelectHeroListIconLayer*)sender;
		if (iconLayer==mHeroList[i])
		{
			const SelectHeroLayer::SelectRoleInfo* role = layer->GetRoleByIndex(mTag*mHeroList.Size+i);

			if (!role->IsInForce)
			{
				layer->TapListHero(mTag*mHeroList.Size+i);
			}
		}
	}
}


IMPLEMENT_REGISTER_LAYER(SelectHeroListTabLayer,"SelectHeroListTab.layer");