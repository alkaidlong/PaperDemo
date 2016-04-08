#pragma once
#include "Scene/Element/LayerNode.h"
USING_MEDUSA;
#include "Game/UI/Main/SelectHeroListIconLayer.h"

#include "Core/Collection/Array.h"
//this class is used to implement logic codes
class SelectHeroListTabLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	SelectHeroListTabLayer(const IEventArg& e=IEventArg::Empty);
	~SelectHeroListTabLayer();

	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual bool UpdateLogic();
protected:
	void OnButtonTap(INode* sender,TapGestureEventArg& e);
private:
	int mTag;

	Array<SelectHeroListIconLayer*,6> mHeroList;

};
