
#include "ResourceManager.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/IO/FileId.h"
#include "Engine/Animation/AnimationManager.h"
#include "Core/Event/UIEventDispatcher.h"

ResourceManager::ResourceManager(void)
{

}


ResourceManager::~ResourceManager(void)
{
	Release();
}


void ResourceManager::Release()
{
}


bool ResourceManager::Load()
{
	mMainThreadId=Thread::GetCurrentThreadId();

	Release();

	return true;
}



void ResourceManager::Shrink(bool isClearAnimation)
{
	if (isClearAnimation)
	{
		AnimationManager::Instance().Shrink();
	}
	
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

cocos2d::CCTexture2D* ResourceManager::LoadTexture( const FileId& imageFile )
{
	FileSystemOrderItem* orderItem=FileSystem::Instance().GetOrderItem(imageFile);
	return LoadTexture(orderItem);
}

cocos2d::CCTexture2D* ResourceManager::LoadTexture( FileSystemOrderItem* orderItem )
{
	return LoadTexture(orderItem->GetFileId());
}

cocos2d::CCTexture2D* ResourceManager::LoadTexture(size_t fileId)
{
	FileListFileItem* fileItem= FileSystem::Instance().GetFileList().GetFileItem(fileId);
	return LoadTexture(fileItem);
}

cocos2d::CCTexture2D* ResourceManager::LoadTexture(FileListFileItem* fileItem)
{
	HeapString realPath=FileSystem::Instance().GetReadFilePath(fileItem->GetFileId());
    
    if (realPath.IsEmpty())
    {
        Log::LogErrorFormat("Cannot read FileId:%zu",fileItem->GetFileId());
		return NULL;
    }
	cocos2d::CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey(realPath.c_str());
	if (texture!=NULL)
	{
		return texture;
	}

	MemoryByteData data;
	if (fileItem!=NULL)
	{
		data=FileSystem::Instance().GetAccessor().ReadAllData(realPath,fileItem->GetCoderList());
	}
	else
	{
		data=FileSystem::Instance().GetAccessor().ReadAllData(realPath,FileCoderList::Empty);
	}

	if (data.IsNull())
	{
		Log::LogErrorFormat("Cannot read:%s",realPath.c_str());
		return NULL;
	}

	if (IsInMainThread())
	{
		if (realPath.EndWith(".pvr"))
		{
			texture=CCTextureCache::sharedTextureCache()->addPVRImageWithData(realPath.c_str(),(char*)data.GetData(),data.GetSize());
			if (texture==NULL)
			{
				Log::LogErrorFormat("Cannot add texture:%s",realPath.c_str());
			}
		}
		else
		{
			texture=CCTextureCache::sharedTextureCache()->addImageWithData(realPath.c_str(),(char*)data.GetData(),data.GetSize());
			if (texture==NULL)
			{
				Log::LogErrorFormat("Cannot add texture:%s",realPath.c_str());
			}
		}

	}
	else
	{
		//Òì²½
		TextureLoadEventArg* e=new TextureLoadEventArg(realPath,data);
		UIEventDispatcher::Instance().FireEventAsync(TextureLoadHandler(this,&ResourceManager::OnLoadTextureHelper),(void*)NULL,e);
		while (!e->Handled)
		{
			Thread::Sleep(0);
		}
		texture=e->GetTexture();
		SAFE_DELETE(e);
	}


	return texture;
}


bool ResourceManager::LoadTexturesInDirectory(const StringRef& dir,bool isRecursively/*=false*/,const StringRef& serarchPattern/*=StringRef::Empty*/)
{
	List<FileListFileItem*> outFiles;
	bool result=FileSystem::Instance().GetFileList().EnumeateFiles(dir,outFiles,isRecursively,serarchPattern);
	RETURN_FALSE_IF_FALSE(result);

	FOR_EACH_COLLECTION(i,outFiles)
	{
		FileListFileItem* fileItem=*i;
		CONTINUE_IF_FALSE(fileItem->IsImageFile());
		CCTexture2D* texture=LoadTexture(fileItem);
		RETURN_FALSE_IF_NULL(texture);
	}

	return true;
}

bool ResourceManager::LoadTexturesByOriginalName(const FileId& fileId)
{
	FileSystemOrderItem* orderItem=FileSystem::Instance().GetOrderItem(fileId);
	RETURN_FALSE_IF_NULL(orderItem);
	CCTexture2D* texture=ResourceManager::Instance().LoadTexture(orderItem);
	return texture!=NULL;
}


FileSystemOrderItem* ResourceManager::InitSprite( CCSprite* sprite,const CoreProto::Editor::ImageFile& imageFile ,const CoreProto::SizeU& contentSize)
{
	const CoreProto::FileId& fileId=imageFile.file();
	FileSystemOrderItem* orderItem=FileSystem::Instance().GetOrderItem(fileId);
	if (orderItem==NULL)
	{
		Log::AssertFailedFormat("InitSprite:Cannot find image:%s",fileId.name().c_str());
		return NULL;
	}
	CCTexture2D* texture=ResourceManager::Instance().LoadTexture(orderItem);
	if (texture==NULL)
	{
		Log::AssertFailedFormat("Cannot load texture:%s",fileId.name().c_str());
		return NULL;
	}

	Rect2F textureRect=orderItem->GetTextureRectOrZero();

	if (textureRect.Size==Size2F::Zero)
	{
		textureRect.Size.Width=(float)texture->getContentSizeInPixels().width;
		textureRect.Size.Height=(float)texture->getContentSizeInPixels().height;
	}

	if(imageFile.has_border()&&(imageFile.border().left()!=0||imageFile.border().right()!=0||imageFile.border().top()!=0||imageFile.border().bottom()!=0))
	{
		sprite->SetScaleNineBorder(imageFile.border().left(),imageFile.border().right(),imageFile.border().top(),imageFile.border().bottom());

		if(!sprite->initWithTexture(texture,CCRect(textureRect.Origin.X,textureRect.Origin.Y,textureRect.Size.Width,textureRect.Size.Height),CCSize(contentSize.width(),contentSize.height()),SpriteType::ScaleNine))
		{
			Log::LogErrorFormat("Cannot init texture:%s",fileId.name().c_str());
			return NULL;
		}

	}
	else
	{
		if(!sprite->initWithTexture(texture,CCRect(textureRect.Origin.X,textureRect.Origin.Y,textureRect.Size.Width,textureRect.Size.Height)))
		{
			Log::LogErrorFormat("Cannot init texture:%s",fileId.name().c_str());
			return NULL;
		}
	}
	return orderItem;
}

FileSystemOrderItem* ResourceManager::ReloadSprite( CCSprite* sprite,const CoreProto::Editor::ImageFile& imageFile ,const CoreProto::SizeU& contentSize)
{
	const CoreProto::FileId& fileId=imageFile.file();
	FileSystemOrderItem* orderItem=FileSystem::Instance().GetOrderItem(fileId);
	if (orderItem==NULL)
	{
		Log::AssertFailedFormat("ReloadSprite:Cannot find image:%s",fileId.name().c_str());
		return NULL;
	}

	CCTexture2D* texture=ResourceManager::Instance().LoadTexture(orderItem);
	if (texture==NULL)
	{
		Log::AssertFailedFormat("Cannot load texture:%s",fileId.name().c_str());
		return NULL;
	}

	Rect2F textureRect=orderItem->GetTextureRectOrZero();
	if (textureRect.Size==Size2F::Zero)
	{
		textureRect.Size.Width=(float)texture->getContentSizeInPixels().width;
		textureRect.Size.Height=(float)texture->getContentSizeInPixels().height;
	}

	if(imageFile.has_border()&&(imageFile.border().left()!=0||imageFile.border().right()!=0||imageFile.border().top()!=0||imageFile.border().bottom()!=0))
	{
		sprite->SetSpriteType(SpriteType::ScaleNine);
		sprite->SetScaleNineBorder(imageFile.border().left(),imageFile.border().right(),imageFile.border().top(),imageFile.border().bottom());
		sprite->setTexture(texture);
		sprite->setTextureRect(CCRect(textureRect.Origin.X,textureRect.Origin.Y,textureRect.Size.Width,textureRect.Size.Height),false,CCSize(contentSize.width(),contentSize.height()));
	}
	else
	{
		sprite->SetSpriteType(SpriteType::Normal);
		sprite->setTexture(texture);
		sprite->setTextureRect(CCRect(textureRect.Origin.X,textureRect.Origin.Y,textureRect.Size.Width,textureRect.Size.Height),false,CCSize(textureRect.Size.Width,textureRect.Size.Height));
	}

	return orderItem;
}

FileSystemOrderItem* ResourceManager::ReloadSprite( CCSprite* sprite,const FileId& fileID ,const CoreProto::SizeU& contentSize)
{
	CoreProto::Editor::ImageFile imageFile;
	CoreProto::FileId* newFileID = imageFile.mutable_file();
	newFileID->set_name(std::string(fileID.Name.c_str()) );
	newFileID->set_order(fileID.Order);
	newFileID->set_tag(fileID.mTag);
	return ReloadSprite(sprite,imageFile,contentSize);
}

FileSystemOrderItem* ResourceManager::ReloadSprite( CCSprite* sprite,const FileId& fileID )
{
	CoreProto::SizeU zeroSize;
	return ReloadSprite(sprite,fileID,zeroSize);
}

FileSystemOrderItem* ResourceManager::InitScaleNineSprite( CCScale9Sprite* sprite,const CoreProto::Editor::ImageFile& imageFile )
{
	const CoreProto::FileId& fileId=imageFile.file();
	FileSystemOrderItem* orderItem=FileSystem::Instance().GetOrderItem(fileId);
	if (orderItem==NULL)
	{
		Log::LogErrorFormat("InitScaleNineSprite:Cannot find image:%s",fileId.name().c_str());
		return NULL;
	}

	HeapString realPath= FileSystem::Instance().GetReadFilePath(fileId);
	if(imageFile.has_border())
	{
		Rect2F textureRect=orderItem->GetTextureRectOrZero();
		if (textureRect!=Rect2F::Zero)
		{
			CCRect rectImage;
			rectImage.origin = ccp(textureRect.Origin.X,textureRect.Origin.Y);
			rectImage.size = CCSize(textureRect.Size.Width,textureRect.Size.Height);
			if (textureRect.Size!=Size2F::Zero)
			{
				sprite->initWithFile(realPath.c_str(),rectImage);

				sprite->setInsetLeft(imageFile.border().left());
				sprite->setInsetRight(imageFile.border().right());
				sprite->setInsetTop(imageFile.border().top());
				sprite->setInsetBottom(imageFile.border().bottom());
			}
		}
		else
		{
			sprite->initWithFile(realPath.c_str());

			sprite->setInsetLeft(imageFile.border().left());
			sprite->setInsetRight(imageFile.border().right());
			sprite->setInsetTop(imageFile.border().top());
			sprite->setInsetBottom(imageFile.border().bottom());
		}
	}
	else
	{
		Log::LogError("Failed to init CCScale9Sprite without border");
	}

	return orderItem;
}

IAnimation* ResourceManager::CreateAnimation(FrameNode* parentFrame,const FileId& fileId,bool isRun,bool isRepeat )
{
	if (parentFrame==NULL)
	{
		Log::LogErrorFormat("Create Animation from frame error");
		return NULL;
	}

	const CoreProto::Editor::Frame& frameProto = parentFrame->GetProtoData();
	cocos2d::CCPoint point;
	point.x = frameProto.size().width()*frameProto.anchor().x();
	point.y = frameProto.size().height()*frameProto.anchor().y();

	IAnimation* ani = AnimationManager::Instance().CreateAnimation(isRepeat,0,fileId);
	ani->setPosition(point);
	parentFrame->addChild(ani);

	if (isRun)
	{
		ani->Run();
	}

	return ani;
}

bool ResourceManager::IsInMainThread() const
{
	return Thread::IsInSameThread(mMainThreadId);
}

void ResourceManager::OnLoadTextureHelper(void* sender,TextureLoadEventArg* e)
{
	StringRef realPath=e->GetPath();
	const MemoryByteData& data=e->GetData();
	CCTexture2D* texture=NULL;
	if (realPath.EndWith(".pvr"))
	{
		texture=CCTextureCache::sharedTextureCache()->addPVRImageWithData(realPath.c_str(),(char*)data.GetData(),data.GetSize());
	}
	else
	{
		texture=CCTextureCache::sharedTextureCache()->addImageWithData(realPath.c_str(),(char*)data.GetData(),data.GetSize());
	}

	if (texture==NULL)
	{
		Log::LogErrorFormat("Cannot add texture:%s",realPath.c_str());
	}
	e->SetTexture(texture);
	e->Handled=true;
	OnLoadTexture(NULL,e);
}
