#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;

class HTTPFileDownloader:public IHTTPDownloader
{
public:
	HTTPFileDownloader(const StringRef& url,const StringRef& localFilePath,const StringRef& md5);
	~HTTPFileDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime);

	StringRef GetLocalFilePath() const { return mLocalFilePath; }
private:

	//************************************
	// 名称:    	WriteDataCallback
	// 返回:   	size_t	返回真正写入的长度，若与传入长度不同，则触发CURLE_WRITE_ERROR
	// 参数: 	void * buffer		
	// 参数: 	size_t size		数据片的长度
	// 参数: 	size_t nmemb		数据片的数量
	// 参数: 	void * user_p		用户指针
	// 功能:		
	// 描述:		
	// 例子:		
	//************************************
	static size_t WriteDataCallback(void *buffer, size_t size, size_t nmemb, void *user_p);
	

protected:
	HeapString mLocalFilePath;
};

MEDUSA_END;
