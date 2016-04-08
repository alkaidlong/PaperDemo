#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/Proto/Client/FileSystem.pb.h"
#include "Core/System/EnvironmentTag.h"

MEDUSA_BEGIN;

class FileId
{
public:
	FileId():Order(0),mTag(0){}
	FileId(const StringRef& name,size_t order=0):Name(name),Order(order),mTag(0){}

	template<uint TSize>
	FileId(const StackString<TSize>& name,size_t order=0):Name(name),Order(order),mTag(0){}

	FileId(const HeapString& name,size_t order=0):Name(name),Order(order),mTag(0){}
	FileId(const char* name,size_t order=0):Name(name),Order(order),mTag(0){}
	FileId(const CoreProto::FileId& fileId):Name(fileId.name()),Order(fileId.order()),mTag(fileId.tag()){}
	FileId(const std::basic_string<char, std::char_traits<char>, std::allocator<char> >& str,size_t order=0):Name(str),Order(order),mTag(0){}

	~FileId(){}
	bool operator<(const FileId& fileId)const
	{
		if (Order<fileId.Order)
		{
			return true;
		}
		else if (Order==fileId.Order)
		{
			return Name<fileId.Name;
		}

		return false;
	}
	void operator=(const FileId& fileId){Name = fileId.Name;Order = fileId.Order;mTag = fileId.mTag;}
	bool operator==(const FileId& fileId)const{return Name==fileId.Name && Order == fileId.Order && mTag == fileId.mTag;}
	bool operator!=(const FileId& fileId)const{return Name!=fileId.Name || Order != fileId.Order||mTag != fileId.mTag;}
	bool IsValid()const{return !Name.IsEmpty();}

	int GetTag()const
	{
		if (mTag!=0)
		{
			return mTag;
		}

		EnvironmentTag tag=EnvironmentTag::Parse(Name);
		mTag=tag.GetTag();
		return mTag;

	}
	bool HasTag()const
	{
		if (mTag!=0)
		{
			return true;
		}
		return Name.Contains('-');
	}

	intp GetHashCode()const
	{
		return Name.GetHashCode()^Order^mTag;
	}
public:
	StringRef Name;	//performance hit
	size_t Order;
	mutable int mTag;
	const static FileId Empty;
};

MEDUSA_END;
