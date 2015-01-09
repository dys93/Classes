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
	//初始化的方法
	virtual bool init();
	//返回键监听
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	//确定按钮的回调方法
	void goToMenuLayer();
	//并做好相应的初始化与释放工作
	CREATE_FUNC(HelpLayer);
public:
	//按钮引用
	CCMenu* pMenu;
	//场景管理者引用
	SceneManager* sm;
	//可见区域
	cocos2d::CCSize visibleSize;
	//原点坐标
	cocos2d::CCPoint origin;
	//背景精灵
	cocos2d::CCSprite* backGround;
};

