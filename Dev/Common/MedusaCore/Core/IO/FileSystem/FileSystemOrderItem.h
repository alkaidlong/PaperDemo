#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/Proto/Client/FileSystem.pb.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"

MEDUSA_BEGIN;

class FileSystemOrderItem
{
public:
	FileSystemOrderItem():mFileId(0),mOrder(0),mTextureRect(NULL),mOffset(NULL),mOriginalSize(NULL){}
	FileSystemOrderItem(size_t order,MemoryByteData data):mData(data),mFileId(0),mOrder(order),mTextureRect(NULL),mOffset(NULL),mOriginalSize(NULL){}
	FileSystemOrderItem(size_t order,size_t fileId):mFileId(fileId),mOrder(order),mTextureRect(NULL),mOffset(NULL),mOriginalSize(NULL){}

	~FileSystemOrderItem();
public:
	bool Initialize(const CoreProto::FileSystemOrderItem& item);

	size_t GetOrder() const { return mOrder; }
	const Rect2F& GetTextureRect() const { return *mTextureRect; }
	const Point2F& GetOffset() const { return *mOffset; }
	const Size2F& GetOriginalSize() const { return *mOriginalSize; }


	const Rect2F& GetTextureRectOrZero() const { if(mTextureRect!=NULL){return *mTextureRect; } return Rect2F::Zero;}
	const Point2F& GetOffsetOrZero() const {if(mOffset!=NULL){ return *mOffset; }return Point2F::Zero;}
	const Size2F& GetOriginalSizeOrZero() const { if(mOriginalSize!=NULL){return *mOriginalSize; }return Size2F::Zero;}

	bool HasData()const{return mData.IsValid();}
	MemoryByteData GetData() const { return mData; }
	void SetData(MemoryByteData val) { mData = val; }

	bool HasTextureRect() const { return mTextureRect!=NULL; }
	bool HasOffset() const { return mOffset!=NULL; }
	bool HasOriginalSize() const { return mOriginalSize!=NULL; }
	size_t GetFileId() const { return mFileId; }

private:
	size_t mFileId;
	HeapString mRealFilePath;

	size_t mOrder;
	Rect2F* mTextureRect;
	Point2F* mOffset;
	Size2F* mOriginalSize;

	MemoryByteData mData;
};
MEDUSA_END;
