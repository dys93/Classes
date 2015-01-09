
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
	
	//�ƶ�ʱ����
	void addspeed(Vec2 speed);
	//ѡ�е�ʱ�����
	void besel(GameState state);
	//ȡ��ѡ��ʱ����
	void nosel(GameState state);
	//�ܵ��˺�ʱ����
	void behurt();
	//��������ʱ����snack ���������ӵ�
	MySprite* attack(Vec2 speed);
	

	
	CCArray *menu;
	
};



