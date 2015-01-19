
#pragma once
#ifndef  _GameScene_H_
#define  _GameScene_H_
#endif
#include "cocos2d.h"
#include "SpriteFactory.h"
#include "SceneManager.h"
#include "infor.h"

USING_NS_CC;

class GameScene:public CCLayer
{
public:

	static Scene * createScene();
	CCScene *myScene;
	virtual bool init();

	CCLayer *createshadelayer();

	//打开菜单
	CCLayer *createmenu();

	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	
	
	CREATE_FUNC(GameScene);

	SceneManager *sm;

	//控制游戏回合以及菜单呼出的menu 

	CCMenu *pMenu=NULL;

	void initpMenu();
	void startpMenu();
	void stoppMenu();

	//未知的阴影效果
	CCLayer *shade;	
	
	//用于系统菜单的layer
	CCLayer *menu;
	//打开游戏菜单
	void openMenuCallback();

	//游戏菜单的回调函数
	void menuContinueCallback();
	void menuBackMenuCallback();
	void menuExitGame();

	CCLabelBMFont* moneylabel;
	CCLabelBMFont* readyspritelabel;
	CCLabelBMFont* totalspritelabel;
	void labelcreate();
	void labelupdate();
	bool myTurn=true;       //交替轮回
	int money=0;				//你的钱
	void changemoney(int change);
	int earn=30;
	int enemy_ready_spritenum=0;     //敌人可移动数量
	int my_ready_spritenum=0;		//你的可移动数量
	int enemy_total_spritenum=0;     //敌人可移动数量
	int my_total_spritenum=0;		//你的可移动数量
	
	void changemoney();
	void change_state_start_round();
	void change_state_over_round();
	void change_state_start_day();
	void change_state_over_day();
	void change_state_sel();
	void change_state_move1();
	void change_state_move2();
	void change_state_attack();

	MySprite *create_ani(int b, int k, CCSize position);

	


	CCArray *SpriteListen; //精灵监听
	CCArray *SpriteMenuListen; //精灵菜单监听
	CCArray  *AllSprite; //mysprite的单位
	CCArray  *movingSprite;   //正在动的用于判定是否可以进行伤害结算以及减少判定范围

	PhysicsWorld* m_world;	
	
	//控制类
	MySprite *selSprite;	//选定的
	GameState control_state;//控制状态

	void startSpriteListen();
	void stopSpriteListen();
	
	void startSpriteMenuListen();
	void stopSpriteMenuListen();

	void startSpriteMoveListen();
	void stopSpriteMoveListen();

	void startSpriteAttackListen();
	void stopSpriteAttackListen();
	
	EventListenerTouchOneByOne* creatSpriteListener();
	EventListenerTouchOneByOne* creatSpriteMenuListener();
	EventListenerTouchOneByOne* creatSpriteMoveListener();
	EventListenerTouchOneByOne* creatSpriteAttackListener();

	EventListenerTouchOneByOne* listener1;  //精灵的监听
	EventListenerTouchOneByOne* listener2;	//精灵菜单监听
	EventListenerTouchOneByOne* listener3;  //移动监听
	EventListenerTouchOneByOne* listener4;  //攻击监听
	void update(float dt);
	void onEnter();


	MySprite * MyAIget(int belongto, int issleep);


	virtual ~GameScene();

};

