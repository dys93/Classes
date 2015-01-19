
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

	//�򿪲˵�
	CCLayer *createmenu();

	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	
	
	CREATE_FUNC(GameScene);

	SceneManager *sm;

	//������Ϸ�غ��Լ��˵�������menu 

	CCMenu *pMenu=NULL;

	void initpMenu();
	void startpMenu();
	void stoppMenu();

	//δ֪����ӰЧ��
	CCLayer *shade;	
	
	//����ϵͳ�˵���layer
	CCLayer *menu;
	//����Ϸ�˵�
	void openMenuCallback();

	//��Ϸ�˵��Ļص�����
	void menuContinueCallback();
	void menuBackMenuCallback();
	void menuExitGame();

	CCLabelBMFont* moneylabel;
	CCLabelBMFont* readyspritelabel;
	CCLabelBMFont* totalspritelabel;
	void labelcreate();
	void labelupdate();
	bool myTurn=true;       //�����ֻ�
	int money=0;				//���Ǯ
	void changemoney(int change);
	int earn=30;
	int enemy_ready_spritenum=0;     //���˿��ƶ�����
	int my_ready_spritenum=0;		//��Ŀ��ƶ�����
	int enemy_total_spritenum=0;     //���˿��ƶ�����
	int my_total_spritenum=0;		//��Ŀ��ƶ�����
	
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

	


	CCArray *SpriteListen; //�������
	CCArray *SpriteMenuListen; //����˵�����
	CCArray  *AllSprite; //mysprite�ĵ�λ
	CCArray  *movingSprite;   //���ڶ��������ж��Ƿ���Խ����˺������Լ������ж���Χ

	PhysicsWorld* m_world;	
	
	//������
	MySprite *selSprite;	//ѡ����
	GameState control_state;//����״̬

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

	EventListenerTouchOneByOne* listener1;  //����ļ���
	EventListenerTouchOneByOne* listener2;	//����˵�����
	EventListenerTouchOneByOne* listener3;  //�ƶ�����
	EventListenerTouchOneByOne* listener4;  //��������
	void update(float dt);
	void onEnter();


	MySprite * MyAIget(int belongto, int issleep);


	virtual ~GameScene();

};

