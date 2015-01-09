#pragma once
#ifndef _MusicLayer_h
#define _MusicLayer_h
#endif
#include "cocos2d.h"//导入头文件
using namespace cocos2d;//使用命名空间
class MusicLayer : public CCLayer{
public:
	CCMenu* pMenu;
	//创建声音按钮的精灵
	 cocos2d::MenuItemSprite* soundon;
	//创建声音按钮的精灵
	 cocos2d::MenuItemSprite* soundclose;
	//创建音效按钮的精灵
	 cocos2d::MenuItemSprite* effecton;
	//创建音效按钮的精灵
	 cocos2d::MenuItemSprite* effectclose;

public:

	virtual bool init();
	void initDialog();


	//返回键监听
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	//返回键的回调方法
	void menuCallbackKeyBackClicked(CCObject* pSender);
	//层在进入动作执行完之后的回调方法
	void resumeMenu();
	//打开声音
	void  menuCallbacKOpenMusic(CCObject* pSender);
	//关闭声音
	void  menuCallbackCloseMusic(CCObject* pSender);
	//打开音效
	void  menuCallbackOpengEffect(CCObject* pSender);
	//关闭音效
	void  menuCallbackCloseEffect(CCObject* pSender);
	//返回菜单
	void  menuCallbacKToMenuLayer(CCObject* pSender);
	CREATE_FUNC(MusicLayer);
};

