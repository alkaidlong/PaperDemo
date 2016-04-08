#include "MedusaCorePreCompiled.h"
#include "FileList.h"
#include "Core/IO/File.h"
#include "Core/Proto/Proto.h"
#include "Core/Coder/XOR/XORDecoder.h"
#include "Core/Coder/LZMA/LZMADecoder.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/Coder/CoderPool.h"

MEDUSA_BEGIN;

FileList::FileList(void)
{
	mVersion=0;
	mMaxAvailableFileId=0;
	mMaxCurrentFileId=-1;
}


FileList::~FileList(void)
{
	Unload();
}


void FileList::Unload()
{
	mVersion=0;
	mMaxAvailableFileId=0;
	mMaxCurrentFileId=-1;
	SAFE_DELETE_DICTIONARY_VALUE(mDirFileDict);
	SAFE_DELETE_DICTIONARY_VALUE(mFileItemIdMap);
	mFileItemNameMap.Clear();
}


bool FileList::LoadFromData(const MemoryByteData& data)
{
	RETURN_FALSE_IF_FALSE(ILoadable::LoadFromData(data));

	CoreProto::FileList fileList;
	bool isSuccess=Proto::ParseFrom(fileList,data);
	RETURN_FALSE_IF_FALSE(isSuccess);

	mVersion.SetMajor(fileList.curversion().major());
	mVersion.SetMinor(fileList.curversion().minor());
	mVersion.SetBuild(fileList.curversion().build());
	mVersion.SetRevision(fileList.curversion().revision());

	FOR_EACH_COLLECTION_STL(i,fileList.dirs())
	{
		const std::string& dir=*i;
		mDirList.Add(HeapString(dir.c_str()));
	}

	FOR_EACH_COLLECTION_STL(i,fileList.files())
	{
		const CoreProto::FileList::FileItem& fileItem=*i;
		int dirIndex=fileItem.dirindex();
		FileListFileItem* item=NULL;
		if (dirIndex>=0)
		{
			item=new FileListFileItem(fileItem.fileid(),dirIndex,mDirList[dirIndex]+fileItem.name(),fileItem.md5(),fileItem.originalname(),fileItem.coders());
		}
		else
		{
			item=new FileListFileItem(fileItem.fileid(),dirIndex,fileItem.name(),fileItem.md5(),fileItem.originalname(),fileItem.coders());
		}

		
		AddFile(item);
	}

	return isSuccess;
}


void FileList::AddFile( FileListFileItem* fileItem )
{
	//We don't check duplicate file id because we trust ResourceLister!
	size_t id=fileItem->GetFileId();
	if ((int)id<=mMaxCurrentFileId)
	{
		Log::AssertFailedFormat("Error file item Id:%zuu <=Max:%d",id,mMaxCurrentFileId);
		return;
	}

	mMaxCurrentFileId=Math::Max((int)id,mMaxCurrentFileId);
	if (mMaxAvailableFileId<(size_t)mMaxCurrentFileId)
	{
		mMaxAvailableFileId=(size_t)mMaxCurrentFileId+1;
	}

	mFileItemIdMap.Add(id,fileItem);
	mFileItemNameMap.Add(fileItem->GetPath(),fileItem);

	int dirIndex=fileItem->GetDirIndex();
	if (dirIndex>=0)
	{
		const HeapString& dir=mDirList[dirIndex];
		if (dirIndex>=0)
		{
			List<FileListFileItem*>* fileItems=mDirFileDict.TryGetValueWithFailed(dir,NULL);
			if (fileItems==NULL)
			{
				fileItems=new List<FileListFileItem*>();
				mDirFileDict.Add(dir,fileItems);
			}

			fileItems->Add(fileItem);
		}
	}

}

StringRef FileList::GetPath( size_t fileId ) const
{
	FileListFileItem* fileItem=mFileItemIdMap.TryGetValueWithFailed(fileId,NULL);
	if (fileItem==NULL)
	{
		return StringRef::Empty;
	}
	return fileItem->GetPath();
}

FileListFileItem* FileList::GetFileItem( size_t fileId ) const
{
	FileListFileItem* fileItem=mFileItemIdMap.TryGetValueWithFailed(fileId,NULL);
	if (fileItem==NULL)
	{
		return NULL;
	}
	return fileItem;
}

size_t FileList::AddNewFile(StringRef filePath,StringRef md5/*=StringRef::Empty*/,StringRef originalName/*=StringRef::Empty*/,
							const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders
							/*=List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >::Empty*/)
{
	if (mFileItemNameMap.ContainsKey(filePath))
	{
		Log::AssertFailedFormat("Duplicate file path:%s",filePath.c_str());
		return Math::UIntMaxValue;
	}

	size_t newId=GenerateNewId();
	FileListFileItem* newFileItem=new FileListFileItem(newId,-1,filePath,originalName,md5,coders);
	AddFile(newFileItem);
	return newId;
}

void FileList::InitializeDefaultCoder( bool isEncrypt,const MemoryByteData& key,bool isCompressed )
{
	if (isEncrypt)
	{
		UserDataEventArg<MemoryByteData> userDataKey(key);
		XORDecoder* xorDecoder=new XORDecoder(userDataKey);
		CoreProto::FileList::FileCoder coderInfo;
		coderInfo.set_type(CoreProto::FileList::FileCoder::XORDecoder);
		CoderPool::Instance().Add(coderInfo,xorDecoder);
		mDefaultFileCoder.Add(xorDecoder);
	}

	if (isCompressed)
	{
		LZMADecoder* lzmaDecoder=new LZMADecoder(IEventArg::Empty);
		CoreProto::FileList::FileCoder coderInfo;
		coderInfo.set_type(CoreProto::FileList::FileCoder::LZMADecoder);
		CoderPool::Instance().Add(coderInfo,lzmaDecoder);
		mDefaultFileCoder.Add(lzmaDecoder);
	}
}

bool FileList::EnumeateFiles(const StringRef& dir,List<FileListFileItem*>& outFiles,bool isRecursively/*=false*/,const StringRef& serarchPattern/*=StringRef::Empty*/) const
{
	if (isRecursively)
	{
		FOR_EACH_COLLECTION(i,mDirList)
		{
			const HeapString& tempDir=*i;
			if (tempDir.BeginWith(dir))
			{
				List<FileListFileItem*>* fileItems=mDirFileDict.TryGetValueWithFailedByOtherKey(tempDir,tempDir.GetHashCode(),NULL);
				RETURN_FALSE_IF_NULL(fileItems);
				outFiles.AddRange(*fileItems);
			}
		}
	}
	else
	{
		List<FileListFileItem*>* fileItems=mDirFileDict.TryGetValueWithFailedByOtherKey(dir,dir.GetHashCode(),NULL);
		RETURN_FALSE_IF_NULL(fileItems);
		outFiles.AddRange(*fileItems);
	}

	return true;
}


MEDUSA_END;
