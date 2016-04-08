#include "MedusaCorePreCompiled.h"
#include "Core/IO/FileSystem/FileSystemOrderItem.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

FileSystemOrderItem::~FileSystemOrderItem(void)
{
	SAFE_DELETE(mTextureRect);
	SAFE_DELETE(mOffset);
	SAFE_DELETE(mOriginalSize);
}

bool FileSystemOrderItem::Initialize( const CoreProto::FileSystemOrderItem& item )
{
	mFileId= item.fileid();
	mOrder=item.order();
	if (item.has_texturerect())
	{
		const CoreProto::RectU& textureRect= item.texturerect();
		mTextureRect=new Rect2F();

		mTextureRect->Origin.X=(float)textureRect.origin().x();
		mTextureRect->Origin.Y=(float)textureRect.origin().y();

		mTextureRect->Size.Width=(float)textureRect.size().width();
		mTextureRect->Size.Height=(float)textureRect.size().height();
	}

	if (item.has_offset())
	{
		const CoreProto::PointU& offset=item.offset();
		mOffset=new Point2F();
		mOffset->X=(float)offset.x();
		mOffset->Y=(float)offset.y();
	}

	if (item.has_originalsize())
	{
		const CoreProto::SizeU& originalSize=item.originalsize();
		mOriginalSize=new Size2F();
		mOriginalSize->Width=(float)originalSize.width();
		mOriginalSize->Height=(float)originalSize.height();
	}

	if (item.has_data())
	{
		const std::string& data=item.data();
		mData=MemoryByteData::CopyFrom((byte*)data.c_str(),data.length());
	}

	return true;
}


MEDUSA_END;
