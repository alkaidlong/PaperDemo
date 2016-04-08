#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
#include "Core/Net/HTTP/HTTPClient.h"

MEDUSA_BEGIN;

class GlobalDownloadingProgressEventArg:public IEventArg
{
public:
	GlobalDownloadingProgressEventArg(const HTTPClient& client,const IHTTPDownloader& downloader,size_t total,size_t current)
		:mClient(client),mDownloader(downloader),mTotal(total),mCurrent(current),mIsContinue(true)
	{

	}
	virtual ~GlobalDownloadingProgressEventArg(void){}

	bool IsContinue() const { return mIsContinue; }
	void SetIsContinue(bool val) { mIsContinue = val; }

	size_t GetTotal() const { return mTotal; }
	size_t GetCurrent() const { return mCurrent; }
	float GetPercent()const{return (float)mCurrent/mTotal;}
	const HTTPClient& GetClient() const { return mClient; }
	const IHTTPDownloader& GetDownloader() const { return mDownloader; }

protected:
	const size_t mTotal;
	const size_t mCurrent;
	bool mIsContinue;
	const HTTPClient& mClient;
	const IHTTPDownloader& mDownloader;
};


MEDUSA_END;
