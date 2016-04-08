#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
#include "Core/IO/Stream/FileStream.h"
#include "Core/Log/Log.h"
#include "Core/Utility/MD5.h"
#include "Core/Net/HTTP/SingleDownloadingProgressEventArg.h"

MEDUSA_BEGIN;


IHTTPDownloader::IHTTPDownloader(const StringRef& url,const StringRef& md5)
	:mUrl(url),mMD5Check(md5),mIsSuccess(false)
{
	
}

IHTTPDownloader::~IHTTPDownloader(void)
{
}


void IHTTPDownloader::FireProgressEvent( double total, double now )
{
	if (mProgressHandler.IsValid())
	{
		SingleDownloadingProgressEventArg eventArg(*this,total,now);
		mProgressHandler.Invoke(this,eventArg);
	}
}

int IHTTPDownloader::ProgressCallback( void *clientp, double dltotal, double dlnow, double ultotal, double ulnow )
{
	IHTTPDownloader* downloader=(IHTTPDownloader*)clientp;
	downloader->FireProgressEvent(dltotal,dlnow);
	return 0;
}
MEDUSA_END;
