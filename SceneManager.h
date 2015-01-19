#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#endif

#pragma once
#include "cocos2d.h"
#include "SceneManager.h"

USING_NS_CC;
class SceneManager
{
public:
		//创建场景对象的方法
		CCScene *loadScene;
		CCScene *menuScene;
		CCScene *gameScene;
		CCScene *helpScene;
		CCScene *resultScene;
		//创建场景对象的方法
		void createScene();
		void goMenuLayer();
		void goGameScene();
		void goHelpLayer();
		//1输
		void goResultScene(int result);
};


