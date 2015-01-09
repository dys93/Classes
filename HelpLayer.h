#pragma once
#ifndef __HELPLAYER_H__
#define __HELPLAYER_H__
#endif
#include "SceneManager.h"
#include "cocos2d.h"
USING_NS_CC;
class HelpLayer:public CCLayer
{
public:
	//��ʼ���ķ���
	virtual bool init();
	//���ؼ�����
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	//ȷ����ť�Ļص�����
	void goToMenuLayer();
	//��������Ӧ�ĳ�ʼ�����ͷŹ���
	CREATE_FUNC(HelpLayer);
public:
	//��ť����
	CCMenu* pMenu;
	//��������������
	SceneManager* sm;
	//�ɼ�����
	cocos2d::CCSize visibleSize;
	//ԭ������
	cocos2d::CCPoint origin;
	//��������
	cocos2d::CCSprite* backGround;
};

