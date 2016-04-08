#include "MedusaCorePreCompiled.h"
#include "FileInfo.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;

StringRef FileInfo::GetExtension( StringRef file )
{
	intp index= file.IndexOf('.');
	if (index>0)
	{
		return file.SubString(index);
	}
	return StringRef::Empty;
}


Medusa::FileType FileInfo::GetType( StringRef filePath )
{
	StringRef ext=GetExtension(filePath);
	return CheckFileType(ext);
}


FileInfo::FileInfo(StringRef filePath):mFullPath(filePath)
{
	MEDUSA_ASSERT_NOT_NULL_OR_EMPTY_STRING(mFullPath,"");

	intp index=mFullPath.LastIndexOf('.');
	if (index>0)
	{
		//this is a file
		size_t length=(size_t)(mFullPath.Length()-index+1);
		filePath.CopyTo(mFileExtension.Buffer(),mFileExtension.Size(),(size_t)(index),length);
		mFileExtension.ForceSetLength(length);
		mFileType=CheckFileType(mFileExtension);


		intp index2= filePath.LastIndexOfAny(Path::DirectorySeparatorChars);
		if (index2>0)
		{
			mFullName= mFullPath.SubString(index2+1);
			mName=mFullPath.SubString(index2+1,index-index2-1);
			mDirectoryPath=mFullPath.SubString(0,index2);
		}
		else
		{
			mFullName=mFullPath;
			mName=mFullPath;
		}
	}
	else
	{
		//this is a directory
		mDirectoryPath=mFullPath;
	}
}


FileInfo::~FileInfo(void)
{
}

FileType FileInfo::CheckFileType( StringRef fileExt )
{
	if (fileExt.IsNullOrEmpty())
	{
		return FileType::Unknown;
	}

	fileExt=fileExt.SubString(1);	//remove '.' at head

	FileType* fileType= mFileExtDict.TryGetValue(fileExt);
	if (fileType!=NULL)
	{
		return *fileType;
	}

	return FileType::Unknown;
}


bool FileInfo::IsImageFile()const
{
	return IsImageFile(mFileType);
}

bool FileInfo::IsImageFile(FileType fileType)
{
	switch(fileType.ToInt())
	{
	case FileType::jpeg.IntValue:
	case FileType::png.IntValue:
	case FileType::pvr.IntValue:
	case FileType::gif.IntValue:
		return true;
	default:
		return false;

	}
}


bool FileInfo::IsShaderFile()const
{
	switch(mFileType.ToInt())
	{
	case FileType::fsh.IntValue:
	case FileType::vsh.IntValue:
		return true;
	default:
		return false;
	}
}

void FileInfo::OnInitFileExtDict()
{
	mFileExtDict.Add(FileType::png.ToString(),FileType::png);
	mFileExtDict.Add(FileType::jpeg.ToString(),FileType::jpeg);
	mFileExtDict.Add(FileType::gif.ToString(),FileType::gif);
	mFileExtDict.Add(FileType::pvr.ToString(),FileType::pvr);
	mFileExtDict.Add(FileType::fsh.ToString(),FileType::fsh);
	mFileExtDict.Add(FileType::vsh.ToString(),FileType::vsh);
	mFileExtDict.Add(FileType::pod.ToString(),FileType::pod);
	mFileExtDict.Add(FileType::pfx.ToString(),FileType::pfx);
	mFileExtDict.Add(FileType::ttf.ToString(),FileType::ttf);
	mFileExtDict.Add(FileType::fnt.ToString(),FileType::fnt);


	//others
	mFileExtDict.Add("jpg",FileType::jpeg);


}

Dictionary<StringRef,FileType> FileInfo::mFileExtDict;

MEDUSA_IMPLEMENT_STATIC_CONSTRUCTOR(FileInfo,OnInitFileExtDict);

MEDUSA_END;