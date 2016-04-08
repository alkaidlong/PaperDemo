
#include "AnimationBlock.h"
#include "Engine/Resource/ResourceManager.h"

AnimationBlock::AnimationBlock()
{
	CCSprite::init();


}

AnimationBlock::~AnimationBlock()
{
}

void AnimationBlock::Initialize( const FileId& fileID,unsigned int blockID )
{
	SetFileID(fileID);
	Initialize(blockID);
	mOrderItem = ResourceManager::Instance().ReloadSprite(this,fileID);
}

void AnimationBlock::Initialize(unsigned int blockID)
{
	mBlockID = blockID;
	Initialize();
}

void AnimationBlock::Initialize()
{
	setVisible(true);
}



void AnimationBlock::UnInitialize()
{
	setVisible(false);
	if(isFlipX())
	{
		setFlipX(false);
		setAnchorPoint(ccp( 1.0f-getAnchorPoint().x , getAnchorPoint().y ));
	}
	if(isFlipY())
	{
		setFlipY(false);
		setAnchorPoint(ccp( getAnchorPoint().x , 1.0f-getAnchorPoint().y ));
	}
	removeFromParentAndCleanup(true);
}

void AnimationBlock::update( const CoreProto::BlockInfo& blockmodel )
{
	const CoreProto::PointF &point = blockmodel.pos();
	CCPoint pointInPixels(point.x(),point.y());
	const CoreProto::PointF &skew = blockmodel.skew();
	float skewx = skew.x();
	float skewy = skew.y();

	if( m_bFlipX )
	{
		pointInPixels.x = -point.x();
		skewx = 360 - skewx;
		skewy = 360 - skewy;
	}

	if( m_bFlipY )
	{
		pointInPixels.y = -point.y();
		skewx = 360 - skewx;
		skewy = 360 - skewy;
	}

	setPosition(pointInPixels);
	setSkewX(skewx);
	setSkewY(skewy);

	const CoreProto::ScaleF &scale = blockmodel.scale();
	setScaleX(scale.x());
	setScaleY(scale.y());

	if(blockmodel.has_colormultiplier())
	{
		setOpacity( (unsigned char)(blockmodel.colormultiplier().a()*255) );
		ccColor3B color = ccc3(255,255,255);
		color.r *= blockmodel.colormultiplier().r();
		color.g *= blockmodel.colormultiplier().g();
		color.b *= blockmodel.colormultiplier().b();
		setColor(color);
	}

	if (blockmodel.has_coloroffset())
	{
		ccColor4B color4;
		color4.a = blockmodel.coloroffset().a() ;
		color4.r = blockmodel.coloroffset().r() ;
		color4.g = blockmodel.coloroffset().g() ;
		color4.b = blockmodel.coloroffset().b() ;
		SetDeltaColor(color4);
	}

	SetRenderFlag((RenderFlag)blockmodel.renderflag());

	if( blockmodel.zorder() != getZOrder() )
	{
		getParent()->reorderChild(this,blockmodel.zorder());
	}

}

void AnimationBlock::setFlipX( bool isFlipX )
{
	if( isFlipX != m_bFlipX	 )
	{
		CCSprite::setFlipX(isFlipX);
		setAnchorPoint(ccp(1.0f-getAnchorPoint().x,getAnchorPoint().y));
	}
}

void AnimationBlock::setFlipY( bool isFlipY )
{
	if( isFlipY != m_bFlipY	 )
	{
		CCSprite::setFlipY(isFlipY);
		setAnchorPoint(ccp(getAnchorPoint().x,1.0f-getAnchorPoint().y));
	}
}
