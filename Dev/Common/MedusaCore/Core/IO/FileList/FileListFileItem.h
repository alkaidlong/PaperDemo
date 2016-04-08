#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/FileList.pb.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/List.h"
#include "Core/IO/FileList/FileCoderList.h"
#include "Core/IO/FileInfo.h"

MEDUSA_BEGIN;

class FileListFileItem
{
public:
	FileListFileItem(){}
	~FileListFileItem(void){}
	FileListFileItem(size_t id,int dirIndex,const StringRef& path,const StringRef& md5,const StringRef& originalName,const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileList_FileCoder >& coders)
		:mFileId(id),mPath(path),mMD5(md5),mOriginalName(originalName),mDirIndex(dirIndex)
	{
		mCoderList.Initialize(coders);
		mFileType=FileInfo::GetType(path);
	}

	FileListFileItem(size_t id,int dirIndex,const StringRef& path,const StringRef& md5,const StringRef& originalName,const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders)
		:mFileId(id),mPath(path),mMD5(md5),mOriginalName(originalName),mDirIndex(dirIndex)
	{
		mCoderList.Initialize(coders);
		mFileType=FileInfo::GetType(path);
	}

	FileListFileItem(size_t id,int dirIndex,const StringRef& path,const StringRef& md5,const StringRef& originalName)
		:mFileId(id),mPath(path),mMD5(md5),mOriginalName(originalName),mDirIndex(dirIndex)
	{
		mFileType=FileInfo::GetType(path);
	}

public:
	StringRef GetPath() const { return mPath; }
	StringRef GetOriginalName() const { return mOriginalName; }

	StringRef GetMD5() const { return mMD5; }
	size_t GetFileId() const { return mFileId; }
	const FileCoderList& GetCoderList() const { return mCoderList; }
	int GetDirIndex() const { return mDirIndex; }
	bool IsImageFile()const{return FileInfo::IsImageFile(mFileType);}
private:
	size_t mFileId;
	int mDirIndex;
	HeapString mPath;
	HeapString mOriginalName;

	HeapString mMD5;
	FileCoderList mCoderList;

	FileType mFileType;
};


MEDUSA_END;
