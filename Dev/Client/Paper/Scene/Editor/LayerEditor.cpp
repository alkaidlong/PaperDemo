
#include "Scene/Editor/LayerEditor.h"
#include "Scene/Editor/LayerFactory.h"
#include "Scene/Element/NormalLayerNode.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Scene/Element/SpriteNode.h"
#include "Scene/Element/ButtonNode.h"
#include "Scene/Element/FrameNode.h"
#include "Scene/Element/LabelNode.h"
#include "Scene/Element/EditBoxNode.h"
#include "Scene/Element/ProgressBarNode.h"
#include "Scene/Element/TriggerNode.h"
#include "Scene/Element/TriggerRefNode.h"
#include "Scene/Element/ListBoxNode.h"
#include "Scene/Element/BMPLabelNode.h"






LayerEditor::LayerEditor(void)
{
	mIsCacheProtoData=false;
}


LayerEditor::~LayerEditor(void)
{
	ReleaseProtoCache();
}


LayerNode* LayerEditor::CreateLayer( FileId name ,const IEventArg& e/*=IEventArg::Empty*/,bool enableTouch/*=true*/)
{
	CoreProto::Editor::Layer* layerData=GetProtoData(name.Name);
	RETURN_NULL_IF_NULL(layerData);
	LayerNode* resultLayer= CreateEmptyLayer(name.Name,e);

	if (resultLayer==NULL)
	{
		Log::LogErrorFormat("Cannot create empty layer:%s",name.Name.c_str());
	}

	resultLayer->SetProtoData(*layerData);
	resultLayer->setAnchorPoint(ccp(0,0));

	if (!SetupLayerNode(resultLayer,*layerData,e))
	{
		SAFE_DELETE(resultLayer);
	}

	ReleaseProtoData(layerData);
	return resultLayer;
}



LayerNode* LayerEditor::CreateLayerRef(FileId name,const CoreProto::Editor::LayerRef& refData,const IEventArg& e/*=IEventArg::Empty*/,bool enableTouch/*=true*/)
{
	CoreProto::Editor::Layer* layerData=GetProtoData(name.Name);
	RETURN_NULL_IF_NULL(layerData);
	LayerNode* resultLayer= CreateEmptyLayer(name.Name,e);

	if (resultLayer==NULL)
	{
		Log::LogErrorFormat("Cannot create empty layer:%s",name.Name.c_str());
	}

	resultLayer->SetProtoData(*layerData);
	resultLayer->setAnchorPoint(ccp(0,0));

	resultLayer->SetProtoData(refData);
	if (!SetupLayerNode(resultLayer,*layerData,e))
	{
		SAFE_DELETE(resultLayer);
	}

	ReleaseProtoData(layerData);
	return resultLayer;
}

LayerNode* LayerEditor::CreateEmptyLayer( FileId name ,const IEventArg& e/*=IEventArg::Empty*/)
{
	LayerNode* resultLayer= LayerFactory::Instance().Create(name.Name,e);
	if (resultLayer!=NULL)
	{
		resultLayer->autorelease();
		return resultLayer;
	}

	NormalLayerNode* normalLayer=new NormalLayerNode(e);
	normalLayer->autorelease();
	normalLayer->SetProtoName(name.Name);
	return normalLayer;
}

ButtonNode* LayerEditor::CreateButtonNode(LayerNode* parentNode,const FrameNode* sourceFrame,StringRef spriteID,const FileId& normalFileID) const
{
	if (parentNode==NULL||sourceFrame==NULL)
	{
		Log::LogErrorFormat("CreateButtonNode error");
		return NULL;
	}

	const CoreProto::Editor::Frame& frameProto = sourceFrame->GetProtoData();
	CoreProto::Editor::Button buttonData;

	buttonData.set_id(spriteID.c_str());
	buttonData.mutable_position()->set_x(frameProto.position().x());
	buttonData.mutable_position()->set_y(frameProto.position().y());
	buttonData.mutable_anchor()->set_x(frameProto.anchor().x());
	buttonData.mutable_anchor()->set_y(frameProto.anchor().y());
	buttonData.set_zorder(frameProto.zorder());
	buttonData.set_isvisible(true);

	CoreProto::FileId* newFileID = buttonData.mutable_normalimage()->mutable_file();
	newFileID->set_name(std::string(normalFileID.Name.c_str()) );
	newFileID->set_order(normalFileID.Order);
	newFileID->set_tag(normalFileID.mTag);

	ButtonNode* sprite=new ButtonNode();
	sprite->autorelease();
	sprite->SetProtoData(buttonData);
	sprite->Initialize();
	parentNode->AddChild(sprite);
	sprite->OnCreated();

	return sprite;
}

SpriteNode* LayerEditor::CreateSpriteNode( LayerNode* parentNode,const FrameNode* sourceFrame,StringRef spriteID,const FileId& fileID) const
{
	if (parentNode==NULL||sourceFrame==NULL)
	{
		Log::LogErrorFormat("CreateSpriteNode error");
		return NULL;
	}

	const CoreProto::Editor::Frame& frameProto = sourceFrame->GetProtoData();
	CoreProto::Editor::Image imageData;
	imageData.set_id(spriteID.c_str());
	imageData.mutable_position()->set_x(frameProto.position().x());
	imageData.mutable_position()->set_y(frameProto.position().y());
	imageData.mutable_anchor()->set_x(frameProto.anchor().x());
	imageData.mutable_anchor()->set_y(frameProto.anchor().y());

	imageData.mutable_scissorbox()->mutable_origin()->set_x(frameProto.scissorbox().origin().x());
	imageData.mutable_scissorbox()->mutable_origin()->set_y(frameProto.scissorbox().origin().y());
	imageData.mutable_scissorbox()->mutable_size()->set_width(frameProto.scissorbox().size().width());
	imageData.mutable_scissorbox()->mutable_size()->set_height(frameProto.scissorbox().size().height());

	if (frameProto.has_scale())
	{
		imageData.mutable_scale()->set_x(frameProto.scale().x());
		imageData.mutable_scale()->set_y(frameProto.scale().y());
	}
	else
	{
		imageData.mutable_scale()->set_x(1.0f);
		imageData.mutable_scale()->set_y(1.0f);
	}

	imageData.set_zorder(frameProto.zorder());
	imageData.set_isvisible(true);

	CoreProto::FileId* newFileID = imageData.mutable_file()->mutable_file();
	newFileID->set_name(std::string(fileID.Name.c_str()) );
	newFileID->set_order(fileID.Order);
	newFileID->set_tag(fileID.mTag);

	SpriteNode* sprite=new SpriteNode();
	sprite->autorelease();
	sprite->SetProtoData(imageData);
	sprite->Initialize();
	parentNode->AddChild(sprite);
	sprite->OnCreated();
	return sprite;
}


cocos2d::CCPoint LayerEditor::GetFlowPosition(CCPoint firstPosition, CCSize containerSize,CCSize elementSize,uint index,bool isLimitWidth,bool isLimitHeight )
{
	//return left-bottom pos
	Log::AssertFormat(containerSize.width>=elementSize.width,"Container width:%f should >= element width:%f",containerSize.width,elementSize.width);
	Log::AssertFormat(containerSize.height>=elementSize.height,"Container width:%f should >= element width:%f",containerSize.height,elementSize.height);


	if (isLimitWidth)
	{
		int maxColumn=(int)floorf(containerSize.width/elementSize.width);
		int row=index/maxColumn;
		int column=index%maxColumn;

		if (isLimitHeight)
		{
			int maxRow=(int)floorf(containerSize.height/elementSize.height);
			Log::AssertFormat(row<=maxRow,"row %d exceed max row:%d",row,maxRow);
		}
		return ccp(elementSize.width*column,containerSize.height-elementSize.height*(row+1))+firstPosition;

	}
	else
	{
		return ccp(elementSize.width*index,containerSize.height-elementSize.height)+firstPosition;
	}

}

void LayerEditor::BeginProtoCache()
{
	mIsCacheProtoData=true;
	SAFE_DELETE_DICTIONARY_VALUE(mProtoDataDict);
}

void LayerEditor::ReleaseProtoCache()
{
	SAFE_DELETE_DICTIONARY_VALUE(mProtoDataDict);
	mIsCacheProtoData=false;
}

CoreProto::Editor::Layer* LayerEditor::GetProtoData(FileId name )
{
	if (mIsCacheProtoData)
	{
		CoreProto::Editor::Layer* result=mProtoDataDict.TryGetValueWithFailed(FileIdStorage(name),NULL);
		if (result!=NULL)
		{
			//Log::LogInfoFormat("UI proto cache hit:%s",name.Name.c_str());
			return result;
		}
	}

	CoreProto::Editor::Layer* layerData=new CoreProto::Editor::Layer();
	if(!FileSystem::Instance().LoadProto(*layerData,name))
	{
		SAFE_DELETE(layerData);
		return NULL;
	}

	if (mIsCacheProtoData)
	{
		mProtoDataDict.Add(FileIdStorage(name),layerData);
	}

	return layerData;
}

void LayerEditor::ReleaseProtoData( CoreProto::Editor::Layer* layerData )
{
	if (!mIsCacheProtoData)
	{
		SAFE_DELETE(layerData);
	}
}

bool LayerEditor::SetupLayerNode( LayerNode* layer,const CoreProto::Editor::Layer& protoData ,const IEventArg& e/*=IEventArg::Empty*/)
{


	FOR_EACH_COLLECTION_STL(i,protoData.images())
	{
		const CoreProto::Editor::Image& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));
		SpriteNode* sprite=new SpriteNode();
		sprite->autorelease();
		sprite->SetProtoData(imageData);
		sprite->Initialize();
		layer->AddChild(sprite);
		sprite->OnCreated();
	}

	
	FOR_EACH_COLLECTION_STL(i,protoData.buttons())
	{
		const CoreProto::Editor::Button& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		ButtonNode* sprite=new ButtonNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);
		sprite->OnCreated();

	}


	FOR_EACH_COLLECTION_STL(i,protoData.progressbars())
	{
		const CoreProto::Editor::ProgressBar& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		ProgressBarNode* sprite=new ProgressBarNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);
		sprite->OnCreated();

	}



	FOR_EACH_COLLECTION_STL(i,protoData.frames())
	{
		const CoreProto::Editor::Frame& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		FrameNode* sprite=new FrameNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);
		sprite->OnCreated();

	}


	FOR_EACH_COLLECTION_STL(i,protoData.labels())
	{
		const CoreProto::Editor::Label& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));
		StringRef fontName=imageData.fontname().name();
		if (fontName.EndWith("ttf"))
		{
			LabelNode* sprite=new LabelNode();
			sprite->autorelease();
			sprite->SetProtoData(imageData);
			sprite->Initialize();
			layer->AddChild(sprite);
			sprite->OnCreated();
		}
		else if (fontName.EndWith("fnt"))
		{
			BMPLabelNode* sprite=new BMPLabelNode();
			sprite->autorelease();
			sprite->SetProtoData(imageData);
			sprite->Initialize();
			layer->AddChild(sprite);
			sprite->OnCreated();
		}
		else
		{
			Log::AssertFormat( 0, "Invalid font:%s",fontName.c_str());
		}

	}


	FOR_EACH_COLLECTION_STL(i,protoData.editboxs())
	{
		const CoreProto::Editor::EditBox& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		EditBoxNode* sprite=new EditBoxNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);
		sprite->OnCreated();

	}

	FOR_EACH_COLLECTION_STL(i,protoData.layerrefs())
	{
		const CoreProto::Editor::LayerRef& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		LayerNode* layerNode= CreateLayerRef(imageData.modelname(),imageData,e);
		//layerNode->SetProtoData(imageData);
		layerNode->Initialize();

		layer->AddChild(layerNode);
		layerNode->OnCreated();

	}


	FOR_EACH_COLLECTION_STL(i,protoData.triggers())
	{
		const CoreProto::Editor::Trigger& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		TriggerNode* sprite=new TriggerNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);
		sprite->OnCreated();

	}


	FOR_EACH_COLLECTION_STL(i,protoData.triggerrefs())
	{
		const CoreProto::Editor::TriggerRef& imageData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(imageData.id()));

		TriggerRefNode* sprite=new TriggerRefNode();
		sprite->autorelease();

		sprite->SetProtoData(imageData);
		sprite->Initialize();

		layer->AddChild(sprite);

	}


	FOR_EACH_COLLECTION_STL(i,protoData.lists())
	{
		const CoreProto::Editor::ListBox& listData=*i;
		CONTINUE_IF_FALSE(layer->IsCreateElement(listData.id()));

		ListBoxNode* listBox=new ListBoxNode();
		listBox->autorelease();

		listBox->SetProtoData(listData);
		listBox->Initialize();
		layer->AddChild(listBox);

	}

	return true;
}

Point2F LayerEditor::CalculateAnchor( const Point2F& anchorPoint, const Point2F& offset ,const Size2F& originalSize, const Size2F& finalSize )
{
	return Point2F((anchorPoint.X * originalSize.Width-offset.X)/finalSize.Width,(anchorPoint.Y * originalSize.Height-offset.Y)/finalSize.Height);
}

Medusa::Point2F LayerEditor::CalculateRoute(const Point2F& beginPos, float distance,List<Point2U>& refRoutes)
{
	uint routeCount=refRoutes.GetCount();
	if (routeCount==0||distance<=0.f)
	{
		return beginPos;
	}
	Point2F prevPos=beginPos;
	uint i=0;
	for (;i<routeCount;++i)
	{
		Point2F curPos=refRoutes[i];

		float curDistance=prevPos.GetDistance(curPos);
		if (distance<=curDistance)
		{
			prevPos=Point2F::Move(prevPos,curPos,distance);
			distance-=curDistance;
			break;
		}
		else
		{
			prevPos=curPos;
			distance-=curDistance;
		}
	}

	if (distance>0.f||i>=routeCount)
	{
		//all routes is too short
		refRoutes.Clear();
	}
	else if(i>0)
	{
		refRoutes.RemoveRange(0,i);
	}


	return prevPos;
}



