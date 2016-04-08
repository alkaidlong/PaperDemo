#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/FileId.h"
#include "Core/IO/FileList/FileList.h"
#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/SortedDictionary.h"
#include "Core/Proto/Client/FileSystem.pb.h"
#include "Core/Collection/SortedList.h"
#include "Core/System/Environment.h"
#include "Core/Proto/Proto.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/IO/FileSystem/Accessor/IFileSystemAccessor.h"


MEDUSA_BEGIN;

/*
1.Initialize file aysnc,progress callback
2.cache some files
*/

class FileSystem:public Pattern::Singleton<FileSystem>,public Pattern::ILoadable,public Pattern::IInitializable
{
	friend class Pattern::Singleton<FileSystem>;
private:
	FileSystem(void);
	~FileSystem(void);

public:
	bool Initialize(StringRef fileListName,StringRef fileSystemName);
	virtual bool Uninitialize();
	const IFileSystemAccessor& GetAccessor() const { return *mFileSystemAccessor; }

	virtual bool LoadFromData(const MemoryByteData& data);
	virtual void Unload();

	const Version& GetVersion() const { return mFileList.GetVersion(); }

	HeapString GetReadFilePath(const FileId& fileId)const;
	HeapString GetWriteFilePath(const FileId& fileId)const;
	HeapString GetReadFilePath(size_t fileId)const;
	HeapString GetWriteFilePath(size_t fileId)const;

	IStream* OpenReadText(const FileId& fileId)const;
	IStream* OpenReadBinary(const FileId& fileId)const;


	bool IsFileExists(const FileId& fileId)const;

	void ApplyTag(const EnvironmentTag& tag);

	FileSystemTagItem* GetTagItem(const EnvironmentTag& tag)const;
	bool AddTagItem(FileSystemTagItem* tagItem);

	bool GetNameItems(StringRef name,List<FileSystemNameItem*>& outNameItems)const;
	

	FileSystemOrderItem* GetOrderItem(const FileId& fileId)const;
	bool ContainsOrderItem(const FileId& fileId)const;

	bool AddMemoryFile(const FileId& fileId,const MemoryByteData& data,const EnvironmentTag& tag=EnvironmentTag::MatchAll);
	bool AddFileInFileList(const FileId& fileId,StringRef filePath,StringRef md5=StringRef::Empty,const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders=List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >::Empty,const EnvironmentTag& tag=EnvironmentTag::MatchAll);
public:
	MemoryByteData ReadAllData(const FileId& fileId);
	bool SaveFileData(const FileId& fileId,MemoryByteData data);
	FileList& GetFileList() { return mFileList; }
	const FileList& GetFileList()const { return mFileList; }


	template<typename T>
	bool LoadProto(T& outItem,const FileId& fileId,bool isBinaryFormat=true,bool printItem=false)
	{
		MemoryByteData data=ReadAllData(fileId);

		if(data.IsNull())
		{
			return false;
		}
		bool result=Proto::ParseFrom(outItem,data,isBinaryFormat);

		if (printItem)
		{
			StringRef str=outItem.ShortDebugString();
			Log::LogInfoFormat("%s-->%s",fileId.Name.c_str(),str.c_str());
		}
		

		return result;
	}

	template<typename T>
	bool SaveProto(const T& item,const FileId& fileId,bool isBinaryFormat=true)
	{
		MemoryByteData data=Proto::Serialize(item,isBinaryFormat);

		if(data.IsNull())
		{
			return false;
		}

		return SaveFileData(fileId,data);
	}

private:
	void LoadFileDataAsyncHelper(IEventArg& eventArg);
	void SaveFileDataAsyncHelper(IEventArg& eventArg);
private:
	FileList mFileList;
	SortedDictionary<EnvironmentTag,FileSystemTagItem*> mTagItems;
	List<FileSystemTagItem*> mValidTagList;
	IFileSystemAccessor* mFileSystemAccessor;
};

MEDUSA_END;
