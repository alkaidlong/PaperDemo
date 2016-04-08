#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileList/FileCoderList.h"
#include "Core/Coder/CoderPool.h"
#include "Core/Coder/CoderFactory.h"
#include "Core/Log/Log.h"
#include "Core/Event/EventArg/UserDataEventArg.h"

MEDUSA_BEGIN;




void FileCoderList::Initialize( const ::google::protobuf::RepeatedPtrField< ::Medusa::CoreProto::FileList_FileCoder >& coders )
{
	if (coders.size()<=0)
	{
		return;
	}

	FOR_EACH_COLLECTION_STL(i,coders)
	{
		const CoreProto::FileList::FileCoder& fileCoder=*i;
		ICoder* coder= CoderPool::Instance().TryGetObjectWithFailed(fileCoder,NULL);
		if (coder==NULL)
		{
			Log::LogErrorFormat("Cannot find coder:%d",fileCoder.type());
		}
		else
		{
			Add(coder);
		}
	}
}

void FileCoderList::Initialize(const List< ::Medusa::CoreProto::FileList_FileCoder,NoCompare< ::Medusa::CoreProto::FileList_FileCoder> >& coders)
{
	RETURN_IF_EMPTY(coders);
	FOR_EACH_COLLECTION(i,coders)
	{
		const CoreProto::FileList::FileCoder& fileCoder=*i;
		ICoder* coder= CoderPool::Instance().TryGetObjectWithFailed(fileCoder,NULL);
		if (coder==NULL)
		{
			Log::LogErrorFormat("Cannot find coder:%d",fileCoder.type());
		}
		else
		{
			Add(coder);
		}
	}
}

MemoryByteData FileCoderList::Code( MemoryByteData& data ) const
{
	if (data.IsNull())
	{
		return data;
	}

	MemoryByteData result=data;

	FOR_EACH_COLLECTION(i,*this)
	{
		const ICoder* coder=*i;
		result=coder->CodeSmart(result);
	}

	return result;
}


const FileCoderList FileCoderList::Empty;

MEDUSA_END;
