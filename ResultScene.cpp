#include "ResultScene.h"

#include "GameScene.h"
ResultScene::ResultScene()
{
}
Scene* ResultScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));

	// return the scene  
	return scene;
}

ResultScene::~ResultScene()
{
}
bool ResultScene::init()
{
	CCLog("init");

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	menu = NULL;

	//建立背景
	auto background = CCSprite::create(pic_game_back_ground);
	background->setPosition(Point(visibleSize.width / 2.0, visibleSize.height / 2.0));
	background->setOpacity(opac);
	this->addChild(background, PrioGame::background);
	//background->setOpacity(150);
	this->setTouchEnabled(true);
	scheduleUpdate();
	//2个按钮控制
	

	return true;


}
void ResultScene::statu(int lost)
{
	CCLayer *mmm = this->createmenu();
	this->myScene->addChild(mmm);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	CCSprite *sp = NULL;
	if (lost)
	{
		sp = CCSprite::create("youlost.png");
		if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/youlost.mp3");
		}
	}
	else
	{
		sp = CCSprite::create("youwin.png");
		if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/youwin.mp3");
		}
	}
	sp->setPosition(CCSizeMake(0.5*visibleSize.width,0.8*visibleSize.height));
	this->addChild(sp);
}


CCLayer * ResultScene::createmenu()
{
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//if (!menu){
	menu = CCLayer::create();
	menu->setSwallowsTouches(true);

	auto listen = EventListenerTouchOneByOne::create();
	listen->setSwallowTouches(true);
	listen->onTouchBegan = [=](Touch* touch, Event* event){
		return true;
	};
	//Trigger when moving touch
	listen->onTouchMoved = [=](Touch* touch, Event* event){};

	listen->onTouchEnded = [=](Touch* touch, Event* event){};

	CCSprite *background = CCSprite::create(pic_game_back_ground);
	background->setOpacity(0);
	background->setScale(3);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, background);
	background->setGlobalZOrder(PrioGame::Menu2back);
	menu->addChild(background);
	//background->setOpacity(150);
	
	cocos2d::MenuItemSprite* back_menu = CCMenuItemSprite::create
		(
		Sprite::create("back_menu.png"),
		Sprite::create("back_menu_select.png"),
		CC_CALLBACK_0(ResultScene::menuBackMenuCallback, this)
		);
	back_menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	back_menu->getNormalImage()->setGlobalZOrder(PrioGame::Menu2);
	back_menu->getSelectedImage()->setGlobalZOrder(PrioGame::Menu2);

	//创建退出按钮的精灵
	cocos2d::MenuItemSprite* exit = MenuItemSprite::create
		(
		Sprite::create("exit_game.png"),
		Sprite::create("exit_game_select.png"),
		CC_CALLBACK_0(ResultScene::menuExitGame, this)
		);
	exit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);
	exit->getNormalImage()->setGlobalZOrder(PrioGame::Menu2);
	exit->getSelectedImage()->setGlobalZOrder(PrioGame::Menu2);
	CCMenu *Menu = CCMenu::create(back_menu, exit, NULL);

	//设置菜单位置
	Menu->setPosition(CCPointZero);
	//设置为菜单可用
	Menu->setEnabled(true);
	menu->setSwallowsTouches(true);
	Menu->setGlobalZOrder(PrioGame::Menu2);
	menu->addChild(Menu);
	//}
	return menu;
}


void ResultScene::menuBackMenuCallback()
{
	if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	//返回到菜单界面
	sm->goMenuLayer();

}
void ResultScene::menuExitGame()
{
	if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	//退出
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		exit(0);
	}
#endif
}

