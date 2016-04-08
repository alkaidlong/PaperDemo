#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Net/HTTP/IHTTPDownloader.h"
MEDUSA_BEGIN;

class HTTPMemoryDownloader:public IHTTPDownloader
{
public:
	HTTPMemoryDownloader(const StringRef& url,const StringRef& md5);
	~HTTPMemoryDownloader(void);

	virtual bool Run(CURL* curl,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime);
	const std::vector<byte>& GetData() const { return mData; }

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
	std::vector<byte> mData;
};

MEDUSA_END;
