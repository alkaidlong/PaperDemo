#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;
class FileDownloadingProgressEventArg:public IEventArg
{
public:
	FileDownloadingProgressEventArg(size_t total,size_t current)
		:mTotal(total),mCurrent(current),mIsContinue(true)
	{

	}
	virtual ~FileDownloadingProgressEventArg(void){}

	bool IsContinue() const { return mIsContinue; }
	void SetIsContinue(bool val) { mIsContinue = val; }

	size_t GetTotal() const { return mTotal; }
	size_t GetCurrent() const { return mCurrent; }
	float GetPercent()const{return ((float)mCurrent)/mTotal*100.f;}

protected:
	const size_t mTotal;
	const size_t mCurrent;
	bool mIsContinue;
};

MEDUSA_END;