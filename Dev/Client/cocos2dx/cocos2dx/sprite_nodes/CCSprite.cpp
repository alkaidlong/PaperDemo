/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCSpriteBatchNode.h"
#include "CCAnimation.h"
#include "CCAnimationCache.h"
#include "ccConfig.h"
#include "CCSprite.h"
#include "CCSpriteFrame.h"
#include "CCSpriteFrameCache.h"
#include "textures/CCTextureCache.h"
#include "draw_nodes/CCDrawingPrimitives.h"
#include "shaders/CCShaderCache.h"
#include "shaders/ccGLStateCache.h"

#include "shaders/CCGLProgram.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"
#include "cocoa/CCGeometry.h"
#include "textures/CCTexture2D.h"
#include "cocoa/CCAffineTransform.h"
#include "support/TransformUtils.h"
#include "support/CCProfiling.h"
// external
#include "kazmath/GL/matrix.h"
#include <string.h>

using namespace std;

NS_CC_BEGIN

#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif



	const GLushort CCSprite::mScaleNineVerticesIndex[] = { 0, 4, 1,  1, 4, 5,  1, 5, 2,  2, 5, 6,  2, 6, 3,  3, 6, 7,
	4, 8, 5,  5, 8, 9,  5, 9, 6,  6, 9, 10,  6, 10, 7,  7, 10, 11,
	8, 12, 9,  9, 12, 13,  9, 13, 10,  10, 13, 14,  10, 14, 11,  11, 14, 15 };

CCSprite* CCSprite::createWithTexture(CCTexture2D *pTexture,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture,spriteType))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect,spriteType))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::create(const char *pszFileName,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName,spriteType))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::create(const char *pszFileName, const CCRect& rect,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCSprite *pobSprite = new CCSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect,spriteType))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	CCSprite *pobSprite = new CCSprite();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSprite* CCSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCSprite* CCSprite::create(SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCSprite *pSprite = new CCSprite();
	if (pSprite && pSprite->init(spriteType))
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool CCSprite::init(SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	return initWithTexture(NULL, CCRectZero,CCSizeZero,spriteType);
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect,bool rotated,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	return initWithTexture(pTexture,rect,rect.size,rotated,spriteType);
}
// designated initializer
bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, const CCSize& expectedSize,bool rotated,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	if (CCNodeRGBA::init())
	{
		m_pobBatchNode = NULL;

		m_bRecursiveDirty = false;
		setDirty(false);

		m_bOpacityModifyRGB = true;

		m_sBlendFunc.src = CC_BLEND_SRC;
		m_sBlendFunc.dst = CC_BLEND_DST;

		m_bFlipX = m_bFlipY = false;

		// default transform anchor: center
		setAnchorPoint(ccp(0.5f, 0.5f));

		// zwoptex default values
		m_obOffsetPosition = CCPointZero;

		m_bHasChildren = false;

		mSpriteType=spriteType;
		if (mSpriteType==SpriteType::Normal)
		{
			m_sQuad=new ccV3F_C4B_T2F_Quad();
			// clean the Quad
			memset(m_sQuad, 0, sizeof(ccV3F_C4B_T2F_Quad));

			// Atlas: Color
			ccColor4B tmpColor = { 255, 255, 255, 255 };
			m_sQuad->bl.colors = tmpColor;
			m_sQuad->br.colors = tmpColor;
			m_sQuad->tl.colors = tmpColor;
			m_sQuad->tr.colors = tmpColor;

			m_sQuad->bl.deltaColors = mDeltaColor;
			m_sQuad->br.deltaColors = mDeltaColor;
			m_sQuad->tl.deltaColors = mDeltaColor;
			m_sQuad->tr.deltaColors = mDeltaColor;

		}
		else
		{
			mScaleNineVertices = new ccV3F_C4B_T2F[16];
		}


		setVertexRect(rect);
		// update texture (calls updateBlendFunc)
		setTexture(pTexture);
		setTextureRect(rect, rotated, expectedSize);

		// by default use "Self Render".
		// if the sprite is added to a batchnode, then it will automatically switch to "batchnode Render"
		setBatchNode(NULL);

		return true;
	}
	else
	{
		return false;
	}
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect,const CCSize& expectedSize,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	return initWithTexture(pTexture, rect,expectedSize, false,spriteType);
}
bool CCSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	return initWithTexture(pTexture, rect,rect.size, false,spriteType);
}

bool CCSprite::initWithTexture(CCTexture2D *pTexture,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCAssert(pTexture != NULL, "Invalid texture for sprite");

	CCRect rect = CCRectZero;
	rect.size = pTexture->getContentSize();

	return initWithTexture(pTexture, rect,rect.size,spriteType);
}

bool CCSprite::initWithFile(const char *pszFilename,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCAssert(pszFilename != NULL, "Invalid filename for sprite");

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		CCRect rect = CCRectZero;
		rect.size = pTexture->getContentSize();
		return initWithTexture(pTexture, rect,spriteType);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release(); 
	return false;
}

bool CCSprite::initWithFile(const char *pszFilename, const CCRect& rect,SpriteType::SpriteType_t spriteType/*=SpriteType::Normal*/)
{
	CCAssert(pszFilename != NULL, "");

	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFilename);
	if (pTexture)
	{
		return initWithTexture(pTexture, rect,spriteType);
	}

	// don't release here.
	// when load texture failed, it's better to get a "transparent" sprite then a crashed program
	// this->release(); 
	return false;
}

bool CCSprite::initWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	CCAssert(pSpriteFrame != NULL, "");

	bool bRet = initWithTexture(pSpriteFrame->getTexture(), pSpriteFrame->getRect());
	setDisplayFrame(pSpriteFrame);

	return bRet;
}

bool CCSprite::initWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCAssert(pszSpriteFrameName != NULL, "");

	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
	return initWithSpriteFrame(pFrame);
}

// XXX: deprecated
/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage)
{
// todo
// because it is deprecated, so we do not implement it

return NULL;
}
*/

/*
CCSprite* CCSprite::initWithCGImage(CGImageRef pImage, const char *pszKey)
{
CCAssert(pImage != NULL);

// XXX: possible bug. See issue #349. New API should be added
CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addCGImage(pImage, pszKey);

const CCSize& size = pTexture->getContentSize();
CCRect rect = CCRectMake(0 ,0, size.width, size.height);

return initWithTexture(texture, rect);
}
*/

CCSprite::CCSprite(void)
	: m_bShouldBeHidden(false),
	m_pobTexture(NULL),
	mSpriteType(SpriteType::Normal)
{

	m_sQuad=NULL;
	mScaleNineVertices=NULL;
	mLeftBorder=0;
	mRightBorder=0;
	mTopBorder=0;
	mBottomBorder=0;
	mDeltaColor.r=0;
	mDeltaColor.g=0;
	mDeltaColor.b=0;
	mDeltaColor.a=0;


}

CCSprite::~CCSprite(void)
{
	CC_SAFE_RELEASE(m_pobTexture);
	if (m_sQuad!=NULL)
	{
		delete m_sQuad;
		m_sQuad=NULL;
	}

	if (mScaleNineVertices!=NULL)
	{
		delete[] mScaleNineVertices;
		mScaleNineVertices=NULL;
	}


}

void CCSprite::setTextureRect(const CCRect& rect)
{
	setTextureRect(rect, false, rect.size);
}


void CCSprite::setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize)
{
	m_bRectRotated = rotated;

	setContentSize(untrimmedSize);
	setVertexRect(rect);
	setTextureCoords(rect);

	CCPoint relativeOffset = m_obUnflippedOffsetPositionFromCenter;

	// issue #732
	if (m_bFlipX)
	{
		relativeOffset.x = -relativeOffset.x;
	}
	if (m_bFlipY)
	{
		relativeOffset.y = -relativeOffset.y;
	}

	m_obOffsetPosition.x = relativeOffset.x + (m_obContentSize.width - m_obRect.size.width) / 2;
	m_obOffsetPosition.y = relativeOffset.y + (m_obContentSize.height - m_obRect.size.height) / 2;

	// rendering using batch node
	if (m_pobBatchNode)
	{
		// update dirty_, don't update recursiveDirty_
		setDirty(true);
	}
	else
	{
		// self rendering

		// Atlas: Vertex


		// Don't update Z.
		if (m_sQuad!=NULL)
		{
			float x1 = 0 + m_obOffsetPosition.x;
			float y1 = 0 + m_obOffsetPosition.y;
			float x2 = x1 + m_obRect.size.width;
			float y2 = y1 + m_obRect.size.height;

			m_sQuad->bl.vertices = vertex3(x1, y1, 0);
			m_sQuad->br.vertices = vertex3(x2, y1, 0);
			m_sQuad->tl.vertices = vertex3(x1, y2, 0);
			m_sQuad->tr.vertices = vertex3(x2, y2, 0);
		}
		else
		{
			ReCalculateScaleNineVertices();
		}

	}
}

// override this method to generate "double scale" sprites
void CCSprite::setVertexRect(const CCRect& rect)
{
	m_obRect = rect;
}

void CCSprite::setTextureCoords(CCRect rect)
{
	rect = CC_RECT_POINTS_TO_PIXELS(rect);

	CCTexture2D *tex = m_pobBatchNode ? m_pobTextureAtlas->getTexture() : m_pobTexture;
	if (! tex)
	{
		return;
	}

	float atlasWidth = (float)tex->getPixelsWide();
	float atlasHeight = (float)tex->getPixelsHigh();

	float left, right, top, bottom;

	if (m_bRectRotated)
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left    = (2*rect.origin.x+1)/(2*atlasWidth);
		right    = left+(rect.size.height*2-2)/(2*atlasWidth);
		top        = (2*rect.origin.y+1)/(2*atlasHeight);
		bottom    = top+(rect.size.width*2-2)/(2*atlasHeight);
#else
		left    = rect.origin.x/atlasWidth;
		right    = (rect.origin.x+rect.size.height) / atlasWidth;
		top        = rect.origin.y/atlasHeight;
		bottom    = (rect.origin.y+rect.size.width) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if (m_bFlipX)
		{
			CC_SWAP(top, bottom, float);
		}

		if (m_bFlipY)
		{
			CC_SWAP(left, right, float);
		}

		if (m_sQuad!=NULL)
		{
			m_sQuad->bl.texCoords.u = left;
			m_sQuad->bl.texCoords.v = top;
			m_sQuad->br.texCoords.u = left;
			m_sQuad->br.texCoords.v = bottom;
			m_sQuad->tl.texCoords.u = right;
			m_sQuad->tl.texCoords.v = top;
			m_sQuad->tr.texCoords.u = right;
			m_sQuad->tr.texCoords.v = bottom;
		}


	}
	else
	{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
		left    = (2*rect.origin.x+1)/(2*atlasWidth);
		right    = left + (rect.size.width*2-2)/(2*atlasWidth);
		top        = (2*rect.origin.y+1)/(2*atlasHeight);
		bottom    = top + (rect.size.height*2-2)/(2*atlasHeight);
#else
		left    = rect.origin.x/atlasWidth;
		right    = (rect.origin.x + rect.size.width) / atlasWidth;
		top        = rect.origin.y/atlasHeight;
		bottom    = (rect.origin.y + rect.size.height) / atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

		if(m_bFlipX)
		{
			CC_SWAP(left,right,float);
		}

		if(m_bFlipY)
		{
			CC_SWAP(top,bottom,float);
		}

		if (m_sQuad!=NULL)
		{
			m_sQuad->bl.texCoords.u = left;
			m_sQuad->bl.texCoords.v = bottom;
			m_sQuad->br.texCoords.u = right;
			m_sQuad->br.texCoords.v = bottom;
			m_sQuad->tl.texCoords.u = left;
			m_sQuad->tl.texCoords.v = top;
			m_sQuad->tr.texCoords.u = right;
			m_sQuad->tr.texCoords.v = top;
		}
	}
}

void CCSprite::updateTransform(void)
{
	CCAssert(m_pobBatchNode, "updateTransform is only valid when CCSprite is being rendered using an CCSpriteBatchNode");

	// recalculate matrix only if it is dirty
	if( isDirty() )
	{

		// If it is not visible, or one of its ancestors is not visible, then do nothing:
		if( !m_bVisible || ( m_pParent && m_pParent != m_pobBatchNode && ((CCSprite*)m_pParent)->m_bShouldBeHidden) )
		{
			if (m_sQuad!=NULL)
			{
				m_sQuad->br.vertices = m_sQuad->tl.vertices = m_sQuad->tr.vertices = m_sQuad->bl.vertices = vertex3(0,0,0);
			}

			m_bShouldBeHidden = true;
		}
		else 
		{
			m_bShouldBeHidden = false;

			if( ! m_pParent || m_pParent == m_pobBatchNode )
			{
				m_transformToBatch = nodeToParentTransform();
			}
			else 
			{
				CCAssert( dynamic_cast<CCSprite*>(m_pParent), "Logic error in CCSprite. Parent must be a CCSprite");
				m_transformToBatch = CCAffineTransformConcat( nodeToParentTransform() , ((CCSprite*)m_pParent)->m_transformToBatch );
			}

			//
			// calculate the Quad based on the Affine Matrix
			//

			CCSize size = m_obRect.size;

			float x1 = m_obOffsetPosition.x;
			float y1 = m_obOffsetPosition.y;

			float x2 = x1 + size.width;
			float y2 = y1 + size.height;
			float x = m_transformToBatch.tx;
			float y = m_transformToBatch.ty;

			float cr = m_transformToBatch.a;
			float sr = m_transformToBatch.b;
			float cr2 = m_transformToBatch.d;
			float sr2 = -m_transformToBatch.c;
			float ax = x1 * cr - y1 * sr2 + x;
			float ay = x1 * sr + y1 * cr2 + y;

			float bx = x2 * cr - y1 * sr2 + x;
			float by = x2 * sr + y1 * cr2 + y;

			float cx = x2 * cr - y2 * sr2 + x;
			float cy = x2 * sr + y2 * cr2 + y;

			float dx = x1 * cr - y2 * sr2 + x;
			float dy = x1 * sr + y2 * cr2 + y;

			if (m_sQuad!=NULL)
			{
				m_sQuad->bl.vertices = vertex3( RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), m_fVertexZ );
				m_sQuad->br.vertices = vertex3( RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), m_fVertexZ );
				m_sQuad->tl.vertices = vertex3( RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), m_fVertexZ );
				m_sQuad->tr.vertices = vertex3( RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), m_fVertexZ );
			}


		}

		// MARMALADE CHANGE: ADDED CHECK FOR NULL, TO PERMIT SPRITES WITH NO BATCH NODE / TEXTURE ATLAS
		if (m_pobTextureAtlas&&m_sQuad!=NULL)
		{
			m_pobTextureAtlas->updateQuad(m_sQuad, m_uAtlasIndex);
		}

		m_bRecursiveDirty = false;
		setDirty(false);
	}

	// MARMALADE CHANGED
	// recursively iterate over children
	/*    if( m_bHasChildren ) 
	{
	// MARMALADE: CHANGED TO USE CCNode*
	// NOTE THAT WE HAVE ALSO DEFINED virtual CCNode::updateTransform()
	arrayMakeObjectsPerformSelector(m_pChildren, updateTransform, CCSprite*);
	}*/
	CCNode::updateTransform();

#if CC_SPRITE_DEBUG_DRAW
	// draw bounding box
	CCPoint vertices[4] = {
		ccp( m_sQuad->bl.vertices.x, m_sQuad->bl.vertices.y ),
		ccp( m_sQuad->br.vertices.x, m_sQuad->br.vertices.y ),
		ccp( m_sQuad->tr.vertices.x, m_sQuad->tr.vertices.y ),
		ccp( m_sQuad->tl.vertices.x, m_sQuad->tl.vertices.y ),
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
}

// draw

void CCSprite::draw(void)
{
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
	//update shader type
	// shader program
	if (m_pobTexture)
	{
		if (mRenderFlag==RenderFlag::Grayscale)
		{
			if (mDeltaColor.a==0&&mDeltaColor.r==0&&mDeltaColor.g==0&&mDeltaColor.b==0)
			{
				CCGLProgram* curProgram=getShaderProgram();
				if (curProgram==NULL||curProgram->GetType()!=kCCShaderType_PositionTextureColor_Flag)
				{
					setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorFlag));
				}
			}
			else
			{
				CCGLProgram* curProgram=getShaderProgram();
				if (curProgram==NULL||curProgram->GetType()!=kCCShaderType_PositionTextureColor_Delta_Flag)
				{
					setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorDeltaFlag));
				}
			}
		}
		else
		{
			if (mDeltaColor.a==0&&mDeltaColor.r==0&&mDeltaColor.g==0&&mDeltaColor.b==0)
			{
				CCGLProgram* curProgram=getShaderProgram();
				if (curProgram==NULL||curProgram->GetType()!=kCCShaderType_PositionTextureColor)
				{
					setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
				}
			}
			else
			{
				
				CCGLProgram* curProgram=getShaderProgram();
				if (curProgram==NULL||curProgram->GetType()!=kCCShaderType_PositionTextureColor_Delta)
				{
					setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorDelta));
				}
			}
		}

	}
	else
	{
		setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	}



	getShaderProgram()->SetRenderFlag(mRenderFlag);
	CC_NODE_DRAW_SETUP();

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	if (m_pobTexture != NULL)
	{
		ccGLBindTexture2D( m_pobTexture->getName() );
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
	}
	else
	{
		ccGLBindTexture2D(0);
		ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color );
	}

#define kQuadSize sizeof(m_sQuad->bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(m_sQuad, 4 * kQuadSize, 0);
#else
	long offset;
	if (mSpriteType==SpriteType::Normal)
	{
		offset= (long)m_sQuad;
	}
	else
	{
		offset= (long)mScaleNineVertices;
	}


#endif // EMSCRIPTEN

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	if (m_pobTexture != NULL)
	{
		// texCoods
		diff = offsetof( ccV3F_C4B_T2F, texCoords);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	}

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	//delta color
	diff = offsetof( ccV3F_C4B_T2F, deltaColors);
	glVertexAttribPointer(kCCVertexAttrib_DeltaColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	if (mSpriteType == SpriteType::Normal)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	else if (mSpriteType == SpriteType::ScaleNine)
	{
		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_SHORT, mScaleNineVerticesIndex);
	}

	CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
	// draw bounding box
	CCPoint vertices[4]={
		ccp(m_sQuad->tl.vertices.x,m_sQuad->tl.vertices.y),
		ccp(m_sQuad->bl.vertices.x,m_sQuad->bl.vertices.y),
		ccp(m_sQuad->br.vertices.x,m_sQuad->br.vertices.y),
		ccp(m_sQuad->tr.vertices.x,m_sQuad->tr.vertices.y),
	};
	ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
	// draw texture box
	CCSize s = this->getTextureRect().size;
	CCPoint offsetPix = this->getOffsetPosition();
	CCPoint vertices[4] = {
		ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
		ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

// CCNode overrides

void CCSprite::addChild(CCNode* pChild)
{
	CCNode::addChild(pChild);
}

void CCSprite::addChild(CCNode *pChild, int zOrder)
{
	CCNode::addChild(pChild, zOrder);
}

void CCSprite::addChild(CCNode *pChild, int zOrder, int tag)
{
	CCAssert(pChild != NULL, "Argument must be non-NULL");

	if (m_pobBatchNode)
	{
		CCSprite* pChildSprite = dynamic_cast<CCSprite*>(pChild);
		CCAssert( pChildSprite, "CCSprite only supports CCSprites as children when using CCSpriteBatchNode");
		CCAssert(pChildSprite->getTexture()->getName() == m_pobTextureAtlas->getTexture()->getName(), "");
		//put it in descendants array of batch node
		m_pobBatchNode->appendChild(pChildSprite);

		if (!m_bReorderChildDirty)
		{
			setReorderChildDirtyRecursively();
		}
	}
	//CCNode already sets isReorderChildDirty_ so this needs to be after batchNode check
	CCNode::addChild(pChild, zOrder, tag);
	m_bHasChildren = true;
}

void CCSprite::reorderChild(CCNode *pChild, int zOrder)
{
	CCAssert(pChild != NULL, "");
	CCAssert(m_pChildren->containsObject(pChild), "");

	if (zOrder == pChild->getZOrder())
	{
		return;
	}

	if( m_pobBatchNode && ! m_bReorderChildDirty)
	{
		setReorderChildDirtyRecursively();
		m_pobBatchNode->reorderBatch(true);
	}

	CCNode::reorderChild(pChild, zOrder);
}

void CCSprite::removeChild(CCNode *pChild, bool bCleanup)
{
	if (m_pobBatchNode)
	{
		m_pobBatchNode->removeSpriteFromAtlas((CCSprite*)(pChild));
	}

	CCNode::removeChild(pChild, bCleanup);

}

void CCSprite::removeAllChildrenWithCleanup(bool bCleanup)
{
	if (m_pobBatchNode)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
			if (pChild)
			{
				m_pobBatchNode->removeSpriteFromAtlas(pChild);
			}
		}
	}

	CCNode::removeAllChildrenWithCleanup(bCleanup);

	m_bHasChildren = false;
}

void CCSprite::sortAllChildren()
{
	if (m_bReorderChildDirty)
	{
		int i = 0,j = 0,length = m_pChildren->data->num;
		CCNode** x = (CCNode**)m_pChildren->data->arr;
		CCNode *tempItem = NULL;

		// insertion sort
		for(i=1; i<length; i++)
		{
			tempItem = x[i];
			j = i-1;

			//continue moving element downwards while zOrder is smaller or when zOrder is the same but orderOfArrival is smaller
			while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder() == x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
			{
				x[j+1] = x[j];
				j = j-1;
			}
			x[j+1] = tempItem;
		}

		if ( m_pobBatchNode)
		{
			arrayMakeObjectsPerformSelector(m_pChildren, sortAllChildren, CCSprite*);
		}

		m_bReorderChildDirty = false;
	}
}

//
// CCNode property overloads
// used only when parent is CCSpriteBatchNode
//

void CCSprite::setReorderChildDirtyRecursively(void)
{
	//only set parents flag the first time
	if ( ! m_bReorderChildDirty )
	{
		m_bReorderChildDirty = true;
		CCNode* pNode = (CCNode*)m_pParent;
		while (pNode && pNode != m_pobBatchNode)
		{
			((CCSprite*)pNode)->setReorderChildDirtyRecursively();
			pNode=pNode->getParent();
		}
	}
}


void CCSprite::setDirtyRecursively(bool bValue)
{
	m_bRecursiveDirty = bValue;
	setDirty(bValue);
	// recursively set dirty
	if (m_bHasChildren)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCSprite* pChild = dynamic_cast<CCSprite*>(pObject);
			if (pChild)
			{
				pChild->setDirtyRecursively(true);
			}
		}
	}
}

// XXX HACK: optimization
#define SET_DIRTY_RECURSIVELY() {                                    \
	if (m_pobBatchNode && ! m_bRecursiveDirty) {    \
	m_bRecursiveDirty = true;                    \
	setDirty(true);                              \
	if ( m_bHasChildren)                        \
	setDirtyRecursively(true);                \
	}                                            \
}

void CCSprite::setPosition(const CCPoint& pos)
{
	CCNode::setPosition(pos);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotation(float fRotation)
{
	CCNode::setRotation(fRotation);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotationX(float fRotationX)
{
	CCNode::setRotationX(fRotationX);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setRotationY(float fRotationY)
{
	CCNode::setRotationY(fRotationY);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewX(float sx)
{
	CCNode::setSkewX(sx);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setSkewY(float sy)
{
	CCNode::setSkewY(sy);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleX(float fScaleX)
{
	CCNode::setScaleX(fScaleX);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScaleY(float fScaleY)
{
	CCNode::setScaleY(fScaleY);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setScale(float fScale)
{
	CCNode::setScale(fScale);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setVertexZ(float fVertexZ)
{
	CCNode::setVertexZ(fVertexZ);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setAnchorPoint(const CCPoint& anchor)
{
	CCNode::setAnchorPoint(anchor);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::ignoreAnchorPointForPosition(bool value)
{
	CCAssert(! m_pobBatchNode, "ignoreAnchorPointForPosition is invalid in CCSprite");
	CCNode::ignoreAnchorPointForPosition(value);
}

void CCSprite::setVisible(bool bVisible)
{
	CCNode::setVisible(bVisible);
	SET_DIRTY_RECURSIVELY();
}

void CCSprite::setFlipX(bool bFlipX)
{
	if (m_bFlipX != bFlipX)
	{
		m_bFlipX = bFlipX;
		setTextureRect(m_obRect, m_bRectRotated, m_obContentSize);
	}
}

bool CCSprite::isFlipX(void)
{
	return m_bFlipX;
}

void CCSprite::setFlipY(bool bFlipY)
{
	if (m_bFlipY != bFlipY)
	{
		m_bFlipY = bFlipY;
		setTextureRect(m_obRect, m_bRectRotated, m_obContentSize);
	}
}

bool CCSprite::isFlipY(void)
{
	return m_bFlipY;
}

//
// RGBA protocol
//

void CCSprite::updateColor(void)
{
	ccColor4B resultColor=ccc4BFromccc4F(GetResultColor());
	ccColor4B resultDeltaColor=GetResultDeltaColor();

	// special opacity for premultiplied textures
	/*if (m_bOpacityModifyRGB)
	{
	resultColor.r *= _displayedOpacity/255.0f;
	resultColor.g *= _displayedOpacity/255.0f;
	resultColor.b *= _displayedOpacity/255.0f;
	}*/

	if (m_sQuad!=NULL)
	{
		m_sQuad->bl.colors = resultColor;
		m_sQuad->br.colors = resultColor;
		m_sQuad->tl.colors = resultColor;
		m_sQuad->tr.colors = resultColor;

		m_sQuad->bl.deltaColors = resultDeltaColor;
		m_sQuad->br.deltaColors = resultDeltaColor;
		m_sQuad->tl.deltaColors = resultDeltaColor;
		m_sQuad->tr.deltaColors = resultDeltaColor;
	}
	else
	{
		ReCalculateScaleNineVertices();
	}


	// renders using batch node
	if (m_pobBatchNode)
	{
		if (m_uAtlasIndex != CCSpriteIndexNotInitialized)
		{
			m_pobTextureAtlas->updateQuad(m_sQuad, m_uAtlasIndex);
		}
		else
		{
			// no need to set it recursively
			// update dirty_, don't update recursiveDirty_
			setDirty(true);
		}
	}

	// self render
	// do nothing
}

void CCSprite::setOpacity(GLubyte opacity)
{
	CCNodeRGBA::setOpacity(opacity);

	UpdateColorRecursively();
}

void CCSprite::setColor(const ccColor3B& color3)
{
	CCNodeRGBA::setColor(color3);

	UpdateColorRecursively();
}


void CCSprite::SetDeltaColor( cocos2d::ccColor4B val )
{
	mDeltaColor = val;
	UpdateColorRecursively();
}


void CCSprite::setOpacityModifyRGB(bool modify)
{
	if (m_bOpacityModifyRGB != modify)
	{
		m_bOpacityModifyRGB = modify;
		UpdateColorRecursively();
	}
}

bool CCSprite::isOpacityModifyRGB(void)
{
	return m_bOpacityModifyRGB;
}

void CCSprite::updateDisplayedColor(const ccColor3B& parentColor)
{
	CCNodeRGBA::updateDisplayedColor(parentColor);

	UpdateColorRecursively();
}

void CCSprite::updateDisplayedOpacity(GLubyte opacity)
{
	CCNodeRGBA::updateDisplayedOpacity(opacity);

	UpdateColorRecursively();
}

// Frames

void CCSprite::setDisplayFrame(CCSpriteFrame *pNewFrame)
{
	m_obUnflippedOffsetPositionFromCenter = pNewFrame->getOffset();

	CCTexture2D *pNewTexture = pNewFrame->getTexture();
	// update texture before updating texture rect
	if (pNewTexture != m_pobTexture)
	{
		setTexture(pNewTexture);
	}

	// update rect
	m_bRectRotated = pNewFrame->isRotated();
	setTextureRect(pNewFrame->getRect(), m_bRectRotated, pNewFrame->getOriginalSize());
}

void CCSprite::setDisplayFrameWithAnimationName(const char *animationName, int frameIndex)
{
	CCAssert(animationName, "CCSprite#setDisplayFrameWithAnimationName. animationName must not be NULL");

	CCAnimation *a = CCAnimationCache::sharedAnimationCache()->animationByName(animationName);

	CCAssert(a, "CCSprite#setDisplayFrameWithAnimationName: Frame not found");

	CCAnimationFrame* frame = (CCAnimationFrame*)a->getFrames()->objectAtIndex(frameIndex);

	CCAssert(frame, "CCSprite#setDisplayFrame. Invalid frame");

	setDisplayFrame(frame->getSpriteFrame());
}

bool CCSprite::isFrameDisplayed(CCSpriteFrame *pFrame)
{
	CCRect r = pFrame->getRect();

	return (r.equals(m_obRect) &&
		pFrame->getTexture()->getName() == m_pobTexture->getName() &&
		pFrame->getOffset().equals(m_obUnflippedOffsetPositionFromCenter));
}

CCSpriteFrame* CCSprite::displayFrame(void)
{
	return CCSpriteFrame::createWithTexture(m_pobTexture,
		CC_RECT_POINTS_TO_PIXELS(m_obRect),
		m_bRectRotated,
		CC_POINT_POINTS_TO_PIXELS(m_obUnflippedOffsetPositionFromCenter),
		CC_SIZE_POINTS_TO_PIXELS(m_obContentSize));
}

CCSpriteBatchNode* CCSprite::getBatchNode(void)
{
	return m_pobBatchNode;
}

void CCSprite::setBatchNode(CCSpriteBatchNode *pobSpriteBatchNode)
{
	m_pobBatchNode = pobSpriteBatchNode; // weak reference

	// self render
	if( ! m_pobBatchNode ) {
		m_uAtlasIndex = CCSpriteIndexNotInitialized;
		setTextureAtlas(NULL);
		m_bRecursiveDirty = false;
		setDirty(false);

		float x1 = m_obOffsetPosition.x;
		float y1 = m_obOffsetPosition.y;
		float x2 = x1 + m_obRect.size.width;
		float y2 = y1 + m_obRect.size.height;
		if (m_sQuad!=NULL)
		{
			m_sQuad->bl.vertices = vertex3( x1, y1, 0 );
			m_sQuad->br.vertices = vertex3( x2, y1, 0 );
			m_sQuad->tl.vertices = vertex3( x1, y2, 0 );
			m_sQuad->tr.vertices = vertex3( x2, y2, 0 );
		}



	} else {

		// using batch
		m_transformToBatch = CCAffineTransformIdentity;
		setTextureAtlas(m_pobBatchNode->getTextureAtlas()); // weak ref
	}
}

// Texture protocol

void CCSprite::updateBlendFunc(void)
{
	CCAssert (! m_pobBatchNode, "CCSprite: updateBlendFunc doesn't work when the sprite is rendered using a CCSpriteBatchNode");

	// it is possible to have an untextured sprite
	if (! m_pobTexture || ! m_pobTexture->hasPremultipliedAlpha())
	{
		m_sBlendFunc.src = GL_SRC_ALPHA;
		m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
		setOpacityModifyRGB(false);
	}
	else
	{
		m_sBlendFunc.src = CC_BLEND_SRC;
		m_sBlendFunc.dst = CC_BLEND_DST;
		setOpacityModifyRGB(true);
	}
}

void CCSprite::setTexture(CCTexture2D *texture)
{
	// If batchnode, then texture id should be the same
	CCAssert(! m_pobBatchNode || texture->getName() == m_pobBatchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
	// accept texture==nil as argument
	CCAssert( !texture || dynamic_cast<CCTexture2D*>(texture), "setTexture expects a CCTexture2D. Invalid argument");

	// shader program
	if (texture)
	{
		setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
	}
	else
	{
		setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	}

	if (!m_pobBatchNode && m_pobTexture != texture)
	{
		CC_SAFE_RETAIN(texture);
		CC_SAFE_RELEASE(m_pobTexture);
		m_pobTexture = texture;
		updateBlendFunc();
	}
}

CCTexture2D* CCSprite::getTexture(void)
{
	return m_pobTexture;
}

#pragma region ScaleNineSprite
void CCSprite::ReCalculateScaleNineVertices()
{
	if (mSpriteType != SpriteType::ScaleNine)
	{
		return;
	}

	float textureOriginX = m_obRect.origin.x;
	float textureOriginY = m_obRect.origin.y;

	float textureWidth = m_obRect.size.width;
	float textureHeight = m_obRect.size.height;

	CCAssert((mLeftBorder < textureWidth) && (mRightBorder < textureWidth) && 
		(mTopBorder < textureHeight) && (mBottomBorder < textureHeight), "The SIZE of Corner is too BIG!");

	float contentWidth = m_obContentSize.width;
	float contentHeight = m_obContentSize.height;

	unsigned int textureAtlasWidth = getTexture()->getPixelsWide();
	unsigned int textureAtlasHeight = getTexture()->getPixelsHigh();

	ccV3F_C4B_T2F vertice;

	// First Line

	ccColor4B resultColor=ccc4BFromccc4F(GetResultColor());
	ccColor4B resultDeltaColor=GetResultDeltaColor();

	// special opacity for premultiplied textures
	if (m_bOpacityModifyRGB)
	{
		resultColor.r *= _displayedOpacity/255.0f;
		resultColor.g *= _displayedOpacity/255.0f;
		resultColor.b *= _displayedOpacity/255.0f;
	}


	vertice.vertices.x = 0;
	vertice.vertices.y = contentHeight;
	vertice.vertices.z = 0;
	vertice.colors = resultColor;
	vertice.deltaColors=resultDeltaColor;

	vertice.texCoords.u = textureOriginX / textureAtlasWidth;
	vertice.texCoords.v = textureOriginY / textureAtlasHeight;
	mScaleNineVertices[0] = vertice;

	vertice.vertices.x = (float) mLeftBorder;
	vertice.texCoords.u = (float) (textureOriginX + mLeftBorder) / textureAtlasWidth;
	mScaleNineVertices[1] = vertice;

	vertice.vertices.x = (float) (contentWidth - mRightBorder);
	vertice.texCoords.u = (float) (textureOriginX + textureWidth - mRightBorder) / textureAtlasWidth;
	mScaleNineVertices[2] = vertice;

	vertice.vertices.x = (float) contentWidth;
	vertice.texCoords.u = (float) (textureOriginX + textureWidth) / textureAtlasWidth;
	mScaleNineVertices[3] = vertice;

	// Second Line
	vertice.vertices.x = 0;
	vertice.vertices.y = (float) (contentHeight - mTopBorder);
	vertice.texCoords.u = textureOriginX / textureAtlasWidth;
	vertice.texCoords.v = (float) (textureOriginY + mTopBorder) / textureAtlasHeight;
	mScaleNineVertices[4] = vertice;

	vertice.vertices.x = (float) mLeftBorder;
	vertice.texCoords.u = (float) (textureOriginX + mLeftBorder) / textureAtlasWidth;
	mScaleNineVertices[5] = vertice;

	vertice.vertices.x = (float) (contentWidth - mRightBorder);
	vertice.texCoords.u = (float) (textureOriginX + textureWidth - mRightBorder) / textureAtlasWidth;
	mScaleNineVertices[6] = vertice;

	vertice.vertices.x = (float) contentWidth;
	vertice.texCoords.u = (float) (textureOriginX + textureWidth) / textureAtlasWidth;
	mScaleNineVertices[7] = vertice;

	// Third Line
	vertice.vertices.x = 0;
	vertice.vertices.y = (float) mBottomBorder;
	vertice.texCoords.u = textureOriginX / textureAtlasWidth;
	vertice.texCoords.v = (float) (textureOriginY + textureHeight - mBottomBorder) / textureAtlasHeight;
	mScaleNineVertices[8] = vertice;

	vertice.vertices.x = (float) mLeftBorder;
	vertice.texCoords.u = (float) (textureOriginX + mLeftBorder) / textureAtlasWidth;
	mScaleNineVertices[9] = vertice;

	vertice.vertices.x = (float) (contentWidth - mRightBorder);
	vertice.texCoords.u = (float) (textureOriginX + textureWidth - mRightBorder) / textureAtlasWidth;
	mScaleNineVertices[10] = vertice;

	vertice.vertices.x = (float) contentWidth;
	vertice.texCoords.u = (float) (textureOriginX + textureWidth) / textureAtlasWidth;
	mScaleNineVertices[11] = vertice;

	// Fourth Line
	vertice.vertices.x = 0;
	vertice.vertices.y = 0;
	vertice.texCoords.u = textureOriginX / textureAtlasWidth;
	vertice.texCoords.v = (float) (textureOriginY + textureHeight) / textureAtlasHeight;
	mScaleNineVertices[12] = vertice;

	vertice.vertices.x = (float) mLeftBorder;
	vertice.texCoords.u = (float) (textureOriginX + mLeftBorder) / textureAtlasWidth;
	mScaleNineVertices[13] = vertice;

	vertice.vertices.x = (float) (contentWidth - mRightBorder);
	vertice.texCoords.u = (float) (textureOriginX + textureWidth - mRightBorder) / textureAtlasWidth;
	mScaleNineVertices[14] = vertice;

	vertice.vertices.x = (float) contentWidth;
	vertice.texCoords.u = (float) (textureOriginX + textureWidth) / textureAtlasWidth;
	mScaleNineVertices[15] = vertice;
}



void CCSprite::SetScaleNineBorder( unsigned int leftBorder, unsigned int rightBorder, unsigned int topBorder, unsigned int bottomBorder )
{
	mLeftBorder=leftBorder;
	mRightBorder=rightBorder;
	mTopBorder=topBorder;
	mBottomBorder=bottomBorder;
}

void CCSprite::SetScaleNineBorder( unsigned int leftBorder, unsigned int topBorder )
{
	SetScaleNineBorder(leftBorder,leftBorder,topBorder,topBorder);
}

void CCSprite::SetScaleNineBorder( unsigned int border )
{
	SetScaleNineBorder(border,border);
}

void CCSprite::UpdateColorRecursively()
{
	updateColor();
	if(m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(m_pChildren, child)
		{
			CCNode* pChild = (CCNode*) child;
			if (pChild!=NULL&&pChild->IsSprite())
			{
				((CCSprite*)pChild)->UpdateColorRecursively();
			}
		}
	}
}

cocos2d::ccColor4F CCSprite::GetResultColor() const
{
	ccColor4F color4 = { _displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f };

	if (m_pParent!=NULL&&m_pParent->IsSprite())
	{
		ccColor4F parentColor=((CCSprite*)m_pParent)->GetResultColor();
		return color4*parentColor;
	}

	return color4;
}

cocos2d::ccColor4B CCSprite::GetResultDeltaColor() const
{
	ccColor4F color4 = { _displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f };
	if (m_pParent!=NULL&&m_pParent->IsSprite())
	{
		ccColor4B parentDeltaColor=((CCSprite*)m_pParent)->GetDeltaColor();
		return mDeltaColor+ccc4BFromccc4F(color4*ccc4FFromccc4B(parentDeltaColor));
	}

	return mDeltaColor;
}



#pragma endregion ScaleNineSprite
NS_CC_END
