#pragma once


#include "Core/Proto/Proto.h"
#include "Core/IO/FileId.h"
#include "Core/Proto/Client/AnimationModel.pb.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "PaperHeader.h"
USING_MEDUSA;

class AnimationBlock : public CCSprite
{
	friend class AnimationBlockPool;
private:
	unsigned int mBlockID;
	FileId mFileID;
	FileSystemOrderItem* mOrderItem;
private:
	AnimationBlock();
	virtual ~AnimationBlock();
public :
	void Initialize();
	void Initialize(unsigned int blockID);
	void Initialize( const FileId& fileID ,unsigned int blockID );
	void UnInitialize();
	void update( const CoreProto::BlockInfo& blockmodel );
public:
	const FileId& GetFileID() const { return mFileID; }
	void SetFileID(const FileId& val) { mFileID = val; }
	virtual void setFlipX( bool isFlipX );
	virtual void setFlipY( bool isFlipY );
	unsigned int GetBlockID() const { return mBlockID; }
	void SetBlockID(unsigned int val) { mBlockID = val; }
	const FileSystemOrderItem* GetOrderItem()const { return mOrderItem; }
};
