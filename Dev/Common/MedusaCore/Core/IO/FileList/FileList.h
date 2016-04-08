#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/FileList/FileListFileItem.h"
#include "Core/IO/FileId.h"
#include "Core/Log/Log.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/ILoadable.h"
#include "Core/Utility/Version.h"

/*
1.Load file aysnc,progress callback
2.cache some files
*/

MEDUSA_BEGIN;

class FileList:public Pattern::ILoadable
{
public:
	FileList(void);
	~FileList(void);
public:
	size_t GenerateNewId(){return mMaxAvailableFileId++;}
	virtual bool LoadFromData(const MemoryByteData& data);
	virtual void Unload();

	StringRef GetPath(size_t fileId)const;
	FileListFileItem* GetFileItem(size_t fileId)const;
	const Dictionary<size_t,FileListFileItem*>& GetFileItemIdMap() const { return mFileItemIdMap; }
	const Dictionary<HeapString,FileListFileItem*>& GetFileItemNameMap() const { return mFileItemNameMap; }

	const Version& GetVersion() const { return mVersion; }
	bool IsValid()const{return !mFileItemIdMap.IsEmpty();}
	void AddFile(FileListFileItem* fileItem);

	size_t AddNewFile(StringRef filePath,StringRef md5=StringRef::Empty,StringRef originalName=StringRef::Empty,const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders=List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >::Empty);
	Medusa::FileCoderList& GetDefaultFileCoder() { return mDefaultFileCoder; }
	void InitializeDefaultCoder(bool isEncrypt,const MemoryByteData& key,bool isCompressed);

	bool EnumeateFiles(const StringRef& dir,List<FileListFileItem*>& outFiles,bool isRecursively=false,const StringRef& serarchPattern=StringRef::Empty)const;

	
private:
	Version mVersion;
	List<HeapString> mDirList;
	Dictionary<HeapString,List<FileListFileItem*>*> mDirFileDict;

	Dictionary<size_t,FileListFileItem*> mFileItemIdMap;
	Dictionary<HeapString,FileListFileItem*> mFileItemNameMap;

	size_t mMaxAvailableFileId;
	int mMaxCurrentFileId;

	FileCoderList mDefaultFileCoder;
};

MEDUSA_END;
