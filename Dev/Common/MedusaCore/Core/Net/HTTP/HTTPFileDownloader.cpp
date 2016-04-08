#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/HTTPFileDownloader.h"
#include "Core/Log/Log.h"
#include "Core/Utility/MD5.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem/FileSystem.h"

MEDUSA_BEGIN;

HTTPFileDownloader::HTTPFileDownloader(const StringRef& url,const StringRef& localFilePath,const StringRef& md5)
	:IHTTPDownloader(url,md5),mLocalFilePath(localFilePath)
{
	
}

HTTPFileDownloader::~HTTPFileDownloader(void)
{
}


bool HTTPFileDownloader::Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)
{
	mIsSuccess=true;
	FileStream fs;
	if(!fs.OpenNewWriteBinary(mLocalFilePath))
	{
		Log::AssertFailedFormat("Cannot open local file: %s",mLocalFilePath.c_str());
		mIsSuccess=false;
		return false;
	}
	//set url
	curl_easy_setopt(curl,CURLOPT_URL,mUrl.c_str());
	//set write data callback
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&fs);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&WriteDataCallback);
	//show progress
	curl_easy_setopt(curl,CURLOPT_NOPROGRESS,0);
	curl_easy_setopt(curl,CURLOPT_PROGRESSDATA,this);
	curl_easy_setopt(curl,CURLOPT_PROGRESSFUNCTION,&ProgressCallback);
	curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,httpConnectTimeoutSeconds);	//timeout to connect
	curl_easy_setopt(curl,CURLOPT_TIMEOUT,httpReadTimeoutSeconds);			//timeout to download files
	curl_easy_setopt(curl,CURLOPT_LOW_SPEED_LIMIT,httpReadLowSpeedLimit);	
	curl_easy_setopt(curl,CURLOPT_LOW_SPEED_TIME,httpReadLowSpeedTime);


	CURLcode code= curl_easy_perform(curl);
	if(code!=CURLE_OK)
	{
		const char* str=curl_easy_strerror(code);
		Log::LogErrorFormat("CURL error:%s",str);
		mIsSuccess=false;

		return false;
	}

	if (!mMD5Check.IsEmpty())
	{
		fs.Close();
		MemoryByteData data= FileSystem::Instance().GetAccessor().ReadAllData(mLocalFilePath,FileCoderList::Empty);
		if (data.IsNull())
		{
			Log::AssertFailedFormat("Cannot open file path:%s",mLocalFilePath.c_str());
			mIsSuccess=false;
			return false;
		}
		MD5 md5Coder(data.GetData(),data.GetSize());
		HeapString resultMd5=md5Coder.ToString();
		if (resultMd5!=mMD5Check)
		{
			Log::LogErrorFormat("Failed to check MD5 for %s",mUrl.c_str());
			mIsSuccess=false;

			return false;
		}
		else
		{
			Log::LogInfoFormat("MD5 check OK! %s",mUrl.c_str());
			mIsSuccess=true;
		}

	}

	return mIsSuccess;
}


size_t HTTPFileDownloader::WriteDataCallback( void *buffer, size_t size, size_t nmemb, void *user_p )
{
	FileStream* fs=(FileStream*)user_p;
	MemoryByteData data=MemoryByteData::FromStatic((byte*)buffer,size*nmemb);
	size_t resultSize=fs->WriteData(data);
	return resultSize;
}

MEDUSA_END;
