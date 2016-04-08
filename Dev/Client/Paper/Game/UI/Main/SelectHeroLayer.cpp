
#include "Game/UI/Main/SelectHeroLayer.h"
#include "Scene/Editor/LayerFactory.h"
#include "Core/Log/Log.h"
#include "Game/PaperGame.h"
#include "Game/Battle/BattleManager.h"

SelectHeroLayer::SelectHeroLayer(const IEventArg& e/*=IEventArg::Empty*/):LayerNode()
{
}

SelectHeroLayer::~SelectHeroLayer()
{
}

bool SelectHeroLayer::Initialize()
{
	mListBox = (ListBoxNode*)FindChildConfidently("ListBox");

	StackString<64> str;
	FOR_EACH_SIZE(i,mForceHeros.Size)
	{
		str.Format("LayerRef%d",i+1);
		mForceHeros[i] = (SelectHeroListIconLayer*)FindChildConfidently(str);
		mForceHeros[i]->SetIsShowBackground(true);
		mForceHeros[i]->AddTapGestureHandler(TapEventHandler(this,&SelectHeroLayer::OnButtonTap));
		mForceHeros[i]->EnableInput(true);
	}

	
	const Dictionary<uint,Role*>& roleDic = PaperGame::Instance().GetRoles();

	SelectRoleInfo selectRoleInfo;
	FOR_EACH_COLLECTION(i,roleDic)
	{
		selectRoleInfo.RoleData = (*i).Value;
		selectRoleInfo.IsInForce = false;
		selectRoleInfo.IsSelect = false;
		mRoleList.Add(selectRoleInfo);
	}

	((ButtonNode*)FindChildConfidently("EnterButton"))->AddTapGestureHandler(TapEventHandler(this,&SelectHeroLayer::OnButtonToBattle));
	
	mSelectRoleListIndex = INVALID_INT_SelectHero;

	return true;
}

bool SelectHeroLayer::Uninitialize()
{
	return true;
}


bool SelectHeroLayer::UpdateLogic()
{
	int listBoxItemCount = 0;
	if (mRoleList.GetCount()%6==0)
	{
		listBoxItemCount = mRoleList.GetCount()/6;
	}
	else
	{
		listBoxItemCount = mRoleList.GetCount()/6+1;
	}

	mListBox->SetItemCount(listBoxItemCount);
	mListBox->reloadData();


	return true;
}

const SelectHeroLayer::SelectRoleInfo* SelectHeroLayer::GetRoleByIndex( uint index ) const
{
	if (index<mRoleList.GetCount())
	{
		return &mRoleList[index];
	}
	return NULL;
}

void SelectHeroLayer::OnButtonTap( INode* sender,TapGestureEventArg& e )
{
	FOR_EACH_SIZE(i,mForceHeros.Size)
	{
		SelectHeroListIconLayer* iconLayer = (SelectHeroListIconLayer*)sender;
		if (iconLayer==mForceHeros[i])
		{
			TapForceHero(i);
		}
	}
}

void SelectHeroLayer::TapListHero( uint index )
{
	mRoleList[index].IsSelect = !mRoleList[index].IsSelect;

	if (mRoleList[index].IsSelect)
	{
		mSelectRoleListIndex = index;

		FOR_EACH_SIZE(i,mRoleList.GetCount())
		{
			if (i!=index)
			{
				mRoleList[i].IsSelect= false;
			}
		}
	}
	else
	{
		mSelectRoleListIndex = INVALID_INT_SelectHero;
	}

	mListBox->UpdateCell();
}

void SelectHeroLayer::TapForceHero( uint index )
{
	if (mForceHeros[index]->GetRoleData()==NULL)
	{
		if (mSelectRoleListIndex!=INVALID_INT_SelectHero)
		{
			mForceHeros[index]->SetHeroInfo(mRoleList[mSelectRoleListIndex].RoleData);
			mRoleList[mSelectRoleListIndex].IsInForce = true;
			mRoleList[mSelectRoleListIndex].IsSelect = false;

			mSelectRoleListIndex = INVALID_INT_SelectHero;
		}
	}
	else
	{
		FOR_EACH_SIZE(i,mRoleList.GetCount())
		{
			if (mForceHeros[index]->GetRoleData()==mRoleList[i].RoleData)
			{
				mRoleList[i].IsInForce = false;
				break;
			}
		}
		mForceHeros[index]->SetHeroInfo(NULL);
	}

	mListBox->UpdateCell();
}

void SelectHeroLayer::OnButtonToBattle( INode* sender,TapGestureEventArg& e )
{
	BattleManager::Instance().ReadyToBattle(1);
	FOR_EACH_SIZE(i,mForceHeros.Size)
	{
		if (mForceHeros[i]->GetRoleData()!=NULL)
		{
			BattleManager::Instance().AddRoleToBattle((Role*)mForceHeros[i]->GetRoleData(),i);
		}
	}
	
	PaperGame::Instance().SwitchToBattle();
}


IMPLEMENT_REGISTER_LAYER(SelectHeroLayer,"SelectHero.layer");
