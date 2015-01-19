#include "SceneManager.h"

#include "GameScene.h"
#include "ControlLayer.h"
#include "LoadLayer.h"
#include "MenuLayer.h"
#include "HelpLayer.h"
#include "MapFactory.h"
using namespace cocos2d;
//实现createScene方法
void SceneManager::createScene()
{
	//创建CCScene（场景）对象
	loadScene = CCScene::create();
	//创建LoadLayer布景对象
	LoadLayer *loadLayer = LoadLayer::create();
	//设置场景管理者
	loadLayer->sm = this;
	//向场景中添加布景
	loadScene->addChild(loadLayer);
}
void SceneManager::goGameScene()
{
	//创建场景对象 
	gameScene = CCScene::create();
	//创建布景对象
	gameScene = GameScene::createScene();
	auto layer = GameScene::create();
	gameScene->retain();
	layer->setPhyWorld(gameScene->getPhysicsWorld());
	layer->sm = this;
	layer->myScene = gameScene;
	layer->retain();
	gameScene->addChild(layer, 2);
	
	//添加其他layer

	if (UserDefault::sharedUserDefault()->getBoolForKey("openshade"), 1);
	{
		gameScene->addChild(layer->createshadelayer(), 3);
	}
	MapFactory map;
	map.getMap(3);
	map.MapLoad(layer);
	//设置场景管理者
	//controlLayer->sm = this;
	//创建切换特效
	CCTransitionScene* ccts = CCTransitionFade::create(0.8, gameScene, ccWHITE);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
	layer->change_state_start_day();
}
void SceneManager::goMenuLayer()
{
	//创建场景对象
	menuScene = CCScene::create();
	//创建布景对象
	MenuLayer *menuLayer = MenuLayer::create();
	//向场景中添加布景
	menuScene->addChild(menuLayer);
	//设置场景管理者
	menuLayer->sm = this;
	//创建切换特效
	CCTransitionScene* ccts = CCTransitionFade::create(1.5, menuScene, ccWHITE);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}
void SceneManager::goHelpLayer()
{
	//创建场景对象
	helpScene = CCScene::create();
	//创建布景对象
	HelpLayer *helpLayer = HelpLayer::create();
	//向场景中添加布景
	helpScene->addChild(helpLayer);
	//设置场景管理者
	helpLayer->sm = this;
	//创建切换特效
	CCTransitionScene* ccts = CCTransitionFade::create(1.5, helpScene, ccWHITE);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}