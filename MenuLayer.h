#pragma once
#ifndef  _MenuLayer_H_
#define  _MenuLayer_H_
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;
class MenuLayer : public CCLayer{
public:
	//��ʼ���ķ���
	virtual bool init();
	//���ؼ�����
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	//��ת����Ϸ����ķ���
	void goToGameLayer(CCObject* pSender);
	//��ת����������ķ���
	void goToHelpLayer(CCObject* pSender);
	//�˳��Ļص�����
	void musicLayer(CCObject* pSender);
	//�˳���Ϸ
	void exitGame(CCObject* pSender);
	//��ʼ��Ϸ��ť�����������֮��ĵĻص�����
	void setMenuEnabled(CCObject* pSender);
	//����������
	SceneManager *sm;
	//��ť�˵�
	CCMenu* pMenu;
	CREATE_FUNC(MenuLayer);
};
#endif

