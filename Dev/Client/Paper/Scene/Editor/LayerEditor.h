#pragma once

#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/List.h"

#include "Core/Proto/Client/LayerEditor.pb.h"
#include "Core/String/StringRef.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/IO/FileId.h"
#include "Core/IO/FileIdStorage.h"


#include "Scene/Element/ButtonNode.h"
//#include "Scene/Element/SpriteNode.h"
#include "Scene/Element/FrameNode.h"
class LayerNode;
class SpriteNode;

USING_MEDUSA;
class LayerEditor:public Pattern::Singleton<LayerEditor>
{
	friend class Pattern::Singleton<LayerEditor>;
private:
	LayerEditor(void);
	~LayerEditor(void);

public:
	
	template<typename T>
	T* CreateLayer(const IEventArg& e=IEventArg::Empty,bool enableTouch=true){return (T*)CreateLayer(T::ClassGetProtoName(),e,enableTouch);}

	LayerNode* CreateLayer( FileId name,const IEventArg& e=IEventArg::Empty,bool enableTouch=true);
	LayerNode* CreateLayerRef( FileId name,const CoreProto::Editor::LayerRef& refData,const IEventArg& e=IEventArg::Empty,bool enableTouch=true);


	ButtonNode* CreateButtonNode(LayerNode* parentNode,const FrameNode* sourceFrame,StringRef spriteID,const FileId& normalFileID)const;
	SpriteNode* CreateSpriteNode( LayerNode* parentNode,const FrameNode* sourceFrame,StringRef spriteID,const FileId& fileID)const;
	LayerNode* CreateLayerNode(const FrameNode* sourceFrame)const;

	static CCPoint GetFlowPosition(CCPoint firstPosition,CCSize containerSize,CCSize elementSize,uint index,bool isLimitWidth,bool isLimitHeight);
	static Point2F CalculateAnchor( const Point2F& anchorPoint, const Point2F& offset ,const Size2F& originalSize, const Size2F& finalSize );

	static Point2F CalculateRoute( const Point2F& beginPos, float distance,List<Point2U>& refRoutes);


	CoreProto::Editor::Layer* GetProtoData(FileId name);
	void ReleaseProtoData(CoreProto::Editor::Layer* layerData);
	LayerNode* CreateEmptyLayer(FileId name,const IEventArg& e=IEventArg::Empty);
	void BeginProtoCache();
	void ReleaseProtoCache();

	bool SetupLayerNode(LayerNode* layer,const CoreProto::Editor::Layer& protoData,const IEventArg& e=IEventArg::Empty);
private:
	
private:
	bool mIsCacheProtoData;
	Dictionary<FileIdStorage,CoreProto::Editor::Layer*>  mProtoDataDict;
};

