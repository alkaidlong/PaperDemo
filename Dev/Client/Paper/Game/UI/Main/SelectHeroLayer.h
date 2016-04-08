#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/ListBoxNode.h"
#include "Scene/Element/ButtonNode.h"
#include "Game/UI/Main/SelectHeroListIconLayer.h"

#include "Core/Collection/Array.h"
USING_MEDUSA;
class Role;

#define INVALID_INT_SelectHero -1
//this class is used to implement logic codes
class SelectHeroLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	struct SelectRoleInfo
	{
		Role* RoleData;
		bool IsSelect;
		bool IsInForce;
	};

public:
	SelectHeroLayer(const IEventArg& e=IEventArg::Empty);
	~SelectHeroLayer();

	virtual bool Initialize();
	virtual bool Uninitialize();

	virtual bool UpdateLogic();

	const SelectRoleInfo* GetRoleByIndex(uint index)const;

	void TapListHero(uint index);
	void TapForceHero(uint index);

protected:
	void OnButtonTap(INode* sender,TapGestureEventArg& e);
	void OnButtonToBattle(INode* sender,TapGestureEventArg& e);

private:
	ListBoxNode* mListBox;
	Array<SelectHeroListIconLayer*,5> mForceHeros;
	List<SelectRoleInfo,NoCompare<SelectRoleInfo>> mRoleList;

	uint mSelectRoleListIndex;
};
