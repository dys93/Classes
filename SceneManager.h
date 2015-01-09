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
		//������������ķ���
		CCScene *loadScene;
		CCScene *menuScene;
		CCScene *gameScene;
		CCScene *helpScene;
		//������������ķ���
		void createScene();
		void goMenuLayer();
		void goGameScene();
		void goHelpLayer();
};


