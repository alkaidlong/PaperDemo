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
	// ����:    	WriteDataCallback
	// ����:   	size_t	��������д��ĳ��ȣ����봫�볤�Ȳ�ͬ���򴥷�CURLE_WRITE_ERROR
	// ����: 	void * buffer		
	// ����: 	size_t size		����Ƭ�ĳ���
	// ����: 	size_t nmemb		����Ƭ������
	// ����: 	void * user_p		�û�ָ��
	// ����:		
	// ����:		
	// ����:		
	//************************************
	static size_t WriteDataCallback(void *buffer, size_t size, size_t nmemb, void *user_p);
	

protected:
	HeapString mLocalFilePath;
};

MEDUSA_END;
