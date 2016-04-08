#pragma once
#include "Scene/Element/LayerNode.h"
#include "Scene/Element/LabelNode.h"
USING_MEDUSA;

//this class is used to implement logic codes
class AlertLayer:public LayerNode
{
	DECLARE_REGISTER_LAYER();
public:
	AlertLayer(const IEventArg& e=IEventArg::Empty);
	~AlertLayer();

	virtual bool IsModal()const{return true;}
	virtual bool Initialize();
	virtual bool Uninitialize();

	void Show(StringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);
	void Show(WStringRef text,Pattern::Action0 callback=Pattern::Action0::Empty);
protected:
	void OnButtonTap(INode* sender,TapGestureEventArg& e);

private:
	LabelNode* mLabel;
	Pattern::Action0 mCallback;
};
