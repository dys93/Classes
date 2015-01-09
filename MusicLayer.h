#pragma once
#ifndef _MusicLayer_h
#define _MusicLayer_h
#endif
#include "cocos2d.h"//����ͷ�ļ�
using namespace cocos2d;//ʹ�������ռ�
class MusicLayer : public CCLayer{
public:
	CCMenu* pMenu;
	//����������ť�ľ���
	 cocos2d::MenuItemSprite* soundon;
	//����������ť�ľ���
	 cocos2d::MenuItemSprite* soundclose;
	//������Ч��ť�ľ���
	 cocos2d::MenuItemSprite* effecton;
	//������Ч��ť�ľ���
	 cocos2d::MenuItemSprite* effectclose;

public:

	virtual bool init();
	void initDialog();


	//���ؼ�����
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	//���ؼ��Ļص�����
	void menuCallbackKeyBackClicked(CCObject* pSender);
	//���ڽ��붯��ִ����֮��Ļص�����
	void resumeMenu();
	//������
	void  menuCallbacKOpenMusic(CCObject* pSender);
	//�ر�����
	void  menuCallbackCloseMusic(CCObject* pSender);
	//����Ч
	void  menuCallbackOpengEffect(CCObject* pSender);
	//�ر���Ч
	void  menuCallbackCloseEffect(CCObject* pSender);
	//���ز˵�
	void  menuCallbacKToMenuLayer(CCObject* pSender);
	CREATE_FUNC(MusicLayer);
};

