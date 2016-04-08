
#include "HRocker.h"

void HRocker::UpdatePos(float dt)
{
	jsSprite->setPosition(ccpAdd(jsSprite->getPosition(),ccpMult(ccpSub(currentPoint, jsSprite->getPosition()),0.5)));
}
//启动摇杆
void HRocker::Active()
{
	if (!active) 
	{
		active=true;
//		schedule(schedule_selector(HRocker::UpdatePos));//添加刷新函数
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0,false);//添加触摸委托
	}
	else
	{
	}
}
//解除摇杆
void   HRocker::Inactive()
{
	if (active) 
	{
		active=false;
		this->unschedule(schedule_selector(HRocker::UpdatePos));//删除刷新
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);//删除委托
	}
	else 
	{
	}
}
//摇杆方位
CCPoint HRocker::GetDirection()
{
	return ccpNormalize(ccpSub(centerPoint, currentPoint));
}
//摇杆力度
float HRocker::GetVelocity()
{
	return ccpDistance(centerPoint, currentPoint);
}

HRocker * HRocker::Create( void )
{
	HRocker * pRet = new HRocker();
	pRet->autorelease();
	return pRet;
}

HRocker* HRocker:: HRockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole){
	HRocker *jstick=HRocker::Create();
	jstick->InitWithCenter(aPoint,aRadius,aJsSprite,aJsBg,_isFollowRole);
	return jstick;
}
bool HRocker::ccTouchBegan(CCTouch* touch, CCEvent* event)
{

	if (!active)
		return false;
	this->setVisible(true);
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
	if(!isFollowRole)
	{
		if (ccpDistance(touchPoint, centerPoint) > radius)
		{
			return false;
		}
	}
	currentPoint = touchPoint;
	if(isFollowRole)
	{
		centerPoint=currentPoint;
		jsSprite->setPosition(currentPoint);
		this->getChildByTag(88)->setPosition(currentPoint);
	}
	return true;
}
void  HRocker::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CCPoint touchPoint = touch->getLocationInView();
	touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
	if (ccpDistance(touchPoint, centerPoint) > radius)
	{
		currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
	}
	else 
	{
		currentPoint = touchPoint;
	}
}
void  HRocker::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	currentPoint = centerPoint;
	if(isFollowRole)
	{
		this->setVisible(false);
	}
}

HRocker* HRocker::InitWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole)
{
	isFollowRole =_isFollowRole;
	active = false;
	radius = aRadius;
	if(!_isFollowRole)
	{
		centerPoint =aPoint;
	}
	else
	{
		centerPoint =ccp(0,0);
	}

	currentPoint = centerPoint;
	jsSprite = aJsSprite;
	jsSprite->setPosition(centerPoint);
	aJsBg->setPosition(centerPoint);
	aJsBg->setTag(88);
	this->addChild(aJsBg);
	this->addChild(jsSprite);
	if(isFollowRole)
	{
		this->setVisible(false);
	}
	this->Active();//激活摇杆
	return this;
}