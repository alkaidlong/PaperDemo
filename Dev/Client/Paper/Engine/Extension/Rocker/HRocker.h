#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class HRocker :public CCLayer {

public :
	
	static HRocker *Create(void);
	//��ʼ�� aPoint��ҡ������ aRadius��ҡ�˰뾶 aJsSprite��ҡ�˿��Ƶ� aJsBg��ҡ�˱���
	static HRocker*  HRockerWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole);
	//����ҡ��
	void Active();
	//���ҡ��
	void Inactive();

public:
	CCPoint GetDirection();
	float GetVelocity();
	void  UpdatePos(float dt);
private:
	HRocker * InitWithCenter(CCPoint aPoint ,float aRadius ,CCSprite* aJsSprite,CCSprite* aJsBg,bool _isFollowRole);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCPoint centerPoint;//ҡ������
	CCPoint currentPoint;//ҡ�˵�ǰλ��
	bool active;//�Ƿ񼤻�ҡ��
	float radius;//ҡ�˰뾶
	CCSprite *jsSprite;
	bool isFollowRole;//�Ƿ�����û����
};
