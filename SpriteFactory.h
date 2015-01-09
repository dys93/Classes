
#pragma once
#include<string>
#include "cocos2d.h"
#include "infor.h"

using namespace std;
USING_NS_CC;
class MySprite:public CCSprite
{
public:

	static  MySprite *creates(int belongto, int kind);
	CCSprite *sleep;

	bool trysleep();
	void getup_animation();
	void dayup();
	void sleep_animation();

	CCParticleSystem * die_animation();
	bool trydie();
	


	CCSprite *breakshade;
	int hasmove;
	int Maxmove;
	int Maxspeed;
	int kind;//
	int belongto;
	bool hurt;
	bool ismenushow;
	bool hasattck;
	int Maxblood;
	int sleeptime;
	int menunum;

	void hidemenu();
	void showmenu();
	void hidemenu2();
	void createmenu();
	
	//移动时调用
	void addspeed(Vec2 speed);
	//选中的时候调用
	void besel(GameState state);
	//取消选中时调用
	void nosel(GameState state);
	//受到伤害时调用
	void behurt();
	//发出攻击时调用snack 攻击返回子弹
	MySprite* attack(Vec2 speed);
	

	
	CCArray *menu;
	
};



