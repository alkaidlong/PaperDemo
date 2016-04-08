#include "MedusaCorePreCompiled.h"
#include "Core/IO/Updater/FileUpdater.h"
#include "Core/Proto/Proto.h"
#include "Core/Event/ThreadEventDispatcher.h"
#include "Core/System/Environment.h"
#include "Core/IO/FileSystem/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Net/HTTP/GlobalDownloadingProgressEventArg.h"
#include "Core/Net/HTTP/SingleDownloadingProgressEventArg.h"
#include "Core/Net/HTTP/HTTPMemoryDownloader.h"
#include "Core/Net/HTTP/HTTPFileDownloader.h"
#include "Core/IO/Directory.h"
#include "Core/Event/UIEventDispatcher.h"
#include "Core/IO/Updater/FileDownloadingProgressEventArg.h"
#include "Core/IO/Updater/ServerStatusEventArg.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#include "Core/System/System.h"
#include "Core/IO/Path.h"


MEDUSA_BEGIN;

FileUpdater::FileUpdater()
{
	mUpdateList=NULL;
	mHTTPConnectTimeoutSeconds=8;	//default 8 seconds
	mHTTPReadTimeoutSeconds=180;	//default 3 minutes
	mHTTPReadLowSpeedLimit=10;	//8b/s
	mHTTPReadLowSpeedTime=5;	//5s
}

FileUpdater::~FileUpdater(void)
{

}

bool FileUpdater::Initialize(const Version& clientVersion,StringRef url,StringRef serverConfigName,size_t httpConnectTimeoutSeconds,size_t httpReadTimeoutSeconds,size_t httpReadLowSpeedLimit,size_t httpReadLowSpeedTime)
{
	HTTPClient::Initialize();
	mUpdateServerUrl=url;
	mServerConfigName=serverConfigName;
	mHTTPConnectTimeoutSeconds=httpConnectTimeoutSeconds;
	mHTTPReadTimeoutSeconds=httpReadTimeoutSeconds;
	mHTTPReadLowSpeedLimit=httpReadLowSpeedLimit;
	mHTTPReadLowSpeedTime=httpReadLowSpeedTime;
	

	HeapString path=System::Instance().GetWritablePath(mUpdateListFileName);
	MemoryByteData data=FileSystem::Instance().GetAccessor().ReadAllData(path,FileCoderList::Empty);
	RETURN_FALSE_IF(data.IsNull());
	mUpdateList=new CoreProto::FileUpdateList();
	Proto::ParseFrom(*mUpdateList,data);

	Version updateListVersion(mUpdateList->version().major(),mUpdateList->version().minor(),mUpdateList->version().build(),mUpdateList->version().revision());
	if (updateListVersion<=clientVersion)
	{
		Log::LogInfoFormat("Initialize::Updating version:%s <= client version:%s.Maybe he upgrade the client mantual!",updateListVersion.ToString().c_str(),clientVersion.ToString().c_str());
		CleanUpdateList();
		return false;
	}
	return true;
}

bool FileUpdater::Uninitialize()
{
	HTTPClient::Uninitialize();
	SAFE_DELETE(mUpdateList);
	return true;
}


void FileUpdater::UpdateServerStatusAsync( ServerStatusEventHandler serverStatusHandler )
{
	ThreadEventDispatcher::Instance().FireEvent(BeginServerStatusEventHandler(this,&FileUpdater::OnUpdateServerStatus),this,serverStatusHandler);
}

void FileUpdater::OnUpdateServerStatus(FileUpdater* sender,ServerStatusEventHandler serverStatusHandler )
{
	UpdateServerStatus(serverStatusHandler);
}

void FileUpdater::UpdateServerStatus(ServerStatusEventHandler serverStatusHandler)
{
	mServerStatusHandler=serverStatusHandler;

	if (!Environment::Instance().IsNetworkAvailable())
	{
		FireMessageEvent(MessageType::NetworkError);	
		FireServerStatusEvent(ResourceCheckingResult::NetworkError);
		return;
	}

	HeapString url=mUpdateServerUrl+mServerConfigName;
	mHTTPClient.SetGlobalProgessHandler(HTTPClient::GlobalDownloadingProgressEventHandler(this,&FileUpdater::OnDownloadServerConfig));
	mHTTPClient.SetHTTPConnectTimeoutSeconds(mHTTPConnectTimeoutSeconds);
	mHTTPClient.SetHTTPReadTimeoutSeconds(mHTTPReadTimeoutSeconds);
	mHTTPClient.SetHTTPReadLowSpeedLimit(mHTTPReadLowSpeedLimit);
	mHTTPClient.SetHTTPReadLowSpeedTime(mHTTPReadLowSpeedTime);
	mHTTPClient.AddMemoryTask(url,"");
	if(mHTTPClient.Run())
	{
		//if success at this time, server config has been initialized

		if (mServer.status()==CoreProto::UpdateServer_UpdateServerStatus_DontUpgrade)
		{
			FireMessageEvent(MessageType::DontUpgragde);
			FireServerStatusEvent(ResourceCheckingResult::CientAlreadyNewest);
			return;
		}

		if(mServer.status()==CoreProto::UpdateServer_UpdateServerStatus_Error||mServer.status()==CoreProto::UpdateServer_UpdateServerStatus_Maintain)
		{
			FireMessageEvent(MessageType::ServerMaintain);

			FireServerStatusEvent(ResourceCheckingResult::ServerUnavailable);
			return;
		}

		Version serverCurVersion(mServer.curversion().major(),mServer.curversion().minor(),mServer.curversion().build(),mServer.curversion().revision());
		Version serverMinVersion(mServer.minversion().major(),mServer.minversion().minor(),mServer.minversion().build(),mServer.minversion().revision());

		if (serverCurVersion<serverMinVersion)
		{
			Log::LogErrorFormat("Server min version:%s > cur version:%s",serverMinVersion.ToString().c_str(),serverMinVersion.ToString().c_str());
			FireMessageEvent(MessageType::ServerMaintain);

			FireServerStatusEvent(ResourceCheckingResult::ServerUnavailable);

			return;
		}

		Version clientVersion=FileSystem::Instance().GetVersion();
		if (clientVersion<serverMinVersion)
		{
			Log::LogErrorFormat("Client version:%s < server min version:%s.Maybe the server just roll back the version stupidly.",clientVersion.ToString().c_str(),serverMinVersion.ToString().c_str());
			FireMessageEvent(MessageType::IncompatiableClient);
			FireServerStatusEvent(ResourceCheckingResult::ClientUncompatiable);

			return;
		}
		else if (clientVersion>serverCurVersion)
		{
			Log::LogInfoFormat("Client version:%s > server cur version:%s.Maybe the client has been upgraded manually.",clientVersion.ToString().c_str(),serverCurVersion.ToString().c_str());
			CleanUpdateList();
			FireServerStatusEvent(ResourceCheckingResult::CientAlreadyNewest);
			return;
		}
		else if (clientVersion==serverCurVersion)
		{
			if (mUpdateList!=NULL)
			{
				Log::LogError("There's a UpdatingList when client is newest.Maybe the server just roll back the version stupidly.");
				CleanUpdateList();
			}
			Log::LogInfoFormat("Client version:%s is the newest!",clientVersion.ToString().c_str());
			FireServerStatusEvent(ResourceCheckingResult::CientAlreadyNewest);
			return;
		}
		else
		{
			if (mUpdateList!=NULL)
			{
				Version updateListVersion(mUpdateList->version().major(),mUpdateList->version().minor(),mUpdateList->version().build(),mUpdateList->version().revision());

				if (updateListVersion<serverCurVersion)
				{
					Log::LogInfoFormat("Updating version:%s < server cur version:%s.Need to upgrade to newer version.",updateListVersion.ToString().c_str(),serverCurVersion.ToString().c_str());
					CleanUpdateList();
					FireServerStatusEvent(ResourceCheckingResult::ClientNeedNewUpdating);
					return;
				}
				else if (updateListVersion==serverCurVersion)
				{
					FireServerStatusEvent(ResourceCheckingResult::ClientNeedContinueUpdating);
					return;
				} 
				else
				{
					Log::LogErrorFormat("Updating version:%s > server cur version:%s.Maybe the server just roll back the version stupidly.Try to start a new updading",updateListVersion.ToString().c_str(),serverCurVersion.ToString().c_str());
					CleanUpdateList();
					FireServerStatusEvent(ResourceCheckingResult::ClientNeedNewUpdating);
					return;
				}
			}
			else
			{
				FireServerStatusEvent(ResourceCheckingResult::ClientNeedNewUpdating);
				return;
			}
		}
	}
	else
	{
		FireMessageEvent(MessageType::SeverError);	
		FireServerStatusEvent(ResourceCheckingResult::ServerConfigError);
		return;
	}
}

void FileUpdater::BeginUpdatingAsync( FileDownloadingProgressEventHandler progressHandler,CompleteUpdatingEventHandler completeHandler )
{
	KeyValuePair<FileDownloadingProgressEventHandler,CompleteUpdatingEventHandler> handlers(progressHandler,completeHandler);
	ThreadEventDispatcher::Instance().FireEvent(BeginUpdatingEventHandler(this,&FileUpdater::OnBeginUpdating),this,handlers);
}

void FileUpdater::OnBeginUpdating(FileUpdater* sender,KeyValuePair<FileDownloadingProgressEventHandler,CompleteUpdatingEventHandler> eventArg )
{
	BeginUpdating(eventArg.Key,eventArg.Value);
}

void FileUpdater::BeginUpdating(FileDownloadingProgressEventHandler progressHandler,CompleteUpdatingEventHandler completeHandler)
{
	Log::Assert(IsNeedUpdating(),"Error invoke BeginUpdatingAsync when no need to do updating");
	mProgressHandler=progressHandler;
	mCompleteUpdatingHandler=completeHandler;
	
	if (mCheckingStatus==ResourceCheckingResult::ClientNeedNewUpdating)
	{
		if(!DownloadServerFileList())
		{
			Log::LogError("Failed to download FileSystem.bin");
			FireCompleteUpdatingEvent(false);
			return;
		}
		if(!GenerateUpdatingList())
		{
			Log::LogError("Failed to GenerateUpdatingList");
			FireCompleteUpdatingEvent(false);
			return;
		}
	}

	if(!ContinueUpdating())
	{
		Log::LogError("Failed to download all files");
		FireCompleteUpdatingEvent(false);
		return;
	}

	if(!ApplyNewFiles())
	{
		Log::LogError("Failed to apply new files");
		FireCompleteUpdatingEvent(false);
		return;
	}

	//should notify other models to reload,like resource manager,face war config
	FireCompleteUpdatingEvent(true);

}


bool FileUpdater::DownloadServerFileList()
{
	HeapString url=Path::CombineNoChecks(mUpdateServerUrl,mFileListFilePath);
	HeapString localPath=System::Instance().GetTempPath(mFileListFilePath);
	mHTTPClient.SetGlobalProgessHandler(HTTPClient::GlobalDownloadingProgressEventHandler(this,&FileUpdater::OnDownloadFileListConfig));
	mHTTPClient.SetHTTPConnectTimeoutSeconds(mHTTPConnectTimeoutSeconds);
	mHTTPClient.SetHTTPReadTimeoutSeconds(mHTTPReadTimeoutSeconds);
	mHTTPClient.SetHTTPReadLowSpeedLimit(mHTTPReadLowSpeedLimit);
	mHTTPClient.SetHTTPReadLowSpeedTime(mHTTPReadLowSpeedTime);
	mHTTPClient.AddFileTask(url,localPath,"");
	if(mHTTPClient.Run())
	{
		return true;
	}
	else
	{
		FireMessageEvent(MessageType::SeverError);
		return false;
	}
}


void FileUpdater::OnDownloadServerConfig( HTTPClient* sender,GlobalDownloadingProgressEventArg& eventArg )
{
	if(mHTTPClient.IsResponseOK())
	{
		const HTTPMemoryDownloader& memoryDownloader=(const HTTPMemoryDownloader&)eventArg.GetDownloader();
		if (memoryDownloader.IsSuccess())
		{
			const std::vector<byte>& data= memoryDownloader.GetData();
			Proto::ParseFrom(mServer,MemoryByteData::FromStatic((byte*)data.data(),data.size()));
		}
	}
	
}


void FileUpdater::OnDownloadFileListConfig(HTTPClient* sender, GlobalDownloadingProgressEventArg& eventArg )
{
	if(mHTTPClient.IsResponseOK())
	{
		const HTTPFileDownloader& downloader=(const HTTPFileDownloader&)eventArg.GetDownloader();
		if (downloader.IsSuccess())
		{
			StringRef localFilePath=downloader.GetLocalFilePath();
			mNewFileList.LoadFromFile(localFilePath,FileSystem::Instance().GetFileList().GetDefaultFileCoder());
		}
	}
}

void FileUpdater::OnDownloadFile(HTTPClient* sender, GlobalDownloadingProgressEventArg& eventArg )
{
	if(mHTTPClient.IsResponseOK())
	{
		const HTTPFileDownloader& downloader=(const HTTPFileDownloader&)eventArg.GetDownloader();
		if (downloader.IsSuccess()&&mUpdateList!=NULL)
		{
			mUpdateList->mutable_items()->RemoveLast();
			SaveUpdateList();
			FireUpdaingProgressEvent(eventArg.GetTotal(),eventArg.GetCurrent());
		}
	}
}

bool FileUpdater::GenerateUpdatingList()
{
	RETURN_FALSE_IF_FALSE(mNewFileList.IsValid());
	//compare current file system and temp file system
	//const FileList& currentFileList=FileSystem::Instance().GetFileList();
	const Dictionary<HeapString,FileListFileItem*>& currentFileItems=FileSystem::Instance().GetFileList().GetFileItemNameMap();
	const Dictionary<HeapString,FileListFileItem*>& newFileItems=mNewFileList.GetFileItemNameMap();

	if (mUpdateList!=NULL)
	{
		Log::AssertFailed("Not clean updating list before GenerateUpdatingList");
		CleanUpdateList();
	}

	mUpdateList=new CoreProto::FileUpdateList();
	const Version& newVersion=mNewFileList.GetVersion();

	mUpdateList->mutable_version()->set_major(newVersion.Major());
	mUpdateList->mutable_version()->set_minor(newVersion.Minor());
	mUpdateList->mutable_version()->set_build(newVersion.Build());
	mUpdateList->mutable_version()->set_revision(newVersion.Revision());


	FOR_EACH_COLLECTION(i,newFileItems)
	{
		FileListFileItem* newFileItem=(*i).Value;
		FileListFileItem* currentFileItem=currentFileItems.TryGetValueWithFailed(newFileItem->GetPath(),NULL);
		if (currentFileItem==NULL)
		{
			//this is a new file
			AddUpdateTask(newFileItem->GetPath(),newFileItem->GetMD5());
		}
		else
		{
			if (newFileItem->GetMD5()!=currentFileItem->GetMD5())
			{
				//file has changed
				AddUpdateTask(newFileItem->GetPath(),newFileItem->GetMD5());
			}
		}
	}


	if (mUpdateList->items().size()==0)
	{
		CleanUpdateList();
		Log::LogInfoFormat("No file changes.");
		return true;
	}

	//save update list
	SaveUpdateList();

	//release new file system as we no longer need it
	mNewFileList.Unload();
	return true;

}

bool FileUpdater::ContinueUpdating()
{
	if (mUpdateList==NULL)
	{
		Log::LogInfoFormat("No file changes.");
		return true;
	}

	//reverse add file task so that we can always remove the last one
	FOR_EACH_COLLECTION_BEGIN_END(i,mUpdateList->items().rbegin(),mUpdateList->items().rend())
	{
		const CoreProto::FileUpdateItem& updateFileItem=*i;
		HeapString url=Path::CombineNoChecks(mUpdateServerUrl,updateFileItem.path());
		HeapString localFilePath=System::Instance().GetTempPath(updateFileItem.path());
		mHTTPClient.AddFileTask(url,localFilePath,updateFileItem.md5());
	}

	mHTTPClient.SetGlobalProgessHandler(HTTPClient::GlobalDownloadingProgressEventHandler(this,&FileUpdater::OnDownloadFile));
	mHTTPClient.SetHTTPConnectTimeoutSeconds(mHTTPConnectTimeoutSeconds);
	mHTTPClient.SetHTTPReadTimeoutSeconds(mHTTPReadTimeoutSeconds);
	mHTTPClient.SetHTTPReadLowSpeedLimit(mHTTPReadLowSpeedLimit);
	mHTTPClient.SetHTTPReadLowSpeedTime(mHTTPReadLowSpeedTime);
	if(mHTTPClient.Run())
	{
		CleanUpdateList();
		mCheckingStatus=ResourceCheckingResult::CientAlreadyNewest;
		return true;
	}
	else
	{
		FireMessageEvent(MessageType::DownloadingInterrupted);
		return false;
	}


	return true;
}

bool FileUpdater::IsServerAvailable() const
{
	return mCheckingStatus==ResourceCheckingResult::CientAlreadyNewest;
}
bool FileUpdater::IsNeedUpdating()
{
	return mCheckingStatus==ResourceCheckingResult::ClientNeedNewUpdating||mCheckingStatus==ResourceCheckingResult::ClientNeedContinueUpdating;
}


void FileUpdater::FireUpdaingProgressEvent(size_t total,size_t current)
{
	if (mProgressHandler.IsValid())
	{
		UIEventDispatcher::Instance().FireEventAsync(mProgressHandler,this,FileDownloadingProgressEventArg(total,current));
	}
}

void FileUpdater::FireCompleteUpdatingEvent(bool isSuccess)
{
	if (mCompleteUpdatingHandler.IsValid())
	{
		UIEventDispatcher::Instance().FireEventAsync(mCompleteUpdatingHandler,this,IEventArg::Empty);
	}
}

void FileUpdater::FireServerStatusEvent( ResourceCheckingResult result )
{
	mCheckingStatus=result;
	if (mServerStatusHandler.IsValid())
	{
		UIEventDispatcher::Instance().FireEventAsync(mServerStatusHandler,this,result);
	}
}

void FileUpdater::FireMessageEvent( MessageType msg )
{
	if (mShowMessageHandler.IsValid())
	{
		UIEventDispatcher::Instance().FireEventAsync(mShowMessageHandler,this,msg);
	}
}

void FileUpdater::AddUpdateTask( StringRef path,StringRef md5 )
{
	LOG_ASSERT_NOT_NULL(mUpdateList);

	CoreProto::FileUpdateItem* fileItem=mUpdateList->add_items();
	fileItem->set_path(path.c_str());
	fileItem->set_md5(md5.c_str());
}


void FileUpdater::SaveUpdateList()
{
	MemoryByteData data=Proto::Serialize(*mUpdateList);
	HeapString path=System::Instance().GetTempPath(mUpdateListFileName);
	FileSystem::Instance().GetAccessor().WriteAllDataTo(data,path,FileCoderList::Empty);
}

void FileUpdater::CleanUpdateList()
{
	SAFE_DELETE(mUpdateList);
	HeapString path=System::Instance().GetTempPath(mUpdateListFileName);
	FileSystem::Instance().GetAccessor().Delete(path);
}

bool FileUpdater::ApplyNewFiles()
{
	Directory::Move(System::Instance().GetTempPath(),System::Instance().GetWritablePath());
	return true;
}


bool FileUpdater::IsChecked() const
{
	return mCheckingStatus!=ResourceCheckingResult::NetworkError;
}

const HeapString FileUpdater::mUpdateListFileName=HeapString("ResourceUpdateList.bin");
const HeapString FileUpdater::mFileListFilePath=HeapString("FileList.bin");

MEDUSA_END;
