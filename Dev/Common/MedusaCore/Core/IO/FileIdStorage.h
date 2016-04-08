#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/HeapString.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

class FileIdStorage
{
public:
	FileIdStorage():Order(0){}
	FileIdStorage(const StringRef& name,size_t order=0):Name(name),Order(order){}
	FileIdStorage(const FileId& fileId):Name(fileId.Name),Order(fileId.Order){}

	~FileIdStorage(){}
	bool operator<(const FileIdStorage& fileId)const
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
	void operator=(const FileIdStorage& fileId){Name = fileId.Name;Order = fileId.Order;}
	void operator=(const FileId& fileId){Name = fileId.Name;Order = fileId.Order;}

	bool operator==(const FileIdStorage& fileId)const{return Name==fileId.Name && Order == fileId.Order;}
	bool operator!=(const FileIdStorage& fileId)const{return Name!=fileId.Name || Order != fileId.Order;}
	bool operator==(const FileId& fileId)const{return Name==fileId.Name && Order == fileId.Order;}
	bool operator!=(const FileId& fileId)const{return Name!=fileId.Name || Order != fileId.Order;}

	bool IsValid()const{return !Name.IsEmpty();}
	void Reset(){Name.Clear();Order=0;}

	FileId ToFileId()const{return FileId(Name,Order);}
	intp GetHashCode()const{return Name.GetHashCode()^Order;}

	static FileIdStorage ParseFrom(const StringRef& name);
public:
	HeapString Name;	//performance hit
	size_t Order;
};


MEDUSA_END;
