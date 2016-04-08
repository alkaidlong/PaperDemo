#pragma  once

#include "Core/Pattern/ObjectCache.h"
#include "Core/Coder/ICoder.h"
#include "Core/Proto/Client/FileList.pb.h"

MEDUSA_BEGIN;

class FileListFileCoderHashCoder
{
public:
	static intp GetHashCode(const CoreProto::FileList::FileCoder& key)
	{
		return key.type()^key.info();
	}
	
};

class FileListFileCoderComparer
{
public:
	static int Compare(const CoreProto::FileList::FileCoder& t1, const CoreProto::FileList::FileCoder& t2)
	{
		if (t1.type()==t2.type()&&t1.info()==t2.info())
		{
			return 0;
		}
		return -1;
	}

	bool operator()(const CoreProto::FileList::FileCoder& t1, const CoreProto::FileList::FileCoder& t2)const
	{
		return t1.type()==t2.type()&&t1.info()==t2.type();
	}

};


class CoderPool:public Pattern::ObjectCache<CoreProto::FileList::FileCoder,ICoder*,FileListFileCoderHashCoder,FileListFileCoderComparer >
{
private:
	CoderPool()
	{
		
	}
	~CoderPool(){}
public:
	static CoderPool& Instance()
	{
		static CoderPool factory;
		return factory;
	}

};

MEDUSA_END;
