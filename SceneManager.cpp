#include "SceneManager.h"

#include "GameScene.h"
#include "ControlLayer.h"
#include "LoadLayer.h"
#include "MenuLayer.h"
#include "HelpLayer.h"
#include "MapFactory.h"
using namespace cocos2d;
//ʵ��createScene����
void SceneManager::createScene()
{
	//����CCScene������������
	loadScene = CCScene::create();
	//����LoadLayer��������
	LoadLayer *loadLayer = LoadLayer::create();
	//���ó���������
	loadLayer->sm = this;
	//�򳡾�����Ӳ���
	loadScene->addChild(loadLayer);
}
void SceneManager::goGameScene()
{
	//������������ 
	gameScene = CCScene::create();
	//������������
	gameScene = GameScene::createScene();
	auto layer = GameScene::create();
	gameScene->retain();
	layer->setPhyWorld(gameScene->getPhysicsWorld());
	layer->sm = this;
	layer->myScene = gameScene;
	layer->retain();
	gameScene->addChild(layer, 2);
	
	//�������layer

	if (UserDefault::sharedUserDefault()->getBoolForKey("openshade"), 1);
	{
		gameScene->addChild(layer->createshadelayer(), 3);
	}
	MapFactory map;
	map.getMap(3);
	map.MapLoad(layer);
	//���ó���������
	//controlLayer->sm = this;
	//�����л���Ч
	CCTransitionScene* ccts = CCTransitionFade::create(0.8, gameScene, ccWHITE);
	//ִ���л�
	CCDirector::sharedDirector()->replaceScene(ccts);
	layer->change_state_start_day();
}
void SceneManager::goMenuLayer()
{
	//������������
	menuScene = CCScene::create();
	//������������
	MenuLayer *menuLayer = MenuLayer::create();
	//�򳡾�����Ӳ���
	menuScene->addChild(menuLayer);
	//���ó���������
	menuLayer->sm = this;
	//�����л���Ч
	CCTransitionScene* ccts = CCTransitionFade::create(1.5, menuScene, ccWHITE);
	//ִ���л�
	CCDirector::sharedDirector()->replaceScene(ccts);
}
void SceneManager::goHelpLayer()
{
	//������������
	helpScene = CCScene::create();
	//������������
	HelpLayer *helpLayer = HelpLayer::create();
	//�򳡾�����Ӳ���
	helpScene->addChild(helpLayer);
	//���ó���������
	helpLayer->sm = this;
	//�����л���Ч
	CCTransitionScene* ccts = CCTransitionFade::create(1.5, helpScene, ccWHITE);
	//ִ���л�
	CCDirector::sharedDirector()->replaceScene(ccts);
}