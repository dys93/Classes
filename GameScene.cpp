#include "GameScene.h"
#include "SpriteFactory.h"
#include "SceneManager.h"
#include "Toast.h"
Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));

	// return the scene  
	return scene;
}

bool GameScene::init()
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

	/////////////////////////////
	// 3. add your codes below...

	//初始化各种数据

	
	shade = NULL;
	menu = NULL;
	labelcreate();
	AllSprite = CCArray::create();
	movingSprite = CCArray::create();
	SpriteListen= CCArray::create(); //精灵监听
	SpriteMenuListen=CCArray::create();

	AllSprite->retain();
	movingSprite->retain();
	SpriteListen->retain();
	SpriteMenuListen->retain();
	selSprite = NULL;
	//四类监听器
	listener1 = creatSpriteListener();
	listener2 = creatSpriteMenuListener();
	listener3 = creatSpriteMoveListener();
	listener4 = creatSpriteAttackListener();

	listener1->retain();
	listener2->retain();
	listener3->retain();
	listener4->retain();
	control_state = g_begin;
	//建立边界边框
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(CCSizeMake(visibleSize.width*7.0/9.0,visibleSize.height*7.0/9.0), PHYSICSBODY_MATERIAL_DEFAULT, 3);

	edgeSp->setPosition(Point(visibleSize.width /2.0, visibleSize.height /2));
	edgeSp->setPhysicsBody(body);
	this->addChild(edgeSp);

	//建立背景
	auto background = CCSprite::create(pic_game_back_ground);
	background->setPosition(Point(visibleSize.width / 2.0, visibleSize.height /2.0));
	background->setOpacity(opac);
	this->addChild(background,PrioGame::background);
//background->setOpacity(150);
	this->setTouchEnabled(true);
	scheduleUpdate();

	//3个按钮控制回合以及呼出菜单
	startpMenu();
	labelupdate();

	return true;


}

//打开Menu2
void GameScene::openMenuCallback()
{
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCLayer *mmm = this->createmenu();
	this->myScene->addChild(mmm);
	stoppMenu();
	if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
}
//未完成  战争迷雾效果
CCLayer * GameScene::createshadelayer()
{
	//if (shade==NULL){
		shade = CCLayer::create();
		CCSprite *background = CCSprite::create("shade.png");
		background->setOpacity(shade_opacity);
		background->setPosition(CCDirector::sharedDirector()->getVisibleSize()/2);
		shade->setVisible(false);
		background->setGlobalZOrder(PrioGame::shade);
		shade->addChild(background);
	//}
	return shade;
}
//菜单呼出
CCLayer * GameScene::createmenu()
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
		listen->onTouchMoved = [=](Touch* touch, Event* event){	};
		
		listen->onTouchEnded = [=](Touch* touch, Event* event){	};

		CCSprite *background = CCSprite::create(pic_game_back_ground);
		background->setOpacity(100);
		background->setScale(3);
		background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,background);
		background->setGlobalZOrder(PrioGame::Menu2back);
		menu->addChild(background);
		//background->setOpacity(150);
		cocos2d::MenuItemSprite* back_game = MenuItemSprite::create
			(
			Sprite::create("back_game.png"),
			Sprite::create("back_game_select.png"),
			CC_CALLBACK_0(GameScene::menuContinueCallback, this)
			);
		back_game->getNormalImage()->setGlobalZOrder(PrioGame::Menu2);
		back_game->getSelectedImage()->setGlobalZOrder(PrioGame::Menu2);
		back_game->setPosition(visibleSize.width / 2, visibleSize.height / 2+150);
		back_game->setGlobalZOrder(PrioGame::Menu2);
		cocos2d::MenuItemSprite* back_menu = CCMenuItemSprite::create
			(
			Sprite::create("back_menu.png"),
			Sprite::create("back_menu_select.png"),
			CC_CALLBACK_0(GameScene::menuBackMenuCallback, this)
			);
		back_menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		back_menu->getNormalImage()->setGlobalZOrder(PrioGame::Menu2);
		back_menu->getSelectedImage()->setGlobalZOrder(PrioGame::Menu2);

		//创建退出按钮的精灵
		cocos2d::MenuItemSprite* exit = MenuItemSprite::create
			(
			Sprite::create("exit_game.png"),
			Sprite::create("exit_game_select.png"),
			CC_CALLBACK_0(GameScene::menuExitGame, this)
			);
		exit->setPosition(visibleSize.width / 2, visibleSize.height / 2-150);
		exit->getNormalImage()->setGlobalZOrder(PrioGame::Menu2);
		exit->getSelectedImage()->setGlobalZOrder(PrioGame::Menu2);
		CCMenu *Menu = CCMenu::create(back_game,back_menu,exit, NULL);
		
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
void GameScene::menuBackMenuCallback()
{
	if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	stopSpriteAttackListen();
	stopSpriteListen();
	stopSpriteMenuListen();
	stopSpriteMoveListen();

	//返回到菜单界面
	sm->goMenuLayer();

}
void GameScene::menuExitGame()
{
	if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
	}
	//退出
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		exit(0);
	}
#endif
}


void GameScene :: menuContinueCallback()
{
	this->myScene->removeChild(menu);
	//设置为菜单可用
	startpMenu();
}
//游戏回合控制菜单的相关函数
void GameScene::initpMenu()
{
	auto visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	cocos2d::MenuItemSprite* over_round = MenuItemSprite::create
		(
		Sprite::create("over_round.png"),
		Sprite::create("over_round_select.png"),
		CC_CALLBACK_0(GameScene::change_state_over_round, this)
		);
	over_round->setPosition(visibleSize.width / 5, 50);

	//创建跳过一天
	cocos2d::MenuItemSprite* over_day = CCMenuItemSprite::create
		(
		Sprite::create("over_day.png"),
		Sprite::create("over_day_select.png"),
		CC_CALLBACK_0(GameScene::change_state_over_day, this)
		);
	over_day->setPosition(visibleSize.width / 2, 50);
	//创建打开菜单
	cocos2d::MenuItemSprite* open_menu = MenuItemSprite::create
		(
		Sprite::create("open_game_menu.png"),
		Sprite::create("open_game_select.png"),
		CC_CALLBACK_0(GameScene::openMenuCallback, this)
		);
	open_menu->setPosition(visibleSize.width / 5 * 4, 50);
	this->pMenu = CCMenu::create(over_round, over_day, open_menu, NULL);
	
	//设置菜单位置
	this->pMenu->setPosition(CCPointZero);
}
void GameScene::startpMenu()
{
	if (pMenu == NULL)
	{
		initpMenu();
		pMenu->setGlobalZOrder(PrioGame::Menu1);
		this->addChild(this->pMenu);
	}
	this->pMenu->setVisible(true);
	this->pMenu->setEnabled(true);
}
void GameScene::stoppMenu()
{
	if (pMenu == NULL)
	{
		initpMenu();
		pMenu->setGlobalZOrder(PrioGame::Menu1);
		this->addChild(this->pMenu);
	}
	//this->pMenu->setVisible(false);
	this->pMenu->setEnabled(false);
}

void GameScene::change_state_start_round()
{
	if (enemy_total_spritenum == 0)
	{
		CCLog("youwin");
		Toast::makeText(this, "YOU WIN", 2.5f);
		sm->goResultScene(0);
		return;
	}
	if (my_total_spritenum == 0)
	{
		CCLog("youlost");
		Toast::makeText(this, "YOU LOST", 2.5f);
		sm->goResultScene(1);
		return;
	}
	CCLog("start_round");
	
	if (enemy_ready_spritenum<=0&&my_ready_spritenum<=0)
	{
		change_state_start_day();
		return;
	}
	//Toast::makeText(this, "START ROUND", 2.5f);
	int r = rand();
	int m = (enemy_ready_spritenum > 0 ? enemy_ready_spritenum : 0 )+ (my_ready_spritenum > 0 ? my_ready_spritenum : 0);
	myTurn = (r%m)< my_ready_spritenum;
	if (myTurn)
	{
		startpMenu();
		CCLog("Your Turn");
		Toast::makeText(this, "Your Turn", 2.5f);
		//分发
		//selSprite = NULL;
		//control_state = g_begin;
		startSpriteListen();
		control_state = g_begin;
	}
	else//AI的第一步
	{
		stoppMenu();
		//执行AI
		CCLog("enemyturn");
		
		selSprite = MyAIget(1,0);
		if (selSprite== NULL)
		{
			change_state_over_round();
			return;
		}
		int ttag = selSprite->getTag();
		if (selSprite->kind == 3)
		{
			create_ani(1,rand()%3, CCSizeMake(selSprite->getPositionX(), selSprite->getPositionY() - 100));		
		}
		selSprite = MyAIget(1,0);
		
		MySprite *target = MyAIget(0,0);
		if (target == NULL)target = MyAIget(0, 1);
		if (target == NULL)
		{
			change_state_over_round();
			return;
		}
		else
		{
			auto speed = target->getPosition() - selSprite->getPosition();
			switch (selSprite->kind)
			{

			case 0://牛
				change_state_attack();
				selSprite->attack(speed);

				stopSpriteAttackListen();
				movingSprite->addObject(selSprite);
				break;
			case 1://马
			case 2://蛇
				change_state_move1();
				selSprite->addspeed(speed);
				movingSprite->addObject(selSprite);
				stopSpriteMoveListen();
				break;
			case 3://龙
				change_state_over_round();
				break;
			default:
				change_state_over_round();
				break;
			}
		}

	
		//先选择可执行对象 若没有就结束
		//根据对象选择操作
		//
	//	enemy_ready_spritenum--;
		
	}

};
//随机选取目标
MySprite * GameScene::MyAIget(int belongto,int sleeptime)
{
	int m = rand() % AllSprite->count();
	MySprite *mysp=NULL;
	if (AllSprite->count() == 0)
		return NULL;
	int n = AllSprite->count();
	for (int i = 0; i < n; i++)
	{
		mysp = (MySprite *)AllSprite->getObjectAtIndex((i+m)%n);
		if (mysp->belongto == belongto&&mysp->sleeptime==sleeptime)
			return mysp;
	}
	return NULL;
}
void GameScene::change_state_over_round()
{ 
	
	if (  movingSprite->count()>0)
	{
		return ;
	}
	CCLog("overround");
	stopSpriteListen();
	stopSpriteMenuListen();
	stopSpriteAttackListen();
	stopSpriteMoveListen();

	

	if (selSprite != NULL)
	{
		selSprite->trysleep();
		selSprite->nosel(control_state);
	}
	
	if (myTurn){
		my_ready_spritenum--;
	}
	else
	{
		enemy_ready_spritenum--;
	}
	labelupdate();
	
	control_state = g_end;
	if (selSprite != NULL)
	{
		selSprite = NULL;
	}
	
	change_state_start_round();
	//启用AI进行enemy的操作：

}	
void GameScene::change_state_start_day()
{
	CCLog("startday");
	this->enemy_ready_spritenum = enemy_total_spritenum;
	this->my_ready_spritenum = my_total_spritenum;
	if (UserDefault::sharedUserDefault()->getBoolForKey("limit", true) == false)
	{
		changemoney(+earn);
	}
	changemoney(+100);
	for (int i = 0; i<AllSprite->count(); i++)
	{
		auto mysp = ((MySprite*)(AllSprite->getObjectAtIndex(i)));
		mysp->dayup();
	}
	labelupdate();
	change_state_start_round();
}
void GameScene::change_state_over_day()
{
	CCLog("overday");
	my_ready_spritenum = 1;
	labelupdate();
	change_state_over_round();
}

void GameScene::change_state_sel(){
	switch (control_state)
	{
	case g_begin:
		//分发
		startSpriteMenuListen();
		break;
	case g_sel:
		stopSpriteMenuListen();
		startSpriteMenuListen();
		break;
	}
	control_state = g_sel;
}
void GameScene::change_state_move1()
{
	//分发
	CCLog("move1");
	stopSpriteListen();
	stopSpriteMenuListen();
	startSpriteMoveListen();
	control_state = g_move1;
};
void GameScene::change_state_move2()
{
	//分发
	CCLog("move2");
	stopSpriteListen();
	stopSpriteMenuListen();
	selSprite->nosel(control_state);
	startSpriteMoveListen();
	control_state = g_move2;
};
void GameScene::change_state_attack()
{

	stopSpriteListen();
	stopSpriteMenuListen();
	selSprite->hidemenu();
	//分发
	startSpriteAttackListen();
	control_state = g_attack;
};
//建立精灵 通过种类和所有者 以及位置
MySprite* GameScene::create_ani(int b,int k, CCSize position)
{
	MySprite * firsttest = MySprite::creates(b,k);
	firsttest->setZOrder(PrioGame::Sprite);
	this->addChild(firsttest );
	AllSprite->addObject(firsttest);
	firsttest->setPosition(position);
	if (b <= 1){
		my_total_spritenum += 1 - b;
		enemy_total_spritenum += b;
	}
	labelupdate();
	return firsttest;
}

//精灵按键
void GameScene::startSpriteListen()
{
	for (int i = 0; i < AllSprite->count(); i++)
	{
		
		MySprite *mysp = (MySprite *)AllSprite->getObjectAtIndex(i);
		if (myTurn)
		{
			if ((mysp->belongto + myTurn)==1&&mysp->sleeptime==0)
			{
				EventListenerTouchOneByOne * listen = listener1->clone();
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, mysp);
				SpriteListen->addObject(listen);
			}
		}
	}
}
void GameScene::stopSpriteListen()
{
	for (int i = 0; i < SpriteListen->count(); i++)
	{
		_eventDispatcher->removeEventListener((EventListenerTouchOneByOne*)SpriteListen->getObjectAtIndex(i));
	}
	SpriteListen->removeAllObjects();
}
//精灵按键
EventListenerTouchOneByOne* GameScene::creatSpriteListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			if (selSprite != NULL)
			{
				selSprite->nosel(control_state);
				selSprite = NULL;
			}
			
			return true;
		}
		return false;
	};
	//Trigger when moving touch
	listener1->onTouchMoved = [=](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			CCLog("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			
		}
	};
	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			selSprite = target;
			selSprite->besel(control_state);
			change_state_sel();
		}
		if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
		}
		if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
		}
	};
	return listener1;
}
//精灵菜单
void GameScene::startSpriteMenuListen()
{
	CCSprite *ccsp;
	for (int i = 0;selSprite!=NULL&& i < selSprite->menu->count(); i++)
	{
		//蛇的第二次运动不显示移动
		if (i==2&&control_state == g_move1&&selSprite->kind==2)
		{
			ccsp = (CCSprite*)selSprite->menu->objectAtIndex(i);
			ccsp->setVisible(false);
			continue;
		}
		//龙的中间功能开启，其他的关闭切不显示
		if (myTurn&&selSprite->belongto == 0 && (i != 1 || selSprite->kind == 3))
		{
			EventListenerTouchOneByOne * listen = listener2->clone();
			SpriteMenuListen->addObject(listen);
			ccsp = (CCSprite*)selSprite->menu->objectAtIndex(i);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, ccsp);
		}
	}
}
void GameScene::stopSpriteMenuListen()
{
	for (int i = 0;  i < SpriteMenuListen->count(); i++)
	{
		auto* listen = (EventListenerTouchOneByOne*)SpriteMenuListen->getObjectAtIndex(i);
			_eventDispatcher->removeEventListener(listen);
	}
	SpriteMenuListen->removeAllObjects();
}
EventListenerTouchOneByOne* GameScene::creatSpriteMenuListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			CCLog("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			return true;
		}
		return false;
	};
	//Trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event){
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//Check the click area

		if (rect.containsPoint(locationInNode))
		{
			int tag = target->getTag();
			int a, b;
			selSprite->hidemenu();
			switch (tag)
			{
			case 30:  //三种动物创建
			case 31:
			case 32:
			
				if (money - moneycost[tag % 10] >= 0)
				{
					changemoney(-moneycost[tag%10]);
					create_ani(0,tag%10, CCSizeMake(selSprite->getPositionX(), selSprite->getPositionY() + 100));
				}
				else{
					CCLog("don't have enough money");
				}
				selSprite->nosel(control_state);
				selSprite = NULL;
				stopSpriteMenuListen();
				break;
				
				//攻击
			case 00:
			case 10:
			case 20:
				change_state_attack();
				break;
			case 01:
			case 11:
			case 21:
				//未完成sleep
				selSprite->nosel(control_state);
				break;
			case 02:
			case 12:
			case 22:
				if (selSprite->hasmove)
					change_state_move2();
				else 
					change_state_move1();
				break;
			default:
				break;
			}
		}
		if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/select.wav");
		}
	};
	return listener1;
}
void  GameScene::startSpriteMoveListen()
{
	stopSpriteMoveListen();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3,selSprite);
}
void  GameScene::stopSpriteMoveListen()
{
	_eventDispatcher->removeEventListener(listener3);
}

void  GameScene::startSpriteAttackListen()
{
	stopSpriteAttackListen();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, selSprite);
}
void  GameScene::stopSpriteAttackListen()
{
	_eventDispatcher->removeEventListener(listener4);
}
EventListenerTouchOneByOne* GameScene::creatSpriteMoveListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		return false;
	};
	//Trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event){
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		//Check the click area
		auto speed = selSprite->getPosition() - touch->getLocation();

		selSprite->addspeed(speed);
			//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, selSprite);
		movingSprite->addObject(selSprite);
		stopSpriteMoveListen();
		selSprite->setOpacity(255);
	};
	return listener1;
}

EventListenerTouchOneByOne* GameScene::creatSpriteAttackListener()
{

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			return true;
		}
		return false;
	};
	//Trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event){
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		auto target = static_cast<MySprite*>(event->getCurrentTarget());
		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		//Check the click area
		if (selSprite == NULL)
			change_state_sel();
		auto speed = selSprite->getPosition() - touch->getLocation();

		//有点问题？
			auto * array = selSprite->attack(speed);
			if(array!=NULL)
				movingSprite->addObject(array);
			movingSprite->addObject(selSprite);
		
		stopSpriteAttackListen();
		selSprite->setOpacity(255);
	};
	return listener1;

}


void GameScene::update(float dt)
{
	
	int t=movingSprite->count();
	//t==0 说明没有运动的单位
	if (t == 0)return;
	t--;    //因为t是最大的标号+1
	for (; t>=0; t--)
	{
		
		MySprite * sp = (MySprite*)movingSprite->getObjectAtIndex(t);
		int ttt= sp->getTag();
		Vec2 mm = (sp->getPhysicsBody())->getVelocity();
		if (sp->getPhysicsBody()->getVelocity().getDistance(CCPointZero)<10.)
		{
			movingSprite->removeObjectAtIndex(t);
			if (sp->trydie())
			{
				//死亡操作
				int tag = sp->getTag();
				if (sp->kind != 4)
				{
					if (sp->kind != 3){
						CCParticleSystem *par = sp->die_animation();
						par->setPosition(sp->getPosition());
						par->setGlobalZOrder(PrioGame::SpriteDiePar);
						this->addChild(par);
					}
					if (tag / 100 != 2){
						my_total_spritenum -= 1 - tag / 100;
						enemy_total_spritenum -= tag / 100;
					}
					if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/dead.wav");
					}
				}
				
				AllSprite->removeObject(sp);
			}
		}
	}
	labelupdate();
	//这个时候>0 表示还有运动的单位
	t = movingSprite->count();
	if ( t >0 )return;
	
	if (selSprite!=NULL&&selSprite->hasmove)
	{
		switch (control_state)
		{
		case g_move1:
			if (myTurn)
			{
				startpMenu();
				int mm = selSprite->hasmove;
				if (selSprite->hasmove >= selSprite->Maxmove)
				{
					change_state_over_round();
				}
				else
				{
					selSprite->besel(control_state);
					this->startSpriteMenuListen();
				}

			}
			else if (!myTurn)  //执行ai的攻击动作
			{
				CCLog("beginAIattack");
				MySprite *target = MyAIget(0,0);
				if (target == NULL)target = MyAIget(0, 1);
				if (target != NULL)
				{
					CCLog("enemyattack");
					auto speed = target->getPosition() - selSprite->getPosition();
	
					auto array = selSprite->attack(speed);
					if(array!=NULL)movingSprite->addObject(array);
					movingSprite->addObject(selSprite);
					
					stopSpriteAttackListen();
				}
				change_state_attack();
			}
			
			break;
		case g_attack:
			if (selSprite->hasattck)
				change_state_over_round();
			
			break;
		case g_move2:
			if (selSprite->hasmove>=selSprite->Maxmove)
				change_state_over_round();
			break;

		}
	}
}


void GameScene::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [=](const PhysicsContact& contact)
	{
		//CCLog("onContactBegin");
		auto *sp1 = (MySprite*)contact.getShapeA()->getBody()->getNode();
		auto *sp2 = (MySprite*)contact.getShapeB()->getBody()->getNode();
		if (sp1->getPhysicsBody()->getVelocity().getDistance(CCPointZero) > 11.0 ||
			sp2->getPhysicsBody()->getVelocity().getDistance(CCPointZero) > 11.0)
		{
			if (sp1->belongto != sp2->belongto)
			{
				//在对方回合移动的就会受到伤害
				if ((sp1->belongto + myTurn) != 1 && control_state == g_attack)
				{
					//受到伤害
					if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hit.mp3");
					}
					sp1->behurt();
				}
				if ((sp2->belongto + myTurn) != 1 && control_state == g_attack)
				{
					//受到伤害
					if (UserDefault::sharedUserDefault()->getIntegerForKey("effectFlag", 1) == 1)
					{
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hit.mp3");
					}
					sp2->behurt();
				}
			}
			if (!movingSprite->containsObject(sp1))
				movingSprite->addObject(sp1);
			if (!movingSprite->containsObject(sp2))
				movingSprite->addObject(sp2);
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10);


}

GameScene::~GameScene(void)
{

	AllSprite->release();
	movingSprite->release();
	SpriteListen->release();
	SpriteMenuListen->release();

	listener1->release();
	listener2->release();
	listener3->release();
	listener4->release();

}

void GameScene::labelcreate()
{
	CCSize size = CCDirector::getInstance()->getVisibleSize();

		moneylabel = CCLabelBMFont::create
			("0",
			"fonts/font_kick bug.fnt");
		CCSprite *m_l = CCSprite::create("money.png");
		m_l->setPosition(Vec2(size.width / 7, size.height *20/ 21));
		m_l->setScale(0.5);
		moneylabel->setPosition(Vec2(size.width / 7 + size.width / 11, size.height * 20 / 21));
		
		this->addChild(m_l,PrioGame::PlayerInfor);
		
		this->addChild(moneylabel, PrioGame::PlayerInfor);
		
		readyspritelabel = CCLabelBMFont::create
			("0",
			"fonts/font_kick bug.fnt");
		CCSprite *r_s = CCSprite::create("run.png");
		r_s->setScale(0.5);
		r_s->setPosition(Vec2(size.width * 3 / 7, size.height * 20 / 21));

		readyspritelabel->setPosition(Vec2(size.width * 3 / 7 + size.width / 11, size.height * 20 / 21));
	//	r_s->setGlobalZOrder();
		this->addChild(r_s, PrioGame::PlayerInfor);
	//	readyspritelabel->setGlobalZOrder(PrioGame::PlayerInfor);
		this->addChild(readyspritelabel, PrioGame::PlayerInfor);

	
		totalspritelabel = CCLabelBMFont::create
			("0",
			"fonts/font_kick bug.fnt");
		CCSprite *t_s = CCSprite::create("total.png");
		t_s->setPosition(Vec2(size.width * 5 / 7, size.height * 20 / 21));
		t_s->setScale(0.5);
		totalspritelabel->setPosition(Vec2(size.width * 5 / 7 + size.width / 11, size.height * 20 / 21));
	//	t_s->setGlobalZOrder(PrioGame::PlayerInfor);
		this->addChild(t_s, PrioGame::PlayerInfor);
	//	totalspritelabel->setGlobalZOrder(PrioGame::PlayerInfor);
		this->addChild(totalspritelabel, PrioGame::PlayerInfor);

	
}
void GameScene::labelupdate()
{
	moneylabel->setString((CCString::createWithFormat("%d", money))->getCString());
	readyspritelabel->setString((CCString::createWithFormat("%d", my_ready_spritenum))->getCString());
	totalspritelabel->setString((CCString::createWithFormat("%d", my_total_spritenum))->getCString());
}
void GameScene::changemoney(int change)
{
	money += change;
	labelupdate();
}