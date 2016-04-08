#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"


MEDUSA_BEGIN;

class IHTTPDownloader
{
public:
	typedef Pattern::Delegate<void (IHTTPDownloader* sender,SingleDownloadingProgressEventArg&)> SingleDownloadingProgressEventHandler;

	IHTTPDownloader(const StringRef& url,const StringRef& md5);
	virtual ~IHTTPDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)=0;

	bool IsSuccess() const { return mIsSuccess; }
	StringRef GetUrl() const { return mUrl; }

	SingleDownloadingProgressEventHandler GetProgressHandler() const { return mProgressHandler; }
	void SetProgressHandler(SingleDownloadingProgressEventHandler val) { mProgressHandler = val; }
protected:
	//************************************
	// 名称:    	ProgressCallback
	// 返回:   	int					non-zero to abort transfer and return CURLE_ABORTED_BY_CALLBACK
	// 参数: 	void * clientp		用户指针
	// 参数: 	double dltotal		下载total
	// 参数: 	double dlnow		下载now
	// 参数: 	double ultotal		上传total
	// 参数: 	double ulnow		上传now
	// 功能:		
	// 描述:		
	// 例子:		
	//************************************
	static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	void FireProgressEvent(double total, double now);
protected:
	HeapString mUrl;
	HeapString mMD5Check;
	bool mIsSuccess;

	SingleDownloadingProgressEventHandler mProgressHandler;

};

MEDUSA_END;
