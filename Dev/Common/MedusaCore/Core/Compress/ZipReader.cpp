#include "MedusaCorePreCompiled.h"
#include "Core/Compress/ZipReader.h"
#include "Core/IO/Path.h"
#include "Core/Log/Log.h"

#ifdef MEDUSA_ZIP
MEDUSA_BEGIN;

ZipReader::ZipReader()
{
	mZipFile=NULL;
}


ZipReader::~ZipReader()
{
	Close();
}

bool ZipReader::Open( StringRef path)
{
	Close();
	mZipFile = unzOpen(path.c_str());
	if (mZipFile!=NULL)
	{
		StackString<Path::MaxPathLength> outFileName;
		unz_file_info64 outFileInfo;

		int err = unzGoToFirstFile64(mZipFile, &outFileInfo,outFileName.c_str(),static_cast<uLong>((outFileName.Size() - 1)*sizeof(char)));
		outFileName.ForceUpdateLength();
		while (err == UNZ_OK)
		{
			unz_file_pos posInfo;
			int posErr = unzGetFilePos(mZipFile, &posInfo);
			if (posErr == UNZ_OK)
			{
				ZipFileInfo entry;
				entry.Pos = posInfo;
				entry.UncompressedSize = (uLong)outFileInfo.uncompressed_size;
				mFileDict.Add(outFileName.ToString(),entry);
			}
			err = unzGoToNextFile64(mZipFile, &outFileInfo,outFileName.c_str(), static_cast<uLong>((outFileName.Size() - 1)*sizeof(char)));
			outFileName.ForceUpdateLength();
		}


		return true;
	}

	return false;
}


void ZipReader::Close()
{
	if (mZipFile!=NULL)
	{
		unzClose(mZipFile);
		mZipFile=NULL;
	}

	mFileDict.Clear();

}

bool ZipReader::Exists(StringRef fileName) const
{
	return mFileDict.ContainsOtherKey(fileName,fileName.GetHashCode());
}

MemoryByteData ZipReader::ReadAllData(StringRef fileName)const
{
	MemoryByteData result;

	if (mZipFile==NULL||fileName.IsEmpty())
	{
		return result;
	}


	ZipFileInfo* zipEntryInfo=mFileDict.TryGetValueByOtherKey(fileName,fileName.GetHashCode());
	if (zipEntryInfo==NULL)
	{
		return result;
	}

	int err = unzGoToFilePos(mZipFile, &zipEntryInfo->Pos);
	if (err!=UNZ_OK)
	{
		return result;
	}

	err = unzOpenCurrentFile(mZipFile);
	if (err!=UNZ_OK)
	{
		return result;
	}

	result=MemoryByteData::Alloc(zipEntryInfo->UncompressedSize);
	int readSize = unzReadCurrentFile(mZipFile, result.GetData(), (uint)zipEntryInfo->UncompressedSize);
	Log::Assert(readSize==(int)zipEntryInfo->UncompressedSize,"Invalid zip file size.");	//readSize could be 0 because we may have zero file such as "StringTable-enus.bin"
	unzCloseCurrentFile(mZipFile);

	return result;
}


MEDUSA_END;
#endif

