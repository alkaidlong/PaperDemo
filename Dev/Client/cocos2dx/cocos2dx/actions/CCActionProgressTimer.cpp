/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (C) 2010      Lam Pham
 
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
#include "CCActionProgressTimer.h"
#include "misc_nodes/CCProgressTimer.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN

#define kProgressTimerCast CCProgressTimer*

// implementation of CCProgressTo

CCProgressTo* CCProgressTo::create(float duration, float fPercent)
{
    CCProgressTo *pProgressTo = new CCProgressTo();
    pProgressTo->initWithDuration(duration, fPercent);
    pProgressTo->autorelease();

    return pProgressTo;
}

bool CCProgressTo::initWithDuration(float duration, float fPercent)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fTo = fPercent;

        return true;
    }

    return false;
}

CCObject* CCProgressTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCProgressTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCProgressTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCProgressTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fTo);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCProgressTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_fFrom = ((kProgressTimerCast)(pTarget))->getPercentage();

    // XXX: Is this correct ?
    // Adding it to support CCRepeat
    if (m_fFrom == 100)
    {
        m_fFrom = 0;
    }
}

void CCProgressTo::update(float time)
{
    ((kProgressTimerCast)(m_pTarget))->setPercentage(m_fFrom + (m_fTo - m_fFrom) * time);
}

// implementation of CCProgressFromTo

CCProgressFromTo* CCProgressFromTo::create(float duration, float fFromPercentage, float fToPercentage)
{
    CCProgressFromTo *pProgressFromTo = new CCProgressFromTo();
    pProgressFromTo->initWithDuration(duration, fFromPercentage, fToPercentage);
    pProgressFromTo->autorelease();

    return pProgressFromTo;
}

bool CCProgressFromTo::initWithDuration(float duration, float fFromPercentage, float fToPercentage)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_fTo = fToPercentage;
        m_fFrom = fFromPercentage;

        return true;
    }

    return false;
}

CCObject* CCProgressFromTo::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCProgressFromTo* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCProgressFromTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCProgressFromTo();
        pZone = pNewZone = new CCZone(pCopy);
    }

    CCActionInterval::copyWithZone(pZone);

    pCopy->initWithDuration(m_fDuration, m_fFrom, m_fTo);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

CCActionInterval* CCProgressFromTo::reverse(void)
{
    return CCProgressFromTo::create(m_fDuration, m_fTo, m_fFrom);
}

void CCProgressFromTo::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
}

void CCProgressFromTo::update(float time)
{
    ((kProgressTimerCast)(m_pTarget))->setPercentage(m_fFrom + (m_fTo - m_fFrom) * time);
}






CCProgressBy* CCProgressBy::create(float duration, float fPercent)
{
	CCProgressBy *pProgressBy = new CCProgressBy();
	pProgressBy->initWithDuration(duration, fPercent);
	pProgressBy->autorelease();

	return pProgressBy;
}

bool CCProgressBy::initWithDuration(float duration, float fPercent)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		mBy = fPercent;
		mIncrement = fPercent / duration;
		mTimeIncrement = FLT_EPSILON;

		return true;
	}

	return false;
}

CCActionInterval* CCProgressBy::reverse(void)
{
	return CCProgressBy::create(m_fDuration, -mBy);
}

CCObject* CCProgressBy::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCProgressBy* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCProgressBy*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCProgressBy();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	pCopy->initWithDuration(m_fDuration, mBy);

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCProgressBy::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
}

void CCProgressBy::update(float time)
{
	if (mBy == FLT_EPSILON)
	{
		return;
	}

	float dt = (time - mTimeIncrement) * m_fDuration;
	mTimeIncrement = time;

	float by = mBy - mIncrement * dt;
	if ((mBy * by) < 0)
	{
		mBy = FLT_EPSILON;
	}
	else
	{
		mBy = by;
	}

	float curPercent = ((kProgressTimerCast)(m_pTarget))->getPercentage();
	float nextPercent = curPercent + mIncrement * dt;
	((kProgressTimerCast)(m_pTarget))->setPercentage(nextPercent);
}

NS_CC_END

