#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/UpdateServer.pb.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/Proto/Client/FileUpdateList.pb.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/Singleton.h"
#include "Core/IO/FileList/FileList.h"
#include "Core/Net/HTTP/HTTPClient.h"
#include "Core/IO/Updater/UpdaterDefines.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;


class FileUpdater:public Pattern::Singleton<FileUpdater>,public Pattern::IInitializable
{
public:
	enum class MessageType
	{
		NetworkError,
		DontUpgragde,
		ServerMaintain,
		IncompatiableClient,
		SeverError,
		DownloadingInterrupted
	};
private:
	friend class Pattern::Singleton<FileUpdater>;
	FileUpdater();
	~FileUpdater(void);
public:
	typedef Pattern::Delegate<void (FileUpdater* sender,FileDownloadingProgressEventArg)> FileDownloadingProgressEventHandler;
	typedef Pattern::Delegate<void (FileUpdater* sender,MessageType message)> ShowMessageEventHandler;
	typedef Pattern::Delegate<void (FileUpdater* sender,ResourceCheckingResult)> ServerStatusEventHandler;
	typedef Pattern::Delegate<void (FileUpdater* sender,ServerStatusEventHandler)> BeginServerStatusEventHandler;

	typedef Pattern::Delegate<void (FileUpdater* sender,IEventArg)> CompleteUpdatingEventHandler;
	typedef Pattern::Delegate<void (FileUpdater* sender,KeyValuePair<FileDownloadingProgressEventHandler,CompleteUpdatingEventHandler>)> BeginUpdatingEventHandler;

	bool Initialize(const Version& clientVersion,StringRef url,StringRef serverConfigName,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime);
	bool Uninitialize();
public:
	void SetShowMessageHandler(ShowMessageEventHandler val) { mShowMessageHandler = val; }

	StringRef GetUpdateServerUrl() const { return mUpdateServerUrl; }
	StringRef GetServerConfigName() const { return mServerConfigName; }

	void UpdateServerStatusAsync(ServerStatusEventHandler completeHandler);

	void UpdateServerStatus(ServerStatusEventHandler serverStatusHandler);

	void BeginUpdatingAsync(FileDownloadingProgressEventHandler progressHandler,CompleteUpdatingEventHandler completeHandler);
	void BeginUpdating(FileDownloadingProgressEventHandler progressHandler,CompleteUpdatingEventHandler completeHandler);

	bool IsServerAvailable()const;
	const Medusa::CoreProto::Version& GetServerMinVersion()const{return mServer.minversion();}
	const Medusa::CoreProto::Version& GetServerCurrentVersion()const{return mServer.curversion();}
	bool IsNeedUpdating();
	bool IsChecked()const;

	ResourceCheckingResult GetCheckingStatus(void){return mCheckingStatus;}

private:
	void OnUpdateServerStatus(FileUpdater* sender,ServerStatusEventHandler serverStatusHandler);
	void OnBeginUpdating(FileUpdater* sender,KeyValuePair<FileDownloadingProgressEventHandler,CompleteUpdatingEventHandler> eventArg);


	void OnDownloadServerConfig(HTTPClient* sender,GlobalDownloadingProgressEventArg& eventArg);
	void OnDownloadFileListConfig(HTTPClient* sender,GlobalDownloadingProgressEventArg& eventArg);
	void OnDownloadFile(HTTPClient* sender,GlobalDownloadingProgressEventArg& eventArg);


	bool DownloadServerFileList();
	bool GenerateUpdatingList();
	bool ContinueUpdating();
	bool ApplyNewFiles();

	void FireUpdaingProgressEvent(size_t total,size_t current);
	void FireCompleteUpdatingEvent(bool isSuccess);
	void FireServerStatusEvent(ResourceCheckingResult result);
	void FireMessageEvent(MessageType msg);

	void SaveUpdateList();
	void CleanUpdateList();

private:
	void AddUpdateTask(StringRef path,StringRef md5);
private:
	ResourceCheckingResult mCheckingStatus;
	CoreProto::FileUpdateList* mUpdateList;


	HeapString mUpdateServerUrl;	//like "http://192.168.10.33/"
	HeapString mServerConfigName;	//default "Server.bin"
	size_t mHTTPConnectTimeoutSeconds;
	size_t mHTTPReadTimeoutSeconds;
	size_t mHTTPReadLowSpeedLimit;
	size_t mHTTPReadLowSpeedTime;


	CoreProto::UpdateServer mServer;
	HTTPClient mHTTPClient;

	FileDownloadingProgressEventHandler mProgressHandler;
	CompleteUpdatingEventHandler mCompleteUpdatingHandler;
	ServerStatusEventHandler mServerStatusHandler;
	ShowMessageEventHandler mShowMessageHandler;

	FileList mNewFileList;

	const static HeapString mUpdateListFileName;
	const static HeapString mFileListFilePath;



};

MEDUSA_END;
