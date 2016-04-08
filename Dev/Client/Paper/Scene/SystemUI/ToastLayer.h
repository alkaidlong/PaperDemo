#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/LabelNode.h"
#include "Scene/Element/SpriteNode.h"
USING_MEDUSA;

//this class is used to implement logic codes
class ToastLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	ToastLayer(const IEventArg& e=IEventArg::Empty);
	~ToastLayer();

	virtual bool IsModal()const{return true;}
	virtual bool Initialize();
	virtual bool Uninitialize();

	void SetString(StringRef str);

	void Run();
private:
	void OnHide(void*);
	LabelNode* mLabel;
	SpriteNode* mBackgroundImage;
};
