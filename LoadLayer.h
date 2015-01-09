#pragma once
#ifndef  _LoadLayer_H_
#define  _LoadLayer_H_
#endif
#include "cocos2d.h"
#include "SceneManager.h"
using namespace cocos2d;
class LoadLayer :
	public CCLayer
{
public:
	//初始化的方法
	virtual bool init();
	//所属管理者
	SceneManager *sm;
	//跳转到菜单界面的方法
	void goToMenuLayer(CCObject* pSender);
	CREATE_FUNC(LoadLayer);
};

