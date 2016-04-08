#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/LabelNode.h"
USING_MEDUSA;
class SpriteNode;

//this class is used to implement logic codes
class ActivityLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	ActivityLayer(const IEventArg& e=IEventArg::Empty);
	~ActivityLayer();

	virtual bool IsModal()const{return true;}
	virtual bool Initialize();
	virtual bool Uninitialize();

	void Show();
	void Hide();
private:
	int mActivityIndicatorCount;
	SpriteNode* mNode;
};
