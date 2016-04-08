#include "MedusaCorePreCompiled.h"
#include "FileSystem.h"
#include "Core/Proto/Proto.h"
#include "Core/System/System.h"
#include "Core/IO/File.h"
#include "Core/Collection/List.h"
#include "Core/IO/FileList/FileListFileItem.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/IO/FileSystem/FileSystemTagItem.h"
#include "Core/IO/FileSystem/FileSystemNameItem.h"
#include "Core/IO/Directory.h"
#include "Core/IO/Path.h"
#include "Core/String/StringParser.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/IO/Stream/FileStream.h"


#if defined(MEDUSA_WINDOWS)||defined(MEDUSA_IOS)||defined(MEDUSA_LINUX)
#include "Core/IO/FileSystem/Accessor/posix/PosixFileSystemAccessor.h"
#else
#include "Core/IO/FileSystem/Accessor/android/AndroidFileSystemAccessor.h"
#endif

MEDUSA_BEGIN;

FileSystem::FileSystem(void)
{
	
#if defined(MEDUSA_WINDOWS)||defined(MEDUSA_IOS)||defined(MEDUSA_LINUX)
	mFileSystemAccessor=new PosixFileSystemAccessor();
#else
	mFileSystemAccessor=new AndroidFileSystemAccessor(System::Instance().GetApplicationPath());
#endif

}


FileSystem::~FileSystem(void)
{
	Uninitialize();
	SAFE_DELETE(mFileSystemAccessor);
}


bool FileSystem::Uninitialize()
{
	mFileList.Unload();
	Unload();
	return true;
}

void FileSystem::Unload()
{
	SAFE_DELETE_MAP_SECOND_STL(mTagItems.GetSTLItems());
	mValidTagList.Clear();
}


bool FileSystem::Initialize(StringRef fileListName,StringRef fileSystemName)
{
	Uninitialize();
	if (!mFileList.LoadFromFilesPriority(System::Instance().GetWritablePath(fileListName),System::Instance().GetReadonlyPath(fileListName),mFileList.GetDefaultFileCoder()))
	{
		Log::AssertFailed("Failed to load file list");
		return false;
	}

	if (!LoadFromFilesPriority(System::Instance().GetWritablePath(fileSystemName),System::Instance().GetReadonlyPath(fileSystemName),mFileList.GetDefaultFileCoder()))
	{
		Log::AssertFailed("Failed to load resource map");
		return false;
	}

	return true;
}


bool FileSystem::LoadFromData( const MemoryByteData& data )
{
	RETURN_FALSE_IF_FALSE(ILoadable::LoadFromData(data));

	CoreProto::FileSystem config;
	bool isSuccess=Proto::ParseFrom(config,data);
	RETURN_FALSE_IF_FALSE(isSuccess);

	FOR_EACH_COLLECTION_STL(i,config.tagitems())
	{
		const CoreProto::FileSystemTagItem& tagItem=*i;
		EnvironmentTag currentTag(tagItem.tag());
		FileSystemTagItem* fileSystemTagItem=mTagItems.TryGetValueWithFailed(currentTag,NULL);
		if (fileSystemTagItem==NULL)
		{
			fileSystemTagItem=new FileSystemTagItem();
			fileSystemTagItem->Initialize(tagItem);
			mTagItems.Add(currentTag,fileSystemTagItem);
		}
		else
		{
			Log::AssertFailed("duplicate register");
		}
	}


	ApplyTag(EnvironmentTag::MatchAll);
	return true;
}



void FileSystem::ApplyTag( const EnvironmentTag& tag )
{
	mValidTagList.Clear();	FOR_EACH_COLLECTION_STL(i,mTagItems.GetSTLItems())
	{
		FileSystemTagItem* tagItem=i->second;
		int diffScore=tagItem->UpdateDiffScore(tag);
		if (diffScore!=Math::IntMinValue)
		{
			mValidTagList.Add(tagItem);
		}
	}

}


FileSystemOrderItem* FileSystem::GetOrderItem( const FileId& fileId ) const
{
	if (fileId.HasTag())
	{
		EnvironmentTag tag(fileId.GetTag());
		FOR_EACH_COLLECTION(i,mValidTagList)
		{
			FileSystemTagItem* tagItem=*i;
			if (tagItem->GetTag()==tag)
			{
				return tagItem->GetOrderItem(fileId);
			}
		}
	}
	else
	{
		FOR_EACH_COLLECTION(i,mValidTagList)
		{
			FileSystemTagItem* tagItem=*i;
			FileSystemOrderItem* orderItem= tagItem->GetOrderItem(fileId);

			if (orderItem!=NULL)
			{
				return orderItem;
			}
		}
	}
	return NULL;
}



bool FileSystem::ContainsOrderItem( const FileId& fileId ) const
{
	return GetOrderItem(fileId)!=NULL;
}


bool FileSystem::GetNameItems( StringRef name,List<FileSystemNameItem*>& outNameItems ) const
{
	FOR_EACH_COLLECTION_STL(i,mTagItems.GetSTLItems())
	{
		FileSystemTagItem* tagItem=i->second;
		FileSystemNameItem* nameItem= tagItem->GetNameItem(name);

		if (nameItem!=NULL)
		{
			outNameItems.Append(nameItem);
		}
	}
	return !outNameItems.IsEmpty();
}


bool FileSystem::IsFileExists( const FileId& fileId ) const
{
	HeapString writeFilePath= GetWriteFilePath(fileId);

	if (!writeFilePath.IsEmpty()&&mFileSystemAccessor->Exists(writeFilePath))
	{
		return true;
	}

	FileSystemOrderItem* orderItem =GetOrderItem(fileId);
	if (orderItem!=NULL)
	{
		RETURN_TRUE_IF(orderItem->HasData());
		size_t fileId=orderItem->GetFileId();
		return !mFileList.GetPath(fileId).IsEmpty();
	}

	return false;
}


HeapString FileSystem::GetReadFilePath( const FileId& fileId ) const
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	if (orderItem!=NULL&&orderItem->HasData())
	{
		return HeapString::Empty;
	}

	HeapString testPath;
	if (orderItem==NULL)
	{
		//test path across file system
		testPath=System::Instance().GetWritablePath(fileId.Name);
		if (!testPath.IsEmpty()&&mFileSystemAccessor->Exists(testPath))
		{
			return testPath;
		}

		//test path across file system
		testPath=System::Instance().GetReadonlyPath(fileId.Name);
		if (!testPath.IsEmpty()&&mFileSystemAccessor->Exists(testPath))
		{
			return testPath;
		}
	}
	else
	{
		testPath=GetWriteFilePath(orderItem->GetFileId());
		if (!testPath.IsEmpty())
		{
			return testPath;
		}

		testPath=GetReadFilePath(orderItem->GetFileId());
		if (!testPath.IsEmpty())
		{
			return testPath;
		}
	}

	return HeapString::Empty;
}


IStream* FileSystem::OpenReadText(const FileId& fileId) const
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	if (orderItem->HasData())
	{
		return new MemoryStream(orderItem->GetData());
	}

	HeapString path=GetReadFilePath(fileId);
	RETURN_NULL_IF_EMPTY(path);
	return new FileStream(path,FileOpenMode::ReadOnly,FileDataType::Text);
}

IStream* FileSystem::OpenReadBinary(const FileId& fileId) const
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	if (orderItem->HasData())
	{
		return new MemoryStream(orderItem->GetData());
	}

	HeapString path=GetReadFilePath(fileId);
	RETURN_NULL_IF_EMPTY(path);
	return new FileStream(path,FileOpenMode::ReadOnly,FileDataType::Binary);
}


HeapString FileSystem::GetReadFilePath( size_t fileId ) const
{
	StringRef path=mFileList.GetPath(fileId);
	if(!path.IsEmpty())
	{
		HeapString testPath=System::Instance().GetReadonlyPath(path);
		if (!testPath.IsEmpty())
		{
            if (mFileSystemAccessor->Exists(testPath))
            {
                return testPath;
            }
            
		}
	}

	return HeapString::Empty;

}


HeapString FileSystem::GetWriteFilePath( const FileId& fileId ) const
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	HeapString testPath;
	if (orderItem==NULL)
	{
		testPath=System::Instance().GetWritablePath(fileId.Name);
		if (!testPath.IsEmpty()&&mFileSystemAccessor->Exists(testPath))
		{
			return testPath;
		}
	}
	else
	{
		if (orderItem->HasData())
		{
			return HeapString::Empty;
		}

		return GetWriteFilePath(orderItem->GetFileId());
	}

	return HeapString::Empty;
}

Medusa::HeapString FileSystem::GetWriteFilePath( size_t fileId ) const
{
	StringRef path=mFileList.GetPath(fileId);
	if(!path.IsEmpty())
	{
		HeapString testPath=System::Instance().GetWritablePath(path);
		if (!testPath.IsEmpty()&&mFileSystemAccessor->Exists(testPath))
		{
			return testPath;
		}
	}
	
	return HeapString::Empty;
}

bool FileSystem::AddMemoryFile( const FileId& fileId,const MemoryByteData& data ,const EnvironmentTag& tag/*=EnvironmentTag::MatchAll*/)
{
	if (ContainsOrderItem(fileId))
	{
		Log::AssertFailedFormat("Duplicate file:%s,%zu",fileId.Name.c_str(),fileId.Order);
		return false;
	}

	FileSystemTagItem* tagItem=GetTagItem(tag);
	if (tagItem==NULL)
	{
		tagItem=new FileSystemTagItem(tag);
		mTagItems.Add(tag,tagItem);
	}

	FileSystemNameItem* nameItem=tagItem->GetNameItem(fileId.Name);
	if (nameItem==NULL)
	{
		nameItem=new FileSystemNameItem(fileId.Name);
		tagItem->AddNameItem(nameItem);
	}

	FileSystemOrderItem* orderItem=new FileSystemOrderItem(fileId.Order,data);
	return nameItem->AddOrderItem(orderItem);
}

FileSystemTagItem* FileSystem::GetTagItem( const EnvironmentTag& tag ) const
{
	return mTagItems.TryGetValueWithFailed(tag,NULL);
}

bool FileSystem::AddTagItem( FileSystemTagItem* tagItem )
{
	return mTagItems.TryAdd(tagItem->GetTag(),tagItem);
}


bool FileSystem::AddFileInFileList(const FileId& fileId,StringRef filePath,StringRef md5/*=StringRef::Empty*/,const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders/*=List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare<::Medusa::CoreProto::FileList_FileCoder> >::Empty*/,const EnvironmentTag& tag/*=EnvironmentTag::MatchAll*/)
{
	size_t id=mFileList.AddNewFile(filePath,md5,StringRef::Empty,coders);
	if (id==Math::UIntMaxValue)
	{
		return false;
	}

	FileSystemTagItem* tagItem=GetTagItem(tag);
	if (tagItem==NULL)
	{
		tagItem=new FileSystemTagItem(tag);
		mTagItems.Add(tag,tagItem);
	}

	FileSystemNameItem* nameItem=tagItem->GetNameItem(fileId.Name);
	if (nameItem==NULL)
	{
		nameItem=new FileSystemNameItem(fileId.Name);
		tagItem->AddNameItem(nameItem);
	}

	FileSystemOrderItem* orderItem=new FileSystemOrderItem(fileId.Order,id);
	return nameItem->AddOrderItem(orderItem);
}

MemoryByteData FileSystem::ReadAllData( const FileId& fileId )
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	if (orderItem!=NULL)
	{
		if (!orderItem->GetData().IsNull())
		{
			return orderItem->GetData();
		}
		size_t fileId=orderItem->GetFileId();
		FileListFileItem* fileItem=mFileList.GetFileItem(fileId);
		if (fileItem!=NULL)
		{
			return mFileSystemAccessor->ReadAllDataPriority(System::Instance().GetWritablePath(fileItem->GetPath()),System::Instance().GetReadonlyPath(fileItem->GetPath()),fileItem->GetCoderList());
		}
	}

	return MemoryByteData::Empty;
}

bool FileSystem::SaveFileData( const FileId& fileId,MemoryByteData data )
{
	FileSystemOrderItem* orderItem=GetOrderItem(fileId);
	if (orderItem!=NULL)
	{
		size_t fileId=orderItem->GetFileId();
		FileListFileItem* fileItem=mFileList.GetFileItem(fileId);
		if (fileItem!=NULL)
		{
			return mFileSystemAccessor->WriteAllDataTo(data,System::Instance().GetWritablePath(fileItem->GetPath()),fileItem->GetCoderList());
		}
	}

	return false;

}


MEDUSA_END;
