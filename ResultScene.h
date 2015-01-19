#pragma once
#ifndef  _ResultScene_H_
#define  _ResultScene_H_
#endif
#include "cocos2d.h"
#include "SpriteFactory.h"
#include "SceneManager.h"
#include "infor.h"


USING_NS_CC;
class ResultScene:public CCLayer
{
public:
	ResultScene();
	~ResultScene();
	void statu(int win);
	static Scene * createScene();
	SceneManager * sm;
	CCScene *myScene;
	virtual bool init();
	CCLayer *menu;
	void menuBackMenuCallback();
	void menuExitGame();
	CCLayer * createmenu();
	CREATE_FUNC(ResultScene);
};

