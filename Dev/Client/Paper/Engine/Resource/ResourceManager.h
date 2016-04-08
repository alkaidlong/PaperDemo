#pragma once

#include "Core/Pattern/Singleton.h"
#include "Core/Proto/Client/LayerEditor.pb.h"
#include "Engine/Extension/cocos-ext.h"
#include "PaperHeader.h"
#include "Scene/Element/FrameNode.h"
#include "TextureLoadEventArg.h"
#include "Core/Threading/Thread.h"

USING_MEDUSA;
class IAnimation;
/*
1.Load file aysnc,progress callback
2.cache some files
*/

class ResourceManager:public Pattern::Singleton<ResourceManager>
{
	friend class Pattern::Singleton<ResourceManager>;
	ResourceManager(void);
	~ResourceManager(void);
public:
	typedef Pattern::Delegate<void (void* sender,TextureLoadEventArg*)> TextureLoadHandler;
	typedef Pattern::Event<void (void* sender,TextureLoadEventArg*)> TextureLoadEvent;

public:
	bool Load();
	void Release();

	cocos2d::CCTexture2D* LoadTexture(const FileId& imageFile);
	cocos2d::CCTexture2D* LoadTexture(FileSystemOrderItem* orderItem);
	cocos2d::CCTexture2D* LoadTexture(size_t fileId);
	cocos2d::CCTexture2D* LoadTexture(FileListFileItem* fileItem);

	bool LoadTexturesInDirectory(const StringRef& dir,bool isRecursively=false,const StringRef& serarchPattern=StringRef::Empty);
	bool LoadTexturesByOriginalName(const FileId& fileId);



	FileSystemOrderItem* InitSprite(CCSprite* sprite,const CoreProto::Editor::ImageFile& imageFile,const CoreProto::SizeU& contentSize);
	FileSystemOrderItem* ReloadSprite(CCSprite* sprite,const CoreProto::Editor::ImageFile& imageFile,const CoreProto::SizeU& contentSize);
	FileSystemOrderItem* ReloadSprite(CCSprite* sprite,const FileId& fileID,const CoreProto::SizeU& contentSize);
	FileSystemOrderItem* ReloadSprite(CCSprite* sprite,const FileId& fileID);


	FileSystemOrderItem* InitScaleNineSprite(CCScale9Sprite* sprite,const CoreProto::Editor::ImageFile& imageFile);

	IAnimation* CreateAnimation(FrameNode* parentFrame,const FileId& fileId,bool isRun = true,bool isRepeat = true);
public:
	void Shrink(bool isClearAnimation=true);
	bool IsInMainThread()const;

	TextureLoadEvent OnLoadTexture;
protected:
	void OnLoadTextureHelper(void* sender,TextureLoadEventArg* e);
protected:
	ThreadIdType mMainThreadId;

};

