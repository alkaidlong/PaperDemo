#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class SingleDownloadingProgressEventArg:public IEventArg
{
public:
	SingleDownloadingProgressEventArg(const IHTTPDownloader& downloader,double total,double current)
		:mDownloader(downloader),mTotal(total),mCurrent(current)
	{

	}
	virtual ~SingleDownloadingProgressEventArg(void){}

	const double GetTotal() const { return mTotal; }
	const double GetCurrent() const { return mCurrent; }
	const IHTTPDownloader& GetDownloader() const { return mDownloader; }

protected:
	const double mTotal;
	const double mCurrent;
	const IHTTPDownloader& mDownloader;
};

MEDUSA_END;

